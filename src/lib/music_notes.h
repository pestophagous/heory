//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_LIB_MUSIC_NOTES_H
#define PROJECT_LIB_MUSIC_NOTES_H

#include <QtCore/QObject>
#include <QtQml/QQmlEngine>

#include <memory>

namespace heory
{
class FsynthWrapper;

class MusicNotes : public QObject
{
    Q_OBJECT

    // clang-format off

    // Q_PROPERTY( QString
    //             READ
    //             NOTIFY  )
    // clang-format on

public:
    explicit MusicNotes( FsynthWrapper* fsynth );
    ~MusicNotes() override;

    MusicNotes( const MusicNotes& ) = delete;
    MusicNotes& operator=( const MusicNotes& ) = delete;

    void ExportContextPropertiesToQml( QQmlEngine* engine );

private:
    FsynthWrapper* const m_fsynth;
};

} // namespace heory

#endif // PROJECT_LIB_MUSIC_NOTES_H
