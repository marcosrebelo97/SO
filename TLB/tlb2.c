#define _GNU_SOURCE
#ifndef __USE_GNU
#define __USE_GNU
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <sys/time.h>

double time_diff(struct timeval x, struct timeval y)
{
    double x_ms, y_ms, diff;

    x_ms = (double)x.tv_sec * 1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec * 1000000 + (double)y.tv_usec;

    diff = (double)y_ms - (double)x_ms;

    return diff;
}

int main(int argc, char *argv[])
{

    /*rodar na mesma CPU*/
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(cpu_set_t), &mask);

    int P, I, *v, salto, i, x;
    double tempo, total = 0;

    FILE *f = fopen(argv[1], "r");

    struct timeval inicio, fim;
    printf("NúmeroPáginas Tempo\n");

    while (fscanf(f, "%d %d", &P, &I) != EOF)
    {

        /*printf("%d %d\n", P, I);*/
        v = (int *)malloc(4096 * P);
        salto = 4096 / sizeof(int);

        for (i = 0; i < I; i++)
        {
            for (x = 0; x < (P * salto); x += salto)
            {
                gettimeofday(&inicio, NULL);
                v[x] = i;
                gettimeofday(&fim, NULL);
                tempo = (float)time_diff(inicio, fim);
                total += tempo;
            }
        }

        total /= I * P;
        printf("%d %.15lf\n", P, total);
        free(v);
        total = 0;
    }

    fclose(f);

    return 0;
}