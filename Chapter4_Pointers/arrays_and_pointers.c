#include <stdio.h>

int main(void)
{
	// 一维数组
	int *p[5] //变量名为p, [5] 这里划分5个 sizeof(int) 连续内存空间(即数组), 这个空间每个元素都看作一个指针
	int (*p2)[5] = {1, 2, 3, 4, 5};  //(指针变量名为p), [5] 这里划分5个 sizeof(int) 连续内存空间(即数组)，指针指向第一个元素位置
	int i;

	for (i = 0; i < 5; i++)
	{
		printf("%d\n", *(p2 + i)); //*p 指针 指向地址为数组第一个元素，*指针(p+1) 表示数组的第二个元素
	}

	// 二维数组
	int array[4][5] = {0};// 定义二维数组 ，4行5列
	int i, j, k = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 5; j++)
		{
			array[i][j] = k++;
		}
	}
	// array 是整个二维数组的首地址，数组名 array 相当于一个常量指针，指向二维数组第一个元素 
	// %p 表示指针变量
	// %d 表示数字变量
	printf("*(array+1): %p\n", *(array + 1));  // *星号表示取值，//*(array[0][0] +1) ->array[1][0]
	printf("array[1]: %p\n", array[1]);
	printf("&array[1][0]: %p\n", &array[1][0]); // &与号表示取内存地址(即指针)
	printf("**(array+1): %d\n", **(array+1)); //  -> *(array[1][0]) 取 array[1][0]的值
	printf("**(array+1): %d\n", *(*(array+1)+3));  // *(array + 1) +3 = &array[1][3] ,这里是&取内存地址 ，*星号取值 *(&array[1][3])，代表获取array[1][3]的值

	return 0;
}
