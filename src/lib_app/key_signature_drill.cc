#include "key_signature_drill.h"

#include "src/util/random.h"
#include "util-assert.h"

#define log_func_human_tag "heory.keysigdrill"
#define log_func_preprocessor_symbol ksigtrace
#include "src/util/wrap_qt_trace_category.h"

namespace heory
{
WrapQtTraceCategory thisfiletrace; // OFF by default. try QT_LOGGING_RULES="*=true;qt*=false;"

KeySignatureDrill::KeySignatureDrill( SoundIO_Interface* io, Random* random,
    std::function<void( KeySignatureDrillGuiState )> callback )
    : m_io( io )
    , m_random( random )
    , m_callback( callback )
    , m_currentScale( Scale::MajorFromTonicLength8( Pitch::FromMidi( 60 ) ) )
{
    FASSERT( m_io, "cannot be null" );
    m_io->SubscribeToIncomingPitches( this );
}

KeySignatureDrill::~KeySignatureDrill()
{
    m_io->UnsubscribeToIncomingPitches( this );
}

KeySignatureDrillGuiState KeySignatureDrill::GetCurrentGuiState() const
{
    // struct GuiState
    // {
    //     QString tonalityLabel;
    //     QString svgFile;
    //     QString progressCueLabel;
    // };

    // TODO: handle svgFile
    KeySignatureDrillGuiState state;
    state.tonalityLabel = TonalityLabelString( m_currentScale.GetTonalityLabel() );
    state.progressCueLabel = m_pendingProgressIcon;

    m_pendingProgressIcon = "";
    return state;
}

void KeySignatureDrill::Advance()
{
    thisfiletrace.stream() << "Advance";

    // TODO: implement random without replacement
    thisfiletrace.stream() << "Current Scale:" << m_currentScale.Name();

    m_callback( GetCurrentGuiState() );
}

void KeySignatureDrill::OnIncomingNote( PitchLifetime guess )
{
    if( !m_enabled )
    {
        return; // BAILING OUT!
    }

    FASSERT( m_currentScale.Length() == 8, "should always be length 8" );
    FASSERT(
        m_nextScaleIndexAwaiting >= 0 && m_nextScaleIndexAwaiting < 8, "must be valid index" );

    if( !m_currentScale.Index( m_nextScaleIndexAwaiting ).IsFuzzyMatch( guess.pitch ) )
    {
        thisfiletrace.stream() << "wrong note";
        m_pendingProgressIcon = QString( "\uf0f3" ); // fa_regular_bell
        m_nextScaleIndexAwaiting = 0; // forces user to start over at scale beginning
    }
    else
    {
        thisfiletrace.stream() << "correct note";
        m_pendingProgressIcon = QString( "\uf089" ); // fa_regular_star_half
        m_nextScaleIndexAwaiting++;

        if( m_nextScaleIndexAwaiting >= 8 )
        {
            m_pendingProgressIcon = QString( "\uf005" ); // fa_regular_star
            m_nextScaleIndexAwaiting = 0;
            guess.OnLifetimeComplete( [this]() { Advance(); } );
        }
    }

    m_callback( GetCurrentGuiState() );
}

void KeySignatureDrill::SetEnabled( bool enabled )
{
    thisfiletrace.stream() << "SetEnabled:" << enabled;
    const bool isChangedVal = ( m_enabled != enabled );
    m_enabled = enabled;
    if( enabled && isChangedVal )
    {
        Advance();
    }
}

} // namespace heory
