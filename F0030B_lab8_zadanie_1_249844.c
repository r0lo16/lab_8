#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h>
 #include <unistd.h>
#include <time.h>


#define N 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (phnum + 4) % N 
#define RIGHT (phnum + 1) % N 
  
int obecny_stan[N]; 
int filozof[N] = { 0, 1, 2, 3, 4 }; 
  
sem_t mutex; 
sem_t S[N]; 

void test(int phnum) 
{ 
    if (obecny_stan[phnum] == HUNGRY 
        && obecny_stan[LEFT] != EATING 
        && obecny_stan[RIGHT] != EATING) { 
        // jedzenie
        obecny_stan[phnum] = EATING; 
  
        sleep(2); 
  
        printf("Filozof %d uruchamia fork %d i %d\n", 
                      phnum + 1, LEFT + 1, phnum + 1); 
  
        printf("Filozof %d is je\n", phnum + 1); 
  
        // sem_post(&S[phnum]) brak efektu
        // podczas pracy
        // tworzy głod filozofów
        // podczas wykonywania putfork 
        sem_post(&S[phnum]); 
    } 
}
void take_fork(int phnum) 
{ 
  
    sem_wait(&mutex); 
  
    // stwierdzenie głodu
    obecny_stan[phnum] = HUNGRY; 
  
    printf("Filozof %d jest glodny\n", phnum + 1); 
  
    // jedzenie jesli sasiad nie je
    test(phnum); 
  
    sem_post(&mutex); 
  
    // oczekiwanie na sygnał aby zjesc
    sem_wait(&S[phnum]); 
  
    sleep(1); 
} // odlozono jedzenie
void put_fork(int phnum) 
{ 
  
    sem_wait(&mutex); 
  
    // zaczynaja myslec
    obecny_stan[phnum] = THINKING; 
  
    printf("Filozof %d uruchamia fork %d i %d down\n", 
           phnum + 1, LEFT + 1, phnum + 1); 
    printf("Filozof %d  mysli\n", phnum + 1); 
  
    test(LEFT); 
    test(RIGHT); 
  
    sem_post(&mutex); 
} void* philospher(void* num) 
{ 
  
    while (1) { 
  
        int* i = num; 
  
        sleep(1); 
  
        take_fork(*i); 
  
        sleep(0); 
  
        put_fork(*i); 
    } 
} 
  
int main() 
{ 
  
    int i; 
    pthread_t thread_id[N]; 
  
    // semafory
    sem_init(&mutex, 0, 1); 
  
    for (i = 0; i < N; i++) 
  
        sem_init(&S[i], 0, 0); 
  
    for (i = 0; i < N; i++) { 
  
        // tworzy process filozofow
        pthread_create(&thread_id[i], NULL, 
                       philospher, &filozof[i]); 
  
        printf("Filozof %d  myśli\n", i + 1); 
    } 
  
    for (i = 0; i < N; i++) 
  
        pthread_join(thread_id[i], NULL); 
} 