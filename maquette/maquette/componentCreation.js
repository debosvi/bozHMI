var component;
var count=0;

function createIconObjects() {
    component = Qt.createComponent("qrc:///AppItem.qml");
    if (component.status == Component.Ready)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation() {
    var appitem;
    if (component.status == Component.Ready) {
        appitem = component.createObject(appIconsBar, {"x": 5, "y": 5+110*count});

        if (appitem == null) {
            // Error Handling
            console.log("Error creating object");
        }
        else
            count++;
    } else if (component.status == Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
}
