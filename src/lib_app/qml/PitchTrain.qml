import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.14
import libstyles 1.0
import "./qmlbasics"

FramedSubScreen {
  id: root

  StyledButton {
    anchors.centerIn: parent
    height: 60
    width: 120

    text: "Test"

    onClicked: {
      pitchTrainerViewModel.testing()
    }
  }
}
