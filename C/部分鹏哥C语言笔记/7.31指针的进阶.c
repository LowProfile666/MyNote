#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <string.h>

//1.字符数组 

//2.指针数组--是数组，用来存放指针
//int main()
//{
//	int arr1[10] = { 0 };//整形数组
//	char arr2[5] = { 0 };//字符数组
//	int* parr[10];//存放整形指针的指针数组
//	char* pch[2];//存放字符指针的指针数组
//	return 0;
//}

//int main()
//{
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	int* arr[4] = { &a,&b,&c,&d };
//	int i = 0;
//	for (i = 0; i < 4; i++)
//	{
//		printf("%p\n", arr[i]);
//		printf("%d\n", *arr[i]);
//
//	}
//	return 0;
//}

//int main()
//{
//	int arr1[] = { 1,2,3,4,5 };
//	int arr2[] = { 2,3,4,5,6 };
//	int arr3[] = { 3,4,5,6,7 };
//	int* parr[] = { arr1,arr2,arr3 };
//	int i = 0;
//	for (i = 0; i < 3; i++)
//	{
//		int j = 0;
//		for (j = 0; j < 5; j++)
//		{
//			printf("%d ", *(parr[i] + j));
//		}
//		printf("\n");
//	}
//	return 0;
//}



//数组指针--指针--能够指向数组的指针--存放数组的地址
//int main()
//{
//	int* p = NULL;//整形指针--指向整形的指针--存放整形的地址
//	char* pc = NULL;//字符指针--指向字符的指针--存放字符的地址
//	//int arr[10] = { 0 };
//	//arr--首元素地址
//	//&arr[0]-首元素地址
//	//&arr--数组的地址
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int (*p)[10] = &arr;//数组的地址存起来
//	//上面的p就是数组指针
//
//	return 0;
//}
//
//int main()
//{
//	char* arr[5];//指针数组
//	char (*pa)[5] = &arr;//数组指针
//	//[5]说明pa指向的数组是5个元素的
//	//char说明pa指向的数组的元素类型是char*的
//	//*说明pa是指针
//	//pa是指针名字
//	return 0;
//}

// int main()
// {
// 	int arr[10] = { 0 };
// 	printf("arr=%p\n", arr);//首元素地址
// 	printf("&arr=%p\n",&arr);//数组地址

// 	printf("arr+1=%p\n", arr + 1);
// 	printf("&arr+1=%p\n", &arr + 1);
// 	return 0;
// }
//&arr表示的是数组的地址，而不是数组首元素的地址。
//数组的地址+1，跳过整个数组的大小，所以&arr+1相对于&arr的差值是40

//一般数组指针不这么用
/*
int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9 };
	int(*p)[9] = &arr;
	int i = 0;
	
	for (i = 0; i < 9; i++)
	{
		printf("%d ", (*p)[i]);//打印出每个元素
		//printf("%d ", *(*p + i));
	}
	return 0;
}*/

//void print(int arr[3][4], int x, int y)
//{//参数是数组形式
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < x; i++)
//	{
//		for (j = 0; j < y; j++)
//		{
//			printf("%d ", arr[i][j]);
//		}
//		printf("\n");
//	}
//}
//void print2(int(*p)[4], int x, int y)
//{//参数是指针形式
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < x; i++)
//	{
//		for (j = 0; j < y; j++)
//		{
//			printf("%d ", *(*(p + i) + j));
//		}
//		printf("\n");
//	}
//}
//int main()
//{
//	int arr[3][4] = { {1,2,3,4},{2,3,4,5},{3,4,5,6} };
//	print(arr, 3, 4);//arr-数组名-首元素地址
//	print2(arr, 3, 4);
//	return 0;
//}
//
//int arr[5];                //arr是一个5个元素的整型数组
//int* parr1[10];        //parr1是一个数组，有10个元素，元素类型是int*，parr1是指针数组
//int(*parr2)[10];      //parr2是一个指针，该指针指向了一个数组，数组有10个元素，类型是int，parr2是数组指针
//int(*parr3[10])[5]; //parr3先和[]结合，所以他是一个数组，该数组有10个元素，每个元素是一个数组指针，
//                     //该数组指针指向的数组有5个元素，每个元素是int

/*
//数组参数，指针参数 
//一维数组传参
//[]内的数字可以以省略
void text(int arr[])
{}//这个传参是对的
void text(int arr[10])
{}//这个传参是对的
void text(int *arr)
{}//这个传参是对的
void text2(int* arr[20])
{}//这个传参是对的
void text2(int** arr)
{}//这个传参是对的
int main()
{
	int arr[10] = { 0 };//整型数组
	int* arr2[20] = { 0 };//指针数组
	test(arr);
	test2(arr2);//这首元素地址是一个一级指针的地址，所以传到二级指针去没有问题
	return 0:
}

//二维数组的传参
//第一个[]内可以省略，第二个[]绝对不能省略
void text(int arr[3][5])
{}
//void text(int* arr)
//{}//这个传参是错的
//void text(int* arr[5])
//{}//这个传参是错的
//void text2(int arr[3][])
//{}//这个传参是错的
//void text3(int arr[][])
//{}//这个传参是错的
//void text3(int* arr)
//{}//这个传参是错的
//text4(int** arr)
//{}//这个传参是错的
void text5(int (*arr)[5])
{}//对的     这是一个指向五个int元素的地址的指针，可以用来接受二维数组的首行地址
int main()
{
	int arr[3][5] = { 0 };

	text(arr);
	text1(arr);
	text2(arr);
	text3(arr);
	text4(arr);//首元素地址就是第一行的地址，二级指针是用来放一级指针的地址的，所以text4错误
	text5(arr);
	return 0;
}


//一级指针的传参
void test1(int* p1)
{}

void test2(char* p2)
{}
int main()
{
	int a = 10;
	int* p1 = &a;
	test(&a);//ok
	test(p1);//ok
	char ch = "w";
	char* p2 = &ch;
	test2(&ch);//ok
	test2(p2);//ok
	return 0;
}

//二级指针的传参
void test(int **p)
{}
int main()
{
	int* ptr;
	int** pp = &ptr;
	test(&ptr);
	test(pp);
	int* arr[10];//指针数组也可以
	test(arr);
	return 0;
}


//数组指针--指向数组的指针
//函数指针--指向函数的指针--存放函数地址的指针

int Add(int a, int b)
{
	int z = 0;
	z = a + b;
	return z;
}
int main()
{
	int a = 10;
	int b = 20;
	printf("%d\n", Add(a, b));
	//&函数名 和 函数名 都是函数的地址
	printf("%p\n", &Add);//
	printf("%p\n", Add);//这两个输出结果完全一样
	int (*p)(int, int) = Add;//和数组指针类似：int (*arr)[10]=arr;
	printf("%d", (*p)(3, 5));//结果是8
	return 0;
}

void print(char* str)
{
	printf("%s\n", str);
}
int main()
{
	void (*p)(char*) = print;
	(*p)("hello bit");
	return 0;
}*/

//函数指针数组
//int add(int x, int y)
//{
//	return x + y;
//}
//int sub(int x, int y)
//{
//	return x - y;
//}
//int mul(int x, int y)
//{
//	return x * y;
//}
//int div(int x, int y)
//{
//	return x / y;
//}
//int main()
//{
//	//指针数组
//	int* arr[5];
//	//需要一个数组，这个数组可以存放四个函数的地址-函数指针的数组
//	int (*parr[4])(int, int) = { add,sub,mul,div };//函数指针的数组
//parr[4]数组名 int(*)(int,int)类型
//	int i = 0;  
//	for (i = 0; i < 4; i++)
//	{
//		printf("%d ", parr[i](2, 3));
//	}
//	return 0;
//}

////写一个函数指针pf，指向my_strcpy
//char (*pf)(char, char);
////写一个函数指针数组，能够存放my_strcpy函数的地址
//char (*p[4])(char, char);
//

 //指向函数指针数组的指针
//是一个 指针 ，指针指向一个 数组 ，数组的元素都是 函数指针 。

//void test(const char* str)
//{
//	printf("%s\n", str);
//}
//int main()
//{
//	//函数指针pfun
//	void (*pfun)(const char*) = test;
//	//函数指针的数组pfArr
//	char (*pfArr[1])(const char*);
//	//指向函数指针数组的指针
//	char (*(*pfArr)[1])(const char*)=&pfArr[1];
//}



//回调函数
//就是一个通过函数指针调用的函数，
//如果你把函数的指针（地址）作为参数传递给另一个函数
//当这个指针被用来调用其所指向的函数时，我们说这就是回调函数
//回调函数不是由该函数的实现方式直接调用，而是在特定的事件或条件发生时由另一方调用的，
//用于会该事件或条件进行响应


																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																		
//qsort--可以排序任意类型数据
//quick sort
// qsort();
//第一个参数：待排序数组的首元素地址
//第二个参数：待排序数组的元素个数
//第三个参数：待排序数组的每个元素的大小，单位字节
//第四个参数：是函数指针，比较两个元素所用函数的地址，这个函数使用者自己实现
// 						  函数指针的两个参数是：待比较的两个元素的地址
 
//int main()
//{
	//数组名是首元素地址
	//两个例外：1.sizeof（数组名)-表示整个数组
	//					  2.&数组名-表示整个数组

	//一维数组
//int a[] = { 1,2,3,4 };
//	printf("%d\n", sizeof(a));    //sizeof(数组名)-计算的是数组总大小-单位是字节-16
//	printf("%d\n", sizeof(a+0));//这里的a表示首元素地址-4
//	printf("%d\n", sizeof(*a));  //a是首元素地址-4
//	printf("%d\n", sizeof(a+1));//a是首元素地址，a+1是第二个元素-4
//	printf("%d\n", sizeof(a[1]));//4-第二个元素大小
//	printf("%d\n", sizeof(&a));  //&a取出的是数组的地址，但是数组的地址也是地址，地址的大小就是4
//	printf("%d\n", sizeof(*&a));//16-&a是数组的地址，解引用后访问的数组
//	printf("%d\n", sizeof(&a+1));//4-&a是数组的地址，&a+1虽然地址跳过整个数组，但还是地址，所以4
//	printf("%d\n", sizeof(&a[0]));//4-都一个元素的地址
//	printf("%d\n", sizeof(&a[0]+1));//4-第二个元素的地址





	//字符数组
	//char arr[] = { 'a','b','c','d','e','f' };
	//printf("%d\n", sizeof(char));//1
	//printf("%d\n", sizeof(arr)) ;     //6-siazeof计算的是数组大小：6*1=6字节
	//printf("%d\n", sizeof(arr+0));  //4-首元素地址-地址都是4或8字节
	//printf("%d\n", sizeof(*arr));    //1-arr是首元素地址，*arr就是首元素是字符，大小是一个字节
	//printf("%d\n", sizeof(arr[1])); //1-第二个元素
	//printf("%d\n", sizeof(&arr));   //4-数组地址
	//printf("%d\n", sizeof(&arr+1));//4-&arr+1是跳过整个数组后的地址
	//printf("%d\n", sizeof(&arr[0]+1));//4-第二个元素的地址

	//strlen求字符串长度，找到\0停止
	//printf("%d\n", strlen(arr));//随机值-不知道后面什么时候能找到"\0"
	//printf("%d\n", strlen(arr+0));//随机值-同上
	////printf("%d\n", strlen(*arr));//err-*arr是首元素'a'，相当于传过来了 97 ，然后strlen从97往后数，非法访问
	////printf("%d\n", strlen(arr[1]));//err-arr[1]是第二个元素，同上
	//printf("%d\n", strlen(&arr));//随机值-从数组头开始往后数，什么时候遇到\0不清楚
	//printf("%d\n", strlen(&arr+1));//随机值-跳过整个数组，从数组最后开始往后数，什么时候遇到\0不清楚，与上面的随机值差6
	//printf("%d\n", strlen(&arr[0]+1));//随机值-从第二个元素开始往后，与第一个随机值差值为1

//return 0;
//}



//int main()
//{
//	
	//char arr[] = "abcdef"; //一个字符是一个元素

	//printf("%d\n", sizeof(arr));//7-后面还有一个‘\0’sizeof计算数组的大小
	//printf("%d\n", sizeof(arr+0));//4-arr+0是首元素地址-计算的是地址的大小
	//printf("%d\n", sizeof(*arr));//1-*arr是首元素
	//printf("%d\n", sizeof(arr[1]));//1-计算第二个元素的大小
	//printf("%d\n", sizeof(&arr));//4-整个数组的地址
	//printf("%d\n", sizeof(&arr+1));//4-跳过整个数组的地址
	//printf("%d\n", sizeof(&arr[0]+1));//4-第二个元素的地址大小

	//printf("%d\n", strlen(arr));//6
	//printf("%d\n", strlen(arr + 0));//6
	////printf("%d\n", strlen(*arr));//err-strlen访问地址，*arr是首元素a，相当于传过来一个97，以97为地址往后访问，非法访问err
	////printf("%d\n", strlen(arr[1]));//err-arr[1]是第二个元素，同上
	//printf("%d\n", strlen(&arr));//6-数组的地址-数组指针-char(*p)[7]=&arr;
	//printf("%d\n", strlen(&arr + 1));//随机值
	//printf("%d\n", strlen(&arr[0] + 1));//5
	/*for (int i = 0; i < strlen(arr); i++)
	{
		printf("%c ", arr[i]);

	}
	printf("%d", arr[6]);*/


	//char* p = "abcdef";//将这个常量字符串的首字母a的地址放在了p里面

	//printf("%d\n", sizeof(p));//4-计算指针变量p的大小
	//printf("%d\n", sizeof(p+1));//4-p+1得到的是字符b的地址
	//printf("%d\n", sizeof(*p));//1-*p就是字符串第一个字符a
	//printf("%d\n", sizeof(p[0]));//1-p[0]是a--int arr[10];arr[0]==*(arr+0);=>p[0]==*(p+0)
	//printf("%d\n", sizeof(&p));//4-p的地址
	//printf("%d\n", sizeof(&p+1));//4-跳过p的地址，还是个地址
	//printf("%d\n", sizeof(&p[0]+1));//4-p[0]是a,&p[0]就是p的地址
	//printf("%c", *p);
	

	//printf("%d\n", strlen(p));//6-p是a的地址，
	//printf("%d\n", strlen(p + 1));//5-第二个元素开始往后
	////printf("%d\n", strlen(*p));//err
	////printf("%d\n", strlen(p[0]));//err
	//printf("%d\n", strlen(&p));//随机值
	//printf("%d\n", strlen(&p + 1));//随机值
	//printf("%d\n", strlen(&p[0] + 1));//5



	//二维数组
	//int a[3][4] = { 0 };

	//printf("%d\n", sizeof(a));//12*4=48--数组总大小
	//printf("%d\n", sizeof(a[0][0]));//1*4=4--一个整形的大小
	//printf("%d\n", sizeof(a[0]));//4*4=16--a[0]相当于第一行作为一维数组的数组名，sizeof(a[0])把数组名单独放在sizeof内计算的是第一行的大小
	//printf("%d\n", sizeof(a[0]+1));//4--这里a[0]是第一行数组名，表示的是第一行第一个元素地址，所以+1表示第一行第二个地址，地址大小是4/8个字节
	//printf("%d\n", sizeof(*(a[0] + 1)));//4--第一行第二个元素的大小
	//printf("%d\n", sizeof(a+1));//4--a是二维数组数组名，这里表示首元素地址，二维数组的首元素是第一行，a+1就是第二行地址。
	//printf("%d\n", sizeof(*(a+1)));//16--第二行元素的大小
	//printf("%d\n", sizeof(&a[0]+1));//4--&a[0]是第一行的地址，+1后是第二行地址
	//printf("%d\n", sizeof(*(&a[0] + 1)));//16--第二行元素的大小
	//printf("%d\n", sizeof(*a));//16--a代表首元素地址，就是第一行的地址，*a就是第一行的元素
	//printf("%d\n", sizeof(a[3]));//16--sizeof不会访问()内的内容，只会按照类型来计算大小，a[3]不存在但是sizeof不会区访问，只把他当成第四行元素
	//return 0;
//}


//int main() {
//	unsigned long pulArray[] = { 6,7,8,9,10 };
//	unsigned long* pulPtr;
//	pulPtr = pulArray;			//pulPtr指向6
//	*(pulPtr + 3) += 3;			//+3指向9，*(pulPtr + 3)=9+3=12
//	printf("%d %d \n", *pulPtr, *(pulPtr + 3));//6 12
//	return 0;
//}



//写一个逆序字符串的函数
//void NIXU(char* arr) {
//
//	//int front = 0;
//	//int rear = strlen(arr) - 1;
//	//while (front < rear) {
//	//	int temp = arr[front];
//	//	arr[front] = arr[rear];
//	//	arr[rear] = temp;
//	//	front++;
//	//	rear--;
//	//}
//
//	char* left = arr;
//	char* right = left + strlen(arr) - 1;
//	while (left < right) {
//		char temp = *left;
//		*left = *right;
//		*right = temp;
//		left++;
//		right--;
//	}
//
//	printf("逆序后的字符串：%s", arr);
//}
//int main() {
//	char arr[100] = { 0 };
//	//scanf("%s", arr);//遇到空格会结束读取
//	gets(arr);//读取一行放到arr里面
//	printf("\n原来的字符串：%s\n", arr);
//	NIXU(arr);
//	return 0;
//}

//计算求和，求Sn=a+aa+aaa+aaaa+aaaaa的前五项之和，a是一个数字
//int Sn(int a,int n) {
//	int sum = 0;
//	int m = 0;
//	for (int i = 0; i < n; i++) {
//		m = m * 10 + a;
//		printf("%d\n", m);
//		sum += m;
//	}
//	return sum;
//}
//int main() {
//	int a;
//	int n;
//	scanf("%d%d", &a,&n);
//	int sum=Sn(a,n);
//	printf("%d", sum);
//	return 0;
//}

//水仙花数，求出0-100000之间的 所有水仙花数
//水仙花数是指一个n位数，其各位数字的n次方和等于该数本身
//#include<math.h>
//int main() {
//	for (int i = 0; i <= 100000; i++) {
//		//1、计算i的位数
//		int n = 1;		//起码一位数
//		int m = i;
//		while (m/=10) {//i/10等于0的时候就是最后一位数了，不用再进去
//			n++;
//		}
//		//下面这种循环判断完位数
//	/*	int n = 0;
//		while (m) {
//			m /= 10;
//			n++;
//		}*/
//
//		//2、计算i的每一位的n次方之和
//		int sum = 0;
//		m = i;
//		while (m) {
//			sum += pow(m % 10, n);
//			m /= 10;
//			/*函数名称:   pow
//函数原型:   double pow( double x, double y );
//函数功能:   计算x的y次幂
//所属文件:   <math.h>*/
//		}
//		//3、比较i和sum
//		if (i == sum) {
//			printf("%d ", i);
//		}
//	}
//	return 0;
//}

//打印菱形
//int main() {
//	int n;	//上班部分行数
//	scanf("%d", &n);	
//	//上半部分：
//	for (int i = 1; i <= n; i++) {	//行数做循环条件
//		//1、打印空格
//		for (int j = 0; j < n - i; j++) {	
//			printf(" ");
//		}
//		//2、打印*号
//		for (int j = 0; j < 2*i-1; j++) {
//			printf("*");
//		}
//		//3、没打印完一排换行
//		printf("\n");
//	}
//	//下半部分：
//	for (int i = 1; i <= n - 1; i++) {
//		for (int j = 0; j < i; j++) {
//			printf(" ");
//		}
//		for (int j = 0; j < 2*(n-1-i)+1; j++) {
//			printf("*");
//		}
//		printf("\n");
//	}
//	return 0;
//}


//旋转字符串
//实现一个函数，可以左旋字符串中的k个字符
//ABCD左旋一个字符为BCDA
//ABCD左旋两个字符为CDAB

#include<assert.h>
//1、暴力求解法：
//void left_move(char* arr, int k) {
//	int len = strlen(arr);
//	assert(arr);
//	assert(k < len&& k >= 0);
// //将旋转的第一个字符先存起来，然后将这个字符的后面的字符依次往前移，然后再把旋转的字符放在最后
//	for (int i = 0; i < k; i++) {//旋转几次就循环几次
//		char tmp = arr[0];//*arr
//		for (int j = 0; j < len-1; j++) {
//			arr[j] = arr[j + 1];
//			//*(arr+j)=*(arr+j+1);
//		}
//		arr[len - 1] = tmp;
//	}
//}

//2、三步翻转法
//把一个字符串分为两部分，一部分是要旋转部分，另一部分是不旋转部分
//ab cdef
//先将要旋转部分逆序：ba cdef
//再将不旋转部分逆序：ba fedc
//最后将全部部分逆序：cdefab
//得到旋转后的字符串

void inversion(char* left, char* right) {
	assert(left);
	assert(right);
	while (left < right) {
		char tmp = *left;
		*left = *right;
		*right = tmp;
		left++;
		right--;
	}
}

void left_move(char* arr,int k) {
	assert(arr);
	int len = strlen(arr);
	//用头尾指针来进行逆序
	//1、要旋转部分
	inversion(arr, arr + k - 1);//arr是头地址，arr+k-1是这部分的尾地址
	//2、不旋转部分
	inversion(arr + k, arr + len - 1);
	//3、全部部分
	inversion(arr, arr + len - 1);

}
//int main() {
//	char arr[20] = "0";
//	scanf("%s", arr);
//	int k;
//	scanf("%d", &k);
//	left_move(arr,k);
//	printf("%s", arr);
//	return 0;
//}
//
////1、暴力求解法
///*将原字符串所有的旋转可能都拿出来与另一字符串比较，若有相同的则yes*/
//int is_left_move(char* arr1, char* arr2) {
//	int len = strlen(arr1);
//	for (int i = 0; i < len; i++) {
//		left_move(arr1, 1);//因为是一个一个字符旋转，所以这里旋转个数只能写1
//		if (strcmp(arr1, arr2) == 0)
//			return 1;
//	}
//	return 0;
//}
//2、优化算法
/*在源字符串上加上一个原字符串，然后与另一字符串比较有没有相同部分，如：
arr1="abcdef"-->arr1="abcdefabcdef";
				arr2="cdefab"
用双指针
*/
//让原来的字符串再加一个原来的字符串 
void F(char* arr1) {
	int len = strlen(arr1);
	char* top = arr1;
	char* rear = arr1 + len;
	for (int i = 0; i < len; i++) {
		*rear = *top;
		top++;
		rear++;
	}
}
int is_left_move(char* arr1, char* arr2) {
	assert(arr1);
	assert(arr2);
	/*如果两个字符串不相同那肯定不是由旋转过来的*/
	if (strlen(arr1) != strlen(arr2))
		return 0;
	F(arr1);
	char* top1 = arr1;//arr1的头指针
	char* top2 = arr2;//arr2的头指针
	char* rear1 = arr1;//arr1的尾指针
	/*当arr2的第一个字符和arr1里的某一个字符相同时，top1就不动了，rear1与top2向后移动
	  当rear1-top1即连续相同字符数等于arr2的长度时，说明arr2是由arr1旋转过来的*/
	while (top2<arr2+strlen(arr2)) {
		if (*rear1 == *top2) {
			top2++;
			rear1++;
		}
		else {
			rear1++;
			top1=rear1;
		}
		if (rear1 - top1 == strlen(arr2))
			return 1;
	}
	return 0;

}

//判断字符串是否由字符串旋转得到的
//如cdefab是由abcdef旋转得到的
// int main() {
// 	char arr1[100] = "abcde";
// 	char arr2[100] = "bcdea";
// 	int n=is_left_move(arr1,arr2);
// 	if (n == 1)
// 		printf("yes\n");
// 	else
// 		printf("no\n");
// 	return 0;
// }