//
// Copyright (c) 2021, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_SCALE_H
#define PROJECT_LIB_SCALE_H

#include <QString>

#include <array>
#include <vector>

#include "src/lib_app/music_enums.h"
#include "src/lib_app/pitch.h"

namespace heory
{
class Scale
{
public:
    static Scale MajorFromTonicLength8( Pitch midiTonic, bool flatsIfPossible = false );
    static Scale MinorFromTonicLength8( Pitch midiTonic, bool flatsIfPossible = false );
    static Scale MajorFromTonicLength7( Pitch midiTonic, bool flatsIfPossible = false );
    static Scale MinorFromTonicLength7( Pitch midiTonic, bool flatsIfPossible = false );

    static Scale From7Notes( const std::vector<Pitch>& notes, bool flatsIfPossible = false );

    ~Scale();

    Scale& operator=( const Scale& );

    int Length() const;
    Pitch Index( int i ) const;

    QString AsAlphabeticNoOctave( const QString& separator ) const;
    QString Name() const;

    bool IsExactAuditoryMatch( const Scale& rhs ) const;
    // CSharp would fuzzy-match DFlat. Pitches are normalized to C4 octave.
    bool IsFuzzyMatch( const Scale& rhs ) const;

    bool FlatOrSharpSignatureBothPossible() const;
    bool OnlySharpSignaturePossible() const;
    bool OnlyFlatSignaturePossible() const;

private:
    explicit Scale( Pitch midiTonic, int length, TonalityLabel ton, bool flatsIfPossible );
    explicit Scale( int length, bool flatsIfPossible, std::array<Pitch, 8> notes );
    void AccumulateIndexToStringResult( int index, QString* result ) const;

    // CURRENTLY ALLOWING DEFAULT COPY CTOR. CAREFUL. ALL MUST BE TRIVIALLY COPYABLE.
    const Pitch m_midiTonic;
    const int m_length;
    const TonalityLabel m_ton;
    const bool m_flatsIfPossible;
    const std::array<Pitch, 8> m_scale;
};

} // namespace heory

#endif // PROJECT_LIB_SCALE_H
