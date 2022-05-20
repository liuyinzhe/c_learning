#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024  // macro definition for replacement

int main(void)
{
        FILE *fp;
        char buffer[MAX]; // Define string variable byte length

        // get local time
        struct tm *p;
        time_t t; // undfefined NULL
        time(&t); // t = time(NULL) # t= new //seconds since 1900
        // & Get the variable memory address, which is used for pointers to point to the memory address.
        p = localtime(&t); // Convert the number of seconds to the time in the form of year, month, day and second

        if ((fp = fopen("lines.txt", "w")) == NULL)
        {
                printf("打开文件失败！\n");
                exit(EXIT_FAILURE);
        }

        fputs("Line one: Hello World!\n", fp);
        fputs("Line two: Hello C!\n", fp);
        fprintf(fp, "%d-%d-%d\n", 1900 + p->tm_year, p->tm_mon, p->tm_mday);
        printf("%d-%d-%d",1900 + p->tm_year, p->tm_mon, p->tm_mday);


        fclose(fp);

        if ((fp = fopen("lines.txt", "r")) == NULL)
        {
                printf("打开文件失败！\n");
                exit(EXIT_FAILURE);
        }

        while (!feof(fp)) //feof : check if it read to the end EOF (end of file)
        {
                fgets(buffer, MAX, fp); // contain a string terminator ('\0') 
                printf("%s", buffer);
        }

        return 0;
}
