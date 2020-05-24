#include "collection.h"

#include <QtQml/QQmlContext>

#include "src/lib/music_notes.h"
#include "util-assert.h"

namespace heory
{
namespace tests
{
    struct Collection::Impl
    {
        const QQmlApplicationEngine* engine;
    };

    Collection::Collection( const QQmlApplicationEngine* qmlapp ) : m_( new Impl )
    {
        m_->engine = qmlapp;
    }

    Collection::~Collection()
    {
        delete m_;
    }

    void Collection::Go()
    {
        QVariant vm = m_->engine->rootContext()->contextProperty( "pitchTrainerViewModel" );
        const QString variantTypeName( vm.typeName() );
        FASSERT( variantTypeName.contains( "QObject*" ),
            "this code operates on contextProperty(s) of object type" );

        QObject* obj = qvariant_cast<QObject*>( vm );
        PitchTrainerVM* trainer = dynamic_cast<PitchTrainerVM*>( obj );
        fprintf( stderr, "class: %s\n", obj->metaObject()->className() );
        fprintf( stderr, "after downcast: %p\n", reinterpret_cast<void*>( trainer ) );
    }

} // namespace tests
} // namespace heory
