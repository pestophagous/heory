// Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
// See LICENSE.txt
// https://github.com/pestophagous/
import QtGraphicalEffects 1.12
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Universal 2.2
import QtQuick.Layouts 1.14
import libstyles 1.0
import "./qmlbasics"

ApplicationWindow {
  id: root
  title: "Heory"
  width: 400
  height: 540
  visible: true

  Component.onCompleted: {
    // Don't mess with 'guiTests' log statements, or you risk breaking a test.
    console.log(LogTags.guiTests, "ApplicationWindow onCompleted")
  }

  Rectangle {
    color: Theme.neutralDark
    anchors.fill: parent

    Item {
      id: front
      anchors.top: parent.top
      anchors.bottom: version.top
      anchors.left: parent.left
      anchors.right: parent.right
      anchors.margins: 15

      property int whichScreen: 0

      MainMenu {
        anchors.fill: parent
        visible: front.whichScreen == 0
        onGotoPitchTrain: {
          front.whichScreen = 1
        }
      }

      PitchTrain {
        id: pt
        anchors.fill: parent
        visible: front.whichScreen == 1
        onGotoHome: {
          front.whichScreen = 0
        }
        onVisibleChanged: {
          pitchTrainerViewModel.setActive(pt.visible)
        }
      }
    }

    VersionLabel {
      id: version
      anchors.bottom: parent.bottom
      anchors.bottomMargin: 20
      anchors.horizontalCenter: parent.horizontalCenter
    }
  }
}
