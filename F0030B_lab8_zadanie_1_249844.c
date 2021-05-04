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

void test(int phnum) 
{ 
    if (state[phnum] == HUNGRY 
        && state[LEFT] != EATING 
        && state[RIGHT] != EATING) { 
        // stwierdza ze je 
        state[phnum] = EATING; 
  
        sleep(2); 
  
        printf("Philosopher %d takes fork %d and %d\n", 
                      phnum + 1, LEFT + 1, phnum + 1); 
  
        printf("Philosopher %d is Eating\n", phnum + 1); 
  
        // sem_post(&S[phnum]) brak efektu
        // podczas pracy
        // tworzy głod filozofów
        // podczas wykonywania putfork 
        sem_post(&S[phnum]); 
    } 
} 