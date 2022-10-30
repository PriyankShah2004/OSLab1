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

    if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
        errExit("ftruncate");
    struct shmbuf *shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE,MAP_SHARED, fd, 0);

    if (shmp == MAP_FAILED)
        errExit("mmap");

    if (sem_init(&shmp->sem1, 1, 0) == -1)
        errExit("sem_init-sem1");
               
    if (sem_init(&shmp->sem2, 1, 0) == -1)
         errExit("sem_init-sem2");

    if (sem_wait(&shmp->sem1) == -1)
        errExit("sem_wait");

    printf("%d\n",shmp->a);
    printf("%d\n",shmp->b);

    if (sem_post(&shmp->sem2) == -1)
        errExit("sem_post");


    shm_unlink(shmpath);

    exit(EXIT_SUCCESS);