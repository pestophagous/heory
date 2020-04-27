#include "pitch_training.h"

#include "util-assert.h"

namespace heory
{
// clang-format off
PitchTraining::PitchTraining( const Pitch lowest, const Pitch highest, SoundIO_Interface* io )
    : m_io(io),
      m_lowest( lowest ),
      m_highest( highest.AsMidi() > lowest.AsMidi() ? highest : lowest ),
      m_expectedPitch( lowest )
// clang-format on
{
    FASSERT( m_io, "cannot be null" );
    FASSERT( highest.AsMidi() > lowest.AsMidi(), "we need an ordered pair of distinct values, least to greatest" );
    Restart();
}

void PitchTraining::Restart()
{
    AssignNext();
}

void PitchTraining::Advance()
{
    AssignNext();
    MakeSound();
}

Pitch PitchTraining::CurrentlyExpecting() const
{
    return m_expectedPitch;
}

void PitchTraining::ProcessThisGuess( Pitch guess )
{
    if( guess.AsMidi() == CurrentlyExpecting().AsMidi() )
    {
        Advance();
    }
}

void PitchTraining::AssignNext()
{
    m_expectedPitch = m_expectedPitch.IncrementHalfStep();
    if( m_expectedPitch.AsMidi() > m_highest.AsMidi() )
    {
        m_expectedPitch = m_lowest;
    }
}

void PitchTraining::MakeSound() const
{
    m_io->PlayNote( m_expectedPitch );
}

} // namespace heory
