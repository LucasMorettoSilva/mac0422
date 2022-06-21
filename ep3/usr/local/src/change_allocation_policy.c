#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void process(char *cmd) {
    if (cmd == NULL) {
        printf("Error while processing: invalid algorithm syntax!\n");
        return;
    }

    if (strcmp(cmd, "first_fit") == 0)
        memalloc(FIRST_FIT);

    else if (strcmp(cmd, "worst_fit") == 0)
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
