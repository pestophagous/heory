#ifndef PROJECT_LIB_PITCH_LISTENER_IFACE_H
#define PROJECT_LIB_PITCH_LISTENER_IFACE_H

#include "src/lib/pitch.h"

namespace heory
{
class IncomingPitchListener_Interface
{
public:
    virtual ~IncomingPitchListener_Interface() = default;

    virtual void OnIncomingNote( Pitch pitch ) = 0;
};

} // namespace heory

#endif // PROJECT_LIB_PITCH_LISTENER_IFACE_H
