//
// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
//
// https://github.com/pestophagous/
//
#include "resources.h"

#include <QDir>

#include "src/libstyles/resources.h"

// Q_INIT_RESOURCE cannot be called from inside a named namespace.  See:
// http://doc.qt.io/qt-5/qdir.html#Q_INIT_RESOURCE
static inline void init()
{
    Q_INIT_RESOURCE( libresources );
}

namespace heory
{
void initLibResources()
{
    init();
    heory::initLibStylesResources();

    // Any other qregister things we wish...
    // qRegisterMetaType<CustomType*>("CustomType*");
}

} // namespace heory
