#ifndef PROJECT_LIB_SOUND_IO_IFACE_H
#define PROJECT_LIB_SOUND_IO_IFACE_H

#include "src/lib/incoming_pitch_listener_interface.h"
#include "src/lib/pitch.h"

namespace heory
{
class SoundIO_Interface
{
public:
    virtual ~SoundIO_Interface() = default;

    virtual void PlayNote( Pitch pitch ) = 0;

    virtual void SubscribeToIncomingPitches( IncomingPitchListener_Interface* listener ) = 0;
    virtual void UnsubscribeToIncomingPitches( IncomingPitchListener_Interface* listener ) = 0;
};

} // namespace heory

#endif // PROJECT_LIB_SOUND_IO_IFACE_H
