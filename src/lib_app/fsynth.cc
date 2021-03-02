#include "fsynth.h"

#include <QDebug>

#include <fluidsynth.h>
#include <fluidsynth/fluid_midi.h>
#include <fluidsynth/version.h>

#include <algorithm>
#include <stdlib.h>

#include "util-assert.h"

namespace heory
{
struct FsynthWrapper::VoidDataPreRouter
{
    VoidDataPreRouter( fluid_midi_router_t* r, FsynthWrapper* w ) : router( r ), wrapper( w )
    {
    }
    void OnNote( int asMidi )
    {
        // The next 3 lines guarantee that if someone edits NotifyIncomingPitch
        // in a way that would break our 'invokeMethod' usage, we will CATCH IT
        // AT COMPILE TIME.
        using RequiredSlotType = void ( FsynthWrapper::* )( int );
        RequiredSlotType requiredSlot = &FsynthWrapper::NotifyIncomingPitch;
        (void) requiredSlot; // unused, but provides time-of-compilation
                             // assurance of METHOD SIGNATURE

        // clang-format off
        QMetaObject::invokeMethod( wrapper, "NotifyIncomingPitch",
            Qt::QueuedConnection,
            Q_ARG( int, asMidi ));
        // clang-format on
    }
    void OnNoteTermination( int asMidi )
    {
        // The next 3 lines guarantee that if someone edits NotifyPitchTermination
        // in a way that would break our 'invokeMethod' usage, we will CATCH IT
        // AT COMPILE TIME.
        using RequiredSlotType = void ( FsynthWrapper::* )( int );
        RequiredSlotType requiredSlot = &FsynthWrapper::NotifyPitchTermination;
        (void) requiredSlot; // unused, but provides time-of-compilation
                             // assurance of METHOD SIGNATURE

        // clang-format off
        QMetaObject::invokeMethod( wrapper, "NotifyPitchTermination",
            Qt::QueuedConnection,
            Q_ARG( int, asMidi ));
        // clang-format on
    }

    fluid_midi_router_t* const router = nullptr;
    FsynthWrapper* const wrapper = nullptr;
};

namespace
{
    using std::placeholders::_1;

    bool IsRunningOnGithubRuner()
    {
        if( getenv( "GITHUB_ACTIONS" ) )
        {
            return true;
        }
        return false;
    }

    int OnIncomingMidiEvent( void* data, fluid_midi_event_t* event )
    {
        FsynthWrapper::VoidDataPreRouter* ourData
            = static_cast<FsynthWrapper::VoidDataPreRouter*>( data );

        if( NOTE_ON == event->type )
        {
            ourData->OnNote( event->param1 );
        }
        else if( NOTE_OFF == event->type )
        {
            ourData->OnNoteTermination( event->param1 );
        }

        // TODO: make dump_pre and dump_post optional on CLI flag
        return fluid_midi_dump_prerouter( ourData->router, event );
        // return fluid_midi_router_handle_midi_event( ourData->router, event );
    }

} // namespace

struct FsynthWrapper::Impl
{
    Impl() : test_lacking_alsa( IsRunningOnGithubRuner() )
    {
    }

    ~Impl()
    {
        ShutdownFsynth();
    }

    void ShutdownFsynth();

    const bool test_lacking_alsa;
    fluid_settings_t* settings = nullptr;
    fluid_synth_t* synth = nullptr;
    fluid_midi_router_t* router = nullptr;
    fluid_midi_driver_t* mdriver = nullptr;
    fluid_audio_driver_t* adriver = nullptr;
    std::unique_ptr<VoidDataPreRouter> voidData;
};

void FsynthWrapper::Impl::ShutdownFsynth()
{
    delete_fluid_audio_driver( this->adriver );
    this->adriver = nullptr;
    delete_fluid_midi_driver( this->mdriver );
    this->mdriver = nullptr;
    delete_fluid_midi_router( this->router );
    this->router = nullptr;
    delete_fluid_synth( this->synth );
    this->synth = nullptr;
    delete_fluid_settings( this->settings );
    this->settings = nullptr;
}

FsynthWrapper::FsynthWrapper( const CliOptions& /*options*/ ) : m_i( new Impl )
{
    m_i->settings = new_fluid_settings();
    FASSERT( m_i->settings, "must be non-null" );

    fluid_settings_setstr( m_i->settings, "audio.driver", "pulseaudio" );
    fluid_settings_setstr( m_i->settings, "midi.driver", "alsa_seq" );
    fluid_settings_setint( m_i->settings, "midi.autoconnect", 1 );
    fluid_settings_setnum( m_i->settings, "synth.gain", 1 );

    m_i->synth = new_fluid_synth( m_i->settings );
    FASSERT( m_i->synth, "must be non-null" );

    // dpkg-query -L fluid-soundfont-gm # find where 'sf2' sound fonts were installed
    const int sf = fluid_synth_sfload(
        m_i->synth, "/usr/share/sounds/sf2/FluidR3_GM.sf2", /*reset_presets*/ 1 );
    FASSERT( sf != FLUID_FAILED, "failed call to fluid_synth_sfload" );
    qDebug() << "fluid_synth_sfload returned sf id:" << sf;

    if( !m_i->test_lacking_alsa )
    {
        // fluidsynth: debug: Using 'alsa_seq' midi driver
        // ALSA lib seq_hw.c:466:(snd_seq_hw_open) open /dev/snd/seq failed: No such file or
        // directory fluidsynth: error: Error opening ALSA sequencer

        // TODO: make dump_pre and dump_post optional on CLI flag
        m_i->router = new_fluid_midi_router(
            m_i->settings, fluid_midi_dump_postrouter, static_cast<void*>( m_i->synth ) );
        FASSERT( m_i->router, "must be non-null" );

        m_i->voidData.reset( new VoidDataPreRouter( m_i->router, this ) );

        // In dump mode, text output is generated for events going into and out of
        // the router.  The example dump functions are put into the chain before and
        // after the router.
        m_i->mdriver = new_fluid_midi_driver(
            m_i->settings, &OnIncomingMidiEvent, static_cast<void*>( m_i->voidData.get() ) );
        FASSERT( m_i->mdriver, "must be non-null" );

        m_i->adriver = new_fluid_audio_driver( m_i->settings, m_i->synth );
        FASSERT( m_i->adriver, "must be non-null" );

        const int note
            = fluid_synth_noteon( m_i->synth, 0 /*chan*/, 60 /*key*/, 100 /*velocity*/ );
        FASSERT( note == FLUID_OK, "failed in fluid_synth_noteon" );
    }
}

FsynthWrapper::~FsynthWrapper()
{
    delete m_i;
}

void FsynthWrapper::PlayNote( const Pitch pitch )
{
    const int note = fluid_synth_noteon(
        m_i->synth, 0 /*chan*/, pitch.AsMidi() /*key*/, 100 /*velocity*/ );
    FASSERT( note == FLUID_OK, "failed in fluid_synth_noteon" );
}

void FsynthWrapper::SubscribeToIncomingPitches( IncomingPitchListener_Interface* listener )
{
    const auto finder
        = std::find( m_pitchListeners.begin(), m_pitchListeners.end(), listener );
    if( finder != m_pitchListeners.end() )
    {
        FFAIL( "did you know you already added this listener?" );
        return;
    }

    m_pitchListeners.push_back( listener );
}

void FsynthWrapper::UnsubscribeToIncomingPitches( IncomingPitchListener_Interface* listener )
{
    const auto finder
        = std::find( m_pitchListeners.begin(), m_pitchListeners.end(), listener );
    if( finder == m_pitchListeners.end() )
    {
        FFAIL( "did you know that this listener was not subscribed?" );
        return;
    }

    m_pitchListeners.erase( finder );
}

void FsynthWrapper::NotifyIncomingPitch( const int asMidi )
{
    m_debugFlag_IncomingNotify = true;

    auto finder = m_activePitches.find( asMidi );
    if( finder == m_activePitches.end() )
    {
        m_activePitches[ asMidi ] = std::vector<std::function<void()>>{};
    }

    auto pitch = Pitch::FromMidi( asMidi );
    const PitchLifetime plife(
        pitch, std::bind( &FsynthWrapper::AddOneoffTerminationCallback, this, pitch, _1 ) );

    for( const auto& listener : m_pitchListeners )
    {
        listener->OnIncomingNote( plife );
    }
    m_debugFlag_IncomingNotify = false;
}

void FsynthWrapper::NotifyPitchTermination( const int asMidi )
{
    auto finder = m_activePitches.find( asMidi );
    if( finder == m_activePitches.end() )
    {
        FFAIL( "A pitch is terminating that was never known to have started? did we mess up "
               "our map?" );
        return;
    }

    for( auto& functor : finder->second )
    {
        if( functor )
        {
            functor();
        }
    }

    m_activePitches.erase( finder );
}

void FsynthWrapper::AddOneoffTerminationCallback( Pitch p, std::function<void()> callback )
{
    FASSERT( m_debugFlag_IncomingNotify,
        "our understanding is this can ONLY be reached during NotifyIncomingPitch" );

    auto finder = m_activePitches.find( p.AsMidi() );
    if( finder == m_activePitches.end() )
    {
        FFAIL( "FsynthWrapper sent the pitch to whoever wants a callback. how can the pitch "
               "not be in the map?" );
        return;
    }

    if( callback )
    {
        finder->second.push_back( callback );
    }
}

} // namespace heory
