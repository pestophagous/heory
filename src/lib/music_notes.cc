#include "music_notes.h"

#include <QDebug>

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
    (void) engine;
}

} // namespace heory
