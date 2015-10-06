
#include "ws-apps.h"

int force_exit = 0;

void sighandler(int sig) {
    (void)sig;
    force_exit = 1;
}