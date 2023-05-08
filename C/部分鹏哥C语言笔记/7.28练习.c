#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//创建一个整形数组，
//1.实现函数init（）初始化数组为全0
//2.实现printf（）打印数组每个元素
//3.实现reverse（）完成数组元素的逆置
//void init(int arr[],int sz)
//{
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		//arr[i]=0;
//		arr[i] = i+1;
//	}
//}
//void reverse(int arr[],int sz)
//{
//	int left = 0;
//	int right = sz - 1;
//	//就是将第一个和倒数第一个交换，第二个和倒数第二个交换……
//	while (left<right)
//	{
//		int temp = arr[left];
//		arr[left] = arr[right];
//		arr[right] = temp;
//		left++;
//		right--;
//	}
//}
////void reverse(int arr[])
////{
////	int i = 0;
////	int j = 0;
////	for (i = 0; i < 10; i++)
////	{
////		for (j = 0; j < 10-i; j++)//不能写成10-j
////		{
////			if (arr[j] < arr[j+1])
////			{
////				int temp = arr[j];
////				arr[j] = arr[j+ 1];
////				arr[j+ 1] = temp;
////			}
////		}
////	}
////}
//void print(int arr[])
//{
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	printf("\n");
//}
//int main()
//{
//	int arr[10] = { 0 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	init(arr,sz);//初始化
//	print(arr);//打印
//	//reverse(arr);//逆置1
//	reverse(arr, sz);
//	print(arr);//打印
//	return 0;
//}


//交换数组
//使数组a的内容与数组b的内容交换（数组一样大）
//int get_a(int a[])
//{
//	int i = 0;
//	printf("没交换的a数组：");
//	for (i = 0; i < 10; i++)
//	{
//		a[i] = i + 1;
//		printf("%d ", a[i]);
//	}
//	printf("\n");
//}
//int get_b(int b[])
//{
//	printf("没交换的b数组：");
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		b[i] = i * 2;
//		printf("%d ", b[i]);
//	}
//	printf("\n");
//}
//void exchange(int a[], int b[])
//{
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//           int t = a[i];
//	       a[i] = b[i];
//	       b[i] = t;
//	}
//}
//int main()
//{
//	int i = 0;
//	int a[10] = { 0 };
//	int b[10] = { 0 };
//	get_a(a);
//	get_b(b);
//	exchange(a, b);
//	printf("交换后的a数组：");
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", a[i]);
//	}
//	printf("\n");
//	printf("交换后的b数组：");
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", b[i]);
//	}
//	return 0;
//}

//int main()
//{
//	int arr[] = { 1,2,3,4,5 };
//	short* p = (short*)arr;//每次访问两个字节
//	int i = 0;
//	for (i = 0; i < 4; i++)
//	{
//		*(p + i) = 0;
//	}
//	for (i = 0; i < 5; i++)
//	{
//		printf("%d ", arr[i]);
//
//	}
//	return 0;
//}
//
//int main()
//{
//	int a = 0x11223344;//内存中存放方式是44 33 22 11，两个数字一个字节
//	char* p = (char*)&a;
//	*p = 0;//只改变了一个字节--->00 33 22 11（内存中）
//	printf("%x", a);//输出11 22 33 00
//	return 0;
//}

//int i;//全局变量，不初始化默认是0
//int main()
//{
//	i--;//-1
//	if (i > sizeof(i))//sizeof计算变量/类型所占内存大小恒>=0--返回的是无符号数
//		//当一个数和无符号数进行各种运算时，会将这个数转换为无符号数再进行
//	{
//		printf(">\n");
//	}
//	else
//	{
//		printf("<");
//	}
//	return 0;
//}
//
//int main()
//{
//	int a, b, c;
//	a = 5;
//	c = ++a;
//	b = ++c, c++, ++a, a++;
//	b += a++ + c;
//	printf("a=%d b=%d c=%d", a, b, c);//9 23 8
//	return 0;
//}
 
//统计一个数二进制中1的个数
//int  count_bit_one(unsigned int a)
//{
//	int count = 0;
//	while (a)
//	{
//		a = a & (a - 1);
//		//每执行一次去掉一个1直到0，执行几次就有几个1，
//		count++;
//	}
//	//while (a)
//	//{
//	//	if (a % 2 == 1)
//	//		count++;
//	//	a = a / 2;
//	//}
//	return count;
//}
//int main()
//{
//	//应该算补码中的1的个数
//	int a = 0;
//	scanf("%d", &a);
//	int count = count_bit_one(a);
//	printf("count=%d\n", count);
//	return 0;
//}

//求两个数的二进制的不同位数
//int get_diff_bit(int m, int n)
//{
//	int tmp = m ^ n;//按位异或，相同位0，相异为1
//	int count = 0;
//	while (tmp)
//	{
//		tmp = tmp & (tmp - 1);//执行几次就有几个1，就知道有多少位不同
//		count++;
//	}
//	return count;
//}
//int main()
//{
//	int m = 0;
//	int n = 0;
//	scanf("%d%d", &m, &n);
//	int count=get_diff_bit(m, n);
//	printf("count=%d\n", count);
//	return 0;
// }

//打印一个数的二进制的奇数位和偶数位
//void print(int  m)
//{
//	int i = 0;
//	printf("这个数的奇数位：\n");
//	for (i = 30; i >= 0; i -= 2)
//	{
//		printf("%d ", (m >> i) & 1);//按位与1能表示出这一位是1还是0，1&1=1，0&1=0
//	}
//	printf("\n");
//	printf("这个数的偶数位：\n");
//	for (i = 31; i >= 1; i -= 2)
//	{
//		printf("%d ", (m >> i) & 1);
//	}
//}
//int main()
//{
//	int m = 0;
//	scanf("%d", &m);
//	print(m);
//	return 0;
//}

//不创建变量交换两个整数的内容
//int  exchange(int m, int n)
//{
//按位异或
//	m = m ^ n;
//	n = m ^ n;
//	m = m ^ n;
//	printf("m=%d,n=%d\n", m, n);
//
//}
//int main()
//{
//	int m = 0;
//	int n = 0;
//	scanf("%d%d", &m, &n);
//	printf("m=%d,n=%d\n", m, n);
//	exchange(m, n);
//	return 0;
//}

//使用指针打印数组的内容
//void print(int arr[], int sz)
//{
//	int* p = arr;//首元素
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ",*(p+i) );//p+i跳过i个元素，也就是每一个元素
//	}
//}
//int main()
//{
//	int arr[5] = { 0 ,1,2,3,4};
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	print(arr, sz);
//	return 0;
//}

//判断100-200的素数
//int main()
//{
//	int i = 0;
//	for (i = 100; i <= 200; i++)
//	{
//		int j = 0;
//		for (j = 2; j <=i-1; j++)
//		{
//			if (i % j == 0) 
//			{
//				break;
//			}	
//		}
//		if (i == j)
//			printf("%d ", i);
//	}
//	return 0;
//}

//打印行数列数自定的乘法口诀表
//int main()
//{
//	int i = 0;
//	int input = 0;
//	scanf("%d", &input);
//	for (i = 1; i <= input; i++)
//	{
//		int j = 0;
//		for (j = 1; j <= i; j++)
//		{
//			printf("%d*%d=%2d|", j, i, i * j);
//		}
//		printf("\n");
//	}
//	return 0;
//}

//int f(int arr[][3], int n, int sz)
//{
//    int i = 0;
//    for (i = 0; i < sz; i++)
//    {
//        int j = 0;
//        for (j = 0; j < 3; j++)
//        {
//            if (arr[i][j] == n)
//                return 1;
//        }
//    }
//    return 0;
//}
//int main()
//{
//    int arr[][3] = { 1,2,3,4,5,6,7,8,9 };
//    int n = 0;
//    int sz = sizeof(arr) / sizeof(arr[0][0]);
//    scanf("%d", &n);
//    int ret = f(arr, n, sz);
//    if (ret == 1)
//    {
//        printf("ture");
//    }
//    else
//    {
//        printf("false");
//    }
//    return 0;
//}
//
  
//递归方式打印数的每一位
//int print(int n)
//{
//	if (n > 9)
//	{
//		print(n / 10);
//	}
//	printf("%d ", n % 10);
//}
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	print(n);
//	return 0;
//}
//递归求阶乘
//int f(int n)
//{
//	int ret;
//	if (n <= 1)
//		return 1;
//	else
//		return ret=n* f(n - 1);
//}
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	f(n);
//	printf("%d", f(n));
//	return 0;
//}
//
//
//void revese_string(char arr[], int sz)
//{
//	int left = 0;
//	int right = sz - 1;
//	while (left < right)
//	{
//		int tmp = arr[left];
//		arr[left] = arr[right];
//		arr[right] = tmp;
//		left++;
//		right--;
//	}
//}
//int main()
//{
//	char arr[] = "abcdefg";
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	revese_string(arr, sz);
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%c ", arr[i]);
//	}
//	return 0;
//}
//递归实现一个数的每位之和
//int digitsum(int num)
//{
//	if (num > 9)
//	{
//		return digitsum(num / 10) + num % 10;
//	}
//	else
//	{
//		return num;
//	}
//}
//int main()
//{
//	int ret = 0;
//	int num = 0;
//	scanf("%d", &num);
//	ret=digitsum(num,ret);
//	printf("%d", ret);
//	return 0;
//}

//递归实现n的k次方
//double F(int n, int k)
//{
//	if (k < 0)
//		return (1/(F(n, -k)));//小数用整形的话会输出0，所以用double
//	else if ( k == 0)
//		return 1;
//	else if (n == 0)
//		return 0;
//	else
//		return n * F(n,k - 1);
//}
//double main()
//{
//	int n = 0;
//	int k = 0;
//	scanf("%d%d", &n, &k);
//	int ret=F(n, k);
//	printf("%d", ret);
//	return 0;
//}


