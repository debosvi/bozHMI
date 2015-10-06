
#ifndef _BOZ_WS_APPS_H_
#define _BOZ_WS_APPS_H_

#include <libwebsockets.h>

#ifndef CENTRAL_WS_PORT
    #warning "No CENTRAL_WS_PORT defined, use default"
    #define CENTRAL_WS_PORT 4444
#else
#endif

// websocket stuffs
enum wsapps_protocols_e {
    /* always first */
    PROTOCOL_HTTP = 0,

    PROTOCOL_APPS,

    /* always last */
    PROTOCOL_COUNT
};

extern struct libwebsocket_protocols wsapps_protocols[];

#include "channel-http.h"
#include "channel-apps.h"

// others stuffs
extern int force_exit;
extern char *resource_path;

extern void sighandler(int sig);


#endif // _BOZ_WS_APPS_H_
