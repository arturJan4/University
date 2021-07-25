#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Get string from stdin */
void readline(FILE *in, char *p) {
  int c;
  while (true) {
    c = fgetc(in);
    if (c == EOF || c == '\n')
      break;
    *p++ = c;
  }
  *p = '\0';
} 

void echo(FILE *in) {
  char buf[48];
  readline(in, buf);
  puts(buf);
}

int main(int argc, char *argv[]) {
  FILE *in = NULL;
  if (argc == 2)
    in = fopen(argv[1], "rb");
  if (in == NULL)
    in = stdin;
  echo(in);
  return 0;
} 
