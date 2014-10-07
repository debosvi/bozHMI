var component;
var appitem;

function createSpriteObjects() {
    component = Qt.createComponent("qrc:///AppItem.qml");
    if (component.status == Component.Ready)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation() {
    if (component.status == Component.Ready) {
        appitem = component.createObject(appWindow, {"x": 100, "y": 100});
        if (appitem == null) {
            // Error Handling
            console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
}
