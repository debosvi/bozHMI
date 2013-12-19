
#include "ws-apps.h"

const struct libwebsocket_protocols wsapps_protocols[] = {
    /* first protocol must always be HTTP handler */

    {
        "http-only",        /* name */
        callback_http,      /* callback */
        sizeof (struct per_session_data__http), /* per_session_data_size */
        0,          /* max frame size / rx buffer */
        0,
    },
    {
        "wsapps-protocol",
        callback_wsapps,
        sizeof(struct per_session_data__apps),
        10,
        0,
    },
    { NULL, NULL, 0, 0 } /* terminator */
};
