import QtQuick 2.0

Rectangle {
    width: 100
    height: 100
    id: butState
    property alias icon: urlCurrent.source
    property url pictActive
    property url pictInactive
    property url pictError
    property url pictDisabled
    state: "disabled"

    Image {
        anchors.fill: parent
        id: urlCurrent
        fillMode: Image.PreserveAspectFit
        source: pictDisabled
    }

    states: [
        State {
            name: "disabled"
            PropertyChanges { target: butState; icon: pictDisabled }
        },
        State {
            name: "inactive"
            PropertyChanges { target: butState; icon: pictInactive }
        },
        State {
            name: "active"
            PropertyChanges { target: butState; icon: pictActive }
        },
        State {
            name: "error"
            PropertyChanges { target: butState; icon: pictError }
        }
    ]
}
