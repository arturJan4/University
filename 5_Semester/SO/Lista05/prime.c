#include "csapp.h"

typedef struct {
  int read;
  int write;
} pipe_t;

static inline pipe_t MakePipe(void) {
  int fds[2];
  Pipe(fds);
  return (pipe_t){.read = fds[0], .write = fds[1]};
}

static inline void CloseReadEnd(pipe_t p) {
  Close(p.read);
}

static inline void CloseWriteEnd(pipe_t p) {
  Close(p.write);
}

static bool ReadNum(pipe_t p, long *valp) {
  return Read(p.read, valp, sizeof(long)) == sizeof(long);
}

static bool WriteNum(pipe_t p, long val) {
  return Write(p.write, &val, sizeof(long)) == sizeof(long);
}

static noreturn void generator(pipe_t out, long maxprime) {
  for (long n = 2; n <= maxprime; n++)
    WriteNum(out, n);
  exit(EXIT_SUCCESS);
}

static void filter(pipe_t in, pipe_t out, long prime) {
  long num;
  while (ReadNum(in, &num)) {
    if (num % prime != 0)
      WriteNum(out, num);
  }
}

static noreturn void filter_chain(pipe_t in) {
  long prime;

  /* TODO: Something is missing here! */
  // read all from BUF_PIPE
  if (ReadNum(in, &prime) == 0) {
    CloseReadEnd(in);

    exit(EXIT_SUCCESS);
  }

  printf("%ld ", prime);
  fflush(stdout);

  /*
    [..654321] ->(filter_pipe) [f2] -> [f3] -> [f5] -> .. 
  */
  pipe_t filter_pipe = MakePipe(); // communicate parent == child
  if (Fork()) { /* parent - does filtering for ceratin prime */
    
    CloseReadEnd(filter_pipe);
    filter(in, filter_pipe, prime); // sent data to next in chain
    CloseWriteEnd(filter_pipe);
    
    CloseReadEnd(in); // close in-pipe
  } else { /* child -> next in filter chain */
    CloseWriteEnd(filter_pipe);
    CloseReadEnd(in);

    filter_chain(filter_pipe);
  }

  //pause();
  Waitpid(0, NULL, 0);
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  if (argc != 2)
    app_error("Usage: %s [MAXPRIME]", argv[0]);

  long maxprime = atol(argv[1]);

  if (maxprime < 2 || maxprime > 10000)
    app_error("Give maximum prime number in range from 2 to 10000!");

  /* Spawn generator. */
  pipe_t gen_pipe = MakePipe();
  if (Fork()) { /* parent */
    CloseWriteEnd(gen_pipe);
  } else { /* child */
    CloseReadEnd(gen_pipe);
    generator(gen_pipe, maxprime);
  }

  //
  // [(generator) W] ==(gen_pipe)== [R (filterchain)]
  //

  /* Spawn filter chain. */
  if (Fork()) { /* parent */
    CloseReadEnd(gen_pipe);
  } else { /* child */
    filter_chain(gen_pipe);
  }

  for (int i = 0; i < 2; i++)
    Wait(NULL);

  printf("\n");

  return 0;
}
