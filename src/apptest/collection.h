//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_APP_GUI_TESTS_COLLECTION_H
#define PROJECT_APP_GUI_TESTS_COLLECTION_H

#include <QQmlApplicationEngine>

namespace heory
{
class CliOptions;
class QmlMessageInterceptor;
class Random;

namespace tests
{
    class Collection
    {
    public:
        explicit Collection( const QQmlEngine* qmlapp, Random* random,
            QmlMessageInterceptor* messageIntercept, const CliOptions* options );
        ~Collection();

        Collection( const Collection& ) = delete;
        Collection& operator=( const Collection& ) = delete;

        void Start();

        // Acts as a timer tick so that test work can make progress.
        // Return TRUE when all tests are done.
        bool PollForDoneness();

    private:
        struct Impl;
        friend struct Impl;
        Impl* m_ = nullptr;
    };

} // namespace tests
} // namespace heory

#endif // PROJECT_APP_GUI_TESTS_COLLECTION_H
