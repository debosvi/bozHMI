
#ifndef _BOZ_WS_CHANNEL_HTTP_H_
#define _BOZ_WS_CHANNEL_HTTP_H_

#include <libwebsockets.h>
#include "ws-apps.h"

struct per_session_data__http {
    int fd;
};

extern int callback_http(struct libwebsocket_context *context,
            struct libwebsocket *wsi,
            enum libwebsocket_callback_reasons reason,
            void *user, void *in, size_t len);

#endif // _BOZ_WS_CHANNEL_HHTP_H_
