#include "music_enums.h"

#include "util-assert.h"

namespace heory
{
QString TonalityLabelString( TonalityLabel t )
{
    switch( t ) // be sure to compile with -Wswitch-enum to catch any changes!
    {
    case TonalityLabel::Unknown:
        return "Unknown";
    case TonalityLabel::Major:
        return "Major";
    case TonalityLabel::Minor:
        return "Minor";
    default:
        // fallthrough
        ;
    }

    FFAIL( "should never get here" );
    return "missing-TonalityLabel";
}

} // namespace heory
