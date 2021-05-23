//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_APPTEST_NOTE_PLAYER_H
#define PROJECT_LIB_APPTEST_NOTE_PLAYER_H

#include <QtCore/QObject>
#include <QtQml/QQmlEngine>

#include <memory>

namespace heory
{
class CliOptions;

namespace apptesting
{
    class NotePlayer : public QObject
    {
        Q_OBJECT

        // clang-format off

        // Q_PROPERTY( QString
        //             READ
        //             NOTIFY  )
        // clang-format on

    public:
        explicit NotePlayer( const CliOptions* opts );
        ~NotePlayer() override;

        NotePlayer( const NotePlayer& ) = delete;
        NotePlayer& operator=( const NotePlayer& ) = delete;

        void ExportContextPropertiesToQml( QQmlEngine* engine );

        // lowercase due to use from QML
        Q_INVOKABLE void spoofAnIncomingExternalNote( int midiNote );

    private:
        const CliOptions* const m_opts;
    };

} // namespace apptesting
} // namespace heory

#endif // PROJECT_LIB_APPTEST_NOTE_PLAYER_H
