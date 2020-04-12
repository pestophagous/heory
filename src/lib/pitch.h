//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_PITCH_H
#define PROJECT_LIB_PITCH_H

#include <QString>

namespace heory
{
// middle C is C4 and the note below it is B3
class Pitch
{
public:
    static Pitch FromMidi( int midi );

    ~Pitch();

    int AsMidi() const;

    bool PlayableOnPiano88Key() const;

    QString AsAlphabeticNoOctaveUseSharp() const;
    QString AsAlphabeticNoOctaveUseFlat() const;

    QString OctaveNumberLabel() const;
    int OctaveNumber() const;

private:
    explicit Pitch( int midi );

    // CURRENTLY ALLOWING DEFAULT COPY CTOR. CAREFUL. ALL MUST BE TRIVIALLY COPYABLE.
    const int m_midi;
};

} // namespace heory

#endif // PROJECT_LIB_PITCH_H
