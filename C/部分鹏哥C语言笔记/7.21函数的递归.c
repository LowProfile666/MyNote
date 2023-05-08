#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//链式结构
//int main()
//{
//	printf("%d", printf("%d",printf("%d", printf("%d", 43))));//43211
//	//printf函数返回的是打印的长度，打印了43返回值是2，所以下次打印是2返回值是1
//	//在下次打印是1返回值还是1所以最后一次打印1；
//	return 0;
//}
//函数的声 明
//int Add(int, int);
////若将函数的定义放在主函数的后面代码会被警告
////声明后就又好了
//int main()
//{
//	int a = 10;
//	int b = 20;
//	//函数的调用
//	int sum = Add(a, b);
//	printf("%d", sum);
//	return 0;
//}
////函数的定义
//int Add(int x, int y)
//{
//	int z = x + y;
//	return z;
//}

//函数的递归
//逐个打印出输入的数字
//int print(int x)
//{
//	if (x > 9)
//	{
//		print(x / 10);
//	}
//	printf(  "%d  ", x % 10);
//}
//int main()
//{
//	int a;
//	scanf("%d", &a);
//	print(a);
//	return 0;
//}
//不定义临时变量球字符串长度
//int my_strlen(char* a)
//{
//	if (*a != '\0')
//		return 1 + my_strlen(a + 1);
//	else
//		return 0;
//}
//int main()
//{
//	char arr[] = "hello";
//	int len = my_strlen(arr);
//	printf("%d", len);
//	return 0;
//}
////递归求n的阶乘
//int f(int n)
//{
//	int ret;
//	if (n <= 1)
//		return 1;
//	else
//		return ret = n * f(n - 1);
//}
//int main()
//{
//	int n;
//	scanf("%d", &n);
//	int ret = f(n);
//	printf("%d", ret);
//  return 0;
//
//}
