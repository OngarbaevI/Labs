#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/mman.h>
int main(void)

{
    int fd;
    fd=open("textfile.txt", O_RDONLY);
    if(fd==-1) {
        printf("Невозможно открыть файл\n");
        exit(1);
    }
    struct stat fileStat; структурная переменная, для записи информации о файле
    fstat(fd, &fileStat); записываем данные о файле в переменную
    size_t charNum = fileStat.st_size; записываем размер файла в байтах в переменную
    char *buf;
    buf = mmap (0, charNum, PROT_READ, MAP_SHARED, fd, 0); //создаем отображение файла в память
    // файл считывается с 0 символа, количество символов, Защищаем файл от записи, Разделить использование этого отражения с другими процессами, отражающими тот же объект,
    
    int stringCounter = 0;
    for (int i = 0; i < charNum; i++)
    {
        if (buf[i]=='\n')
            stringCounter++;
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

    for (int i = 0; i < stringCounter; i++)
    {
        printf("%d\n", stringBeginPos[i]);
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
        for (int i = stringBeginPos[choosenString-1]; buf[i]!='\n'; i++)
            printf("%c", buf[i]);
    }
    return(0);
}
