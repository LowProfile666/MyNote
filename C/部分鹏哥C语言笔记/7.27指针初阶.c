#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//ָ���Ǳ���������ר�Ŵ�ŵ�ַ��
//ָ��Ĵ�С��32λƽ̨��4���ֽڣ�64λƽ̨��8���ֽ�
//int main()
//{
//	printf("%d\n", sizeof(int*));//4
//	printf("%d\n", sizeof(short*));//4
//	printf("%d\n", sizeof(double*));//4
//	printf("%d\n", sizeof(char*));//4
//	return 0;
//}
//
// ָ�����;�����ָ����н����ò�����ʱ���ܹ����ʿռ�Ĵ�С
//int *p; *p�ܷ���4���ֽ�
//char *p; *p�ܷ���1���ֽ�
//double *p; *p�ܷ���8���ֽ�
//
//int main()
//{
//
//	int a = 0x11223344;
//	int* pa = &a;
//	char* pc = &a;
//	//ָ�����;�����ָ����һ���߶�Զ��ָ��Ĳ����� 
//	printf("%p\n", pa);//0137FDC4
//	printf("%p\n", pa+1);//0137FDC8
//	printf("%p\n", pc);//0137FDC4
//	printf("%p\n", pc+1);//0137FDC5
//	return 0;
//}

//Ұָ��
//����ָ��ָ���λ���ǲ���֪�ģ�����ģ�����ȷ�ģ�û����ȷ���Ƶģ�
//Ұָ�����
//1.δ��ʼ��
//2.Խ�����
//3.ָ��ָ��Ŀռ��ͷ�

//1.
//int main()
//{
//	int a;//�ֲ���������ʼ����Ĭ�������ֵ
//	int* p;//�ֲ���ָ�����������ʼ�����ֵ
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
//		//��ָ��ָ��ķ�Χ��������a�ķ�Χʱ��p����Ұָ��
//		 p++;
//	}
//	return 0;
//}
//3.
//int* text()
//{
//	int a = 10;
//	return &a;
//	//������������⣬����&a�󣬳�����������������ַ�ͱ�������
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
//	//int* p = NULL;//NULL-������ʼ��ָ�룬��ָ�븳ֵ��
//	int a = 10;
//	int* p = &a;
//	*p = NULL;//��ָ����������ӵĻ����͸���ֵNULL��
//	//Ȼ���ָ�벻ָ���κ���Ч�ռ�
//	//���������ÿ���:
//	if (*p != NULL)
//	{
//		;
//	}
//	return 0;
//}

//ָ������
//1.ָ��+-����
//2.ָ��-ָ��
//�õ�����ָ��֮��Ԫ�صĸ���
//3.ָ��Ĺ�ϵ����

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
//	printf("%d", &arr[9] - &arr[0]);//9��С��ַ-���ַʱ�õ���ʱ����
//	char a[5] = { 0 };
//	printf(" %d ", &arr[4] - &a[0]);//err������û��ֵ
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

//ָ�������
//int main()
//{
//	int arr[10] = { 0 };
//	printf("%p\n", arr);//���arr��ʾ��ַ����Ԫ�صĵ�ַ
//	printf("%p\n", &arr[0]);
//	printf("%p\n", &arr);//��������ĵ�ַ
//	//ֻ��������������²�����Ԫ�ص�ַ��
//	//1.&������--&arr--�����������ʾ�������飬&������ȡ��������������ĵ�ַ
//	//2.sizeof����������--sizeof��arr��--�����������ʾ�������飬������������Ĵ�С
//
//	return 0;
//}

//int main()
//{
//	int arr[10] = { 0 };
//	int* p = arr;
//	int i = 0;
//	//�����鸳ֵ
//	for (i = 0; i < 10; i++)
//	{
//		*(p + i) = i;
//	}
//	//��ӡ����Ԫ��
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", arr[i]);
//		//��printf("%d ", *(p + i));
//	}
//	printf("\n");
//	//��ӡԪ�ص�ַ
//	for (i=0; i < 10; i++)
//	{
//		printf("%p=====%p\n", p + i, &arr[i]);
//	}
//	return 0;
//}

//����ָ��
//int main()
//{
//	int a = 0;
//	int * pa = &a;//һ��ָ��
//	int* * ppa = &pa;//����ָ��
//	int** * pppa = &ppa;//����ָ��
//	***pppa = 20;
//	//*pppa��ppa�ĵ�ַ��**pppa��pa�ĵ�ַ��***pppa��a�ĵ�ַ
//	printf("%d\n", a);
//	return 0;
//}

//ָ������--����--���ָ�������
//����ָ��--ָ��
int main()
{
	//��������-�������
	//�ַ�����-����ַ�
	//ָ������-���ָ��
	int a = 1;
	int b = 2;
	int c = 3;
	/*int* pa = &a;
	int* pb = &b;
	int* pc = &c;*/
	//int a[10] = { 0 };��������
	int* arr[10] = {&a,&b,&c};//ָ������ 
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		printf("%d ", *(arr[i]));//1 2 3
		printf("%p\n", arr[i]);//��ַ
	}
	return 0;
}