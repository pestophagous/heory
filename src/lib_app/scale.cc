#include "scale.h"

#include <algorithm>
#include <functional>

#include "util-assert.h"

namespace heory
{
namespace
{
    const Pitch kHolder = Pitch::MiddleC();
    const std::array<Pitch, 8> kPlaceholderPitches{
        kHolder, kHolder, kHolder, kHolder, kHolder, kHolder, kHolder, kHolder};

    std::array<Pitch, 8> GenerateScaleFromIntervals(
        Pitch midiTonic, const std::array<Pitch::PitchIncrementerFunc, 7>& intervals )
    {
        std::array<Pitch, 8> result = kPlaceholderPitches;
        Pitch nextPitch = midiTonic;

        size_t index = 0;
        for( auto incFunc : intervals )
        {
            result[ index ] = nextPitch;
            Pitch* p = &( result[ index ] );
            nextPitch = std::invoke( incFunc, p );
            index++;
        }
        result[ 7 ] = nextPitch;

        return result;
    }

    std::array<Pitch, 8> GenerateScale( Pitch midiTonic, TonalityLabel ton )
    {
        std::array<Pitch, 8> result = kPlaceholderPitches;
        if( ton == TonalityLabel::Major )
        {
            return GenerateScaleFromIntervals( midiTonic, kMajorScaleIntervals );
        }
        if( ton == TonalityLabel::Minor )
        {
            return GenerateScaleFromIntervals( midiTonic, kMinorScaleIntervals );
        }
        else
        {
            FFAIL( "unsupported" );
        }
        return result;
    }

    std::array<Pitch, 8> SortAnAdHocScaleAndLengthenIfNeeded(
        const size_t inputSize, const std::vector<Pitch>& notes )
    {
        FASSERT( notes.size() >= inputSize,
            "caller is expected to provide at least <inputSize> notes" );
        // TODO: in the case of fewer than <inputSize> values provided, then pad
        // the end with MiddleC.
        std::vector<Pitch> incoming( inputSize, kHolder );
        std::copy_n( notes.begin(), inputSize, incoming.begin() );

        // sort the notes by their normalized number
        std::sort( incoming.begin(), incoming.end(), []( const Pitch& a, const Pitch& b ) {
            return a.NormalizeToC4().AsMidi() < b.NormalizeToC4().AsMidi();
        } );
        if( inputSize < 8 )
        {
            FASSERT( inputSize == 7, "we only deal with 2 lengths" );
            FASSERT( incoming.size() == 7, "we should be about to make the vector hold 8." );
            // set the 8th value to one octave above the first value:
            incoming.push_back( Pitch::FromMidi( incoming[ 0 ].AsMidi() + 12 ) );
        }

        FASSERT( incoming.size() == 8, "we always want size 8 here" );
        std::array<Pitch, 8> rawScale = kPlaceholderPitches;
        std::copy_n( incoming.begin(), 8, rawScale.begin() );
        return rawScale;
    }
} // namespace

/*static*/ Scale Scale::MajorFromTonicLength8( Pitch midiTonic, bool flatsIfPossible )
{
    return Scale( midiTonic, 8, TonalityLabel::Major, flatsIfPossible );
}

/*static*/ Scale Scale::MinorFromTonicLength8( Pitch midiTonic, bool flatsIfPossible )
{
    return Scale( midiTonic, 8, TonalityLabel::Minor, flatsIfPossible );
}

/*static*/ Scale Scale::MajorFromTonicLength7( Pitch midiTonic, bool flatsIfPossible )
{
    return Scale( midiTonic, 7, TonalityLabel::Major, flatsIfPossible );
}

/*static*/ Scale Scale::MinorFromTonicLength7( Pitch midiTonic, bool flatsIfPossible )
{
    return Scale( midiTonic, 7, TonalityLabel::Minor, flatsIfPossible );
}

/*static*/ Scale Scale::From7Notes( const std::vector<Pitch>& notes, bool flatsIfPossible )
{
    FASSERT( notes.size() >= 7, "caller is expected to provide 7 notes" );

    auto rawScale = SortAnAdHocScaleAndLengthenIfNeeded( 7, notes );
    return Scale( 7, flatsIfPossible, rawScale );
}

Scale::Scale( Pitch midiTonic, int length, const TonalityLabel ton, bool flatsIfPossible )
    : m_midiTonic( midiTonic )
    , m_length( length )
    , m_ton( ton )
    , m_flatsIfPossible( flatsIfPossible )
    , m_scale( GenerateScale( midiTonic, ton ) )
{
    FASSERT(
        m_ton == TonalityLabel::Major || m_ton == TonalityLabel::Minor, "cannot be Unknown" );
}

Scale::Scale( int length, bool flatsIfPossible, std::array<Pitch, 8> notes )
    : m_midiTonic( notes[ 0 ] )
    , m_length( length )
    , m_ton( TonalityLabel::Unknown )
    , m_flatsIfPossible( flatsIfPossible )
    , m_scale( notes )
{
}

Scale::~Scale() = default;

Scale& Scale::operator=( const Scale& rhs )
{
    // check for self-assignment
    if( &rhs == this )
    {
        return *this;
    }

    *const_cast<Pitch*>( &m_midiTonic ) = rhs.m_midiTonic;
    *const_cast<int*>( &m_length ) = rhs.m_length;
    *const_cast<TonalityLabel*>( &m_ton ) = rhs.m_ton;
    *const_cast<bool*>( &m_flatsIfPossible ) = rhs.m_flatsIfPossible;
    *const_cast<std::array<Pitch, 8>*>( &m_scale ) = rhs.m_scale;

    return *this;
}

int Scale::Length() const
{
    return m_length;
}

Pitch Scale::Index( int i ) const
{
    return m_scale.at( i );
}

QString Scale::AsAlphabeticNoOctave( const QString& separator ) const
{
    QString result;

    for( int i = 0; i < 7; i++ )
    {
        AccumulateIndexToStringResult( i, &result );

        if( i < 6 )
        {
            result += separator;
        }
    }

    if( Length() > 7 )
    {
        FASSERT( Length() == 8, "this code was only designed for two lengths, 7 or 8" );
        result += separator;
        AccumulateIndexToStringResult( 7, &result );
    }

    return result;
}

void Scale::AccumulateIndexToStringResult( int i, QString* result ) const
{
    if( OnlySharpSignaturePossible() )
    {
        ( *result ) += Index( i ).AsAlphabeticNoOctaveUseSharp();
    }
    else if( OnlyFlatSignaturePossible() )
    {
        ( *result ) += Index( i ).AsAlphabeticNoOctaveUseFlat();
    }
    else
    {
        FASSERT( FlatOrSharpSignatureBothPossible(), "must be this" );
        if( m_flatsIfPossible )
        {
            ( *result ) += Index( i ).AsAlphabeticNoOctaveUseFlat();
        }
        else
        {
            ( *result ) += Index( i ).AsAlphabeticNoOctaveUseSharp();
        }
    }
}

QString Scale::Name() const
{
    QString result;
    if( m_ton == TonalityLabel::Major || m_ton == TonalityLabel::Minor )
    {
        AccumulateIndexToStringResult( 0, &result );
        result += " ";
        result += TonalityLabelString( m_ton );
        return result;
    }

    FASSERT( m_ton == TonalityLabel::Unknown, "the only remaining possibility" );
    const Scale majorCandidate(
        m_midiTonic, Length(), TonalityLabel::Major, m_flatsIfPossible );
    const Scale minorCandidate(
        m_midiTonic, Length(), TonalityLabel::Minor, m_flatsIfPossible );

    if( IsFuzzyMatch( majorCandidate ) )
    {
        return majorCandidate.Name();
    }
    else if( IsFuzzyMatch( minorCandidate ) )
    {
        return minorCandidate.Name();
    }

    // This is possible, when given an unorthodox scale constructed via
    // From7Notes:
    return "";
}

bool Scale::IsExactAuditoryMatch( const Scale& rhs ) const
{
    return m_length == rhs.m_length && m_scale == rhs.m_scale;
}

// CSharp would fuzzy-match DFlat. Pitches are normalized to C4 octave.
bool Scale::IsFuzzyMatch( const Scale& rhs ) const
{
    for( int i = 0; i < 7; i++ )
    {
        if( Index( i ).NormalizeToC4() != rhs.Index( i ).NormalizeToC4() )
        {
            return false;
        }
    }

    if( Length() == rhs.Length() )
    {
        if( Length() == 7 )
        {
            // we already compared all 7 items above, so we are not certain of equality
            return true;
        }

        FASSERT( Length() == 8, "this was written when only 7 and 8 were possible" );
        // Same length, length is 8 for both, so now we compare the final items:
        return Index( 7 ).NormalizeToC4() == rhs.Index( 7 ).NormalizeToC4();
    }

    // If we get here, we have scales of different lengths
    if( Length() == 8 )
    {
        // Different lengths are ok, as long as in the case of the longer scale
        // the last note matches the first:
        return Index( 0 ).NormalizeToC4() == Index( 7 ).NormalizeToC4();
    }

    FASSERT( rhs.Length() == 8, "mustn't exactly one be length 8?" );
    // Different lengths are ok, as long as in the case of the longer scale
    // the last note matches the first:
    return rhs.Index( 0 ).NormalizeToC4() == rhs.Index( 7 ).NormalizeToC4();
}

bool Scale::FlatOrSharpSignatureBothPossible() const
{
    if( m_ton == TonalityLabel::Unknown )
    {
        return true;
    }

    if( m_ton == TonalityLabel::Major )
    {
        // Sharped signatures:                    B     FSharp CSharp
        // Matching/ambiguous flatted signatures: CFlat GFlat  DFlat
        constexpr std::array<int, 3> ambiguous{
            71 /*B*/, 66 /*FSharp*/, 61 /*CSharp*/
        };
        for( const auto val : ambiguous )
        {
            if( m_midiTonic.NormalizeToC4().AsMidi() == val )
            {
                return true;
            }
        }
        return false;
    }

    FASSERT( m_ton == TonalityLabel::Minor, "this should be the only remaining option" );
    // Sharped signatures:                    GSharp DSharp ASharp
    // Matching/ambiguous flatted signatures: AFlat  EFlat  BFlat
    constexpr std::array<int, 3> ambiguous{
        68 /*GSharp*/, 63 /*DSharp*/, 70 /*ASharp*/
    };
    for( const auto val : ambiguous )
    {
        if( m_midiTonic.NormalizeToC4().AsMidi() == val )
        {
            return true;
        }
    }
    return false;
}

bool Scale::OnlySharpSignaturePossible() const
{
    if( m_ton == TonalityLabel::Unknown )
    {
        return true;
    }

    if( m_ton == TonalityLabel::Major )
    {
        constexpr std::array<int, 5> sharped{
            60 /*C*/, 67 /*G*/, 62 /*D*/, 69 /*A*/, 64 /*E*/
        };
        for( const auto val : sharped )
        {
            if( m_midiTonic.NormalizeToC4().AsMidi() == val )
            {
                return true;
            }
        }
        return false;
    }

    FASSERT( m_ton == TonalityLabel::Minor, "this should be the only remaining option" );
    constexpr std::array<int, 5> sharped{
        69 /*A*/, 64 /*E*/, 71 /*B*/, 66 /*FSharp*/, 61 /*CSharp*/
    };
    for( const auto val : sharped )
    {
        if( m_midiTonic.NormalizeToC4().AsMidi() == val )
        {
            return true;
        }
    }
    return false;
}

bool Scale::OnlyFlatSignaturePossible() const
{
    return !FlatOrSharpSignatureBothPossible() && !OnlySharpSignaturePossible();
}

} // namespace heory
