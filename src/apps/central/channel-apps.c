
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "channel-apps.h"

int callback_wsapps(struct libwebsocket_context *context,
        struct libwebsocket *wsi,
        enum libwebsocket_callback_reasons reason, void *user,
        void *in, size_t len) {

    struct per_session_data__apps *pss =
            (struct per_session_data__apps *)user;

    (void)len;
    
    switch (reason) {

    default:
        break;
    }

    return 0;
}
