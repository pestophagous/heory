#include "task_runner.h"

#include <QThread>

#include <cstdlib>
#include <stdio.h>

#include "util-assert.h"

namespace heory
{
namespace tests
{
    // amidi -phw:1,0 -S '80 3c 30'
    void RunTask( Task t )
    {
        FASSERT( t.type == TaskType::PlayNoteBasic, "(for now) we only handle 1 type" );
        FASSERT( t.midiPitch > 0 && t.midiPitch < 255, "only small ints please" );

        char hexString[ 20 ];
        memset( hexString, 0, sizeof( hexString ) );

        const int s = sprintf( hexString, "%x", t.midiPitch );
        FASSERT( s >= 0, "sprintf failed" );

        const QString noteon
            = QStringLiteral( "amidi -phw:1,0 -S '90 %1 30'" ).arg( hexString );
        const QString noteoff
            = QStringLiteral( "amidi -phw:1,0 -S '80 %1 30'" ).arg( hexString );

        int ret = std::system( noteon.toStdString().c_str() );
        FASSERT( ret == 0,
            "test task system call failed (or we should expect a different return code)" );
        QThread::msleep( 100 ); // TODO: make this configurable
        ret = std::system( noteoff.toStdString().c_str() );
        FASSERT( ret == 0,
            "test task system call failed (or we should expect a different return code)" );
    }
} // namespace tests
} // namespace heory
