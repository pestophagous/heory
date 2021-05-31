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
class KeySignatureDrill;
class KeySignatureDrillGuiState;
class PitchTraining;
class Random;
class SoundIO_Interface;

class PitchTrainerVM : public QObject
{
    Q_OBJECT

public:
    explicit PitchTrainerVM( SoundIO_Interface* io, Random* random );
    ~PitchTrainerVM() override;

    Q_INVOKABLE void testing();
    Q_INVOKABLE void setActive( bool active );

private:
    std::unique_ptr<PitchTraining> m_training;
};

class KeySigVM : public QObject
{
    Q_OBJECT

    // clang-format off

    Q_PROPERTY( QString tonalityLabel
                READ GetTonalityLabel
                NOTIFY SignalAll )

    Q_PROPERTY( QString svgFile
                READ GetSvgFile
                NOTIFY SignalAll )

    Q_PROPERTY( QString progressCueLabel
                READ GetProgressCueLabel
                NOTIFY SignalAll )

    // clang-format on

public:
    explicit KeySigVM( SoundIO_Interface* io, Random* random );
    ~KeySigVM() override;

    Q_INVOKABLE void setActive( bool active );

    Q_INVOKABLE void cancelCueLabel();

    QString GetTonalityLabel() const;
    QString GetSvgFile() const;
    QString GetProgressCueLabel() const;

    void OnNewGuiState( KeySignatureDrillGuiState state );
signals:
    void SignalAll();

private:
    QString m_tonalityLabel;
    QString m_svgFile;
    QString m_progressCueLabel;

    std::unique_ptr<KeySignatureDrill> m_drill;
};

class MusicNotes : public QObject
{
    Q_OBJECT

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
    KeySigVM m_keySigVM;
};

} // namespace heory

#endif // PROJECT_LIB_MUSIC_NOTES_H
