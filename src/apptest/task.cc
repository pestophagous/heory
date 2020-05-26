#include "task.h"

namespace heory
{
namespace tests
{
    Task::Task( TaskType t, QString logText, int midi )
        : type( t ), expectedLogText( logText ), midiPitch( midi )
    {
    }
    /*static*/ Task Task::Log( QString text )
    {
        return Task( TaskType::LogRead, text, -1 );
    }

    /*static*/ Task Task::PlayBasic( int midi )
    {
        return Task( TaskType::PlayNoteBasic, "", midi );
    }

    bool Task::IsLogMatch( const QString& logLine ) const
    {
        return this->type == TaskType::LogRead && logLine.contains( this->expectedLogText );
    }

    bool Task::IsActionable() const
    {
        // currently the only action type is PlayNoteBasic, but that could change
        return this->type == TaskType::PlayNoteBasic;
    }
} // namespace tests
} // namespace heory
