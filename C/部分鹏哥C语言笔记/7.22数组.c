#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//����
//int main()
//{
//	char arr[] = "abcdfg";//char ��Ԫ�ص�����
//	printf("%d\n", sizeof(arr)); 
//		//sizeof������ռ�ռ�Ĵ�С
//		printf("%d\n",strlen(arr));
//	//strlen�����ַ����ĳ��� -
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
//�������ڴ�����������ŵ�
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
//��ά����
//int main()
//{
//	//��ά�����ʼ��
//    int arr1[2][2] = { {1,2},{3,4} };
//    int arr2[2][3] = { 1,2,3,4,5,6 };
//	int arr3[][4] = { {1,2,3,4},{5,6,7,8} };
//	int arr4[][4] = { 1,2,3,4,5,6,7,8,9 };
//	//ǰ���п���ʡ�ԣ���������в���ʡ
//	return 0;
//}
//��ӡ��arr[3][4]��ֵ
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
//��ά������ڴ��ַ
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
//��ά����Ҳ��������ŵ� 
//}
//��������������
 //ð�ݺ�������
//void maopao(int sz,int arr[])
//{
//	//ȷ��ð�����������
//	int i = 0;
//	for (i = 0; i < sz-1; i++)
//	{
//		//�Ż����򣬱���һ������5��1��2��3��4����
//		//ֻ��һ��������ܽ���
//		int flag = 1;//������һҪ����������Ѿ�����
//		//ÿһ��ð������
//		int j = 0;
//		for (j = 0; j <sz-1-i ; j++)
//		{
//			if (arr[j] < arr[j + 1])
//			{
//				int t = arr[j + 1];
//				arr[j + 1] = arr[j];
//				arr[j] = t;
//				flag = 0;//���������������ʵ����ȫ����
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
//	//���Ƕ�����arr���д��Σ�ʵ���ϴ��ݹ�ȥ����arr��Ԫ�صĵ�ַ&arr[0]
//	int i = 0;
//	maopao(sz,arr);
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}
//������һ������Ԫ�ص�ַ�������������⣺
//1.sizeof��������������������ʾ�������� ��sizeof���������������Ĵ�С����λ���ֽ�
//2.&����������������ʾ�����������飬&������ȡ��������������ĵ�ַ                                                   
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