#include "gtest/gtest.h"

#include "scale.h"

#include <QDebug>

#include "src/lib_app/notation_strings.h"

namespace heory
{
namespace
{
    using namespace ::heory::notation;

    class ScaleTest : public ::testing::Test
    {
    protected:
        ScaleTest()
            : kMajorC( Scale::MajorFromTonicLength8( Pitch::FromMidi( 60 ) ) )
            , kMajorG( Scale::MajorFromTonicLength8( Pitch::FromMidi( 67 ) ) )
            , kMajorD( Scale::MajorFromTonicLength8( Pitch::FromMidi( 62 ) ) )
            , kMajorA( Scale::MajorFromTonicLength8( Pitch::FromMidi( 69 ) ) )
            , kMajorE( Scale::MajorFromTonicLength8( Pitch::FromMidi( 64 ) ) )
            , kMajorB( Scale::MajorFromTonicLength8( Pitch::FromMidi( 71 ) ) )
            , kMajorFSharp( Scale::MajorFromTonicLength8( Pitch::FromMidi( 66 ) ) )
            , kMajorCSharp( Scale::MajorFromTonicLength8( Pitch::FromMidi( 61 ) ) )
            , kMajorF( Scale::MajorFromTonicLength8( Pitch::FromMidi( 65 ) ) )
            , kMajorBFlat( Scale::MajorFromTonicLength8( Pitch::FromMidi( 70 ) ) )
            , kMajorEFlat( Scale::MajorFromTonicLength8( Pitch::FromMidi( 63 ) ) )
            , kMajorAFlat( Scale::MajorFromTonicLength8( Pitch::FromMidi( 68 ) ) )
            , kMajorDFlat(
                  Scale::MajorFromTonicLength8( Pitch::FromMidi( 61 ), true /*useFlats*/ ) )
            , kMajorGFlat(
                  Scale::MajorFromTonicLength8( Pitch::FromMidi( 66 ), true /*useFlats*/ ) )
            , kMajorCFlat(
                  Scale::MajorFromTonicLength8( Pitch::FromMidi( 71 ), true /*useFlats*/ ) )
            , kMinorA( Scale::MinorFromTonicLength8( Pitch::FromMidi( 69 ) ) )
            , kMinorE( Scale::MinorFromTonicLength8( Pitch::FromMidi( 64 ) ) )
            , kMinorB( Scale::MinorFromTonicLength8( Pitch::FromMidi( 71 ) ) )
            , kMinorFSharp( Scale::MinorFromTonicLength8( Pitch::FromMidi( 66 ) ) )
            , kMinorCSharp( Scale::MinorFromTonicLength8( Pitch::FromMidi( 61 ) ) )
            , kMinorGSharp( Scale::MinorFromTonicLength8( Pitch::FromMidi( 68 ) ) )
            , kMinorDSharp( Scale::MinorFromTonicLength8( Pitch::FromMidi( 63 ) ) )
            , kMinorASharp( Scale::MinorFromTonicLength8( Pitch::FromMidi( 70 ) ) )
            , kMinorD( Scale::MinorFromTonicLength8( Pitch::FromMidi( 62 ) ) )
            , kMinorG( Scale::MinorFromTonicLength8( Pitch::FromMidi( 67 ) ) )
            , kMinorC( Scale::MinorFromTonicLength8( Pitch::FromMidi( 60 ) ) )
            , kMinorF( Scale::MinorFromTonicLength8( Pitch::FromMidi( 65 ) ) )
            , kMinorBFlat(
                  Scale::MinorFromTonicLength8( Pitch::FromMidi( 70 ), true /*useFlats*/ ) )
            , kMinorEFlat(
                  Scale::MinorFromTonicLength8( Pitch::FromMidi( 63 ), true /*useFlats*/ ) )
            , kMinorAFlat(
                  Scale::MinorFromTonicLength8( Pitch::FromMidi( 68 ), true /*useFlats*/ ) )
            , kMajor7NoteC( Scale::MajorFromTonicLength7( Pitch::FromMidi( 60 ) ) )
            , kMajor7NoteG( Scale::MajorFromTonicLength7( Pitch::FromMidi( 67 ) ) )
            , kMajor7NoteD( Scale::MajorFromTonicLength7( Pitch::FromMidi( 62 ) ) )
            , kMajor7NoteA( Scale::MajorFromTonicLength7( Pitch::FromMidi( 69 ) ) )
            , kMajor7NoteE( Scale::MajorFromTonicLength7( Pitch::FromMidi( 64 ) ) )
            , kMajor7NoteB( Scale::MajorFromTonicLength7( Pitch::FromMidi( 71 ) ) )
            , kMajor7NoteFSharp( Scale::MajorFromTonicLength7( Pitch::FromMidi( 66 ) ) )
            , kMajor7NoteCSharp( Scale::MajorFromTonicLength7( Pitch::FromMidi( 61 ) ) )
            , kMajor7NoteF( Scale::MajorFromTonicLength7( Pitch::FromMidi( 65 ) ) )
            , kMajor7NoteBFlat( Scale::MajorFromTonicLength7( Pitch::FromMidi( 70 ) ) )
            , kMajor7NoteEFlat( Scale::MajorFromTonicLength7( Pitch::FromMidi( 63 ) ) )
            , kMajor7NoteAFlat( Scale::MajorFromTonicLength7( Pitch::FromMidi( 68 ) ) )
            , kMajor7NoteDFlat(
                  Scale::MajorFromTonicLength7( Pitch::FromMidi( 61 ), true /*useFlats*/ ) )
            , kMajor7NoteGFlat(
                  Scale::MajorFromTonicLength7( Pitch::FromMidi( 66 ), true /*useFlats*/ ) )
            , kMajor7NoteCFlat(
                  Scale::MajorFromTonicLength7( Pitch::FromMidi( 71 ), true /*useFlats*/ ) )
            , kMinor7NoteA( Scale::MinorFromTonicLength7( Pitch::FromMidi( 69 ) ) )
            , kMinor7NoteE( Scale::MinorFromTonicLength7( Pitch::FromMidi( 64 ) ) )
            , kMinor7NoteB( Scale::MinorFromTonicLength7( Pitch::FromMidi( 71 ) ) )
            , kMinor7NoteFSharp( Scale::MinorFromTonicLength7( Pitch::FromMidi( 66 ) ) )
            , kMinor7NoteCSharp( Scale::MinorFromTonicLength7( Pitch::FromMidi( 61 ) ) )
            , kMinor7NoteGSharp( Scale::MinorFromTonicLength7( Pitch::FromMidi( 68 ) ) )
            , kMinor7NoteDSharp( Scale::MinorFromTonicLength7( Pitch::FromMidi( 63 ) ) )
            , kMinor7NoteASharp( Scale::MinorFromTonicLength7( Pitch::FromMidi( 70 ) ) )
            , kMinor7NoteD( Scale::MinorFromTonicLength7( Pitch::FromMidi( 62 ) ) )
            , kMinor7NoteG( Scale::MinorFromTonicLength7( Pitch::FromMidi( 67 ) ) )
            , kMinor7NoteC( Scale::MinorFromTonicLength7( Pitch::FromMidi( 60 ) ) )
            , kMinor7NoteF( Scale::MinorFromTonicLength7( Pitch::FromMidi( 65 ) ) )
            , kMinor7NoteBFlat(
                  Scale::MinorFromTonicLength7( Pitch::FromMidi( 70 ), true /*useFlats*/ ) )
            , kMinor7NoteEFlat(
                  Scale::MinorFromTonicLength7( Pitch::FromMidi( 63 ), true /*useFlats*/ ) )
            , kMinor7NoteAFlat(
                  Scale::MinorFromTonicLength7( Pitch::FromMidi( 68 ), true /*useFlats*/ ) )
        {
        }

        const Scale kMajorC;
        const Scale kMajorG;
        const Scale kMajorD;
        const Scale kMajorA;
        const Scale kMajorE;
        const Scale kMajorB;
        const Scale kMajorFSharp;
        const Scale kMajorCSharp;
        const Scale kMajorF;
        const Scale kMajorBFlat;
        const Scale kMajorEFlat;
        const Scale kMajorAFlat;
        const Scale kMajorDFlat;
        const Scale kMajorGFlat;
        const Scale kMajorCFlat;

        const Scale kMinorA;
        const Scale kMinorE;
        const Scale kMinorB;
        const Scale kMinorFSharp;
        const Scale kMinorCSharp;
        const Scale kMinorGSharp;
        const Scale kMinorDSharp;
        const Scale kMinorASharp;
        const Scale kMinorD;
        const Scale kMinorG;
        const Scale kMinorC;
        const Scale kMinorF;
        const Scale kMinorBFlat;
        const Scale kMinorEFlat;
        const Scale kMinorAFlat;

        const Scale kMajor7NoteC;
        const Scale kMajor7NoteG;
        const Scale kMajor7NoteD;
        const Scale kMajor7NoteA;
        const Scale kMajor7NoteE;
        const Scale kMajor7NoteB;
        const Scale kMajor7NoteFSharp;
        const Scale kMajor7NoteCSharp;
        const Scale kMajor7NoteF;
        const Scale kMajor7NoteBFlat;
        const Scale kMajor7NoteEFlat;
        const Scale kMajor7NoteAFlat;
        const Scale kMajor7NoteDFlat;
        const Scale kMajor7NoteGFlat;
        const Scale kMajor7NoteCFlat;

        const Scale kMinor7NoteA;
        const Scale kMinor7NoteE;
        const Scale kMinor7NoteB;
        const Scale kMinor7NoteFSharp;
        const Scale kMinor7NoteCSharp;
        const Scale kMinor7NoteGSharp;
        const Scale kMinor7NoteDSharp;
        const Scale kMinor7NoteASharp;
        const Scale kMinor7NoteD;
        const Scale kMinor7NoteG;
        const Scale kMinor7NoteC;
        const Scale kMinor7NoteF;
        const Scale kMinor7NoteBFlat;
        const Scale kMinor7NoteEFlat;
        const Scale kMinor7NoteAFlat;
    };

    TEST_F( ScaleTest, FuzzyMatchesAndFuzzyNonMatches )
    {
        EXPECT_TRUE( kMajorB.IsFuzzyMatch( kMajorCFlat ) );
        EXPECT_TRUE( kMajorFSharp.IsFuzzyMatch( kMajorGFlat ) );
        EXPECT_TRUE( kMajorCSharp.IsFuzzyMatch( kMajorDFlat ) );

        EXPECT_TRUE( kMinorGSharp.IsFuzzyMatch( kMinorAFlat ) );
        EXPECT_TRUE( kMinorDSharp.IsFuzzyMatch( kMinorEFlat ) );
        EXPECT_TRUE( kMinorASharp.IsFuzzyMatch( kMinorBFlat ) );

        EXPECT_TRUE( kMajorB.IsExactAuditoryMatch( kMajorCFlat ) );
        EXPECT_TRUE( kMajorFSharp.IsExactAuditoryMatch( kMajorGFlat ) );
        EXPECT_TRUE( kMajorCSharp.IsExactAuditoryMatch( kMajorDFlat ) );

        EXPECT_TRUE( kMinorGSharp.IsExactAuditoryMatch( kMinorAFlat ) );
        EXPECT_TRUE( kMinorDSharp.IsExactAuditoryMatch( kMinorEFlat ) );
        EXPECT_TRUE( kMinorASharp.IsExactAuditoryMatch( kMinorBFlat ) );

        EXPECT_TRUE( kMajorB.IsFuzzyMatch( kMajor7NoteB ) );
        EXPECT_TRUE( kMajor7NoteB.IsFuzzyMatch( kMajorB ) );

        EXPECT_TRUE( kMinorGSharp.IsFuzzyMatch( kMinor7NoteGSharp ) );
        EXPECT_TRUE( kMinor7NoteGSharp.IsFuzzyMatch( kMinorGSharp ) );

        EXPECT_FALSE( kMajorB.IsExactAuditoryMatch( kMajor7NoteB ) );
        EXPECT_FALSE( kMajor7NoteB.IsExactAuditoryMatch( kMajorB ) );

        EXPECT_FALSE( kMinorGSharp.IsExactAuditoryMatch( kMinor7NoteGSharp ) );
        EXPECT_FALSE( kMinor7NoteGSharp.IsExactAuditoryMatch( kMinorGSharp ) );

        const Scale scaleC3 = Scale::MajorFromTonicLength8( Pitch::FromMidi( 48 ) );

        EXPECT_FALSE( kMajorC.IsExactAuditoryMatch( scaleC3 ) );
        EXPECT_FALSE( scaleC3.IsExactAuditoryMatch( kMajorC ) );
        EXPECT_TRUE( kMajorC.IsFuzzyMatch( scaleC3 ) );
        EXPECT_TRUE( scaleC3.IsFuzzyMatch( kMajorC ) );

        const Scale scaleA3min = Scale::MinorFromTonicLength8( Pitch::FromMidi( 57 ) );

        EXPECT_FALSE( kMinorA.IsExactAuditoryMatch( scaleA3min ) );
        EXPECT_FALSE( scaleA3min.IsExactAuditoryMatch( kMinorA ) );
        EXPECT_TRUE( kMinorA.IsFuzzyMatch( scaleA3min ) );
        EXPECT_TRUE( scaleA3min.IsFuzzyMatch( kMinorA ) );

        const Scale scaleB2 = Scale::MajorFromTonicLength7( Pitch::FromMidi( 47 ) );

        EXPECT_FALSE( kMajor7NoteB.IsExactAuditoryMatch( scaleB2 ) );
        EXPECT_FALSE( scaleB2.IsExactAuditoryMatch( kMajor7NoteB ) );
        EXPECT_TRUE( kMajor7NoteB.IsFuzzyMatch( scaleB2 ) );
        EXPECT_TRUE( scaleB2.IsFuzzyMatch( kMajor7NoteB ) );
    }

    TEST_F( ScaleTest, Printing )
    {
        EXPECT_EQ( QString( "B Major" ), kMajorB.Name() );

        {
            // "B,C♯,D♯,E,F♯,G♯,A♯,B"
            QString scaleString = "B,";
            scaleString += CSharp();
            scaleString += ",";
            scaleString += DSharp();
            scaleString += ",E,";
            scaleString += FSharp();
            scaleString += ",";
            scaleString += GSharp();
            scaleString += ",";
            scaleString += ASharp();
            scaleString += ",B";

            EXPECT_EQ( scaleString, kMajorB.AsAlphabeticNoOctave( "," ) );
        }

        {
            // "C♯;D♯;F;F♯;G♯;A♯;C"
            QString scaleString = CSharp();
            scaleString += ";";
            scaleString += DSharp();
            scaleString += ";F;";
            scaleString += FSharp();
            scaleString += ";";
            scaleString += GSharp();
            scaleString += ";";
            scaleString += ASharp();
            scaleString += ";C";

            EXPECT_EQ( scaleString, kMajor7NoteCSharp.AsAlphabeticNoOctave( ";" ) );
        }

        {
            // "D♭+E♭+F+G♭+A♭+B♭+C"
            QString scaleString = DFlat();
            scaleString += "+";
            scaleString += EFlat();
            scaleString += "+F+";
            scaleString += GFlat();
            scaleString += "+";
            scaleString += AFlat();
            scaleString += "+";
            scaleString += BFlat();
            scaleString += "+C";

            EXPECT_EQ( scaleString, kMajor7NoteDFlat.AsAlphabeticNoOctave( "+" ) );
        }
    }

    TEST_F( ScaleTest, AdHocScales )
    {
        std::vector<Pitch> adHoc{
            Pitch::FromMidi( 65 ),
            Pitch::FromMidi( 60 ),
            Pitch::FromMidi( 62 ),
            Pitch::FromMidi( 71 ),
            Pitch::FromMidi( 69 ),
            Pitch::FromMidi( 64 ),
            Pitch::FromMidi( 67 ),
        };

        const Scale adHocScale = Scale::From7Notes( adHoc );

        EXPECT_TRUE( adHocScale.IsExactAuditoryMatch( kMajor7NoteC ) );
        EXPECT_TRUE( kMajor7NoteC.IsExactAuditoryMatch( adHocScale ) );

        EXPECT_FALSE( adHocScale.IsExactAuditoryMatch( kMajorC ) );
        EXPECT_FALSE( kMajorC.IsExactAuditoryMatch( adHocScale ) );

        EXPECT_TRUE( adHocScale.IsFuzzyMatch( kMajorC ) );
        EXPECT_TRUE( kMajorC.IsFuzzyMatch( adHocScale ) );
    }
} // namespace
} // namespace heory
