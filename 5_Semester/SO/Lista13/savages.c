#include "csapp.h"

static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

#define N 100
#define M 100

static struct {
  /* TODO: Put semaphores and shared variables here. */
  sem_t savage_lock;
  sem_t full_pot;
  sem_t empty_pot;
  int portions;
} *shared = NULL;


static void savage(void) {
  for (;;) {
    /* TODO Take a meal or wait for it to be prepared. */
    Sem_wait(&shared->savage_lock);

    if (shared->portions == 0) {
      // signal that pot is empty (wake up the cook)
      Sem_post(&shared->empty_pot);
      // wait for it to be full
      Sem_wait(&shared->full_pot);
    }

    //assert((shared->portions - 1) > 0);
    shared->portions--;
    printf("[%d] eating %d/%d left\n", getpid(), shared->portions, M);

    Sem_post(&shared->savage_lock);

    /* Sleep and digest. */
    usleep(rand() % 1000 + 1000);
  }

  exit(EXIT_SUCCESS);
}

static void cook(void) {
  for (;;) {
    /* TODO Cook is asleep as long as there are meals.
     * If woken up they cook exactly M meals. */
    // do not cook before savage signaled that pot is empty
    Sem_wait(&shared->empty_pot);
  
    assert(shared->portions == 0);
    printf("[%d] cooking\n", getpid());

    shared->portions = M;
    // signal that pot is full
    Sem_post(&shared->full_pot);
  }
}

/* Do not bother cleaning up after this process. Let's assume that controlling
 * terminal sends SIGINT to the process group on CTRL+C. */
int main(void) {
  shared = Mmap(NULL, getpagesize(), PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED,
                -1, 0);

  /* TODO: Initialize semaphores and other shared state. */
  Sem_init(&shared->savage_lock, 1, 1);
  Sem_init(&shared->full_pot, 1, 0);
  Sem_init(&shared->empty_pot, 1, 0);
  shared->portions = M;

  for (int i = 0; i < N; i++)
    if (Fork() == 0)
      savage();

  cook();

  return EXIT_SUCCESS;
}
