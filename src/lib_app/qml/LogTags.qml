// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
// https://github.com/pestophagous/
// -----------------------------------------------------------------------------
// Rationale for Singleton LoggingCategory(s) comes from qt docs:
// https://web.archive.org/web/20181016025119/https://doc.qt.io/qt-5/qml-qtqml-loggingcategory.html
// "Note: As the creation of objects is expensive, it is encouraged to put the
// needed LoggingCategory definitions into a singleton and import this where
// needed."
pragma Singleton

import QtQuick 2.12

Item {
  property alias guiTests: gui

  LoggingCategory {
    id: gui
    name: customLoggingCategories.guiTestingLogTag
    defaultLogLevel: LoggingCategory.Info
  }
}
