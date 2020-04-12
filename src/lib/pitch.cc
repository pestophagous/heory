#include "pitch.h"

#include <cstring>

#include "src/lib/notation_strings.h"
#include "util-assert.h"

namespace heory
{
namespace
{
    constexpr char ALPHA_WITH_SHARP[] = "cCdDefFgGaAb";
    constexpr char ALPHA_WITH_FLATS[] = "cDdEefGgAaBb";

} // namespace

/*static*/ Pitch Pitch::FromMidi( int midi )
{
    FASSERT( midi >= 0 && midi <= 127, "Not a midi value" );
    return Pitch( midi );
}

Pitch::Pitch( int midi )
    // clang-format off
    : m_midi( midi )
// clang-format on
{
}

Pitch::~Pitch() = default;

int Pitch::AsMidi() const
{
    return m_midi;
}

bool Pitch::PlayableOnPiano88Key() const
{
    return m_midi >= 21 && m_midi <= 108;
}

QString Pitch::AsAlphabeticNoOctaveUseSharp() const
{
    const size_t index = m_midi % 12;
    const char alpha = ALPHA_WITH_SHARP[ index ];
    QString result( alpha );
    if( isupper( alpha ) )
    {
        result = notation::Sharped( alpha );
    }
    return result.toUpper();
}

QString Pitch::AsAlphabeticNoOctaveUseFlat() const
{
    const size_t index = m_midi % 12;
    const char alpha = ALPHA_WITH_FLATS[ index ];
    QString result( alpha );
    if( isupper( alpha ) )
    {
        result = notation::Flatted( alpha );
    }
    return result.toUpper();
}

QString Pitch::OctaveNumberLabel() const
{
    return QString::number( OctaveNumber() );
}

int Pitch::OctaveNumber() const
{
    return ( m_midi / 12 ) - 1;
}

} // namespace heory
