//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_PITCH_TRAINING_H
#define PROJECT_LIB_PITCH_TRAINING_H

#include <QString>

#include "src/lib_app/incoming_pitch_listener_interface.h"
#include "src/lib_app/pitch.h"
#include "src/lib_app/sound_io_interface.h"

namespace heory
{
class Random;

class PitchTraining : public IncomingPitchListener_Interface
{
public:
    PitchTraining( Pitch lowest, Pitch highest, SoundIO_Interface* io, Random* random );
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
    Random* const m_random;
    const Pitch m_lowest;
    const Pitch m_highest;

    Pitch m_expectedPitch;
};

} // namespace heory

#endif // PROJECT_LIB_PITCH_TRAINING_H
