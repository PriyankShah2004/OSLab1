#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "shared.h"
#include <string.h>

 
int main(int argc, char *argv[]) {

    char *shmpath = "Mem_Name2";
    int fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
        fd = shm_open(shmpath, O_RDWR, 0);
    if (fd == -1)
        errExit("shm_open");

    struct shmbuf *shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (shmp == MAP_FAILED)
        errExit("mmap");
    
    shmp->a = 10;
    shmp->b =11;
    
    if (sem_post(&shmp->sem1) == -1)
        errExit("sem_post");

    if (sem_wait(&shmp->sem2) == -1)
        errExit("sem_wait");

    exit(EXIT_SUCCESS);
}