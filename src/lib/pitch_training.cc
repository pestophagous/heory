#include "pitch_training.h"

#include <QDebug>

#include "src/util/random.h"
#include "util-assert.h"

namespace heory
{
// clang-format off
PitchTraining::PitchTraining( const Pitch lowest, const Pitch highest, SoundIO_Interface* io, Random* random )
    : m_io(io),
      m_random( random ),
      m_lowest( lowest ),
      m_highest( highest.AsMidi() > lowest.AsMidi() ? highest : lowest ),
      m_expectedPitch( lowest )
// clang-format on
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

void PitchTraining::Restart()
{
    AssignNext();
}

void PitchTraining::Advance()
{
    qDebug() << "Advance";
    AssignNext();
    MakeSound();
}

Pitch PitchTraining::CurrentlyExpecting() const
{
    return m_expectedPitch;
}

void PitchTraining::ProcessThisGuess( PitchLifetime guess )
{
    if( guess.pitch.AsMidi() == CurrentlyExpecting().AsMidi() )
    {
        guess.OnLifetimeComplete( [this]() { Advance(); } );
    }
}

void PitchTraining::OnIncomingNote( PitchLifetime pitch )
{
    ProcessThisGuess( pitch );
}

void PitchTraining::AssignNext()
{
    m_expectedPitch = Pitch::FromMidi(
        m_random->GetNextFromNToMInclusive( m_lowest.AsMidi(), m_highest.AsMidi() ) );
}

void PitchTraining::MakeSound() const
{
    m_io->PlayNote( m_expectedPitch );
}

} // namespace heory
