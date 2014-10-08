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
            Rectangle {
               // anchors.left: parent.left

                border.color: "green"
                border.width: 1
                radius: 50
                width: 100
                height: 100
                Text {
                    text: name
                }
                Image {
                    anchors.fill: parent
                    anchors.margins: 5
                    source: url
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("click on:" + name)
                        fruitModel.remove(index);
                    }
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: fruitModel
        delegate: fruitDelegate
        addDisplaced: Transition {
                NumberAnimation { properties: "x,y"; duration: 1000 }
            }
    }

    function addElem(url) {
        console.log("addElem")
        fruitModel.append( { name: "app" + fruitModel.count, url: url })
    }
    function getCount() {
        console.log("getCount")
        return fruitModel.count;
    }
}
