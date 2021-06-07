//
// Copyright (c) 2021, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_DECK_OF_SCALES_H
#define PROJECT_LIB_DECK_OF_SCALES_H

#include <QString>

#include <array>
#include <random>

#include "src/lib_app/scale.h"

namespace heory
{
class Random;

struct ScaleWithAssets
{
    explicit ScaleWithAssets( Scale, const QString& );
    Scale scale;
    QString imageName;
};

class DeckOfScales
{
public:
    explicit DeckOfScales( Random* random );
    ~DeckOfScales();

    DeckOfScales( const DeckOfScales& ) = delete;
    DeckOfScales& operator=( const DeckOfScales& ) = delete;

    void Shuffle();
    void UnShuffle();

    ScaleWithAssets NextScale();
    ScaleWithAssets NextScale_ReshuffleAtWraparound();

private:
    void AssertInvariants() const;
    const std::array<ScaleWithAssets, 30> m_deck;

    std::array<size_t, 30> m_indices;
    std::mt19937 m_gen;
    size_t m_position = 0;
};

} // namespace heory

#endif // PROJECT_LIB_DECK_OF_SCALES_H
