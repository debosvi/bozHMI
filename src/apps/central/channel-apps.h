
#ifndef _BOZ_WS_CHANNEL_APPS_H_
#define _BOZ_WS_CHANNEL_APPS_H_

#include <libwebsockets.h>
#include "skarnet/genset.h"

#include "ws-apps.h"

typedef enum {
    BOZ_CENTRAL_APP_CLIENT_STATE_INIT,
    BOZ_CENTRAL_APP_CLIENT_STATE_HMI_DECLARATION,
    BOZ_CENTRAL_APP_CLIENT_STATE_LOGIN_RETURNED,
    BOZ_CENTRAL_APP_CLIENT_STATE_END_VALUE
} boz_central_app_client_state_t;

typedef enum {
    BOZ_CENTRAL_CLIENT_UNKNOWN = 0,
    BOZ_CENTRAL_CLIENT_HMIBROWSER,
    BOZ_CENTRAL_CLIENT_END
} boz_central_client_id_t;

typedef struct {
    char id[64];                /*!< X11 ID string. */
} boz_central_vidplayer_t;

typedef struct {
    boz_central_app_client_state_t state;
    boz_central_client_id_t id;
    struct libwebsocket *wsi;
    union {
        boz_central_vidplayer_t vid;
    } addins;
} boz_central_app_client_t;

typedef GENSETB_TYPE(boz_central_app_client_t, 32) boz_central_clients_array_t;

struct per_session_data__apps {
    int fd;
};

extern int callback_wsapps(struct libwebsocket_context *context,
                           struct libwebsocket *wsi,
                           enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len);

#endif                          // _BOZ_WS_CHANNEL_APPS_H_
