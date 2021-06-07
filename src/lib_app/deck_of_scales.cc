#include "deck_of_scales.h"

#include <algorithm>

#include "src/util/random.h"
#include "util-assert.h"

namespace heory
{
namespace
{
    std::array<ScaleWithAssets, 30> GetDeck()
    {
        return std::array<ScaleWithAssets, 30>{
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 60 ) ),
                "treble_signature_empty.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 67 ) ),
                "treble_signature_1_sharp.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 62 ) ),
                "treble_signature_2_sharps.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 69 ) ),
                "treble_signature_3_sharps.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 64 ) ),
                "treble_signature_4_sharps.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 71 ) ),
                "treble_signature_5_sharps.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 66 ) ),
                "treble_signature_6_sharps.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 61 ) ),
                "treble_signature_7_sharps.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 65 ) ),
                "treble_signature_1_flat.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 70 ) ),
                "treble_signature_2_flats.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 63 ) ),
                "treble_signature_3_flats.svg" ),
            ScaleWithAssets( Scale::MajorFromTonicLength8( Pitch::FromMidi( 68 ) ),
                "treble_signature_4_flats.svg" ),
            ScaleWithAssets(
                Scale::MajorFromTonicLength8( Pitch::FromMidi( 61 ), true /*useFlats*/ ),
                "treble_signature_5_flats.svg" ),
            ScaleWithAssets(
                Scale::MajorFromTonicLength8( Pitch::FromMidi( 66 ), true /*useFlats*/ ),
                "treble_signature_6_flats.svg" ),
            ScaleWithAssets(
                Scale::MajorFromTonicLength8( Pitch::FromMidi( 71 ), true /*useFlats*/ ),
                "treble_signature_7_flats.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 69 ) ),
                "treble_signature_empty.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 64 ) ),
                "treble_signature_1_sharp.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 71 ) ),
                "treble_signature_2_sharps.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 66 ) ),
                "treble_signature_3_sharps.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 61 ) ),
                "treble_signature_4_sharps.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 68 ) ),
                "treble_signature_5_sharps.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 63 ) ),
                "treble_signature_6_sharps.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 70 ) ),
                "treble_signature_7_sharps.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 62 ) ),
                "treble_signature_1_flat.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 67 ) ),
                "treble_signature_2_flats.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 60 ) ),
                "treble_signature_3_flats.svg" ),
            ScaleWithAssets( Scale::MinorFromTonicLength8( Pitch::FromMidi( 65 ) ),
                "treble_signature_4_flats.svg" ),
            ScaleWithAssets(
                Scale::MinorFromTonicLength8( Pitch::FromMidi( 70 ), true /*useFlats*/ ),
                "treble_signature_5_flats.svg" ),
            ScaleWithAssets(
                Scale::MinorFromTonicLength8( Pitch::FromMidi( 63 ), true /*useFlats*/ ),
                "treble_signature_6_flats.svg" ),
            ScaleWithAssets(
                Scale::MinorFromTonicLength8( Pitch::FromMidi( 68 ), true /*useFlats*/ ),
                "treble_signature_7_flats.svg" )};
    }

    int GetSeed( Random* random )
    {
        if( random->ConstructedWithRepeatableSeed() )
        {
            // when constructed with a repeatable seed, it means the user of this
            // code also would like a repeatable outcome here.
            random->Reset();
            return random->GetNextFromNToMInclusive( 0, 100 );
        }

        std::random_device rd;
        return rd();
    }
} // namespace

ScaleWithAssets::ScaleWithAssets( Scale s, const QString& i ) : scale( s ), imageName( i )
{
}

DeckOfScales::DeckOfScales( Random* random )
    : m_deck( GetDeck() )
    , m_indices{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
          22, 23, 24, 25, 26, 27, 28, 29}
    , m_gen( GetSeed( random ) )
{
    AssertInvariants();
}

DeckOfScales::~DeckOfScales() = default;

void DeckOfScales::Shuffle()
{
    AssertInvariants();
    std::shuffle( m_indices.begin(), m_indices.end(), m_gen );
}

void DeckOfScales::UnShuffle()
{
    AssertInvariants();
    std::sort( m_indices.begin(), m_indices.end() );
}

void DeckOfScales::AssertInvariants() const
{
    FASSERT( m_position < m_indices.size(), "position must be valid" );
    FASSERT( m_indices[ m_position ] < m_deck.size(), "shuffled index must be valid" );
    FASSERT(
        m_indices.size() == m_deck.size(), "should not have more indices than exist in deck" );
}

ScaleWithAssets DeckOfScales::NextScale()
{
    AssertInvariants();
    const size_t chosenIndex = m_indices[ m_position ];
    m_position++;
    m_position = m_position % m_indices.size();
    return m_deck[ chosenIndex ];
}

ScaleWithAssets DeckOfScales::NextScale_ReshuffleAtWraparound()
{
    AssertInvariants();
    const size_t chosenIndex = m_indices[ m_position ];
    m_position++;
    if( m_position >= m_indices.size() )
    {
        m_position = 0;
        Shuffle();
    }

    return m_deck[ chosenIndex ];
}

} // namespace heory
