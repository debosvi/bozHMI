
#ifndef _BOZ_WS_APPS_H_
#define _BOZ_WS_APPS_H_

#include <libwebsockets.h>

// websocket stuffs
enum wsapps_protocols_e {
    /* always first */
    PROTOCOL_HTTP = 0,

    PROTOCOL_APPS,

    /* always last */
    PROTOCOL_COUNT
};

extern struct libwebsocket_protocols wsapps_protocols[];

struct per_session_data__http {
    int fd;
};

extern int callback_http(struct libwebsocket_context *context,
            struct libwebsocket *wsi,
            enum libwebsocket_callback_reasons reason,
            void *user, void *in, size_t len);

struct per_session_data__apps {
    int fd;
};

extern int callback_wsapps(struct libwebsocket_context *context,
            struct libwebsocket *wsi,
            enum libwebsocket_callback_reasons reason,
            void *user, void *in, size_t len);

// others stuffs
extern int force_exit;
extern char *resource_path;

extern void sighandler(int sig);


#endif // _BOZ_WS_APPS_H_
