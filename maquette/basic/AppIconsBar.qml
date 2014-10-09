import QtQuick 2.0

Rectangle {
    width: 100
    border.color: "red"
    border.width: 1
    radius: 1
    color: "black"

    ListModel {
        id: fruitModel
    }

    Component {
        id: fruitDelegate
        Rectangle {
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
                    // fruitModel.remove(index);
                    fruitView.currentIndex = index
                }
            }
        }
    }

    ListView {
        id: fruitView
        anchors.fill: parent
        model: fruitModel
        delegate: fruitDelegate
        highlight: Rectangle {
            color: "lightsteelblue"
            radius: 5
            opacity: 0.8
        }
    }

    function addElem(url) {
        console.log("addElem")
        fruitModel.append( { name: "app" + fruitModel.count, url: url, checked: false })
    }
    function getCount() {
        console.log("getCount")
        return fruitModel.count;
    }
}
