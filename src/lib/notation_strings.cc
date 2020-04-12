#include "notation_strings.h"

namespace heory
{
namespace notation
{
    QString SHARP_SIGN()
    {
        return QString::fromUtf8( SHARP_UTF8 );
    }

    QString FLAT_SIGN()
    {
        return QString::fromUtf8( FLAT_UTF8 );
    }

    QString Sharped( const char alpha )
    {
        QString result( alpha );
        result += SHARP_SIGN();
        return result;
    }

    QString Flatted( const char alpha )
    {
        QString result( alpha );
        result += FLAT_SIGN();
        return result;
    }

    QString A()
    {
        return QString( 'A' );
    }
    QString ASharp()
    {
        return Sharped( 'A' );
    }
    QString AFlat()
    {
        return Flatted( 'A' );
    }
    QString B()
    {
        return QString( 'B' );
    }
    QString BSharp()
    {
        return Sharped( 'B' );
    }
    QString BFlat()
    {
        return Flatted( 'B' );
    }
    QString C()
    {
        return QString( 'C' );
    }
    QString CSharp()
    {
        return Sharped( 'C' );
    }
    QString CFlat()
    {
        return Flatted( 'C' );
    }
    QString D()
    {
        return QString( 'D' );
    }
    QString DSharp()
    {
        return Sharped( 'D' );
    }
    QString DFlat()
    {
        return Flatted( 'D' );
    }
    QString E()
    {
        return QString( 'E' );
    }
    QString ESharp()
    {
        return Sharped( 'E' );
    }
    QString EFlat()
    {
        return Flatted( 'E' );
    }
    QString F()
    {
        return QString( 'F' );
    }
    QString FSharp()
    {
        return Sharped( 'F' );
    }
    QString FFlat()
    {
        return Flatted( 'F' );
    }
    QString G()
    {
        return QString( 'G' );
    }
    QString GSharp()
    {
        return Sharped( 'G' );
    }
    QString GFlat()
    {
        return Flatted( 'G' );
    }

} // namespace notation
} // namespace heory
