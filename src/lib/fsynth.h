//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_FSYNTH_H
#define PROJECT_LIB_FSYNTH_H

#include "src/lib/pitch.h"
#include "src/lib/sound_io_interface.h"

#include <vector>

namespace heory
{
class CliOptions;

class FsynthWrapper : public SoundIO_Interface
{
public:
    struct Impl; // "effectively private" type, due to being opaque.

    explicit FsynthWrapper( const CliOptions& options );
    ~FsynthWrapper() override;

    FsynthWrapper( const FsynthWrapper& ) = delete;
    FsynthWrapper& operator=( const FsynthWrapper& ) = delete;

    void PlayNote( Pitch pitch ) override;

    void SubscribeToIncomingPitches( IncomingPitchListener_Interface* listener ) override;
    void UnsubscribeToIncomingPitches( IncomingPitchListener_Interface* listener ) override;

    struct VoidDataPreRouter;
    friend struct VoidDataPreRouter;

private:
    void NotifyIncomingPitch( int asMidi ) const;
    Impl* const m_i;

    std::vector<IncomingPitchListener_Interface*> m_pitchListeners;
};

} // namespace heory

#endif // PROJECT_LIB_FSYNTH_H
