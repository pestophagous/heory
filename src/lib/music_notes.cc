#include "music_notes.h"

#include <QDebug>
#include <QtQml/QQmlContext>

#include "src/lib/fsynth.h"
#include "util-assert.h"

namespace heory
{
MusicNotes::MusicNotes( FsynthWrapper* fsynth )
    : m_fsynth( fsynth )
{
}

MusicNotes::~MusicNotes() = default;

void MusicNotes::ExportContextPropertiesToQml( QQmlEngine* engine )
{
    engine->rootContext()->setContextProperty( "musicNotesViewModel", this );
}

void MusicNotes::playTestNote()
{
    m_fsynth->PlayNote();
}

} // namespace heory
