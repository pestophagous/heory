//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_PITCH_H
#define PROJECT_LIB_PITCH_H

#include <QString>

#include <array>

namespace heory
{
// middle C is C4 and the note below it is B3
class Pitch
{
public:
    typedef Pitch ( Pitch::*PitchIncrementerFunc )() const;

    static Pitch FromMidi( int midi );
    static Pitch MiddleC();
    static Pitch C5();

    ~Pitch();

    Pitch& operator=( const Pitch& );

    bool operator==( const Pitch& rhs ) const;
    bool operator!=( const Pitch& rhs ) const;

    bool IsFuzzyMatch( const Pitch& rhs ) const;
    bool IsFuzzyMatchForMidi( int midi ) const;

    int AsMidi() const;

    bool PlayableOnPiano88Key() const;

    QString AsAlphabeticNoOctaveUseSharp() const;
    QString AsAlphabeticNoOctaveUseFlat() const;

    QString OctaveNumberLabel() const;
    int OctaveNumber() const;

    Pitch IncrementHalfStep() const;
    Pitch IncrementWholeStep() const;

    Pitch NormalizeToC4() const;

private:
    explicit Pitch( int midi );

    // CURRENTLY ALLOWING DEFAULT COPY CTOR. CAREFUL. ALL MUST BE TRIVIALLY COPYABLE.
    const int m_midi;
};

// clang-format off
    static constexpr std::array<Pitch::PitchIncrementerFunc, 7> kMajorScaleIntervals{
      &Pitch::IncrementWholeStep,
      &Pitch::IncrementWholeStep,
      &Pitch::IncrementHalfStep,
      &Pitch::IncrementWholeStep,
      &Pitch::IncrementWholeStep,
      &Pitch::IncrementWholeStep,
      &Pitch::IncrementHalfStep,
    };

    static constexpr std::array<Pitch::PitchIncrementerFunc, 7> kMinorScaleIntervals{
      &Pitch::IncrementWholeStep,
      &Pitch::IncrementHalfStep,
      &Pitch::IncrementWholeStep,
      &Pitch::IncrementWholeStep,
      &Pitch::IncrementHalfStep,
      &Pitch::IncrementWholeStep,
      &Pitch::IncrementWholeStep,
    };
// clang-format on

} // namespace heory

#endif // PROJECT_LIB_PITCH_H
