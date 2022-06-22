#define _MINIX 1
#define _POSIX_SOURCE 1

#include <math.h>
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

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void printArray(Array *a) {
    int i = 0;
    printf("[");
    for (i = 0; i < a->used; ++i) {
        printf("%d,", a->array[i]);
    }
    printf("]\n");
}

float meanArray(Array *a) {
    float arrayMean = 0.0;
    int i = 0;
    
    for (i = 0; i < a->used; ++i) {
        arrayMean += a->array[i];
    }
    
    return arrayMean / a->used;
}

float stdevArray(Array *a) {
    float arrayStdev = 0.0;
    int i = 0;

    float arrayMean = meanArray(a);

    for (i = 0; i < a->used; ++i) {
        arrayStdev += pow(a->array[i] - arrayMean, 2);
    }

    return sqrt(arrayStdev / a->used);
}

int medianArray(Array *a) {
    qsort(a->array, a->used, sizeof(int), cmpfunc);
    return a->array[a->used / 2];
}

int print_memory(struct pm_mem_info *pmi) {
    Array holes;

    float media, desvio;

    int h, mediana;

    initArray(&holes, _NR_HOLES);
    
    for(h = 0; h < _NR_HOLES; h++) {
            if(pmi->pmi_holes[h].h_base && pmi->pmi_holes[h].h_len) {
                    int bytes;
                    bytes = pmi->pmi_holes[h].h_len << CLICK_SHIFT;
                    insertArray(&holes, bytes / 1024);
            }
    }

    media = meanArray(&holes);
    desvio = stdevArray(&holes);
    mediana = medianArray(&holes);

    printf("%d\t%.2f\t%.2f\t%d\n", holes.used, media, desvio, mediana);

    freeArray(&holes);

    return 1;
}

int main(int argc, char *argv[]) {
    static struct pm_mem_info pmi;

    printf("qtd. buracos\tmedia (KB)\tdesvio padrao (KB)\tmediana (KB)\n");

    while (1) {
        if (getsysinfo(PM_PROC_NR, SI_MEM_ALLOC, &pmi) != OK) {
            printf("Falha ao obter a lista de buracos.\n");
            exit(EXIT_FAILURE);
        }

        print_memory(&pmi);
        sleep(1);
    }
}
