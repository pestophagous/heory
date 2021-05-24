import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.14
import libstyles 1.0
import "./qmlbasics"

ColumnLayout {
  id: root

  signal gotoPitchTrain
  signal gotoKeySigTrain

  readonly property int buttonHeight_: 60
  readonly property int buttonWidth_: 135

  StyledButton {
    Layout.alignment: Qt.AlignHCenter
    Layout.minimumHeight: root.buttonHeight_
    Layout.maximumHeight: Layout.minimumHeight
    Layout.minimumWidth: root.buttonWidth_
    Layout.maximumWidth: Layout.minimumWidth

    text: "Pitch Train"

    onClicked: {
      root.gotoPitchTrain()
    }
  }

  StyledButton {
    Layout.alignment: Qt.AlignHCenter
    Layout.minimumHeight: root.buttonHeight_
    Layout.maximumHeight: Layout.minimumHeight
    Layout.minimumWidth: root.buttonWidth_ * 2
    Layout.maximumWidth: Layout.minimumWidth

    text: "Key Signature Reading"

    onClicked: {
      root.gotoKeySigTrain()
    }
  }

  StyledButton {
    Layout.alignment: Qt.AlignHCenter
    Layout.minimumHeight: root.buttonHeight_
    Layout.maximumHeight: Layout.minimumHeight
    Layout.minimumWidth: root.buttonWidth_
    Layout.maximumWidth: Layout.minimumWidth

    text: "TBD"

    onClicked: {
      console.log('clicked')
    }
  }
}
