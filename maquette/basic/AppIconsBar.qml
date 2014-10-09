import QtQuick 2.0

Rectangle {
    width: 150
    border.color: "red"
    border.width: 1
    radius: 1

    ListModel {
        id: fruitModel
    }

    Component {
        id: fruitDelegate
        Rectangle {
            id: toto
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

    PathView {
        id: fruitView
        anchors.fill: parent
        model: fruitModel
        delegate: fruitDelegate
        path: Path {
            startX: 100; startY: 50
            PathArc {
                x: 100; y: height
                radiusX: 5; radiusY: height/2
                direction: PathArc.Counterclockwise
                useLargeArc: false
            }
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
