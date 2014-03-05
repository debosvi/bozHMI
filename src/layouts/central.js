
function central_msgreceive(msg) {
    console.log(msg.data);
    var obj = eval("(" + msg.data + ")");
    if (obj.type == "login") {
        $(document).trigger("rtd_login", obj);
    }
}

function central_events(intevent) {
    switch (intevent) {
    case 0:                    /* disconnection */
        console.log(central_connection.geturl() + ", central disconnected");
        break;
    case 1:                    /* connection */
        console.log(central_connection.geturl() + ", central connected");
        break;
    }
}
