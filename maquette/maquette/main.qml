import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    visible: true
    width: 360
    height: 360

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Image {
        source: "qrc:///resources/images/tux.svg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}
