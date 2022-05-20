#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// File Pointer
	FILE *fp1;
	FILE *fp2;

	int ch;

	// like perl
	// open (my $fh, "<","test.txt") or die "Can't open < test.txt: $!";
	// fh == file header --> file pointer
	if ((fp1 = fopen("inputfile", "r")) == NULL)
	{
		printf("文件打开失败！\n");
		exit(EXIT_FAILURE);
	}

	if ((fp2 = fopen("Hi.txt", "w")) == NULL)
	{
		printf("文件打开失败！\n");
		exit(EXIT_FAILURE);
	}

	while ((ch = fgetc(fp1)) != EOF)
	{
		// fgetc : get each one char
		// fputc : put each one char
		fputc(ch, fp2);
	}
