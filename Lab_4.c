#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <sched.h>


void main(int argc, char* argv[]) {
    //задаем имя симофоров асинхронного симафора
    char *semOneName = "/sem1"; 
    char *semTwoName = "/sem2";
    //создаем асинхронные симафоры 
    sem_t *sem1 = sem_open(semOneName, O_CREAT | O_EXCL, O_RDWR, 0); //!
    sem_t *sem2 = sem_open(semTwoName, O_CREAT | O_EXCL, O_RDWR, 1); //!

    if(fork())//создание подроцессы
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
            sem_wait(sem2); //!
            FILE *filelog = fopen("log.txt", "a");
            fprintf(filelog, "%d <-- \n", getpid()); //
            fclose(filelog); // работа с логами
            sem_post(sem1);//!
        }
    }
    //обязательно для того чтобы не тратить память
    sem_unlink(semOneName);
    sem_unlink(semTwoName);
