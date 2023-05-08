#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
/*
求字符串长度：
strlen
长度不受限制的字符串函数：
strcpy
strcat
strcmp
长度受限制的字符串函数：
strncpy
strncat
strncmp
字符串查找：
strstr
strtok
错误信息报告：
strerror
字符操作
内存操作函数：
memcpy
memmove
memset
memcmp

C语言本身是没有字符串类型的，字符串通常放在 常量字符串 中或者 字符数组 中。
字符串常量 适用于那些对它不做修改的字符串函数
*/

/*
函数介绍：
strlen
	size_t strlen(const char* str);
	字符串已经'\0'作为结束标志，strlen函数返回的是在字符串中的'\0'前面出现的字符个数（不包含\0）
	参数指向的字符串必须以'\0'结束
	注意函数的返回值是size_t，是无符号的（易错）
	size_t==unsigned int
	学会三种方法模拟实现：
	1.计数器
	2.递归，不创建任何变量
	3.指针-指针
*/
#include<string.h>
//int main() {
	//int len = strlen("abcdef");

	//char arr[] = { 'a','b','c','d','e','f' };
	//int len1 = strlen(arr);
	//printf("arr 的长度是：%d\n", len1);     //随机值
	//printf("字符串“abcdef”的长度是：%d\n", len);//6
	

	//因为strlen函数返回的是无符号数，所以两个无符号数相减还是无符号数，所以必然是个正数
	//值得说的是，这里如果不引用头文件的话，就会打印出haha，而引用了头文件就打印hehe
//	if (strlen("abc") - strlen("abcdef") > 0)
//		printf("strlen返回的是一个无符号整数\n");
//	else
//		printf("strlen返回的是一个有符号整数\n");
//	return 0;
//}

//模拟实现strlen 
//1、计数器
//int my_strlen(const char* arr) {
//	int count = 0;
//	while (*arr) {
//		count++;
//		arr++;
//	}
//	return count;
//}
////2.指针
//int my_strlen(const char* arr) {
//	char* front = arr;
//	char* rear = arr;
//	while (*rear) {
//		rear++;
//	}
//	return rear - front;
//	
//}
//3、递归
//int my_strlen(const char* arr) {
//	if (*arr == '\0')
//		return 0;
//	return 1 + my_strlen(arr + 1);
//}
//int main() {
//	char arr[] = "aasdvs  daci";
//	int len=my_strlen(arr);
//	printf("arr 的长度是：%d\n", len);
//	return 0;
//}

//int main() {
//	char arr1[20] = "abcde";
//	char arr2[20] = "sbc";
//	if (strcmp(arr1, arr2) == 0)
//		printf("相等");
//	if (strcmp(arr1, arr2) > 0)
//		printf("大于");
//	if (strcmp(arr1, arr2) < 0) {
//		printf("小于");
//	}
//}




/*
strcpy
	char* strcpy(char* destination,const char* source);
	源字符串必须以'\0'结束
	会将源字符串中的'\0'拷贝到目标空间
	目标空间必须足够大，以确保能存放源字符串
	目标空间必须可变
*/
//模拟实现strcpy简陋版
//void my_strcpy(char* dest, char* src) {
//	while (*src != '\0') {
//		*dest = *src;
//		dest++;
//		src++;
//	}
//	*dest = *src;
//}
//模拟实现strcpy精简版
//void my_strcpy(char* dest, const char* src) {
//	//这个循环条件的值就是*dest的值，当他拷贝完src里面的\0时，就会退出循环了
//	while (*dest++ = *src++) {
//		;
//	}
//}
//
//int main() {
//	char arr1[] = "abcdefghikj";
//	char arr2[] = "hello";
//	strcpy(arr1, arr2);
//	printf("%s", arr1);//hello
//	return 0;
//}

//
//#define MAXSIZE 256
//typedef struct String {
//	char ch[MAXSIZE];
//	int length;
//}String;
//String S;
//String* s = &S;
//typedef struct SS {
//	int ch[MAXSIZE];
//	int length;
//}SS;
//SS a;
//SS* p = &a;
//int main() {
//	printf("%p\n", s);			0078A940
//	printf("%p\n", s->ch);		0078A940
//	printf("%p\n", s->ch+1);	0078A941
//	printf("%p\n", &S);			0078A940
//	printf("%p\n", &s->length);	0078AA40
//	printf("%p\n", p);			0078A520
//	printf("%p\n", p->ch);		0078A520
//	printf("%p\n", &a);			0078A520
//	printf("%p\n", &p->length);	0078A920
//	printf("%p\n", p->ch+1);	0078A524

//
//	return 0;
//}

//strcat
/*
char* strcat(char* destination,const char* source);
源字符串必须以'\0'结束
目标空间必须足够大，能容下源字符串的内容
目标空间必须可更改
不能自己给自己追加
*/
#include<assert.h>
//void my_strcat(char* dest, const char* src) {
//	assert(dest && src);
//	char* ret = dest;
//	//1、找到目标字符串的'\0'
//	while (*dest != '\0') {
//		dest++;
//	}
//	//2、追加
//	while (*dest++ = *src++) {
//		;
//	}
//}
//int main() {
//	char arr1[30] = "hello";
//	char arr2[] = "world";
//	strcat(arr1, arr2);
//	printf("%s\n",arr1);
//	return 0;
//}


/*
strcmp
	int strcmp(const char* str1,const char* str2);
	标准规定：
		第一个字符串大于第二个字符串，则返回大于0的数字
		第一个字符串等于第二个字符串，则返回等于0的数字
		第一个字符串小于第二个字符串，则返回小于0的数字
*/
//int main() {
//	char* p1 = "abcd";
//	char* p2 = "abce";
//	int ret = strcmp(p1, p2);
//	printf("%d", ret);
//	return 0;
//}

//int my_strcmp(const char* str1, const char* str2) {
//	//比较，两串一直相等到'\0'时就返回0，说明他俩相等
//	while (*str1 == *str2) {
//		if (*str1 == '\0')
//			return 0;
//		str1++;
//		str2++;
//	}
//	//退出循环了说明只能大于和小于了
//	if (*str1 > *str2)
//		return 1;//大于
//	else
//		return -1;//小于
//}
//int main() {
//	char* p1 = "abc";
//	char* p2 = "abh";
//	int ret = strcmp(p1, p2);
//	printf("这个返回值是：%d\n", ret);
//	if (ret > 0)
//		printf("他代表着：p1>p2\n");
//	if (ret == 0)
//		printf("他代表着：p1==p2\n");
//	if (ret < 0)
//		printf("他代表着：p1<p2\n");
//	return 0;
//}
/*
strncpy

	char* strncpy(char* destination,const char* source,size_t num);
	拷贝num个 字符从源字符串到目标空间
	如果源字符串的长度小于num，则拷贝完字符串后，在目标的后面追加0，直到num个
*/
//char* my_strncpy(char* str1, const char* str2, int num) {
//	char* dest = str1;
//	//num和str2的值都不能为0，任一为0退出循环
//	while (num && *str2) {
//		*str1 = *str2;
//		num--;
//		str1++;
//		str2++;
//	}
//	//上面循环退出，并没有把'\0'拷贝走
//	if (num != 0) {
//		while (num--) {
//			*str1 = '\0';
//			str1++;
//		}
//	}
//	return dest;
//}
//int main() {
//	char arr1[20] = "abcdefeghi";
//	char arr2[] = "hello";
//	printf("原来的arr1：%s\n", arr1);
//	strncpy(arr1, arr2, 8);//arr2位数不够会补'\0'
//	printf("新来的arr1：%s\n", arr1);
//	return 0;
//}
//char* my_strncpy(char* str1, const char* str2, int num) {
//	char* dest = str1;
//	
//	while (num && (*str1++=*str2++)) {
//		num--;
//	}
//	//上面循环退出，已经拷走了'\0'
//	if (num) {
//		while (--num) {
//			*str1++ = '\0';
//		}
//	}
//	return dest;
//}

/*
strncat
	char* strncat(char* destination,const char* source,size_t num);
	在目标字符串的'\0'后追加，会覆盖当前'\0'，并追加完后给上 一个'\0'
	追加的长度比源字符串长的话，只追加一个源字符串
*/
//char* my_strncat(char* str1, const char* str2, int num) {
//	char* dest = str1;
//	//先找'\0'
//	while (*str1++) {
//		;
//	}
//	//多加了一次需要捡回去
//	str1--;
//	//拷贝
//	while (num--&&(*str1++ = *str2++)) {
//		;
//	}
//	return dest;
//}
//int main() {
//	char arr1[20] = "hello\0xxxxxxxx";
//	char arr2[] = "world";
//	printf("原来的字符串：%s\n", arr1);
//	strncat(arr1, arr2, 8);
//	printf("新来的字符串：%s\n", arr1);
//}


/*
strncmp
	int strncmp(const char* str1,cosnt char* str2,size_t num);
	比较前num个字符
*/
//void F(double T, double k, double m) {
//	double s1, s2, s3;//突触小泡，神经突触，脑细胞
//	s1 = m * T;
//	s2 = s1 / 60;
//	s3 = s2 / 60;
//	double r = (double)k - s3;
//	printf("%lf\n", r);
//	if (r < 1) {
//		printf("Become a fool!\n");
//	}
//}
//int main() {
//	//次数，脑细胞数，通话时间
//	double T = 2;
//	double k = 1;
//	double m = 236+1000;
//	F(T, k, m);
//	return 0;
//}

int main() {
	int n;
	scanf("%d", &n);
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += i;
	}
	printf("%d", sum);
}