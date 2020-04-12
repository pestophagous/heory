//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_NOTATION_STRINGS_H
#define PROJECT_LIB_NOTATION_STRINGS_H

#include <QString>

namespace heory
{
namespace notation
{
    constexpr char SHARP_UTF8[] = "\xE2\x99\xAF";
    constexpr char FLAT_UTF8[] = "\xE2\x99\xAD";

    QString SHARP_SIGN();
    QString FLAT_SIGN();

    QString Sharped( char alpha );
    QString Flatted( char alpha );

    QString A();
    QString ASharp();
    QString AFlat();
    QString B();
    QString BSharp();
    QString BFlat();
    QString C();
    QString CSharp();
    QString CFlat();
    QString D();
    QString DSharp();
    QString DFlat();
    QString E();
    QString ESharp();
    QString EFlat();
    QString F();
    QString FSharp();
    QString FFlat();
    QString G();
    QString GSharp();
    QString GFlat();

} // namespace notation
} // namespace heory

#endif // PROJECT_LIB_NOTATION_STRINGS_H
