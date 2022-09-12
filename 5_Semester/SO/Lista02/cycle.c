#include "csapp.h"

static void signal_handler(int signum, siginfo_t *info, void *data) {
  if (signum == SIGINT) {
    safe_printf("(%d) Screw you guys... I'm going home!\n", getpid());
    _exit(0);
  }
}

static void play(pid_t next, const sigset_t *set) {
  for (;;) {
    printf("(%d) Waiting for a ball!\n", getpid());
    /* TODO: Something is missing here! */
    Sigsuspend(set); // zawiesza proces do otrzymania sygnału z maski (piłka)
    /* --- */
    usleep((300 + random() % 400) * 1000);
    Kill(next, SIGUSR1);
    printf("(%d) Passing ball to (%d)!\n", getpid(), next);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2)
    app_error("Usage: %s [CHILDREN]", argv[0]);

  int children = atoi(argv[1]);

  if (children < 4 || children > 20)
    app_error("Give number of children in range from 4 to 20!");

  /* Register signal handler for SIGUSR1 */
  struct sigaction action = {.sa_sigaction = signal_handler};
  Sigaction(SIGINT, &action, NULL);
  Sigaction(SIGUSR1, &action, NULL);

  /* TODO: Start all processes and make them wait for the ball! */
  sigset_t sigmask;
  sigset_t oldmask;

  sigemptyset(&sigmask);
  sigaddset(&sigmask, SIGUSR1);
  Sigprocmask(SIG_BLOCK, &sigmask, &oldmask); // dodanie SIGUSR1 do blokowanych sygnałów (dla ojca) z sigmask

  pid_t next_pid = getpid(); // parent pid at start
  for (int i = 0; i < children; ++i) 
  {
    pid_t pid;

    if ((pid = Fork()) == 0) 
    {
      play(next_pid, &oldmask);
    }
    else 
    {
      next_pid = pid;
    }
  }

  // rodzic rozpoczyna grę rzucając do najmłodszego dziecka
  Kill(next_pid, SIGUSR1); 
  play(next_pid, &oldmask);

  /* --- */
  return EXIT_SUCCESS;
}
