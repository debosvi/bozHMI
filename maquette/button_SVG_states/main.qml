import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.1

import "components" as MyComponents

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

    Column {
        anchors.top: parent.top
        anchors.left: parent.left
        MyComponents.ButStates {
            id: myBut
            border { width: 1; color: "red" }
            pictActive: "qrc:///bouton_plus_active.svg"
            pictInactive: "qrc:///bouton_plus_inactive.svg"
            pictDisabled: "qrc:///bouton_plus_off.svg"
            pictError: "qrc:///bouton_plus_out.svg"
        }
        MyComponents.ButStates {
            id: myBut1
            width: 50
            height: 150
            border { width: 1; color: "red" }
            pictActive: "qrc:///bouton_plus_active.svg"
            pictInactive: "qrc:///bouton_plus_inactive.svg"
            pictDisabled: "qrc:///bouton_plus_off.svg"
            pictError: "qrc:///bouton_plus_out.svg"
        }
    }

    Column {
        anchors.top: parent.top
        anchors.right: parent.right
        Button {
            id: bActive
            text: "activate"
        }
        Button {
            id: bInactive
            text: "inactivate"
        }
        Button {
            id: bDisabled
            text: "disable"
        }
        Button {
            id: bError
            text: "error"
        }
    }
}
