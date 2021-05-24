import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.14
import QtQuick.Controls.Universal 2.2
import libstyles 1.0

Label {
  id: root
  font: Theme.mediumFont

  color: Theme.neutralLight

  Component.onCompleted: {
    // when this was attempted using 'normal' property syntax, it OVERRODE
    // the choice of Theme.mediumFont!
    root.font.capitalization = Font.Capitalize
  }
}
