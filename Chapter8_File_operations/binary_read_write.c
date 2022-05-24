#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct Date
{
	int year;
	int month;
	int day;
};

struct Book
{
	char name[40];
	char author[40];
	char publisher[40];
	struct Date date;  // 嵌套结构体
};

int main(void)
{
	FILE *fp;
	struct Book *book_for_write, *book_for_read;

	// 申请内存
	book_for_write = (struct Book *)malloc(sizeof(struct Book));
	book_for_read = (struct Book *)malloc(sizeof(struct Book));
	if (book_for_write == NULL || book_for_read == NULL)
	{
        printf("内存分配失败！\n");
        exit(EXIT_FAILURE);
	}
	// 字符赋值
	strcpy(book_for_write->name, "书名");
	strcpy(book_for_write->author, "作者");
	strcpy(book_for_write->publisher, "出版社");
	// 赋值
	book_for_write->date.year = 2017;
	book_for_write->date.month = 11;
	book_for_write->date.day = 11;

	if ((fp = fopen("file.txt", "wb")) == NULL)
	{
        printf("打开文件失败！\n");
        exit(EXIT_FAILURE);
	}
	//写入文件，单位sizeof(struct Book)，个数1，文件句柄(指针)fp file pointer
	fwrite(book_for_write, sizeof(struct Book), 1, fp);
	fclose(fp);

	if ((fp = fopen("file.txt", "rb")) == NULL)
	{
        // printf("打开文件失败！\n");
        fprintf(stderr, "出错啦，原因竟然是 -> %s <- 这个！\n", strerror(errno));
        exit(EXIT_FAILURE);
	}
	// fread文件读取， 指向指针book_for_read,单位大小,个数1，文件指针
	fread(book_for_read, sizeof(struct Book), 1, fp);
	printf("书名：%s\n", book_for_read->name);
	printf("作者：%s\n", book_for_read->author);
	printf("出版社：%s\n", book_for_read->publisher);
	printf("出版日期：%d-%d-%d\n", book_for_read->date.year, book_for_read->date.month, book_for_read->date.day);

	fclose(fp);

	return 0;
}
