#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//指针是变量，用来专门存放地址的
//指针的大小在32位平台是4个字节，64位平台是8个字节
//int main()
//{
//	printf("%d\n", sizeof(int*));//4
//	printf("%d\n", sizeof(short*));//4
//	printf("%d\n", sizeof(double*));//4
//	printf("%d\n", sizeof(char*));//4
//	return 0;
//}
//
// 指针类型决定了指针进行解引用操作的时候，能够访问空间的大小
//int *p; *p能访问4个字节
//char *p; *p能访问1个字节
//double *p; *p能访问8个字节
//
//int main()
//{
//
//	int a = 0x11223344;
//	int* pa = &a;
//	char* pc = &a;
//	//指针类型决定了指针走一步走多远（指针的步长） 
//	printf("%p\n", pa);//0137FDC4
//	printf("%p\n", pa+1);//0137FDC8
//	printf("%p\n", pc);//0137FDC4
//	printf("%p\n", pc+1);//0137FDC5
//	return 0;
//}

//野指针
//就是指针指向的位置是不可知的（随机的，不正确的，没有明确限制的）
//野指针成因：
//1.未初始化
//2.越界访问
//3.指针指向的空间释放

//1.
//int main()
//{
//	int a;//局部变量不初始化，默认是随机值
//	int* p;//局部的指针变量，被初始化随机值
//	*p = 20;
//	return 0;
//}
//2.
//int main()
//{
//	int a[10] = { 0 };
//	int* p = a;
//	int i = 0;
//	for (i = 0; i <= 12; i++)
//	{
//		*p = i;
//		//当指针指向的范围超过数组a的范围时，p就是野指针
//		 p++;
//	}
//	return 0;
//}
//3.
//int* text()
//{
//	int a = 10;
//	return &a;
//	//这个代码有问题，返回&a后，出了这个函数，这个地址就被销毁了
//}
//int main()
//{
//	int* p=text();
//	printf("%d\n", *p);
//	return 0;
//}
//
//
//int main()
//{
//	//int* p = NULL;//NULL-用来初始化指针，给指针赋值的
//	int a = 10;
//	int* p = &a;
//	*p = NULL;//当指针用完后不想扔的话，就给赋值NULL，
//	//然后该指针不指向任何有效空间
//	//若后续还用可用:
//	if (*p != NULL)
//	{
//		;
//	}
//	return 0;
//}

//指针运算
//1.指针+-整数
//2.指针-指针
//得到的是指针之间元素的个数
//3.指针的关系运算

//1.
//int main()
//{
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int i = 0;
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	int* p = arr;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", *p);
//		p++;
//		//p=p+1; 
//	}
//	return 0;
//}

//2.
//int main()
//{
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	printf("%d", &arr[9] - &arr[0]);//9，小地址-大地址时得到的时负数
//	char a[5] = { 0 };
//	printf(" %d ", &arr[4] - &a[0]);//err有问题没价值
//	return 0;
//}
//

 //3.
//#define N_VALUES 5
//int main()
//{
//	float values[N_VALUES];
//	float* vp;
//	for (vp = &values[N_VALUES]; vp > &values[0];)
//	{
//		*--vp = 0;
//	}
//	return 0;
//}

//指针和数组
//int main()
//{
//	int arr[10] = { 0 };
//	printf("%p\n", arr);//这的arr表示地址，首元素的地址
//	printf("%p\n", &arr[0]);
//	printf("%p\n", &arr);//整个数组的地址
//	//只有以下两种情况下不表首元素地址：
//	//1.&数组名--&arr--这的数组名表示整个数组，&数组名取出的是整个数组的地址
//	//2.sizeof（数组名）--sizeof（arr）--这的数组名表示整个数组，计算整个数组的大小
//
//	return 0;
//}

//int main()
//{
//	int arr[10] = { 0 };
//	int* p = arr;
//	int i = 0;
//	//给数组赋值
//	for (i = 0; i < 10; i++)
//	{
//		*(p + i) = i;
//	}
//	//打印数组元素
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", arr[i]);
//		//或printf("%d ", *(p + i));
//	}
//	printf("\n");
//	//打印元素地址
//	for (i=0; i < 10; i++)
//	{
//		printf("%p=====%p\n", p + i, &arr[i]);
//	}
//	return 0;
//}

//二级指针
//int main()
//{
//	int a = 0;
//	int * pa = &a;//一级指针
//	int* * ppa = &pa;//二级指针
//	int** * pppa = &ppa;//三级指针
//	***pppa = 20;
//	//*pppa是ppa的地址，**pppa是pa的地址，***pppa是a的地址
//	printf("%d\n", a);
//	return 0;
//}

//指针数组--数组--存放指针的数组
//数组指针--指针
int main()
{
	//整形数组-存放整形
	//字符数组-存放字符
	//指针数组-存放指针
	int a = 1;
	int b = 2;
	int c = 3;
	/*int* pa = &a;
	int* pb = &b;
	int* pc = &c;*/
	//int a[10] = { 0 };整形数组
	int* arr[10] = {&a,&b,&c};//指针数组 
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		printf("%d ", *(arr[i]));//1 2 3
		printf("%p\n", arr[i]);//地址
	}
	return 0;
}