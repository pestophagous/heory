#include "note_player.h"

#include <QDebug>
#include <QtQml/QQmlContext>

#include "src/apptest/task.h"
#include "src/apptest/task_runner.h"
#include "src/lib_app/cli_options.h"
#include "util-assert.h"

namespace heory
{
namespace apptesting
{
    NotePlayer::NotePlayer( const CliOptions* opts ) : m_opts( opts )
    {
    }

    NotePlayer::~NotePlayer() = default;

    void NotePlayer::ExportContextPropertiesToQml( QQmlEngine* engine )
    {
        engine->rootContext()->setContextProperty( "apptestNotePlayer", this );
    }

    // lowercase due to use from QML
    Q_INVOKABLE void NotePlayer::spoofAnIncomingExternalNote( const int midiNote )
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
        tests::RunTask( tests::Task::PlayBasic( midiNote ), m_opts->AmidiPortToken() );
    }

} // namespace apptesting
} // namespace heory
