import QtQuick 2.0

Rectangle {
    width: 100
    height: 100

    Image {
        source: "qrc:///resources/images/tux.svg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }
}
