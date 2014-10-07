import QtQuick 2.3
import QtQuick.Window 2.2
import "componentCreation.js" as MyScript

Window {
    visible: true
    width: 360
    height: 360
    id: appWindow

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

    Component.onCompleted: MyScript.createSpriteObjects();
}
