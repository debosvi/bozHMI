
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "channel-http.h"

struct serveable {
    const char *urlpath;
    const char *mimetype;
}; 

static const struct serveable whitelist[] = {
    { "/favicon.ico", "image/x-icon" },
    { "/libwebsockets.org-logo.png", "image/png" },

    /* last one is the default served if no match */
    { "/test.html", "text/html" },
};

static const int nb_whitelist= (sizeof(whitelist) / sizeof(whitelist[0]) - 1);

int callback_http(struct libwebsocket_context *context,
        struct libwebsocket *wsi,
        enum libwebsocket_callback_reasons reason, void *user,
        void *in, size_t len) {

    char buf[256];
    char leaf_path[1024];
    int n=0, m=0;
    unsigned char *p=NULL;
    static unsigned char buffer[4096];
    struct stat stat_buf;
    struct per_session_data__http *pss =
            (struct per_session_data__http *)user;

    (void)len;
    
    switch (reason) {
    case LWS_CALLBACK_HTTP:

        /* check for the "send a big file by hand" example case */

        if (!strcmp((const char *)in, "/leaf.jpg")) {
            if (strlen(resource_path) > sizeof(leaf_path) - 10)
                return -1;
            sprintf(leaf_path, "%s/leaf.jpg", resource_path);

            /* well, let's demonstrate how to send the hard way */

            p = buffer;

            pss->fd = open(leaf_path, O_RDONLY);

            if (pss->fd < 0)
                return -1;

            fstat(pss->fd, &stat_buf);

            /*
             * we will send a big jpeg file, but it could be
             * anything.  Set the Content-Type: appropriately
             * so the browser knows what to do with it.
             */

            p += sprintf((char *)p,
                "HTTP/1.0 200 OK\x0d\x0a"
                "Server: libwebsockets\x0d\x0a"
                "Content-Type: image/jpeg\x0d\x0a"
                    "Content-Length: %u\x0d\x0a\x0d\x0a",
                    (unsigned int)stat_buf.st_size);

            /*
             * send the http headers...
             * this won't block since it's the first payload sent
             * on the connection since it was established
             * (too small for partial)
             */

            n = libwebsocket_write(wsi, buffer,
                   p - buffer, LWS_WRITE_HTTP);

            if (n < 0) {
                close(pss->fd);
                return -1;
            }
            /*
             * book us a LWS_CALLBACK_HTTP_WRITEABLE callback
             */
            libwebsocket_callback_on_writable(context, wsi);
            break;
        }

        /* if not, send a file the easy way */

        for (n = 0; n < (int)nb_whitelist; n++)
            if (in && strcmp((const char *)in, whitelist[n].urlpath) == 0)
                break;

        sprintf(buf, "%s%s", resource_path, whitelist[n].urlpath);

        if (libwebsockets_serve_http_file(context, wsi, buf, whitelist[n].mimetype))
            return -1; /* through completion or error, close the socket */

        /*
         * notice that the sending of the file completes asynchronously,
         * we'll get a LWS_CALLBACK_HTTP_FILE_COMPLETION callback when
         * it's done
         */

        break;

    case LWS_CALLBACK_HTTP_FILE_COMPLETION:
//      lwsl_info("LWS_CALLBACK_HTTP_FILE_COMPLETION seen\n");
        /* kill the connection after we sent one file */
        return -1;

    case LWS_CALLBACK_HTTP_WRITEABLE:
        /*
         * we can send more of whatever it is we were sending
         */

        do {
            n = read(pss->fd, buffer, sizeof buffer);
            /* problem reading, close conn */
            if (n < 0)
                goto bail;
            /* sent it all, close conn */
            if (n == 0)
                goto bail;
            /*
             * because it's HTTP and not websocket, don't need to take
             * care about pre and postamble
             */
            m = libwebsocket_write(wsi, buffer, n, LWS_WRITE_HTTP);
            if (m < 0)
                /* write failed, close conn */
                goto bail;
            if (m != n)
                /* partial write, adjust */
                lseek(pss->fd, m - n, SEEK_CUR);

        } while (!lws_send_pipe_choked(wsi));
        libwebsocket_callback_on_writable(context, wsi);
        break;

bail:
        close(pss->fd);
        return -1;

    /*
     * callback for confirming to continue with client IP appear in
     * protocol 0 callback since no websocket protocol has been agreed
     * yet.  You can just ignore this if you won't filter on client IP
     * since the default uhandled callback return is 0 meaning let the
     * connection continue.
     */

    case LWS_CALLBACK_FILTER_NETWORK_CONNECTION:
#if 0
        libwebsockets_get_peer_addresses(context, wsi, (int)(long)in, client_name,
                 sizeof(client_name), client_ip, sizeof(client_ip));

        fprintf(stderr, "Received network connect from %s (%s)\n",
                            client_name, client_ip);
#endif
        /* if we returned non-zero from here, we kill the connection */
        break;

    default:
        break;
    }

    return 0;
}
