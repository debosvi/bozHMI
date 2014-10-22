// MyItem.qml
import QtQuick.Window 2.2
import QtQuick 2.0

Window {
    visible: true
    width: 100
    height: 100
    id: appWindow

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: msg.author
        anchors.centerIn: parent
        Component.onCompleted: {
            msg.author = "Jonah"  // invokes Message::setAuthor()
        }
    }

   // Component.onCompleted: MyScript.createIconObjects();
}
