#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//��ʽ�ṹ
//int main()
//{
//	printf("%d", printf("%d",printf("%d", printf("%d", 43))));//43211
//	//printf�������ص��Ǵ�ӡ�ĳ��ȣ���ӡ��43����ֵ��2�������´δ�ӡ��2����ֵ��1
//	//���´δ�ӡ��1����ֵ����1�������һ�δ�ӡ1��
//	return 0;
//}
//�������� ��
//int Add(int, int);
////���������Ķ�������������ĺ������ᱻ����
////��������ֺ���
//int main()
//{
//	int a = 10;
//	int b = 20;
//	//�����ĵ���
//	int sum = Add(a, b);
//	printf("%d", sum);
//	return 0;
//}
////�����Ķ���
//int Add(int x, int y)
//{
//	int z = x + y;
//	return z;
//}

//�����ĵݹ�
//�����ӡ�����������
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
//��������ʱ�������ַ�������
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
////�ݹ���n�Ľ׳�
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
