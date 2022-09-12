#include "csapp.h"

bool f_lock(const char *path) 
{
    if (access(path, F_OK) == 0) // sprawdza czy plik istnieje pod podaną ścieżką
        return false; // jeśli nie to wracamy
    
    (void)Open(path, O_CREAT|O_WRONLY, 0700); // otwiera/tworzy pliik tyko do odczytu z RWX dla użytkownika
    return true;
}

void f_unlock(const char* path)
{
    Unlink(path);
}

int main(void)
{
  return 0;
}