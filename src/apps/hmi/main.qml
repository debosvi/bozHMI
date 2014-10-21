import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

Window {
    visible: true
    width: 360
    height: 360

    signal message(string msg)

    Button {
        anchors.left: parent.left
        anchors.top: parent.top
        width: 200
        height: 50
        text: "send"
        onClicked: {
            console.log("clicked")
            message("toto is dead")
        }
    }


    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}
