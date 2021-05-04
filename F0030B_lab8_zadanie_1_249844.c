#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define THINNING 2
#define HUNGRY 1
#define EATTING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phum + 1) % N

int state[N];
int phil[N] = {0 ,1 ,2 ,3 ,4};

sem_t mutex;

sem_t S[N];


