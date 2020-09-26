#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char* argv[])
{
pid_t pid;    // id процесса 
int rv;   // Переменна для определения
switch(pid=fork()) {  // назначаем выделенной памяти для потока, новый поток
case -1:
	perror("fork");   // произошла ошибка 
        exit(1);  //выход из родительского процесса
case 0:
        printf("CHILD: Это процесс - потомок!\n");    // Это код потомка
        exit(0);
default:
        printf("PARENT: Это процесс-родитель!\n");    // Это код родительского процесса
        wait(&rv);    // ожидание завершения потомка
        WEXITSTATUS(rv);  // Код возрата потомка
        printf("EXITCODE = %d\n", WEXITSTATUS(rv));
	
 }
return(0);
}
