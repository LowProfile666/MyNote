#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//����һ���������飬
//1.ʵ�ֺ���init������ʼ������Ϊȫ0
//2.ʵ��printf������ӡ����ÿ��Ԫ��
//3.ʵ��reverse�����������Ԫ�ص�����
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
//	//���ǽ���һ���͵�����һ���������ڶ����͵����ڶ�����������
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
////		for (j = 0; j < 10-i; j++)//����д��10-j
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
//	init(arr,sz);//��ʼ��
//	print(arr);//��ӡ
//	//reverse(arr);//����1
//	reverse(arr, sz);
//	print(arr);//��ӡ
//	return 0;
//}


//��������
//ʹ����a������������b�����ݽ���������һ����
//int get_a(int a[])
//{
//	int i = 0;
//	printf("û������a���飺");
//	for (i = 0; i < 10; i++)
//	{
//		a[i] = i + 1;
//		printf("%d ", a[i]);
//	}
//	printf("\n");
//}
//int get_b(int b[])
//{
//	printf("û������b���飺");
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
//	printf("�������a���飺");
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", a[i]);
//	}
//	printf("\n");
//	printf("�������b���飺");
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", b[i]);
//	}
//	return 0;
//}

//int main()
//{
//	int arr[] = { 1,2,3,4,5 };
//	short* p = (short*)arr;//ÿ�η��������ֽ�
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
//	int a = 0x11223344;//�ڴ��д�ŷ�ʽ��44 33 22 11����������һ���ֽ�
//	char* p = (char*)&a;
//	*p = 0;//ֻ�ı���һ���ֽ�--->00 33 22 11���ڴ��У�
//	printf("%x", a);//���11 22 33 00
//	return 0;
//}

//int i;//ȫ�ֱ���������ʼ��Ĭ����0
//int main()
//{
//	i--;//-1
//	if (i > sizeof(i))//sizeof�������/������ռ�ڴ��С��>=0--���ص����޷�����
//		//��һ�������޷��������и�������ʱ���Ὣ�����ת��Ϊ�޷������ٽ���
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
 
//ͳ��һ������������1�ĸ���
//int  count_bit_one(unsigned int a)
//{
//	int count = 0;
//	while (a)
//	{
//		a = a & (a - 1);
//		//ÿִ��һ��ȥ��һ��1ֱ��0��ִ�м��ξ��м���1��
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
//	//Ӧ���㲹���е�1�ĸ���
//	int a = 0;
//	scanf("%d", &a);
//	int count = count_bit_one(a);
//	printf("count=%d\n", count);
//	return 0;
//}

//���������Ķ����ƵĲ�ͬλ��
//int get_diff_bit(int m, int n)
//{
//	int tmp = m ^ n;//��λ�����ͬλ0������Ϊ1
//	int count = 0;
//	while (tmp)
//	{
//		tmp = tmp & (tmp - 1);//ִ�м��ξ��м���1����֪���ж���λ��ͬ
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

//��ӡһ�����Ķ����Ƶ�����λ��ż��λ
//void print(int  m)
//{
//	int i = 0;
//	printf("�����������λ��\n");
//	for (i = 30; i >= 0; i -= 2)
//	{
//		printf("%d ", (m >> i) & 1);//��λ��1�ܱ�ʾ����һλ��1����0��1&1=1��0&1=0
//	}
//	printf("\n");
//	printf("�������ż��λ��\n");
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

//����������������������������
//int  exchange(int m, int n)
//{
//��λ���
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

//ʹ��ָ���ӡ���������
//void print(int arr[], int sz)
//{
//	int* p = arr;//��Ԫ��
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ",*(p+i) );//p+i����i��Ԫ�أ�Ҳ����ÿһ��Ԫ��
//	}
//}
//int main()
//{
//	int arr[5] = { 0 ,1,2,3,4};
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	print(arr, sz);
//	return 0;
//}

//�ж�100-200������
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

//��ӡ���������Զ��ĳ˷��ھ���
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
  
//�ݹ鷽ʽ��ӡ����ÿһλ
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
//�ݹ���׳�
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
//�ݹ�ʵ��һ������ÿλ֮��
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

//�ݹ�ʵ��n��k�η�
//double F(int n, int k)
//{
//	if (k < 0)
//		return (1/(F(n, -k)));//С�������εĻ������0��������double
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


