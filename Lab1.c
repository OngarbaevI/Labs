#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
int main(void)
{
    int fd; 
    fd=open("test.txt", O_RDONLY); 
     if(fd==-1) {
        printf("Невозможно открыть файл\n");
        exit(1);
    }
    int charNum = lseek(fd, 0, SEEK_END);
    lseek (fd, 0, SEEK_SET);
    char buf[charNum];
    read(fd, buf, charNum);
    int stringCounter = 0;
    for (int i = 0; i < charNum; i++)
    {
        if (buf[i]=='\n')
            stringCounter++;
        printf("%c", buf[i]);
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
