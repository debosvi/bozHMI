
#ifndef _BOZ_WS_CHANNEL_APPS_H_
#define _BOZ_WS_CHANNEL_APPS_H_

#include <libwebsockets.h>
#include "ws-apps.h"

struct per_session_data__apps {
    int fd;
};

extern int callback_wsapps(struct libwebsocket_context *context,
            struct libwebsocket *wsi,
            enum libwebsocket_callback_reasons reason,
            void *user, void *in, size_t len);

#endif // _BOZ_WS_CHANNEL_APPS_H_
