#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX 1024 //宏， 文本替换

int main(void)
{
	FILE *fp;//文件指针,指针不用理解就是存放变量的内存起始地址，FILE 表示这个起始位置要作为什么类型解(不同变量类型，使用特定规则读取)
    FILE *fp2;
    char buffer[MAX]; //字符串缓存
    // 读取文件
	if ((fp = fopen("hello.txt", "r")) == NULL)
	{
		printf("打开文件失败！\n");//写入文件
		exit(EXIT_FAILURE);
		/*
		首先介绍一下：
        exit(0): 正常执行程序并退出程序。
        exit(1): 非正常执行导致退出程序。

        其次介绍：
        stdlib.h头文件中 定义了两个变量：

        #define EXIT_SUCCESS 0
        #define EXIT_FAILURE 1

        最后介绍:
        exit(EXIT_SUCCESS)  : 代表安全退出。
        exit(EXIT_FAILURE) ： 代表异常退出。
        */
	}

	char buff[1024];  // 设置1024 字节长度字符-数组
	memset(buff, '\0', sizeof(buff)); // memset 使用'\0' 填充 字符数组buff,填充大小为 sizeof(buff) 字节，就是1024
    setvbuf(stdout, buff, _IOFBF, 1024);// 设置标准输出stdout 的块缓存
    //setvbuf(stdout, buff, _IOLBF, 1024);// 设置标准输出stdout 的行缓存
    //setvbuf(stdout, buff, _IONBF, 1024);// IONBF 不设置缓存

    // 文件坐标seek 指针位置归零，从头开始读取
    fseek(fp,0,SEEK_SET) 
    while (!feof(fp)) // feof 判断是否读取到文件末尾 EOF(end of file)
	{
		fgets(buffer, MAX, fp); // file get chr 逐个字符读取
		printf("%s", buffer);
	}

    if ((fp2 = fopen("fishc.txt", "w")) == NULL)
	{
		//printf("文件打开失败！\n");
		//exit(EXIT_FAILURE);
        fprintf(stderr, "出错啦，原因竟然是 -> %s <- 这个！\n", strerror(errno));
        exit(EXIT_FAILURE);
	}

	fclose(fp);

	return 0;
}
