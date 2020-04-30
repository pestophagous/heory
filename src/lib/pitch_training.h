//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_PITCH_TRAINING_H
#define PROJECT_LIB_PITCH_TRAINING_H

#include <QString>

#include "src/lib/incoming_pitch_listener_interface.h"
#include "src/lib/pitch.h"
#include "src/lib/sound_io_interface.h"

namespace heory
{
class PitchTraining : public IncomingPitchListener_Interface
{
public:
    PitchTraining( Pitch lowest, Pitch highest, SoundIO_Interface* io );
    ~PitchTraining() override;

    PitchTraining( const PitchTraining& ) = delete;
    PitchTraining& operator=( const PitchTraining& ) = delete;

    void Restart();

    void Advance();

    Pitch CurrentlyExpecting() const;
    void MakeSound() const;

    void ProcessThisGuess( PitchLifetime guess );

    void OnIncomingNote( PitchLifetime pitch ) override;

private:
    void AssignNext();

    SoundIO_Interface* const m_io;
    const Pitch m_lowest;
    const Pitch m_highest;

    Pitch m_expectedPitch;
};

} // namespace heory

#endif // PROJECT_LIB_PITCH_TRAINING_H
