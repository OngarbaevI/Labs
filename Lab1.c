#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
int main(void)
{
    int fd; //пременная для передачи кода ошибки
    fd=open("test.txt", O_RDONLY); // 
     if(fd==-1) {
        printf("Невозможно открыть файл\n");
        exit(1);
    }
    int charNum = lseek(fd, 0, SEEK_END);// считаем символы
    lseek (fd, 0, SEEK_SET);    // встаем на нулевой символ
    char buf[charNum];          // создаес массив симолов переноса строки
    read(fd, buf, charNum);     //  читаем 
    int stringCounter = 0;      // счетчик строк
    for (int i = 0; i < charNum; i++) // ищем перенос строк
    {
        if (buf[i]=='\n')
            stringCounter++; //
        printf("%c", buf[i]);//пишем 
    }
    int stringBeginPos[stringCounter]; // Переменная начала строки
    stringBeginPos[0] = 0; // Переменная начала позиции
    int localStringCounter = 1; // Локальная перемена счетчика
    for (int i=0; i < charNum; i++)
    {
        if ((buf[i]=='\n')  ) // Если мы находим новую строку,то 
        {
            stringBeginPos[localStringCounter++] = i + 1;//Устанавилваем начало строки
        }
    }

    int choosenString = 1; // переменная выбранной строки
    while (0==0) // Пока бесконечность
    {

        scanf("%d", &choosenString); // Считываем нужную нам строку для вывода
        if (choosenString == 0) // Если строка нулевая то, вводим другую 
            break;
        if (choosenString > stringCounter)
        {
            printf("Слишком большое значение");// Если число введенное пользователем больше чем есть, то вводим другом
            continue;
        }
        for (int counter = stringBeginPos[choosenString-1]; buf[counter]!='\n'; counter++) // Если успешно, то выводим строку
            printf("%c", buf[counter]);
    }
    return(0);
    }
