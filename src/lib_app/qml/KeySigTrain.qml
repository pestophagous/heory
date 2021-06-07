import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.14
import libstyles 1.0
import "./qmlbasics"

FramedSubScreen {
  id: root

  Item {
    id: subroot
    anchors.fill: parent

    ColumnLayout {
      id: theCol
      anchors.fill: parent
      spacing: 0

      Item {
        Layout.fillHeight: true
        Layout.minimumWidth: 1
        Layout.maximumWidth: Layout.minimumWidth
      }

      Item {
        Layout.minimumHeight: majMin.contentHeight * 1.8
        Layout.maximumHeight: Layout.minimumHeight
        Layout.minimumWidth: majMin.contentWidth * 1.8
        Layout.maximumWidth: Layout.minimumWidth
        Layout.alignment: Qt.AlignHCenter

        StyledLabel {
          id: majMin
          anchors.centerIn: parent
          text: keySigTrainerViewModel.tonalityLabel
        }

        DebugRectangle {
        }
      }

      ImageSvgHelper {
        id: theSvg
        Layout.minimumHeight: subroot.height * 0.4
        Layout.maximumHeight: Layout.minimumHeight
        Layout.minimumWidth: subroot.width
        Layout.maximumWidth: Layout.minimumWidth

        source: {
          if (keySigTrainerViewModel.svgFile.length > 0) {
            resourceHelper.imageSourcePrefix + keySigTrainerViewModel.svgFile
          } else {
            ""
          }
        }
        fillMode: Image.PreserveAspectFit
      }

      Item {
        Layout.minimumHeight: theSvg.height * 0.5
        Layout.maximumHeight: Layout.minimumHeight
        Layout.minimumWidth: subroot.width - (Layout.margins * 2)
        Layout.maximumWidth: Layout.minimumWidth
        Layout.alignment: Qt.AlignHCenter
        Layout.margins: 20

        Label {
          id: cueLabel
          anchors.fill: parent
          horizontalAlignment: Label.AlignHCenter

          text: keySigTrainerViewModel.progressCueLabel
          font: Theme.solidIconStretchToMaxFitFont
          fontSizeMode: Text.Fit

          function cancelTheCue() {
            console.log('Clearing the cue label')
            keySigTrainerViewModel.cancelCueLabel()
          }

          CustomTimeout {
            id: timeout
            callback: cueLabel.cancelTheCue
          }

          onTextChanged: {
            if (cueLabel.text.length > 0) {
              timeout.setTimeout(800)
            }
          }
        }
        DebugRectangle {
        }
      }

      Item {
        Layout.fillHeight: true
        Layout.minimumWidth: 1
        Layout.maximumWidth: Layout.minimumWidth
      }
    }

    DebugRectangle {
      toFill: theCol
    }
  }
}
