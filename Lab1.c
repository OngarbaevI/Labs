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
    int stringBeginPos[stringCounter];
    stringBeginPos[0] = 0;
    int localStringCounter = 1;
    for (int i=0; i < charNum; i++)
    {
        if ((buf[i]=='\n')  )
        {
            stringBeginPos[localStringCounter++] = i + 1;
        }    
    }

    int choosenString = 1;
    while (0==0)
    {
    
        scanf("%d", &choosenString);
        if (choosenString == 0)
            break;
        if (choosenString > stringCounter)
        {
            printf("Слишком большое значение");
            continue;
        }
        for (int counter = stringBeginPos[choosenString-1]; buf[counter]!='\n'; counter++)
            printf("%c", buf[counter]);
    }
    return(0);
    }
