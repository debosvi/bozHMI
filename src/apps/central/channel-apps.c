
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "nxjson.h"
#include "channel-apps.h"

#define BOZLOG(...) fprintf(stderr, __VA_ARGS__)

static boz_central_clients_array_t boz_central_clients_g;

int callback_wsapps(struct libwebsocket_context *context,
                    struct libwebsocket *wsi,
                    enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len) {

    int *p_idx = (int *) user;
    struct per_session_data__apps *pss = (struct per_session_data__apps *) user;

    (void) len;
    BOZLOG("%s: enter\n", __FUNCTION__);

    switch (reason) {
    case LWS_CALLBACK_PROTOCOL_INIT:
        BOZLOG("%s: LWS_CALLBACK_PROTOCOL_INIT received\n", __FUNCTION__);
        {
            GENSETB_init(boz_central_app_client_t, &boz_central_clients_g, 32);
        }
        break;

    case LWS_CALLBACK_ESTABLISHED:
        BOZLOG("%s: LWS_CALLBACK_ESTABLISHED received\n", __FUNCTION__);
        {
            unsigned int new = -1;
            boz_central_app_client_t *p_data = NULL;

            new = gensetb_new(&boz_central_clients_g);
            p_data = gensetb_p(boz_central_app_client_t, &boz_central_clients_g, new);
            if (!p_data) {
                BOZLOG("%s: bad idx(%d) LWS_CALLBACK_ESTABLISHED\n", __FUNCTION__, new);
                (*p_idx) = -1;
            }
            else {
                p_data->state = BOZ_CENTRAL_APP_CLIENT_STATE_INIT;
                p_data->id = BOZ_CENTRAL_CLIENT_UNKNOWN;
                p_data->wsi = wsi;
                // printf("WSI: %p\n", wsi);
                (*p_idx) = (int) new;
            }
        }
        break;

    case LWS_CALLBACK_CLOSED:
        BOZLOG("%s: LWS_CALLBACK_CLOSED received\n", __FUNCTION__);
        {
            gensetb_delete(&boz_central_clients_g, *p_idx);
        }
        break;

    case LWS_CALLBACK_RECEIVE:
        BOZLOG("%s: LWS_CALLBACK_RECEIVE received\n", __FUNCTION__);
        {
            boz_central_app_client_t *p_data=gensetb_p(boz_central_app_client_t, &boz_central_clients_g, *p_idx);
            char *buf = (char *) in;
            const nx_json *root_json = nx_json_parse_utf8(buf);

            if (!root_json) {
                BOZLOG("%s: malformed JSON buffer (%s)\n", __FUNCTION__, buf);
                goto purge_receive;
            }

            const nx_json *cmd_json = nx_json_get(root_json, "command");
            if (!cmd_json) {
                BOZLOG("%s: not compliant to \"command\" field JSON buffer (%s)\n", __FUNCTION__, buf);
                goto purge_receive;
            }

            if (!cmd_json->text_value) {
                BOZLOG("%s: \"command\" field invalid \n", __FUNCTION__);
                goto purge_receive;
            }
            
            if ((strlen(cmd_json->text_value) == 18) && !strncmp(cmd_json->text_value, "client_recognition", 18)) {
            }
            else {
                BOZLOG("%s: \"command\" field not known (%s)\n", __FUNCTION__, cmd_json->text_value);
                p_data->id = BOZ_CENTRAL_CLIENT_UNKNOWN;
                goto purge_receive;
            }

            const nx_json *name_json = nx_json_get(root_json, "command.data.name");
            if (!name_json) {
                BOZLOG("%s: not compliant to \"command.data.name\" field JSON buffer (%s)\n", __FUNCTION__, buf);
                goto purge_receive;
            }

            if (!name_json->text_value) {
                BOZLOG("%s: \"command.data.name\" field invalid \n", __FUNCTION__);
                goto purge_receive;
            }
            
            if ((strlen(name_json->text_value) == 14) && !strncmp(name_json->text_value, "boz-hmibrowser", 14)) {
                BOZLOG("%s: register new HMI browser\n", __FUNCTION__);
                p_data->id = BOZ_CENTRAL_CLIENT_HMIBROWSER;
            }
            else {
                BOZLOG("%s: \"command.data.name\" field not known (%s)\n", __FUNCTION__, name_json->text_value);
                p_data->id = BOZ_CENTRAL_CLIENT_UNKNOWN;
                goto purge_receive;
            }

purge_receive:
            if (root_json)
                nx_json_free(root_json);
        }
        break;

    case LWS_CALLBACK_PROTOCOL_DESTROY:
        BOZLOG("%s: LWS_CALLBACK_PROTOCOL_DESTROY received\n", __FUNCTION__);
        break;

    default:
        BOZLOG("%s: not managed reason (%d) received\n", __FUNCTION__, reason);
        break;
    }

    BOZLOG("%s: exit\n", __FUNCTION__);
    return 0;
}
