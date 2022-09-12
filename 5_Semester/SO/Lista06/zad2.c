#include "csapp.h"

bool my_acces(struct stat *sb, int mode)
{
  // superuser ma dostęp
  if (geteuid() == 0)
    return true;
	
  uint8_t pr  = (mode & R_OK); 	     // flagi z mode
  uint8_t pw  = (mode & W_OK);  
  uint8_t px  = (mode & X_OK);
  
	int sb_mode = sb->st_mode;

  // user ID procesu == uid programu
  // to sprawdzamy bit dostępu
  if (getuid() == sb->st_uid)
  {
    uint8_t sb_ur = (sb_mode & S_IRUSR); // uprawnienia pliku
    uint8_t sb_uw = (sb_mode & S_IWUSR);
    uint8_t sb_ux = (sb_mode & S_IXUSR);
  
    if (!sb_ur && pr) 
      return false;
    if (!sb_uw && pw)
      return false;
    if (!sb_ux && px)
      return false;

    return true;
  }
	
  // sprawdzamy dla grup
  gid_t gid = sb->st_gid;

  if (getgid() == gid)
  {
    gid_t *groups = NULL;

    int groups_n = getgroups(0, NULL); // when passing 0 -> get size without modyfing groups
    groups = malloc(groups_n * sizeof(gid_t));
    groups_n = getgroups(groups_n, groups);

    for (int i = 0; i < groups_n; ++i)
    {
      if (gid == groups[i])
      {
        uint8_t sb_gr = (sb_mode & S_IRGRP); // uprawnienia pliku
        uint8_t sb_gw = (sb_mode & S_IWGRP);
        uint8_t sb_gx = (sb_mode & S_IXGRP);
    
        if (!sb_gr && pr) 
            return false;
        if (!sb_gw && pw)
            return false;
        if (!sb_gx && px)
            return false;

        return true;
      }
    }
  }
	
  // others 
  uint8_t sb_or = (sb_mode & S_IROTH); // uprawnienia pliku
  uint8_t sb_ow = (sb_mode & S_IWOTH);
  uint8_t sb_ox = (sb_mode & S_IXOTH);
  
  if (!sb_or && pr) 
    return false;
  if (!sb_ow && pw)
    return false;
  if (!sb_ox && px)
    return false;

return true;
}

int main(int argc, char *argv[]) {
  if (!argv[1])
    argv[1] = ".";

  int fd = Open(argv[1], O_RDONLY);
  struct stat sb;
  
  if (fd == -1)
  {
    printf("open fd error");
    return -1;
  }

  fstat(fd, &sb);
  //int mode = sb.st_mode;
  int mode = R_OK | W_OK | X_OK;

  if(my_acces(&sb, mode))
  {
    printf("can access");
  }
  else
  {
    printf("can't access");
  }

  Close(fd);
  return EXIT_SUCCESS;
}
