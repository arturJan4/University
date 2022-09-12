#include "csapp.h"

static pid_t spawn(void (*fn)(void)) {
  pid_t pid = Fork();
  if (pid == 0) {
    fn();
    printf("(%d) I'm done!\n", getpid());
    exit(EXIT_SUCCESS);
  }
  return pid;
}

static void sigint_handler(int a) {}

static void grandchild(void) {
  printf("(%d) Waiting for signal!\n", getpid());
  /* TODO: Something is missing here! */
  // po to by nie kończyć funkcji i wypisać resztę
  // czyli Got the signal
  signal(SIGINT, sigint_handler);
  pause(); // pauzuje do otrzymania sygnału
  /*----*/
  printf("(%d) Got the signal!\n", getpid());
}

static void child(void) {
  pid_t pid;
  /* TODO: Spawn a child! */
  setpgid(getpid(), getpid()); // dziecko staje się liderem grupy
  pid = spawn(grandchild);  // tworzymy wnuka i bierzemy jego pid
  /*----*/
  printf("(%d) Grandchild (%d) spawned!\n", getpid(), pid);
}

/* Runs command "ps -o pid,ppid,pgrp,stat,cmd" using execve(2). */
static void ps(void) {
  /* TODO: Something is missing here! */
  char* const argv[] = {"/bin/ps", "-o", "pid,ppid,pgrp,stat,cmd", NULL};
  execve(argv[0], argv, NULL);
  /*----*/
}

int main(void) {
  /* TODO: Make yourself a reaper. */
#ifdef LINUX
  Prctl(PR_SET_CHILD_SUBREAPER, 1);
#endif
  printf("(%d) I'm a reaper now!\n", getpid());

  pid_t pid, pgrp;
  int status;

  /* TODO: Start child and grandchild, then kill child!
   * Remember that you need to kill all subprocesses before quit. */
  pgrp = spawn(child); // tworzymy syna
  Waitpid(pgrp, NULL, 0);

  pid = spawn(ps); // wydajemy polecenie
  Waitpid(pid, NULL, 0);

  Kill(-pgrp, SIGINT); // wysyłamy sygnał do grupy (pid dziecka == pid grupy)
  printf("(%d): SIGINT to group %d\n", getpid(), pgrp);
  Waitpid(-1, &status, 0); // oczekujemy na wyjście i zapisujemy status do &status
  
  printf("(%d): kod wyjścia wnuka to %d\n", getpid(), WEXITSTATUS(status));

  /*----*/
  return EXIT_SUCCESS;
}
