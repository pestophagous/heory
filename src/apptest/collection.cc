#ifndef HEORY_APPTEST
#    include "collection_inert.cc"
#else //////////////////////////////////////////////////////////////////////////

#    include "collection.h"

#    include <QtQml/QQmlContext>

#    include <algorithm>
#    include <vector>

#    include "src/apptest/test_interface.h"
#    include "src/apptest/test_pitch_train.h"
#    include "util-assert.h"

namespace heory
{
namespace tests
{
    struct Collection::Impl
    {
        const QQmlEngine* engine;
        const CliOptions* options;
        Random* random;
        QmlMessageInterceptor* messageInterceptor;
        std::vector<std::unique_ptr<TestInterface>> tests;
        std::vector<std::unique_ptr<TestInterface>>::iterator testIter;
    };

    Collection::Collection( const QQmlEngine* qmlapp, Random* random,
        QmlMessageInterceptor* messageIntercept, const CliOptions* opts )
        : m_( new Impl )
    {
        m_->engine = qmlapp;
        m_->options = opts;
        m_->random = random;
        m_->messageInterceptor = messageIntercept;

        m_->tests.push_back( std::make_unique<TestPitchTrain>() );
    }

    Collection::~Collection()
    {
        delete m_;
    }

    void Collection::Start()
    {
        FASSERT( !m_->tests.empty(), "let us always be sure to have some tests here" );
        std::random_shuffle( m_->tests.begin(), m_->tests.end() );

        m_->testIter = m_->tests.begin();
        // TODO: put a hard cap on runtime of each test.
        // TODO: if a test 'times out' (fails to end successfully in time limit), then
        // choose a way to report this. (it could be that QT_LOGGING_RULES are not set right)
        ( *m_->testIter )->Go( m_->engine, m_->random, m_->messageInterceptor, m_->options );
    }

    // Acts as a timer tick so that test work can make progress.
    // Return TRUE when all tests are done.
    bool Collection::PollForDoneness()
    {
        bool allDone = false;
        const bool done = ( *m_->testIter )->PollForDoneness();
        if( done )
        {
            m_->testIter++;
            if( m_->testIter == m_->tests.end() )
            {
                allDone = true;
            }
            else
            {
                ( *m_->testIter )
                    ->Go( m_->engine, m_->random, m_->messageInterceptor, m_->options );
            }
        }
        return allDone;
    }

} // namespace tests
} // namespace heory

#endif // #ifndef HEORY_APPTEST
