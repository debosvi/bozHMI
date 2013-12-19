#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

// #include <fcntl.h>
#include <assert.h>
#include <syslog.h>

#include <signal.h>

#include "ws-apps.h"

static struct option options[] = {
    { "help",   no_argument,        NULL, 'h' },
    { "debug",  required_argument,  NULL, 'd' },
    { "port",   required_argument,  NULL, 'p' },
    { "interface",  required_argument,  NULL, 'i' },
    { "closetest",  no_argument,        NULL, 'c' },
#ifndef LWS_NO_DAEMONIZE
    { "daemonize",  no_argument,        NULL, 'D' },
#endif
    { "resource_path", required_argument,       NULL, 'r' },
    { NULL, 0, 0, 0 }
};

#define LOCAL_RESOURCE_PATH INSTALL_DATADIR"/libwebsockets-test-server"
char *resource_path = LOCAL_RESOURCE_PATH;

int main(int argc, char **argv) {
    char cert_path[1024];
    char key_path[1024];
    int n = 0;
    int use_ssl = 0;
    struct libwebsocket_context *context=NULL;
    int opts = 0;
    char interface_name[128] = "";
    const char *iface = NULL;
#ifndef WIN32
    int syslog_options = LOG_PID | LOG_PERROR;
#endif
    struct lws_context_creation_info info;

    int debug_level = 7;
#ifndef LWS_NO_DAEMONIZE
    int daemonize = 0;
#endif

    memset(&info, 0, sizeof(struct lws_context_creation_info));
    info.port = 7681;

    while (n >= 0) {
        n = getopt_long(argc, argv, "ci:hsp:d:Dr:", options, NULL);
        if (n < 0)
            continue;
        switch (n) {
#ifndef LWS_NO_DAEMONIZE
        case 'D':
            daemonize = 1;
            #ifndef WIN32
            syslog_options &= ~LOG_PERROR;
            #endif
            break;
#endif
        case 'd':
            debug_level = atoi(optarg);
            break;
        case 's':
            use_ssl = 1;
            break;
        case 'p':
            info.port = atoi(optarg);
            break;
        case 'i':
            strncpy(interface_name, optarg, sizeof interface_name);
            interface_name[(sizeof interface_name) - 1] = '\0';
            iface = interface_name;
            break;
        case 'r':
            resource_path = optarg;
            printf("Setting resource path to \"%s\"\n", resource_path);
            break;
        case 'h':
            fprintf(stderr, "Usage: test-server "
                    "[--port=<p>] [--ssl] "
                    "[-d <log bitfield>] "
                    "[--resource_path <path>]\n");
            exit(1);
        default:
            break;
        }
    }

#if !defined(LWS_NO_DAEMONIZE) && !defined(WIN32)
    /* 
     * normally lock path would be /var/lock/lwsts or similar, to
     * simplify getting started without having to take care about
     * permissions or running as root, set to /tmp/.lwsts-lock
     */
    if (daemonize && lws_daemonize("/tmp/.lwsts-lock")) {
        fprintf(stderr, "Failed to daemonize\n");
        return 1;
    }
#endif

    signal(SIGINT, sighandler);

#ifndef WIN32
    /* we will only try to log things according to our debug_level */
    setlogmask(LOG_UPTO (LOG_DEBUG));
    openlog("lwsts", syslog_options, LOG_DAEMON);
#endif

    /* tell the library what debug level to emit and to send it to syslog */
    lws_set_log_level(debug_level, lwsl_emit_syslog);

    lwsl_notice("libwebsockets boz HMI websocket server - "
            "(C) Copyright 2013-2014 Vincent de RIBOU <belzo2005-dolphin@yahoo.fr> - "
                            "licensed MIT License (MIT)\n");

    info.iface = iface;
    info.protocols = (struct libwebsocket_protocols*)wsapps_protocols;

    if (!use_ssl) {
        info.ssl_cert_filepath = NULL;
        info.ssl_private_key_filepath = NULL;
    } else {
        if (strlen(resource_path) > sizeof(cert_path) - 32) {
            lwsl_err("resource path too long\n");
            return -1;
        }
        sprintf(cert_path, "%s/libwebsockets-test-server.pem",
                                resource_path);
        if (strlen(resource_path) > sizeof(key_path) - 32) {
            lwsl_err("resource path too long\n");
            return -1;
        }
        sprintf(key_path, "%s/libwebsockets-test-server.key.pem",
                                resource_path);

        info.ssl_cert_filepath = cert_path;
        info.ssl_private_key_filepath = key_path;
    }
    
    info.gid = -1;
    info.uid = -1;
    info.options = opts;

    context = libwebsocket_create_context(&info);
    if (context == NULL) {
        lwsl_err("libwebsocket init failed\n");
        return -1;
    }

    n = 0;
    while (n >= 0 && !force_exit) {
        /*
         * If libwebsockets sockets are all we care about,
         * you can use this api which takes care of the poll()
         * and looping through finding who needed service.
         *
         * If no socket needs service, it'll return anyway after
         * the number of ms in the second argument.
         */

        n = libwebsocket_service(context, 50);

    }

    libwebsocket_context_destroy(context);

    lwsl_notice("libwebsockets-test-server exited cleanly\n");

#ifndef WIN32
    closelog();
#endif

    return 0;
}