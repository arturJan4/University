#include <stdio.h>
#include <fcntl.h>
#include "apue.h"

#define BUFFSIZE 4096

int fd;

int main(int argc, char *argv[]) {
  int n;
  char buf[BUFFSIZE];

  fd = open(argv[1], O_RDONLY);

  while ((n = read(fd, buf, BUFFSIZE)) > 0)
    if (write(STDOUT_FILENO, buf, n) != n)
      err_sys("write error");

  if (n < 0)
    err_sys("read error");

  exit(0);
}
