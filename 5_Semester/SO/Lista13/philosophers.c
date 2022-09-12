#include "csapp.h"

static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

static void randsleep(void) {
  usleep(rand() % 5000 + 5000);
}

#define N 50

static pthread_t td[N];
static sem_t forks[N];
/* TODO: If you need extra shared state, define it here. */
static sem_t free_chairs;

void *philosopher(void *id) {
  int right = (intptr_t)id;
  int left = right == 0 ? N - 1 : right - 1;

  for (;;) {
    /* Think */
    printf("[%ld] Thinking\n", (intptr_t)id);
    randsleep();

    /* TODO: Take forks (without deadlock & starvation) */

    // blocks the last free chair
    // so that we always have one extra fork on the table
    Sem_wait(&free_chairs);

    Sem_wait(&forks[right]);
    Sem_wait(&forks[left]);

    /* Eat */
    printf("[%ld] Eating\n", (intptr_t)id);
    randsleep();

    /* TODO: Put forks (without deadlock & starvation) */
    Sem_post(&forks[left]);  // sends signal to forks[left] semaphore
    Sem_post(&forks[right]); // sends signal to forks[right] semaphore
    
    // the chair is now free
    Sem_post(&free_chairs);
  }

  return NULL;
}

int main(void) {
  /* TODO: If you need extra shared state, initialize it here. */
  // Leave last chair
  Sem_init(&free_chairs, 0, N-1);

  for (int i = 0; i < N; i++)
    Sem_init(&forks[i], 0, 1);

  for (int i = 0; i < N; i++)
    Pthread_create(&td[i], NULL, philosopher, (void *)(intptr_t)i);

  for (int i = 0; i < N; i++)
    Pthread_join(td[i], NULL);
  
  return EXIT_SUCCESS;
}