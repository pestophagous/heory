//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_UTIL_RANDOM_CONCRETE_H
#define PROJECT_UTIL_RANDOM_CONCRETE_H

#include <memory>

#include "src/util/random.h"

namespace heory
{
class RandomConcrete : public Random
{
public:
    RandomConcrete();
    ~RandomConcrete() override;

    int GetNextFromNToMInclusive( int n, int m ) override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace heory

#endif // PROJECT_UTIL_RANDOM_CONCRETE_H
