#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <sched.h>


void main(int argc, char* argv[]) {

    char *semOneName = "/mysem1";
    char *semTwoName = "/mysem2";
    sem_t *sem1 = sem_open(semOneName, O_CREAT | O_EXCL, O_RDWR, 0);
    sem_t *sem2 = sem_open(semTwoName, O_CREAT | O_EXCL, O_RDWR, 1);

    if(fork())
    {
        for(int i = 0; i < 3; i++){
            sem_wait(sem1);
            FILE *filelog = fopen("log.txt", "a");
            fprintf(filelog, "%d <--- \n", getpid());
            fclose(filelog);
            sem_post(sem2);

        }
    }
    else {
        for(int i = 0; i < 3; i++){
            sem_wait(sem2);
            FILE *filelog = fopen("log.txt", "a");
            fprintf(filelog, "%d <-- \n", getpid());
            fclose(filelog);
            sem_post(sem1);
        }
    }
    sem_unlink(semOneName);
    sem_unlink(semTwoName);
