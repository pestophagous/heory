#include "collection.h"

#include <QtQml/QQmlContext>

#include <algorithm>
#include <vector>

#include "src/apptest/interface.h"
#include "src/apptest/test_pitch_train.h"
#include "util-assert.h"

namespace heory
{
namespace tests
{
    struct Collection::Impl
    {
        const QQmlApplicationEngine* engine;
        Random* random;
        QmlMessageInterceptor* messageInterceptor;
        std::vector<std::unique_ptr<TestInterface>> tests;
        std::vector<std::unique_ptr<TestInterface>>::iterator testIter;
    };

    Collection::Collection( const QQmlApplicationEngine* qmlapp, Random* random,
        QmlMessageInterceptor* messageIntercept )
        : m_( new Impl )
    {
        m_->engine = qmlapp;
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
        ( *m_->testIter )->Go( m_->engine, m_->random, m_->messageInterceptor );
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
                ( *m_->testIter )->Go( m_->engine, m_->random, m_->messageInterceptor );
            }
        }
        return allDone;
    }

} // namespace tests
} // namespace heory
