#include "gtest/gtest.h"

#include "pitch.h"

#include "src/lib_app/notation_strings.h"

namespace heory
{
namespace
{
    using namespace ::heory::notation;

    class PitchTest : public ::testing::Test
    {
    protected:
        PitchTest()
        {
            for( int i = 0; i < 128; i++ )
            {
                m_pitchesIndexedByMidi.push_back( Pitch::FromMidi( i ) );
            }
        }

        std::vector<Pitch> m_pitchesIndexedByMidi;
    };

    TEST_F( PitchTest, Basics )
    {
        EXPECT_EQ( 20, m_pitchesIndexedByMidi[ 20 ].AsMidi() );
        EXPECT_FALSE( m_pitchesIndexedByMidi[ 20 ].PlayableOnPiano88Key() );
        EXPECT_EQ( GSharp(), m_pitchesIndexedByMidi[ 20 ].AsAlphabeticNoOctaveUseSharp() );
        EXPECT_EQ( AFlat(), m_pitchesIndexedByMidi[ 20 ].AsAlphabeticNoOctaveUseFlat() );
        EXPECT_EQ( 0, m_pitchesIndexedByMidi[ 20 ].OctaveNumber() );

        // Lowest note on 88 key piano
        EXPECT_EQ( 21, m_pitchesIndexedByMidi[ 21 ].AsMidi() );
        EXPECT_TRUE( m_pitchesIndexedByMidi[ 21 ].PlayableOnPiano88Key() );
        EXPECT_EQ( A(), m_pitchesIndexedByMidi[ 21 ].AsAlphabeticNoOctaveUseSharp() );
        EXPECT_EQ( A(), m_pitchesIndexedByMidi[ 21 ].AsAlphabeticNoOctaveUseFlat() );
        EXPECT_EQ( 0, m_pitchesIndexedByMidi[ 21 ].OctaveNumber() );

        EXPECT_EQ( 42, m_pitchesIndexedByMidi[ 42 ].AsMidi() );
        EXPECT_TRUE( m_pitchesIndexedByMidi[ 42 ].PlayableOnPiano88Key() );
        EXPECT_EQ( FSharp(), m_pitchesIndexedByMidi[ 42 ].AsAlphabeticNoOctaveUseSharp() );
        EXPECT_EQ( GFlat(), m_pitchesIndexedByMidi[ 42 ].AsAlphabeticNoOctaveUseFlat() );
        EXPECT_EQ( 2, m_pitchesIndexedByMidi[ 42 ].OctaveNumber() );

        // Middle C
        EXPECT_EQ( 60, m_pitchesIndexedByMidi[ 60 ].AsMidi() );
        EXPECT_TRUE( m_pitchesIndexedByMidi[ 60 ].PlayableOnPiano88Key() );
        EXPECT_EQ( C(), m_pitchesIndexedByMidi[ 60 ].AsAlphabeticNoOctaveUseSharp() );
        EXPECT_EQ( C(), m_pitchesIndexedByMidi[ 60 ].AsAlphabeticNoOctaveUseFlat() );
        EXPECT_EQ( 4, m_pitchesIndexedByMidi[ 60 ].OctaveNumber() );

        EXPECT_EQ( 75, m_pitchesIndexedByMidi[ 75 ].AsMidi() );
        EXPECT_TRUE( m_pitchesIndexedByMidi[ 75 ].PlayableOnPiano88Key() );
        EXPECT_EQ( DSharp(), m_pitchesIndexedByMidi[ 75 ].AsAlphabeticNoOctaveUseSharp() );
        EXPECT_EQ( EFlat(), m_pitchesIndexedByMidi[ 75 ].AsAlphabeticNoOctaveUseFlat() );
        EXPECT_EQ( 5, m_pitchesIndexedByMidi[ 75 ].OctaveNumber() );

        // Highest note on 88 key piano
        EXPECT_EQ( 108, m_pitchesIndexedByMidi[ 108 ].AsMidi() );
        EXPECT_TRUE( m_pitchesIndexedByMidi[ 108 ].PlayableOnPiano88Key() );
        EXPECT_EQ( C(), m_pitchesIndexedByMidi[ 108 ].AsAlphabeticNoOctaveUseSharp() );
        EXPECT_EQ( C(), m_pitchesIndexedByMidi[ 108 ].AsAlphabeticNoOctaveUseFlat() );
        EXPECT_EQ( 8, m_pitchesIndexedByMidi[ 108 ].OctaveNumber() );

        EXPECT_EQ( 109, m_pitchesIndexedByMidi[ 109 ].AsMidi() );
        EXPECT_FALSE( m_pitchesIndexedByMidi[ 109 ].PlayableOnPiano88Key() );
        EXPECT_EQ( CSharp(), m_pitchesIndexedByMidi[ 109 ].AsAlphabeticNoOctaveUseSharp() );
        EXPECT_EQ( DFlat(), m_pitchesIndexedByMidi[ 109 ].AsAlphabeticNoOctaveUseFlat() );
        EXPECT_EQ( 8, m_pitchesIndexedByMidi[ 109 ].OctaveNumber() );
    }

} // namespace
} // namespace heory
