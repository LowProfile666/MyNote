#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <string.h>

//1.�ַ����� 

//2.ָ������--�����飬�������ָ��
//int main()
//{
//	int arr1[10] = { 0 };//��������
//	char arr2[5] = { 0 };//�ַ�����
//	int* parr[10];//�������ָ���ָ������
//	char* pch[2];//����ַ�ָ���ָ������
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



//����ָ��--ָ��--�ܹ�ָ�������ָ��--�������ĵ�ַ
//int main()
//{
//	int* p = NULL;//����ָ��--ָ�����ε�ָ��--������εĵ�ַ
//	char* pc = NULL;//�ַ�ָ��--ָ���ַ���ָ��--����ַ��ĵ�ַ
//	//int arr[10] = { 0 };
//	//arr--��Ԫ�ص�ַ
//	//&arr[0]-��Ԫ�ص�ַ
//	//&arr--����ĵ�ַ
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int (*p)[10] = &arr;//����ĵ�ַ������
//	//�����p��������ָ��
//
//	return 0;
//}
//
//int main()
//{
//	char* arr[5];//ָ������
//	char (*pa)[5] = &arr;//����ָ��
//	//[5]˵��paָ���������5��Ԫ�ص�
//	//char˵��paָ��������Ԫ��������char*��
//	//*˵��pa��ָ��
//	//pa��ָ������
//	return 0;
//}

// int main()
// {
// 	int arr[10] = { 0 };
// 	printf("arr=%p\n", arr);//��Ԫ�ص�ַ
// 	printf("&arr=%p\n",&arr);//�����ַ

// 	printf("arr+1=%p\n", arr + 1);
// 	printf("&arr+1=%p\n", &arr + 1);
// 	return 0;
// }
//&arr��ʾ��������ĵ�ַ��������������Ԫ�صĵ�ַ��
//����ĵ�ַ+1��������������Ĵ�С������&arr+1�����&arr�Ĳ�ֵ��40

//һ������ָ�벻��ô��
/*
int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9 };
	int(*p)[9] = &arr;
	int i = 0;
	
	for (i = 0; i < 9; i++)
	{
		printf("%d ", (*p)[i]);//��ӡ��ÿ��Ԫ��
		//printf("%d ", *(*p + i));
	}
	return 0;
}*/

//void print(int arr[3][4], int x, int y)
//{//������������ʽ
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
//{//������ָ����ʽ
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
//	print(arr, 3, 4);//arr-������-��Ԫ�ص�ַ
//	print2(arr, 3, 4);
//	return 0;
//}
//
//int arr[5];                //arr��һ��5��Ԫ�ص���������
//int* parr1[10];        //parr1��һ�����飬��10��Ԫ�أ�Ԫ��������int*��parr1��ָ������
//int(*parr2)[10];      //parr2��һ��ָ�룬��ָ��ָ����һ�����飬������10��Ԫ�أ�������int��parr2������ָ��
//int(*parr3[10])[5]; //parr3�Ⱥ�[]��ϣ���������һ�����飬��������10��Ԫ�أ�ÿ��Ԫ����һ������ָ�룬
//                     //������ָ��ָ���������5��Ԫ�أ�ÿ��Ԫ����int

/*
//���������ָ����� 
//һά���鴫��
//[]�ڵ����ֿ�����ʡ��
void text(int arr[])
{}//��������ǶԵ�
void text(int arr[10])
{}//��������ǶԵ�
void text(int *arr)
{}//��������ǶԵ�
void text2(int* arr[20])
{}//��������ǶԵ�
void text2(int** arr)
{}//��������ǶԵ�
int main()
{
	int arr[10] = { 0 };//��������
	int* arr2[20] = { 0 };//ָ������
	test(arr);
	test2(arr2);//����Ԫ�ص�ַ��һ��һ��ָ��ĵ�ַ�����Դ�������ָ��ȥû������
	return 0:
}

//��ά����Ĵ���
//��һ��[]�ڿ���ʡ�ԣ��ڶ���[]���Բ���ʡ��
void text(int arr[3][5])
{}
//void text(int* arr)
//{}//��������Ǵ��
//void text(int* arr[5])
//{}//��������Ǵ��
//void text2(int arr[3][])
//{}//��������Ǵ��
//void text3(int arr[][])
//{}//��������Ǵ��
//void text3(int* arr)
//{}//��������Ǵ��
//text4(int** arr)
//{}//��������Ǵ��
void text5(int (*arr)[5])
{}//�Ե�     ����һ��ָ�����intԪ�صĵ�ַ��ָ�룬�����������ܶ�ά��������е�ַ
int main()
{
	int arr[3][5] = { 0 };

	text(arr);
	text1(arr);
	text2(arr);
	text3(arr);
	text4(arr);//��Ԫ�ص�ַ���ǵ�һ�еĵ�ַ������ָ����������һ��ָ��ĵ�ַ�ģ�����text4����
	text5(arr);
	return 0;
}


//һ��ָ��Ĵ���
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

//����ָ��Ĵ���
void test(int **p)
{}
int main()
{
	int* ptr;
	int** pp = &ptr;
	test(&ptr);
	test(pp);
	int* arr[10];//ָ������Ҳ����
	test(arr);
	return 0;
}


//����ָ��--ָ�������ָ��
//����ָ��--ָ������ָ��--��ź�����ַ��ָ��

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
	//&������ �� ������ ���Ǻ����ĵ�ַ
	printf("%p\n", &Add);//
	printf("%p\n", Add);//��������������ȫһ��
	int (*p)(int, int) = Add;//������ָ�����ƣ�int (*arr)[10]=arr;
	printf("%d", (*p)(3, 5));//�����8
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

//����ָ������
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
//	//ָ������
//	int* arr[5];
//	//��Ҫһ�����飬���������Դ���ĸ������ĵ�ַ-����ָ�������
//	int (*parr[4])(int, int) = { add,sub,mul,div };//����ָ�������
//parr[4]������ int(*)(int,int)����
//	int i = 0;  
//	for (i = 0; i < 4; i++)
//	{
//		printf("%d ", parr[i](2, 3));
//	}
//	return 0;
//}

////дһ������ָ��pf��ָ��my_strcpy
//char (*pf)(char, char);
////дһ������ָ�����飬�ܹ����my_strcpy�����ĵ�ַ
//char (*p[4])(char, char);
//

 //ָ����ָ�������ָ��
//��һ�� ָ�� ��ָ��ָ��һ�� ���� �������Ԫ�ض��� ����ָ�� ��

//void test(const char* str)
//{
//	printf("%s\n", str);
//}
//int main()
//{
//	//����ָ��pfun
//	void (*pfun)(const char*) = test;
//	//����ָ�������pfArr
//	char (*pfArr[1])(const char*);
//	//ָ����ָ�������ָ��
//	char (*(*pfArr)[1])(const char*)=&pfArr[1];
//}



//�ص�����
//����һ��ͨ������ָ����õĺ�����
//�����Ѻ�����ָ�루��ַ����Ϊ�������ݸ���һ������
//�����ָ�뱻������������ָ��ĺ���ʱ������˵����ǻص�����
//�ص����������ɸú�����ʵ�ַ�ʽֱ�ӵ��ã��������ض����¼�����������ʱ����һ�����õģ�
//���ڻ���¼�������������Ӧ


																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																		
//qsort--��������������������
//quick sort
// qsort();
//��һ���������������������Ԫ�ص�ַ
//�ڶ��������������������Ԫ�ظ���
//�����������������������ÿ��Ԫ�صĴ�С����λ�ֽ�
//���ĸ��������Ǻ���ָ�룬�Ƚ�����Ԫ�����ú����ĵ�ַ���������ʹ�����Լ�ʵ��
// 						  ����ָ������������ǣ����Ƚϵ�����Ԫ�صĵ�ַ
 
//int main()
//{
	//����������Ԫ�ص�ַ
	//�������⣺1.sizeof��������)-��ʾ��������
	//					  2.&������-��ʾ��������

	//һά����
//int a[] = { 1,2,3,4 };
//	printf("%d\n", sizeof(a));    //sizeof(������)-������������ܴ�С-��λ���ֽ�-16
//	printf("%d\n", sizeof(a+0));//�����a��ʾ��Ԫ�ص�ַ-4
//	printf("%d\n", sizeof(*a));  //a����Ԫ�ص�ַ-4
//	printf("%d\n", sizeof(a+1));//a����Ԫ�ص�ַ��a+1�ǵڶ���Ԫ��-4
//	printf("%d\n", sizeof(a[1]));//4-�ڶ���Ԫ�ش�С
//	printf("%d\n", sizeof(&a));  //&aȡ����������ĵ�ַ����������ĵ�ַҲ�ǵ�ַ����ַ�Ĵ�С����4
//	printf("%d\n", sizeof(*&a));//16-&a������ĵ�ַ�������ú���ʵ�����
//	printf("%d\n", sizeof(&a+1));//4-&a������ĵ�ַ��&a+1��Ȼ��ַ�����������飬�����ǵ�ַ������4
//	printf("%d\n", sizeof(&a[0]));//4-��һ��Ԫ�صĵ�ַ
//	printf("%d\n", sizeof(&a[0]+1));//4-�ڶ���Ԫ�صĵ�ַ





	//�ַ�����
	//char arr[] = { 'a','b','c','d','e','f' };
	//printf("%d\n", sizeof(char));//1
	//printf("%d\n", sizeof(arr)) ;     //6-siazeof������������С��6*1=6�ֽ�
	//printf("%d\n", sizeof(arr+0));  //4-��Ԫ�ص�ַ-��ַ����4��8�ֽ�
	//printf("%d\n", sizeof(*arr));    //1-arr����Ԫ�ص�ַ��*arr������Ԫ�����ַ�����С��һ���ֽ�
	//printf("%d\n", sizeof(arr[1])); //1-�ڶ���Ԫ��
	//printf("%d\n", sizeof(&arr));   //4-�����ַ
	//printf("%d\n", sizeof(&arr+1));//4-&arr+1���������������ĵ�ַ
	//printf("%d\n", sizeof(&arr[0]+1));//4-�ڶ���Ԫ�صĵ�ַ

	//strlen���ַ������ȣ��ҵ�\0ֹͣ
	//printf("%d\n", strlen(arr));//���ֵ-��֪������ʲôʱ�����ҵ�"\0"
	//printf("%d\n", strlen(arr+0));//���ֵ-ͬ��
	////printf("%d\n", strlen(*arr));//err-*arr����Ԫ��'a'���൱�ڴ������� 97 ��Ȼ��strlen��97���������Ƿ�����
	////printf("%d\n", strlen(arr[1]));//err-arr[1]�ǵڶ���Ԫ�أ�ͬ��
	//printf("%d\n", strlen(&arr));//���ֵ-������ͷ��ʼ��������ʲôʱ������\0�����
	//printf("%d\n", strlen(&arr+1));//���ֵ-�����������飬���������ʼ��������ʲôʱ������\0�����������������ֵ��6
	//printf("%d\n", strlen(&arr[0]+1));//���ֵ-�ӵڶ���Ԫ�ؿ�ʼ�������һ�����ֵ��ֵΪ1

//return 0;
//}



//int main()
//{
//	
	//char arr[] = "abcdef"; //һ���ַ���һ��Ԫ��

	//printf("%d\n", sizeof(arr));//7-���滹��һ����\0��sizeof��������Ĵ�С
	//printf("%d\n", sizeof(arr+0));//4-arr+0����Ԫ�ص�ַ-������ǵ�ַ�Ĵ�С
	//printf("%d\n", sizeof(*arr));//1-*arr����Ԫ��
	//printf("%d\n", sizeof(arr[1]));//1-����ڶ���Ԫ�صĴ�С
	//printf("%d\n", sizeof(&arr));//4-��������ĵ�ַ
	//printf("%d\n", sizeof(&arr+1));//4-������������ĵ�ַ
	//printf("%d\n", sizeof(&arr[0]+1));//4-�ڶ���Ԫ�صĵ�ַ��С

	//printf("%d\n", strlen(arr));//6
	//printf("%d\n", strlen(arr + 0));//6
	////printf("%d\n", strlen(*arr));//err-strlen���ʵ�ַ��*arr����Ԫ��a���൱�ڴ�����һ��97����97Ϊ��ַ������ʣ��Ƿ�����err
	////printf("%d\n", strlen(arr[1]));//err-arr[1]�ǵڶ���Ԫ�أ�ͬ��
	//printf("%d\n", strlen(&arr));//6-����ĵ�ַ-����ָ��-char(*p)[7]=&arr;
	//printf("%d\n", strlen(&arr + 1));//���ֵ
	//printf("%d\n", strlen(&arr[0] + 1));//5
	/*for (int i = 0; i < strlen(arr); i++)
	{
		printf("%c ", arr[i]);

	}
	printf("%d", arr[6]);*/


	//char* p = "abcdef";//����������ַ���������ĸa�ĵ�ַ������p����

	//printf("%d\n", sizeof(p));//4-����ָ�����p�Ĵ�С
	//printf("%d\n", sizeof(p+1));//4-p+1�õ������ַ�b�ĵ�ַ
	//printf("%d\n", sizeof(*p));//1-*p�����ַ�����һ���ַ�a
	//printf("%d\n", sizeof(p[0]));//1-p[0]��a--int arr[10];arr[0]==*(arr+0);=>p[0]==*(p+0)
	//printf("%d\n", sizeof(&p));//4-p�ĵ�ַ
	//printf("%d\n", sizeof(&p+1));//4-����p�ĵ�ַ�����Ǹ���ַ
	//printf("%d\n", sizeof(&p[0]+1));//4-p[0]��a,&p[0]����p�ĵ�ַ
	//printf("%c", *p);
	

	//printf("%d\n", strlen(p));//6-p��a�ĵ�ַ��
	//printf("%d\n", strlen(p + 1));//5-�ڶ���Ԫ�ؿ�ʼ����
	////printf("%d\n", strlen(*p));//err
	////printf("%d\n", strlen(p[0]));//err
	//printf("%d\n", strlen(&p));//���ֵ
	//printf("%d\n", strlen(&p + 1));//���ֵ
	//printf("%d\n", strlen(&p[0] + 1));//5



	//��ά����
	//int a[3][4] = { 0 };

	//printf("%d\n", sizeof(a));//12*4=48--�����ܴ�С
	//printf("%d\n", sizeof(a[0][0]));//1*4=4--һ�����εĴ�С
	//printf("%d\n", sizeof(a[0]));//4*4=16--a[0]�൱�ڵ�һ����Ϊһά�������������sizeof(a[0])����������������sizeof�ڼ�����ǵ�һ�еĴ�С
	//printf("%d\n", sizeof(a[0]+1));//4--����a[0]�ǵ�һ������������ʾ���ǵ�һ�е�һ��Ԫ�ص�ַ������+1��ʾ��һ�еڶ�����ַ����ַ��С��4/8���ֽ�
	//printf("%d\n", sizeof(*(a[0] + 1)));//4--��һ�еڶ���Ԫ�صĴ�С
	//printf("%d\n", sizeof(a+1));//4--a�Ƕ�ά�����������������ʾ��Ԫ�ص�ַ����ά�������Ԫ���ǵ�һ�У�a+1���ǵڶ��е�ַ��
	//printf("%d\n", sizeof(*(a+1)));//16--�ڶ���Ԫ�صĴ�С
	//printf("%d\n", sizeof(&a[0]+1));//4--&a[0]�ǵ�һ�еĵ�ַ��+1���ǵڶ��е�ַ
	//printf("%d\n", sizeof(*(&a[0] + 1)));//16--�ڶ���Ԫ�صĴ�С
	//printf("%d\n", sizeof(*a));//16--a������Ԫ�ص�ַ�����ǵ�һ�еĵ�ַ��*a���ǵ�һ�е�Ԫ��
	//printf("%d\n", sizeof(a[3]));//16--sizeof�������()�ڵ����ݣ�ֻ�ᰴ�������������С��a[3]�����ڵ���sizeof���������ʣ�ֻ�������ɵ�����Ԫ��
	//return 0;
//}


//int main() {
//	unsigned long pulArray[] = { 6,7,8,9,10 };
//	unsigned long* pulPtr;
//	pulPtr = pulArray;			//pulPtrָ��6
//	*(pulPtr + 3) += 3;			//+3ָ��9��*(pulPtr + 3)=9+3=12
//	printf("%d %d \n", *pulPtr, *(pulPtr + 3));//6 12
//	return 0;
//}



//дһ�������ַ����ĺ���
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
//	printf("�������ַ�����%s", arr);
//}
//int main() {
//	char arr[100] = { 0 };
//	//scanf("%s", arr);//�����ո�������ȡ
//	gets(arr);//��ȡһ�зŵ�arr����
//	printf("\nԭ�����ַ�����%s\n", arr);
//	NIXU(arr);
//	return 0;
//}

//������ͣ���Sn=a+aa+aaa+aaaa+aaaaa��ǰ����֮�ͣ�a��һ������
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

//ˮ�ɻ��������0-100000֮��� ����ˮ�ɻ���
//ˮ�ɻ�����ָһ��nλ�������λ���ֵ�n�η��͵��ڸ�������
//#include<math.h>
//int main() {
//	for (int i = 0; i <= 100000; i++) {
//		//1������i��λ��
//		int n = 1;		//����һλ��
//		int m = i;
//		while (m/=10) {//i/10����0��ʱ��������һλ���ˣ������ٽ�ȥ
//			n++;
//		}
//		//��������ѭ���ж���λ��
//	/*	int n = 0;
//		while (m) {
//			m /= 10;
//			n++;
//		}*/
//
//		//2������i��ÿһλ��n�η�֮��
//		int sum = 0;
//		m = i;
//		while (m) {
//			sum += pow(m % 10, n);
//			m /= 10;
//			/*��������:   pow
//����ԭ��:   double pow( double x, double y );
//��������:   ����x��y����
//�����ļ�:   <math.h>*/
//		}
//		//3���Ƚ�i��sum
//		if (i == sum) {
//			printf("%d ", i);
//		}
//	}
//	return 0;
//}

//��ӡ����
//int main() {
//	int n;	//�ϰಿ������
//	scanf("%d", &n);	
//	//�ϰ벿�֣�
//	for (int i = 1; i <= n; i++) {	//������ѭ������
//		//1����ӡ�ո�
//		for (int j = 0; j < n - i; j++) {	
//			printf(" ");
//		}
//		//2����ӡ*��
//		for (int j = 0; j < 2*i-1; j++) {
//			printf("*");
//		}
//		//3��û��ӡ��һ�Ż���
//		printf("\n");
//	}
//	//�°벿�֣�
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


//��ת�ַ���
//ʵ��һ�����������������ַ����е�k���ַ�
//ABCD����һ���ַ�ΪBCDA
//ABCD���������ַ�ΪCDAB

#include<assert.h>
//1��������ⷨ��
//void left_move(char* arr, int k) {
//	int len = strlen(arr);
//	assert(arr);
//	assert(k < len&& k >= 0);
// //����ת�ĵ�һ���ַ��ȴ�������Ȼ������ַ��ĺ�����ַ�������ǰ�ƣ�Ȼ���ٰ���ת���ַ��������
//	for (int i = 0; i < k; i++) {//��ת���ξ�ѭ������
//		char tmp = arr[0];//*arr
//		for (int j = 0; j < len-1; j++) {
//			arr[j] = arr[j + 1];
//			//*(arr+j)=*(arr+j+1);
//		}
//		arr[len - 1] = tmp;
//	}
//}

//2��������ת��
//��һ���ַ�����Ϊ�����֣�һ������Ҫ��ת���֣���һ�����ǲ���ת����
//ab cdef
//�Ƚ�Ҫ��ת��������ba cdef
//�ٽ�����ת��������ba fedc
//���ȫ����������cdefab
//�õ���ת����ַ���

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
	//��ͷβָ������������
	//1��Ҫ��ת����
	inversion(arr, arr + k - 1);//arr��ͷ��ַ��arr+k-1���ⲿ�ֵ�β��ַ
	//2������ת����
	inversion(arr + k, arr + len - 1);
	//3��ȫ������
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
////1��������ⷨ
///*��ԭ�ַ������е���ת���ܶ��ó�������һ�ַ����Ƚϣ�������ͬ����yes*/
//int is_left_move(char* arr1, char* arr2) {
//	int len = strlen(arr1);
//	for (int i = 0; i < len; i++) {
//		left_move(arr1, 1);//��Ϊ��һ��һ���ַ���ת������������ת����ֻ��д1
//		if (strcmp(arr1, arr2) == 0)
//			return 1;
//	}
//	return 0;
//}
//2���Ż��㷨
/*��Դ�ַ����ϼ���һ��ԭ�ַ�����Ȼ������һ�ַ����Ƚ���û����ͬ���֣��磺
arr1="abcdef"-->arr1="abcdefabcdef";
				arr2="cdefab"
��˫ָ��
*/
//��ԭ�����ַ����ټ�һ��ԭ�����ַ��� 
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
	/*��������ַ�������ͬ�ǿ϶���������ת������*/
	if (strlen(arr1) != strlen(arr2))
		return 0;
	F(arr1);
	char* top1 = arr1;//arr1��ͷָ��
	char* top2 = arr2;//arr2��ͷָ��
	char* rear1 = arr1;//arr1��βָ��
	/*��arr2�ĵ�һ���ַ���arr1���ĳһ���ַ���ͬʱ��top1�Ͳ����ˣ�rear1��top2����ƶ�
	  ��rear1-top1��������ͬ�ַ�������arr2�ĳ���ʱ��˵��arr2����arr1��ת������*/
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

//�ж��ַ����Ƿ����ַ�����ת�õ���
//��cdefab����abcdef��ת�õ���
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