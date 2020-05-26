#include "task_queue.h"

#include <functional>
#include <memory>

#include "src/apptest/task_runner.h"
#include "src/util/qml_message_interceptor.h"
#include "util-assert.h"

namespace heory
{
namespace tests
{
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;

    TaskQueue::TaskQueue( std::deque<Task> tasks, const QStringList& logCategories,
        QmlMessageInterceptor* messageIntercept )
        : m_logCategories( logCategories ), m_tasks( tasks )
    {
        m_logSink = std::make_shared<LogTeeFunctor>(
            std::bind( &TaskQueue::IncomingLog, this, _1, _2, _3 ) );
        messageIntercept->AddMessageSink( m_logSink );
    }

    // Acts as a timer tick so that queue can make progress.
    // Return TRUE when all tasks are done.
    bool TaskQueue::PollForDoneness()
    {
        const bool done = m_tasks.empty();
        if( done )
        {
            m_logSink.reset(); // stop spying on the log ASAP. (just to unburden the message
                               // interceptor)
        }
        return done;
    }

    void TaskQueue::IncomingLog(
        QtMsgType, const QMessageLogContext& context, const QString& message )
    {
        FASSERT( m_tasks.empty() || m_tasks.front().type == TaskType::LogRead,
            "front of deque should always have a 'log' item (or else be empty)" );

        if( m_tasks.empty() )
        {
            return;
        }

        if( context.category && m_logCategories.contains( QString( context.category ) ) )
        {
            // if front 'log' item matches:
            //    burn through any actions to get to next log item
            if( m_tasks.front().IsLogMatch( message ) )
            {
                m_tasks.pop_front();
                while( ( !m_tasks.empty() ) && m_tasks.front().IsActionable() )
                {
                    RunTask( m_tasks.front() );
                    m_tasks.pop_front();
                }
            }
        }
    }

} // namespace tests
} // namespace heory
