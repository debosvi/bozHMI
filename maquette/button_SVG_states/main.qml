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
            pictActive: "qrc:///images/bouton_plus_active.svg"
            pictInactive: "qrc:///images/bouton_plus_inactive.svg"
            pictDisabled: "qrc:///images/bouton_plus_off.svg"
            pictError: "qrc:///images/bouton_plus_out.svg"
        }
        MyComponents.ButStates {
            id: myBut1
            width: 50
            height: 150
            border { width: 1; color: "red" }
            pictActive: "qrc:///images/bouton_plus_active.svg"
            pictInactive: "qrc:///images/bouton_plus_inactive.svg"
            pictDisabled: "qrc:///images/bouton_plus_off.svg"
            pictError: "qrc:///images/bouton_plus_out.svg"
        }
    }

    Column {
        anchors.top: parent.top
        anchors.right: parent.right
        Button {
            id: bActive
            text: "activate"
            onClicked: myBut.state = 'active'
        }
        Button {
            id: bInactive
            text: "inactivate"
            onClicked: myBut.state = 'inactive'
        }
        Button {
            id: bDisabled
            text: "disable"
            onClicked: myBut.state = 'disabled'
        }
        Button {
            id: bError
            text: "error"
            onClicked: myBut.state = 'error'
        }
    }
}
