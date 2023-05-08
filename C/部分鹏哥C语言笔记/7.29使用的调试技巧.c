#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>



//调试（英语Debugging/Debug），又称除错，
//是发现和减少计算机程序或电子仪器设备中程序错误的一个过程
//
//
//调试的基本步骤：
//1.发现程序错误的存在
//2.以隔离、消除的方式对错误进行定位
//3.确定错误产生的原因
//4.提出纠正错误的解决方法
//5.对程序错误予以改正，重新测试
//
//Debug和Release
//Debug通常称为调试版本，它包含调试信息，并且不作任何优化，便于程序员调试程序
//Release称为发布版本，它往往是进行了各种优化，
//使得程序在代码大小和运行速度上都是最优的，以便用户很好的使用，不能调试
//
//快捷键：
//F5：启动调试，一般和F9配合使用，直接跳到断点处
//F9：切换断点（代码执行到断点的位置就停下来）
//F10：逐过程，通常用来 处理一个过程，一个过程可以是一次函数调用或者是一条语句
//F11：逐语句，就是每次都执行一条语句，但这个快捷键可以使我们的执行逻辑进行函数内部（最常用）
//Ctrl+F5：开始执行不调试，如果想让程序直接运行不调试就可以直接使用
//int main()
//{
//	int i = 0;
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	for (i = 0; i <= 12; i++)
//	{
//		printf("hehe\n");
//		arr[i] = 0;
//		//从arr[10]开始就是越界访问，程序继续，arr[10]arr[11]arr[12]都等于0
//		//当arr[12]=0时的同时i也从12变倒了0，所以开始死循环
//		//因为arr[12]的地址就是i的地址
//	}
//	return 0;
//}
//栈区存放局部变量
//1.栈区的默认使用：先使用高地址处的空间，再使用低地址处的空间
//2.数组随着下标的增长地址时由低到高变化的


//#include<assert.h>
//char* my_strcpy(char* dest, const char* rec)//const保证rec不会被改变，防止while循环条件写完却不报错
//{
//	/*while (*rec!='\0')
//	{
//		*dest = *rec;
//		dest++;
//		rec++;
//	}*/
//	//*dest = *rec;//'\0'
//	//优化：
//	assert(dest != NULL);//断言
//	assert(rec != NULL);//断言
//	//如果dest或rec=NULL，就会报错，不等于没有影响
//	while (*dest++ = *rec++)
//	{
//		;
//	}
//
//}
//int main()
//{
//	char arr1[] = "###########";
//	char arr2[] = "bit";
//	//strcpy(arr1, arr2);//字符串拷贝
//	//my_strcpy(arr1, NULL);//字符串拷贝
//	//strcpy（目的地，源头）
//	printf("%s\n", my_strcpy(arr1, arr2));//字符串拷贝);//链式访问
//	return 0;
// }


//const作用：
//const放在指针变量的*左边时，修饰的时*p，也就是说，不能通过p来改变*p（num)的值
/*int main()
{
	//int num = 10;
	//int* p = &num;
	//*p = 20;
	//printf("%d", num);//20

	int num = 10;
	const int* p = &num;
	*p = 20;
	printf("%d", num);//程序报错
	return 0;
}*/
//const放在指针变量的*右边时，修饰的是指针变量p的本身，p不能被改变了
//int main()
//{
//	//int n = 0;
//	//int num = 10;
//	//int* p = &num;
//	//p = &n;//程序并不报错，p可以修改
//
//	int n = 0;
//	int num = 10;
//	int* const p = &num;
//	p = &n;//程序报错，p不能修改
//	return 0;
//}

//#include<assert.h>
//int my_strlen(const char* str)
//{
//	int count = 0;
//	assert(str != NULL);
//	while (*str!='\0')
//	{
//		count++;
//		str++;
//	}
//	return count;
//}
//int main()
//{
//	char arr[] = "abcde";
//	printf("%d", my_strlen(arr));
//	return 0;
//}


编译常见的错误分类：
1.编译型错误：直接双击错误提示信息，解决问题，或者凭借经验就可以搞定。
2.链接型错误：看错误提示信息，主要在代码中找到错误信息中的标识符，然后定位问题所在，
一般是标示符名不存在或者拼写错误。
int main()
 {
 	int a = 10;
 	int b = 20;
	int c=add(a, b);
	printf("%d", c);//未定义add
}
3.运行时错误：借助调试，逐步定位问题。
