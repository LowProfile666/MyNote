#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>


//int main()
//{
//	int a[5] = { 1,2,3,4,5 };
//	int* ptr = (int*)(&a + 1);
//	printf("%d %d", *(a + 1), *(ptr - 1));//2 5
//	//*��a+1����ʾ�ڶ���Ԫ��
//	//&a + 1 ��ʾ�����������飬���Ǹ������ַ����Ԫ��5�ĺ���
//	//ptr-1 ָ���������е�5�ĵ�ַ��*��ptr-1�����Ƿ��ʵ�Ԫ��5
//	return 0;
//}


//struct Test
//{
//	int Num;
//	char* pcName;
//	short sDate;
//	char cha[2];
//	short sBa[4];
//}*p;
////����p��ֵΪ0x100000�����±��ʽ��ֵ�ֱ��Ƕ���
////��֪�ṹ��Test���͵ı�����С��20���ֽ�
//int main()
//{
//	//ָ��+-������ȡ����ָ������
//	p = (struct Test*)0x100000;
//	printf("%p\n", p + 0x1);//00000014����ַ��ӡ���λ������
//	//0x1==1,����p + 0x1���ڼ���һ���ṹ��ָ��==0x100000+20==0x100000+0x100014
//	printf("%p\n", (unsigned long)p+0x1);//00000001
//	//�����൱��+1
//	printf("%p\n", (unsigned int*)p + 0x1);//00000004
//	//�����൱��+4
//	return 0;
//}


//int main()
//{
//	int a[4] = { 1,2,3,4 };
//	int* ptr1 = (int*)(&a + 1);
//	int* ptr2 = (int*)((int)a + 1);
//	printf("%x,%x", ptr1[-1], *ptr2);//4,2000000
//	return 0;
//}

//
//int main()
//{
//							//���ű��ʽ
//	int a[3][2] = { (0,1),(2,3),(4,5) };//�����൱��ֻ����1��3��5
//	int* p;
//	p = a[0];//(0,1)�ĵ�ַ
//	printf("%d", p[0]);//p[0]==*(p+0)
//	return 0;
//}


//
//int main()
//{
//	//��ͼ
//	int a[5][5];
//	int(*p)[4];
//	p = a;
//	printf("%p,%d\n", &p[4][2] - &a[4][2], &p[4][2] - &a[4][2]);
//	//p[4]==*(p+4);p[4][2]==*(*(p+4)+2)
//	return 0;
//}




typedef struct List
{
	int arr[100];
	int length;
	int count1;
	int count2;
}L;
//����˳���
void createList(L* P)
{
	int num;

	printf("������Ԫ�ظ�����\n");
	do {
		scanf("%d", &num);
		if (num <= 0)
			printf("����������������룺\n");
	} while (num <= 0);
	printf("������˳���Ԫ�أ�\n");
	for (int i = 0; i < num; i++) {
		
		scanf("%d", &(P->arr[i]));
	}
	P->length = num;
}
//����˳���
void printList(L* p) {
	int count = 0;
	for (int i = 0; i < p->length; i++) {
		printf("%3d ", p->arr[i]);
		count++;
		if (count == 10) {//ʮ��һ��
			printf("\n");
			count = 0;
		}
	}
}
//����Ԫ��
void find(L* p) {
	printf("������������ҵ�Ԫ�أ�\n");
	int intput;
	scanf("%d",&intput);
	for (int i = 0; i < p->length; i++) {
		if (intput == p->arr[i]) {
			printf("�ҵ��ˣ��±���%d", i);
			return;
		}
	}
	printf("�Ҳ�����");
}
//����
int sort(L* p) {
	int j[100];
	int o[100];
	//int count1 = 0;
	//int count2 = 0;
	for (int i = 0; i < p->length; i++) {
		if (p->arr[i] % 2 == 0) {
			o[i] = p->arr[i];
			p->count2++;
		}
		else {
			j[i] = p->arr[i];
			p->count1++;
		}
	}
	for (int i = 1; i <= p->count1; i++) {
		if (j[i - 1] > j[i]) {
			int tmp = j[i - 1];
			j[i - 1] = j[i];
			j[i] = tmp;
		}if (i == p->count1) {
			for (int i = 0; i < p->length; i++) {
				p->arr[i] = j[i];
			}
			break;
		}
	}
	for (int i = 1; i < p->length; i++) {
		if (o[i - 1] > o[i]) {
			int tmp = o[i - 1];
			o[i - 1] = o[i];
			o[i] = tmp;
		}if (i == p->length) {
			for (int i = 1; i <= p->count2; i++) {
				p->arr[p->count1 + i] = o[i];
			}
			break;
		}
	}
	for (int i = 0; i < p->length; i++) {
		printf("%d ", p->arr[i]);
	}
	return p->arr;
}
//�ж϶Գ�
void F(L* p) {
	for (int i = 0; i < p->length/2; i++) {
		if (p->arr[i] != p->arr[p->length - 1]) {
			printf("���Գƣ�");
			return;
		}
	}
	printf("�Գƣ�");
}
//����Ԫ��
int C(L* p) {
	printf("��������Ҫ�����Ԫ�أ�\n");
	int intput;
	scanf("%d", &intput);
	p->length++;
	if(intput%2==0){
		for (int i = p->count1-1; i < p->length; i++) {
			if (p->arr[i] > intput)
				break;
			for (int j = p->length - 1; j > i; j--) {
				p->arr[j + 1] = p->arr[j];
			}
		}
	}
	else {
		for (int i = 1; i <= p->count1; i++) {
			if (p->arr[i] > intput)
				break;
			for (int j = p->count1; j > i; j--) {
				p->arr[j + 1] = p->arr[j];
			}
		}
	}
	printf("������Ԫ�غ��˳���\n");
	for (int i = 0; i < p->length; i++) {
		printf("%d ", p->arr[i]);
	}
	return p->arr;
}

int main()
{
	L p;
	createList(&p);
	printList(&p);
	find(&p);
	printf("\n");
	sort(&p);//
	F(&p);//�Ƿ�Գ�
	C(&p);//����
	return 0;
}
