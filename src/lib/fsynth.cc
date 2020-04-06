#include "fsynth.h"

#include <QDebug>

#include <fluidsynth.h>
#include <fluidsynth/version.h>

#include <stdlib.h>

#include "util-assert.h"

namespace heory
{
namespace
{
    bool IsRunningOnGithubRuner()
    {
        if( getenv( "GITHUB_ACTIONS" ) )
        {
            return true;
        }
        return false;
    }
} // namespace

struct FsynthWrapper::Impl
{
    Impl()
        : test_lacking_alsa( IsRunningOnGithubRuner() )
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

FsynthWrapper::FsynthWrapper( const CliOptions& /*options*/ )
    : m_i( new Impl )
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
    const int sf = fluid_synth_sfload( m_i->synth, "/usr/share/sounds/sf2/FluidR3_GM.sf2", /*reset_presets*/ 1 );
    FASSERT( sf != FLUID_FAILED, "failed call to fluid_synth_sfload" );
    qDebug() << "fluid_synth_sfload returned sf id:" << sf;

    if( !m_i->test_lacking_alsa )
    {
        // fluidsynth: debug: Using 'alsa_seq' midi driver
        // ALSA lib seq_hw.c:466:(snd_seq_hw_open) open /dev/snd/seq failed: No such file or directory
        // fluidsynth: error: Error opening ALSA sequencer

        m_i->router = new_fluid_midi_router(
            m_i->settings,
            fluid_midi_dump_postrouter,
            static_cast<void*>( m_i->synth ) );
        FASSERT( m_i->router, "must be non-null" );

        // In dump mode, text output is generated for events going into and out of
        // the router.  The example dump functions are put into the chain before and
        // after the router.
        m_i->mdriver = new_fluid_midi_driver(
            m_i->settings,
            fluid_midi_dump_prerouter,
            static_cast<void*>( m_i->router ) );
        FASSERT( m_i->mdriver, "must be non-null" );

        m_i->adriver = new_fluid_audio_driver( m_i->settings, m_i->synth );
        FASSERT( m_i->adriver, "must be non-null" );

        const int note = fluid_synth_noteon( m_i->synth, 0 /*chan*/, 60 /*key*/, 100 /*velocity*/ );
        FASSERT( note == FLUID_OK, "failed in fluid_synth_noteon" );
    }
}

FsynthWrapper::~FsynthWrapper()
{
    delete m_i;
}

void FsynthWrapper::PlayNote()
{
    const int note = fluid_synth_noteon( m_i->synth, 0 /*chan*/, 60 /*key*/, 100 /*velocity*/ );
    FASSERT( note == FLUID_OK, "failed in fluid_synth_noteon" );
}

} // namespace heory
