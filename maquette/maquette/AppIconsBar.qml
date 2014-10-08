import QtQuick 2.0

Rectangle {
    width: 110
    border.color: "red"
    border.width: 1
    radius: 1

    ListModel {
        id: fruitModel

    }

    Component {
        id: fruitDelegate
        Row {
            spacing: 50
            Rectangle {
                border.color: "green"
                border.width: 1
                radius: 50
                width: 100
                height: 100
                Text {
                    x: parent.left
                    y: parent.top
                    text: name
                }
                Image {
                    anchors.fill: parent
                    source: url
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: fruitModel
        delegate: fruitDelegate
    }

    function addElem(url) {
        console.log("Click!")
        fruitModel.append( { name: "app" + fruitModel.count, url: url })
    }
}
