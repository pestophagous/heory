import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.14
import QtQuick.Controls.Universal 2.2
import libstyles 1.0

Item {
  id: root

  signal clicked

  // 0 is "dark button"
  // 1 is "bright button"
  property int buttonColorChoice: 0

  property alias text: actualButton.text

  property bool shrinkImageToFit: true // instantiation site can override this
  property alias textFont: textLabel.font
  property alias labelWidth: textLabel.contentWidth

  property int statusAlertSetting: 0 // override to show icon

  property string optionalImageSource: ""

  Button {
    id: actualButton
    anchors.fill: parent

    onClicked: {
      root.clicked()
    }

    readonly property int imageMargin_: height * .25

    // Uncomment (temporarily) for qmlscene work. Otherwise we got too much false security in layouts from these:
    // width: 120
    // height: 80
    text: "" // to be set at instantiation site

    // 0 is "dark button"
    // 1 is "bright button"
    function getTextColor(isPressed) {
      // You might be tempted to just return the inverse from getButtonColor but
      // that DOES NOT HOLD in all cases.
      if (root.buttonColorChoice == 0) {
        return Theme.neutralLight
      } else {
        console.warn('invalid buttonColorChoice', root.buttonColorChoice)
        return Theme.neutralLight
      }
    }

    function getButtonColor(isPressed) {
      // You might be tempted to just return the inverse from getTextColor but
      // that DOES NOT HOLD in all cases.
      if (root.buttonColorChoice == 0) {
        return isPressed ? Theme.primaryLight : Theme.primaryMediumLight
      } else {
        console.warn('invalid buttonColorChoice', root.buttonColorChoice)
        return isPressed ? Theme.primaryMediumLight : Theme.primaryMedium
      }
    }

    background: Rectangle {
      id: buttonBg
      color: actualButton.getButtonColor(actualButton.down)
      radius: height * 0.25

      ImageSvgHelper {
        visible: root.optionalImageSource != ""
        anchors.fill: parent
        anchors.margins: actualButton.imageMargin_
        source: root.optionalImageSource
        fillMode: root.shrinkImageToFit ? Image.PreserveAspectFit : Image.Pad
      }

      Rectangle {
        readonly property int sizing_: 30
        visible: root.statusAlertSetting != 0

        anchors.right: buttonBg.right
        anchors.top: buttonBg.top
        anchors.topMargin: -sizing_ * .35
        anchors.rightMargin: -1 * (buttonBg.width * 0.03)

        height: sizing_
        width: sizing_
        radius: sizing_
        color: Theme.accentOtherDark

        Label {
          anchors.centerIn: parent
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
          font: Theme.mediumFont
          color: Theme.neutralLight
          text: "?"
        }
      }
    }

    contentItem: Label {
      id: textLabel
      text: root.text
      font: Theme.mediumFont
      color: actualButton.getTextColor(actualButton.down)
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
    }
  }
  DropShadow {
    id: shadow
    source: actualButton
    visible: !actualButton.down
    anchors.fill: actualButton
    color: "#54000000"
    horizontalOffset: 0
    verticalOffset: 6
    radius: 14
    samples: 29
    spread: 0.1
  }
}
