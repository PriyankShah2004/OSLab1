#ifndef SHARED_H
#define SHARED_H

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct shmbuf {
    sem_t  sem1;           
    sem_t  sem2;            
    int a;
    int b;  
};

#endif