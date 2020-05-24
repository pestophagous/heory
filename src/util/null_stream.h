#ifndef PROJECT_UTIL_NULL_STREAM_H
#define PROJECT_UTIL_NULL_STREAM_H

#include <QDebug>

namespace heory
{
class NullStream : public QDebug
{
public:
    NullStream( const QDebug& base ) : QDebug( base )
    {
    }

    ~NullStream();

    inline NullStream& operator<<( QChar )
    {
        return *this;
    }
    inline NullStream& operator<<( bool )
    {
        return *this;
    }
    inline NullStream& operator<<( char )
    {
        return *this;
    }
    inline NullStream& operator<<( signed short )
    {
        return *this;
    }
    inline NullStream& operator<<( unsigned short )
    {
        return *this;
    }
    inline NullStream& operator<<( signed int )
    {
        return *this;
    }
    inline NullStream& operator<<( unsigned int )
    {
        return *this;
    }
    inline NullStream& operator<<( signed long )
    {
        return *this;
    }
    inline NullStream& operator<<( unsigned long )
    {
        return *this;
    }
    inline NullStream& operator<<( qint64 )
    {
        return *this;
    }
    inline NullStream& operator<<( quint64 )
    {
        return *this;
    }
    inline NullStream& operator<<( float )
    {
        return *this;
    }
    inline NullStream& operator<<( double )
    {
        return *this;
    }
    inline NullStream& operator<<( const char* )
    {
        return *this;
    }
    inline NullStream& operator<<( const QString& )
    {
        return *this;
    }
    inline NullStream& operator<<( const QStringRef& )
    {
        return *this;
    }
    inline NullStream& operator<<( const QLatin1String& )
    {
        return *this;
    }
    inline NullStream& operator<<( const QByteArray& )
    {
        return *this;
    }
    inline NullStream& operator<<( const void* )
    {
        return *this;
    }
    inline NullStream& operator<<( QTextStreamFunction )
    {
        return *this;
    }
    inline NullStream& operator<<( QTextStreamManipulator )
    {
        return *this;
    }
#ifndef QT_NO_DEBUG_STREAM
    inline NullStream& operator<<( const QUrl& )
    {
        return *this;
    }
#endif

private:
};

} // namespace heory

#endif // PROJECT_UTIL_NULL_STREAM_H
