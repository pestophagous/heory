#include "pitch_training.h"

#include "src/util/random.h"
#include "util-assert.h"

#define log_func_human_tag "heory.pitchtraining"
#define log_func_preprocessor_symbol pttrace
#include "src/util/wrap_qt_trace_category.h"

namespace heory
{
WrapQtTraceCategory thisfiletrace; // OFF by default. try QT_LOGGING_RULES="*=true;qt*=false;"

PitchTraining::PitchTraining(
    const Pitch lowest, const Pitch highest, SoundIO_Interface* io, Random* random )
    : m_io( io )
    , m_random( random )
    , m_lowest( lowest )
    , m_highest( highest.AsMidi() > lowest.AsMidi() ? highest : lowest )
    , m_expectedPitch( lowest )
{
    FASSERT( m_io, "cannot be null" );
    FASSERT( highest.AsMidi() > lowest.AsMidi(),
        "we need an ordered pair of distinct values, least to greatest" );
    m_io->SubscribeToIncomingPitches( this );
    Restart();
}

PitchTraining::~PitchTraining()
{
    m_io->UnsubscribeToIncomingPitches( this );
}

void PitchTraining::SetEnabled( const bool enabled )
{
    thisfiletrace.stream() << "SetEnabled:" << enabled;
    m_enabled = enabled;
}

void PitchTraining::Restart()
{
    thisfiletrace.stream() << "Restart";
    AssignNext();
}

void PitchTraining::Advance()
{
    thisfiletrace.stream() << "Advance";
    AssignNext();
    MakeSound();
}

Pitch PitchTraining::CurrentlyExpecting() const
{
    return m_expectedPitch;
}

void PitchTraining::ProcessThisGuess( PitchLifetime guess )
{
    if( guess.pitch.AsMidi() != CurrentlyExpecting().AsMidi() )
    {
        thisfiletrace.stream() << "Incorrect guess";
    }
    else
    {
        thisfiletrace.stream() << "Guess matches expectation";
        guess.OnLifetimeComplete( [this]() { Advance(); } );
    }
}

void PitchTraining::OnIncomingNote( PitchLifetime pitch )
{
    if( !m_enabled )
    {
        return; // BAILING OUT!
    }
    ProcessThisGuess( pitch );
}

void PitchTraining::AssignNext()
{
    m_expectedPitch = Pitch::FromMidi(
        m_random->GetNextFromNToMInclusive( m_lowest.AsMidi(), m_highest.AsMidi() ) );
    thisfiletrace.stream() << "Next expectation:" << m_expectedPitch.AsMidi();
}

void PitchTraining::MakeSound() const
{
    m_io->PlayNote( m_expectedPitch );
}

} // namespace heory
