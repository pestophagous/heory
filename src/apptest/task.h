//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_GUI_TESTS_TASK_H
#define PROJECT_APP_GUI_TESTS_TASK_H

#include <QString>

namespace heory
{
namespace tests
{
    enum class TaskType
    {
        LogRead,
        PlayNoteBasic,
    };

    struct Task
    {
        static Task Log( QString );
        static Task PlayBasic( int );

        const TaskType type;
        const QString expectedLogText;
        const int midiPitch;

        bool IsLogMatch( const QString& logLine ) const;
        bool IsActionable() const;

    private:
        Task( TaskType, QString, int );
    };

} // namespace tests
} // namespace heory

#endif // PROJECT_APP_GUI_TESTS_TASK_H
