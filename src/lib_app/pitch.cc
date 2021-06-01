#include "pitch.h"

#include <cstring>

#include "src/lib_app/notation_strings.h"
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

/*static*/ Pitch Pitch::MiddleC()
{
    return FromMidi( 60 );
}

/*static*/ Pitch Pitch::C5()
{
    return FromMidi( 72 );
}

Pitch::Pitch( int midi )
    // clang-format off
    : m_midi( midi )
// clang-format on
{
}

Pitch::~Pitch() = default;

Pitch& Pitch::operator=( const Pitch& rhs )
{
    // check for self-assignment
    if( &rhs == this )
    {
        return *this;
    }

    *const_cast<int*>( &m_midi ) = rhs.m_midi;

    return *this;
}

bool Pitch::operator==( const Pitch& rhs ) const
{
    // clang-format off
    return m_midi == rhs.m_midi;
    // clang-format on
}

bool Pitch::operator!=( const Pitch& rhs ) const
{
    return !( *this == rhs );
}

bool Pitch::IsFuzzyMatch( const Pitch& rhs ) const
{
    return NormalizeToC4() == rhs.NormalizeToC4();
}

bool Pitch::IsFuzzyMatchForMidi( int midi ) const
{
    return NormalizeToC4() == Pitch::FromMidi( midi ).NormalizeToC4();
}

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

Pitch Pitch::IncrementHalfStep() const
{
    return FromMidi( m_midi + 1 );
}

Pitch Pitch::IncrementWholeStep() const
{
    return IncrementHalfStep().IncrementHalfStep();
}

Pitch Pitch::NormalizeToC4() const
{
    return FromMidi( ( m_midi % 12 ) + Pitch::MiddleC().AsMidi() );
}
} // namespace heory
