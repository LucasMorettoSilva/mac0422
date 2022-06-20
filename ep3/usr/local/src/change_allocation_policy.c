#define _MINIX 1
#define _POSIX_SOURCE 1

#include <stdio.h>
#include <pwd.h>
#include <curses.h>
#include <timers.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <termcap.h>
#include <termios.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/ioc_tty.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>

#include <minix/ipc.h>
#include <minix/config.h>
#include <minix/type.h>
#include <minix/const.h>

#include "/usr/src/servers/is/inc.h"

#include "/usr/src/servers/pm/mproc.h"
#include "/usr/src/kernel/const.h"
#include "/usr/src/kernel/proc.h"


typedef int bool;
#define true 1
#define false 0

void process(char *cmd) {
    if (cmd == NULL) {
        printf("Error while processing: invalid algorithm syntax!\n");
        return;
    }

    if (strcmp(cmd, "first_fit") == 0)
        memalloc(FIRST_FIT);

    else if (strcmp(cmd, "worst_fir") == 0)
        memalloc(WORST_FIT);

    else if (strcmp(cmd, "best_fit") == 0)
        memalloc(BEST_FIT);

    else if (strcmp(cmd, "next_fit") == 0)
        memalloc(NEXT_FIT);

    else if (strcmp(cmd, "random_fit") == 0)
        memalloc(RANDOM_FIT);

    else {
        fprintf(stderr, "Error while processing: invalid algorithm!\n");
        exit(EXIT_FAILURE);
        return;
    }    
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error in main(): please specify one allocation algorithm\n");
    }

    process(argv[1]);

    return 0;
}
