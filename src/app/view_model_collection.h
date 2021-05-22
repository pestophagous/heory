//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_VIEW_MODEL_COLLECTION_H
#define PROJECT_APP_VIEW_MODEL_COLLECTION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include <memory>

namespace heory
{
class CliOptions;
class FsynthWrapper;
class EventFilter;
class GuiTests;
class LoggingTags;
class MusicNotes;
class QmlMessageInterceptor;
class Random;

class ViewModelCollection
{
public:
    explicit ViewModelCollection( bool skipTheOpts, const QGuiApplication& app );
    ~ViewModelCollection();

    ViewModelCollection( const ViewModelCollection& ) = delete;
    ViewModelCollection& operator=( const ViewModelCollection& ) = delete;

    void ExportContextPropertiesToQml( QQmlEngine* engine );

    void SetRootObject( QObject* object );

private:
    const std::unique_ptr<const CliOptions> m_opts;
    std::unique_ptr<EventFilter> m_eventFilter;
    std::unique_ptr<QmlMessageInterceptor> m_qmlLogger;
    std::unique_ptr<LoggingTags> m_logging;
    std::unique_ptr<FsynthWrapper> m_fsynth;
    std::unique_ptr<Random> m_random;

    std::unique_ptr<MusicNotes> m_musicNotes;

    std::unique_ptr<GuiTests> m_guiTests;
};

} // namespace heory

#endif // PROJECT_APP_VIEW_MODEL_COLLECTION_H
