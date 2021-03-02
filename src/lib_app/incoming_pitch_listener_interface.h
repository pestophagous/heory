#ifndef PROJECT_LIB_PITCH_LISTENER_IFACE_H
#define PROJECT_LIB_PITCH_LISTENER_IFACE_H

#include <functional>

#include "src/lib_app/pitch.h"
#include "util-assert.h"

namespace heory
{
// PitchLifetime objects should only be created by backends (such as fsynth.cc)
// or possibly in tests.
class PitchLifetime
{
public:
    explicit PitchLifetime(
        Pitch p, std::function<void( std::function<void()> )> backendRegistrationLogic )
        : pitch( p ), m_register( backendRegistrationLogic )
    {
        FASSERT( m_register, "please provide a valid functor" );
    }

    const Pitch pitch;
    void OnLifetimeComplete( std::function<void()> callback )
    {
        m_register( callback );
    }

private:
    std::function<void( std::function<void()> )> m_register;
};

class IncomingPitchListener_Interface
{
public:
    virtual ~IncomingPitchListener_Interface() = default;

    virtual void OnIncomingNote( PitchLifetime pitch ) = 0;
};

} // namespace heory

#endif // PROJECT_LIB_PITCH_LISTENER_IFACE_H
