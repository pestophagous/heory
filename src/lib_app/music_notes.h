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
class PitchTraining;
class Random;
class SoundIO_Interface;

class PitchTrainerVM : public QObject
{
    Q_OBJECT

    // clang-format off

    // Q_PROPERTY( QString
    //             READ
    //             NOTIFY  )
    // clang-format on

public:
    explicit PitchTrainerVM( SoundIO_Interface* io, Random* random );
    ~PitchTrainerVM() override;

    Q_INVOKABLE void testing();

private:
    std::unique_ptr<PitchTraining> m_training;
};

class MusicNotes : public QObject
{
    Q_OBJECT

    // clang-format off

    // Q_PROPERTY( QString
    //             READ
    //             NOTIFY  )
    // clang-format on

public:
    explicit MusicNotes( FsynthWrapper* fsynth, Random* random );
    ~MusicNotes() override;

    MusicNotes( const MusicNotes& ) = delete;
    MusicNotes& operator=( const MusicNotes& ) = delete;

    void ExportContextPropertiesToQml( QQmlEngine* engine );

    // lowercase due to use from QML
    Q_INVOKABLE void playTestNote();

private:
    FsynthWrapper* const m_fsynth;

    PitchTrainerVM m_pitchTrainerVM;
};

} // namespace heory

#endif // PROJECT_LIB_MUSIC_NOTES_H
