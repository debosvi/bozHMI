import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

import "."
import "componentCreation.js" as MyScript

Window {
    visible: true
    width: 1024
    height: 768
    id: appWindow

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    AppIconsBar {
        id: appIconsBar
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.bottom: parent.bottom
        clip: true
    }

    Button {
        x: 300
        y: 100
        width: 100
        height: 50
        text: "add icon"
        onClicked: {
            if(appIconsBar.getCount()%2)
                appIconsBar.addElem("qrc:///resources/images/tux.svg");
            else
                appIconsBar.addElem("qrc:///resources/images/bsd_colors_logo.png");
        }
    }

    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }

   // Component.onCompleted: MyScript.createIconObjects();
}
