//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#ifndef PROJECT_UTIL_WRAP_TRACE_H
#define PROJECT_UTIL_WRAP_TRACE_H

#include <QCoreApplication>
#include <QDebug>
#include <QLoggingCategory>
#include <QMessageLogger>

#include <memory>
#include <stdlib.h> // for getenv

#include "src/util/null_stream.h"
#include "util-assert.h"

namespace
{
// The arguments have to be sent via preprocessor.
// We cannot un-macro-ify what Qt chose to macro-ify.
// https://stackoverflow.com/questions/6982179/opposite-of-c-preprocessor-stringification
#ifndef log_func_preprocessor_symbol
#    error you need to pound-define log_func_preprocessor_symbol when you include this header
#endif
#ifndef log_func_human_tag
#    error you need to pound-define log_func_human_tag when you include this header
#endif
Q_LOGGING_CATEGORY( log_func_preprocessor_symbol, log_func_human_tag )

class WrapQtTraceCategory
{
private:
    // Having 'lazy innards' lets the user statically create one
    // WrapQtTraceCategory at the top of the chosen CC file and not worry about
    // timing the creation until after the QCoreApplication is ready.
    class WrapQtTraceCategoryLazyInnards
    {
    public:
        explicit WrapQtTraceCategoryLazyInnards()
            : m_logger(
                  std::make_unique<QMessageLogger>( nullptr, 0, nullptr, log_func_human_tag ) )
            , m_dummyStreamSink( std::make_unique<QString>() )
            , m_nullStream( std::make_unique<heory::NullStream>( m_dummyStreamSink.get() ) )
        {
            FASSERT( QCoreApplication::instance(),
                "if you create this wrapper BEFORE the Qapp, "
                "the logic in this ctor for rules gets discarded when the Qapp is "
                "constructed" );

            if( !getenv( "QT_LOGGING_RULES" ) )
            {
                // In the ABSENSE of QT_LOGGING_RULES env var, we disable our mask.
                //
                // We expect to EXPLICITLY enable these traces by setting the
                // environment appropriately before launching the app. One way:
                //    QT_LOGGING_RULES="*=true;qt*=false;"
                const_cast<QLoggingCategory&>( log_func_preprocessor_symbol() )
                    .setEnabled( QtInfoMsg, false );
            }
        }

        QDebug stream()
        {
            // We initialized NullStream with m_dummyStreamSink as the ultimate
            // destination of all things logged. We never want to actually see
            // anything (that is the point when using NullStream), so we can
            // periodically clear the string sink to avoid it getting large.
            m_dummyStreamSink->clear();

            if( log_func_preprocessor_symbol().isInfoEnabled() )
            {
                return m_logger->info();
            }
            else
            {
                return *m_nullStream;
            }
        }

    private:
        std::unique_ptr<QMessageLogger> m_logger;
        std::unique_ptr<QString> m_dummyStreamSink;
        std::unique_ptr<heory::NullStream> m_nullStream;
    };

    WrapQtTraceCategoryLazyInnards* m_impl = nullptr;

public:
    ~WrapQtTraceCategory()
    {
        delete m_impl;
    }

    QDebug stream()
    {
        // Having 'lazy innards' lets the user statically create one
        // WrapQtTraceCategory at the top of the chosen CC file and not worry
        // about timing the creation until after the QCoreApplication is ready.
        if( !m_impl )
        {
            m_impl = new WrapQtTraceCategoryLazyInnards();
        }
        return m_impl->stream();
    }
};
}
#endif // PROJECT_UTIL_WRAP_TRACE_H
