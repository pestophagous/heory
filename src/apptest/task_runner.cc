#include "task_runner.h"

#include <QThread>

#include <cstdlib>
#include <stdio.h>

#include "util-assert.h"

namespace heory
{
namespace tests
{
    // amidiPortToken is something like: -phw:1,0
    // amidiPortToken could also be:     -phw:2,0
    //
    // amidi -phw:1,0 -S '80 3c 30'
    //
    // We rely on VirMIDI:
    //   sudo modprobe snd-virmidi
    //   ls /dev/snd/midi*
    //   https://tldp.org/HOWTO/MIDI-HOWTO-10.html
    void RunTask( Task t, const QString& amidiPortToken )
    {
        FASSERT( t.type == TaskType::PlayNoteBasic, "(for now) we only handle 1 type" );
        FASSERT( t.midiPitch > 0 && t.midiPitch < 255, "only small ints please" );

        char hexString[ 20 ];
        memset( hexString, 0, sizeof( hexString ) );

        const int s = sprintf( hexString, "%x", t.midiPitch );
        FASSERT( s >= 0, "sprintf failed" );

        const QString noteon = QStringLiteral( "amidi %1 -S '90 %2 30'" )
                                   .arg( amidiPortToken )
                                   .arg( hexString );
        const QString noteoff = QStringLiteral( "amidi %1 -S '80 %2 30'" )
                                    .arg( amidiPortToken )
                                    .arg( hexString );

        int ret = std::system( noteon.toStdString().c_str() );
        FASSERT( ret == 0, "amidi system call failed (is kernel module snd-virmidi loaded?)" );
        QThread::msleep( 100 ); // TODO: make this configurable
        ret = std::system( noteoff.toStdString().c_str() );
        FASSERT( ret == 0, "amidi system call failed (is kernel module snd-virmidi loaded?)" );
    }
} // namespace tests
} // namespace heory
