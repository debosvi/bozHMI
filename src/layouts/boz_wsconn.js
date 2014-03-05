/**
 * @class boz_wsconn
 * @brief boz_wsconn is a class used to manage WebSocket connection.
 *
 * @fn boz_wsconn.open
 * @brief Opens the channel.
 * @param[in] address_port address and port.
 * @param[in] channel      websocket channel.
 * @param[in] msgevent     callback called when an event occurs.
 * @param[in] msgcallback  callback called when data comes up.
 * @param[in] secured      Indicates whether the connection must be secured or not.
 *
 * @fn boz_wsconn.close
 * @brief Closes the channel.
 *
 * @fn boz_wsconn.write
 * @brief Write data through the cnannel
 * @param[in] data         data to write
 *
 * @fn boz_wsconn.geturl
 * @brief Retuens the current url.
 */

function wsconn_url(url, secured) {
    if (secured == 0)
        return "ws://" + url;
    else
        return "wss://" + url;

}

/**
 * Connects the websocket.
 *
 */
function boz_wsconn_connect() {
    console.log("try connection URL:" + this.url + " CHANNEL:" + this.channel);
    if (typeof MozWebSocket != "undefined") {
        this.ws = new MozWebSocket(this.url, this.channel);
    } else {
        this.ws = new WebSocket(this.url, this.channel);
    }
    try {
        var wsconn = this;
        this.ws.onopen = function() {
            clearTimeout(wsconn.timer);
            wsconn.connected = true;
	    if (wsconn.msgevent)
                wsconn.msgevent(1);
        }
        this.ws.onmessage = function got_packet(msg) {
/*            console.log("onmessage: " + msg.data);*/
	    if (wsconn.msgcallback)
                wsconn.msgcallback(msg);
        }
        this.ws.onerror = function(error) {
            console.log("onerror: " + error);
        }
        this.ws.onclose = function() {
            console.log("onclose");
            timer = setTimeout(function() {
                               wsconn.connect();
                               }
                               , 2000);
	    if (wsconn.msgevent != null)
	  	    wsconn.msgevent(0);
            wsconn.connected = false;
        }
    }
    catch(exception) {
        alert('<p>Error' + exception);
    }

}

/**
 * Opens a new websocket and connects it.
 * \param[in] address_port        port of the websocket channel
 * \param[in] channel             name of the websocket channel
 * \param[in] msgevent            callback called on websocket events.
 * \param[in] msgcallback         callback called when a new msg is received.
 * \param[in] secured             0 if the websocket is not secured. 1 otherwise.
 */
function boz_wsconn_open(address_port, channel, msgevent, msgcallback, secured) {
    var timer;

    this.channel = channel;
    this.url = wsconn_url(address_port, secured);
    this.timer = null;
    this.msgevent = msgevent;
    this.msgcallback = msgcallback;

    this.connect();

    return 0;
}

/**
 * Closes the websocket connection.
 */
function boz_wsconn_close() {
    window.clearTimeout(this.timer);
    this.ws.close();
}

/**
 * Writes data over the websocket.
 */
function boz_wsconn_write(data) {
    if (this.ws == null) {
        console.log("write failed. No ws initialized");
        return;
    }
    if (this.connected == true) {
        this.ws.send(data);
    } else {
        console.log("write failed. WS not connected");
    }
}

/**
 * Returns the URL of the websocket.
 */
function boz_wsconn_geturl() {
    if (this.ws == null) {
        console.log("boz_wsconn_geturl: No ws initialized");
        return null;
    }

    return this.url;
}

/**
 * Constructor.
 */
function boz_wsconn() {
    if (typeof(_boz_wsconn_called) == 'undefined') {
        _boz_wsconn_called = true;
        boz_wsconn.ws = null;
	/**
	 * Timer used to manage re-connection.
	 */
        this.timer=null;
	/**
	 * Indicates whether the websocket is connected or not.
	 */
        this.connected=false;
        boz_wsconn.prototype.open = boz_wsconn_open;
        boz_wsconn.prototype.write = boz_wsconn_write;
        boz_wsconn.prototype.close = boz_wsconn_close;
        boz_wsconn.prototype.connect = boz_wsconn_connect;
        boz_wsconn.prototype.geturl = boz_wsconn_geturl;
    }
}


