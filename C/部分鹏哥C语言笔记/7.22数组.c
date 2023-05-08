#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//数组
//int main()
//{
//	char arr[] = "abcdfg";//char 是元素的类型
//	printf("%d\n", sizeof(arr)); 
//		//sizeof计算所占空间的大小
//		printf("%d\n",strlen(arr));
//	//strlen就算字符串的长度 -
//	return 0;
//}
//int main()
//{
//	char arr[] = "abc";
//	char vrr[] = { 'a','b','c'};
//	printf("%d\n", sizeof(arr));
//	printf("%d\n", sizeof(vrr));
//	printf("%d\n", strlen(arr));
//	printf("%d\n", strlen(vrr));
//
//	return 0;
//}
//int main()
//{
//	char arr[] = "abcdrfg";
//	int i=0;
//	/*for (i = 0; i <= 7; i++)
//	{
//		printf("%c ", arr[i]);
//	}*/
//	while (i<=7)
//	{
//		printf("%c ", arr[i]);
//		i++;
//	}
//	return 0;
//}
//数组在内存中是连续存放的
//int main()
//{
//	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	int i = 0;
//	for (; i < sz; i++)
//	{
//		printf("&arr[%d]=%p\n", i, &arr[i]);
//	}
//	return 0;
//}
//二维数组
//int main()
//{
//	//二维数组初始化
//    int arr1[2][2] = { {1,2},{3,4} };
//    int arr2[2][3] = { 1,2,3,4,5,6 };
//	int arr3[][4] = { {1,2,3,4},{5,6,7,8} };
//	int arr4[][4] = { 1,2,3,4,5,6,7,8,9 };
//	//前面行可以省略，但后面的列不能省
//	return 0;
//}
//打印出arr[3][4]的值
//int main()
//{
//	int arr[3][4] = { {1,2,3},{4,5,6,7},8,9,10 };\
//	//1,2,3,0
//	//4,5,6,7
//	//8,9,10,0
//	int i = 0;
//	for (i = 0; i < 3; i++)
//	{
//		int j = 0;
//		for (j = 0; j <4; j++)
//		{
//			printf("%d ", arr[i][j]);
//		}
//		printf("\n");
//	}
//	return 0;
//}
//二维数组的内存地址
//int main()
//{
//	int arr[2][3] = { 1,2,3,4,5,6 };
//	int i = 0;
//	for (i = 0; i < 2; i++)
//	{
//		int j = 0;
//		for (j = 0; j < 3; j++)
//		{
//			printf("&arr[%d][%d]=%p\n", i,j,&arr[i][j]);
//		}
//	}
//	return 0;
//二维数组也是连续存放的 
//}
//数组作函数参数
 //冒泡函数排序
//void maopao(int sz,int arr[])
//{
//	//确定冒泡排序的趟数
//	int i = 0;
//	for (i = 0; i < sz-1; i++)
//	{
//		//优化程序，比如一组数据5，1，2，3，4排序
//		//只需一趟排序就能结束
//		int flag = 1;//假设这一要排序的数据已经有序
//		//每一趟冒泡排序
//		int j = 0;
//		for (j = 0; j <sz-1-i ; j++)
//		{
//			if (arr[j] < arr[j + 1])
//			{
//				int t = arr[j + 1];
//				arr[j + 1] = arr[j];
//				arr[j] = t;
//				flag = 0;//本趟排序的数据其实不完全有序
//			}
//		}
//		if (flag == 1)
//		{
//			break;
//		}
//	}
//}
//int main()
//{
//	int arr[] = { 1,2,3,4,6 ,5,7,9,10,8};
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	//我们对数组arr进行传参，实际上传递过去的是arr首元素的地址&arr[0]
//	int i = 0;
//	maopao(sz,arr);
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}
//数组名一般是首元素地址，但有两个例外：
//1.sizeof（数组名）中数组名表示整个数组 ，sizeof计算的是整个数组的大小，单位是字节
//2.&数组名中数组名表示的是整个数组，&数组名取出的是整个数组的地址                                                   
int main()
{
	int a, b, c, d, t;
	scanf("%d,%d,%d,%d", &a, &b, &c, &d);
	if (a > b)
	{
		t = a;
		a = b;
		b = t;
	}
	if (a > c)
	{
		t = a;
		a = c;
		c = t;
	}
	if (a > d)
	{
		t = a;
		a = d;
		d = t;
	}
	if (b > c)
	{
		t = b;
		b = c;
		c = t;
	}
	if (b > d)
	{
		t = b; b = d; d = t;
	}
	if (c > d)
	{
		t = c;
		c = d;
		d = t;
	}
	printf("%d %d %d %d", a, b, c, d);
	return 0;
 }