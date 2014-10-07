import QtQuick 2.0

Rectangle {
    width: 100
    height: 100
    border.color: "green"
    border.width: 1
    radius: 1

    Image {
        source: "qrc:///resources/images/tux.svg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }
}
