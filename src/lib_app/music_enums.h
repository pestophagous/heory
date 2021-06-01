//
// Copyright (c) 2021, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_MUSIC_ENUMS_H
#define PROJECT_LIB_MUSIC_ENUMS_H

#include <QString>

namespace heory
{
enum class TonalityLabel
{
    Unknown,
    Major,
    Minor
};
QString TonalityLabelString( TonalityLabel );

} // namespace heory

#endif // PROJECT_LIB_MUSIC_ENUMS_H
