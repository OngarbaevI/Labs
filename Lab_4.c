#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <sched.h>


void main(int argc, char* argv[]) {
    //задаем имя асинхронного симофоров
    char *semOneName = "/sem1"; 
    char *semTwoName = "/sem2";
    //создаем асинхронные симафоры 
    sem_t *sem1 = sem_open(semOneName, O_CREAT | O_EXCL, O_RDWR, 0); //!
    sem_t *sem2 = sem_open(semTwoName, O_CREAT | O_EXCL, O_RDWR, 1); //!

    if(fork())//создание подроцесса
    {
        for(int i = 0; i < 3; i++){
            sem_wait(sem1);                             //уменьшает значение семафора на единицу и блокирует выполнение любых потоков
            FILE *filelog = fopen("log.txt", "a");      //открываем файл логов
            fprintf(filelog, "%d <--- \n", getpid());   //записывам логи
            fclose(filelog);                            //закрывааем файл 
            sem_post(sem2);                             //увеличивает значение семафора на единицу и возобновляет выполнение любых потоков
        }

        }
    }
    else {
        for(int i = 0; i < 3; i++){
            sem_wait(sem2);                             //уменьшает значение семафора на единицу и блокирует выполнение любых потоков
            FILE *filelog = fopen("log.txt", "a");      //открываем файл логов
            fprintf(filelog, "%d <-- \n", getpid());    //записывам логи
            fclose(filelog);                            //закрывааем файл
            sem_post(sem1);                             //увеличивает значение семафора на единицу и возобновляет выполнение любых потоков
        }
    }
    //обязательно для того чтобы не тратить память
    sem_unlink(semOneName);
    sem_unlink(semTwoName);
