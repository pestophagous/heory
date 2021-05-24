import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.14
import QtQuick.Controls.Universal 2.2
import libstyles 1.0

Timer {
  // https://stackoverflow.com/a/50224584/10278
  id: root
  property var callback

  function setTimeout(delayTimeMillis) {
    root.stop()
    root.interval = delayTimeMillis
    root.repeat = false
    root.start()
  }

  onTriggered: {
    console.log('onTriggered')
    root.callback()
  }
}
