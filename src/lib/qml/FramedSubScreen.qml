import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.14
import QtQuick.Layouts 1.14
import libstyles 1.0
import "./qmlbasics"

Rectangle {
  id: root

  // This default property means that you can simply nest other QML items inside
  // of a "FramedBreadcrumbedScreen{}" section and they will implicitly be
  // attached as data here. (also see https://stackoverflow.com/a/12772703)
  default property alias contents: placeholder.data

  readonly property int sideMargin_: 20
  readonly property int buttonWidth_: 50
  readonly property int buttonHeight_: 50

  color: Theme.neutralMediumDark

  signal gotoHome

  // The app may override, but leave (height,width) here for qmlscene
  height: 540
  width: 400

  Item {
    id: placeholder

    anchors.top: parent.top
    anchors.bottom: backButton.top
    anchors.left: parent.left
    anchors.right: parent.right
  }

  StyledButton {
    id: backButton
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 20
    anchors.horizontalCenter: parent.horizontalCenter

    height: 60
    width: 120

    text: "Back"
    onClicked: {
      root.gotoHome()
    }
  }
}
