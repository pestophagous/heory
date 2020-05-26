//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_GUI_TESTS_TASK_QUEUE_H
#define PROJECT_APP_GUI_TESTS_TASK_QUEUE_H

#include <QStringList>
#include <QtGlobal>

#include <deque>
#include <functional>
#include <memory>

#include "src/apptest/task.h"

namespace heory
{
class QmlMessageInterceptor;

namespace tests
{
    class TaskQueue
    {
    public:
        explicit TaskQueue(
            std::deque<Task>, const QStringList& logCategories, QmlMessageInterceptor* );

        // Acts as a timer tick so that queue can make progress.
        // Return TRUE when all tasks are done.
        bool PollForDoneness();

    private:
        using LogTeeFunctor
            = std::function<void( QtMsgType, const QMessageLogContext&, const QString& )>;

        void IncomingLog(
            QtMsgType type, const QMessageLogContext& context, const QString& message );

        const QStringList m_logCategories;
        std::deque<Task> m_tasks;
        std::shared_ptr<LogTeeFunctor> m_logSink;
    };
} // namespace tests
} // namespace heory

#endif // PROJECT_APP_GUI_TESTS_TASK_QUEUE_H
