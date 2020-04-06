//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_FSYNTH_H
#define PROJECT_LIB_FSYNTH_H

namespace heory
{
class CliOptions;

class FsynthWrapper
{
public:
    struct Impl; // "effectively private" type, due to being opaque.

    explicit FsynthWrapper( const CliOptions& options );
    ~FsynthWrapper();

    FsynthWrapper( const FsynthWrapper& ) = delete;
    FsynthWrapper& operator=( const FsynthWrapper& ) = delete;

    void PlayNote();

private:
    Impl* const m_i;
};

} // namespace heory

#endif // PROJECT_LIB_FSYNTH_H
