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
  title: "Tester Keyboard"
  width: 400
  height: 540
  visible: true

  property int keyHeight_: 200
  property int keyWidth_: 80

  Item {
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.margins: 30

    Row {
      id: whiteKeyRow
      anchors.top: parent.top
      anchors.left: parent.left

      Repeater {
        model: [60, 62, 64, 65, 67, 69, 71, 72]

        Rectangle {
          color: 'white'
          border.color: 'red'
          border.width: 1
          height: root.keyHeight_
          width: root.keyWidth_
          MouseArea {
            anchors.fill: parent
            onClicked: {
              console.log(modelData)
              apptestNotePlayer.spoofAnIncomingExternalNote(modelData)
            }
          }
        }
      }
    }

    Row {
      anchors.top: whiteKeyRow.top
      anchors.left: whiteKeyRow.left
      anchors.leftMargin: root.keyWidth_ * 0.75

      Repeater {
        model: [61, 63, -1, 66, 68, 70, -1, -1]

        Item {
          height: 1
          width: root.keyWidth_

          Rectangle {
            visible: modelData >= 0
            anchors.top: parent.top
            anchors.left: parent.left

            color: 'yellow'
            border.color: 'blue'
            border.width: 1
            height: root.keyHeight_ * 0.5
            width: root.keyWidth_ * 0.5

            MouseArea {
              anchors.fill: parent
              onClicked: {
                console.log(modelData)
                apptestNotePlayer.spoofAnIncomingExternalNote(modelData)
              }
            }
          }
        }
      }
    }
  }
}
