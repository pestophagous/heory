//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_UTIL_RANDOM_H
#define PROJECT_UTIL_RANDOM_H

namespace heory
{
class Random
{
public:
    virtual ~Random() = default;

    virtual int GetNextFromNToMInclusive( int n, int m ) = 0;

    // For subtypes that use a repeatable seed (for testing), this will restart the
    // random sequence, once again seeding it with the repeatable seed.
    virtual void Reset() = 0;

private:
};

} // namespace heory

#endif // PROJECT_UTIL_RANDOM_H
