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

    void Collection::Go()
    {
        std::random_shuffle( m_->tests.begin(), m_->tests.end() );

        for( auto& test : m_->tests )
        {
            test->Go( m_->engine, m_->random, m_->messageInterceptor );
        }
    }

} // namespace tests
} // namespace heory
