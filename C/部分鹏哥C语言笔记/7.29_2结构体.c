#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//�ṹ
//��һЩֵ�ļ��ϣ���Щֵ��Ϊ��Ա�������ṹ���ÿ����Ա�����ǲ�ͬ���͵ı�����


//struct stu
//	//struct--�ṹ��ؼ��֣�stu--�ṹ���ǩ��struct stu--�ṹ������
//{
//	//��Ա����
//	char name[20];
//	short age;
//	char tlte[12];
//	char sex[5];
//}s1,s2,s3;//s1,s2,s3������ȫ�ֵĽṹ�����
//typedef struct stu//typedef--�����������������
//	//struct--�ṹ��ؼ��֣�stu--�ṹ���ǩ��struct stu--�ṹ������
//{
//	//��Ա����
//	char name[20];
//	short age;
//	char tlte[12];
//	char sex[5];
//}stu;//��������λstu
//
//int main()
//{
//	//��ʼ��
//	struct stu s1 = { "����",20,"15760656503","��" };//�������� ���ֲ�
//	stu s2 = { "����",20,"15583782236","��" };
//	return 0;
//}

//struct S
//{
//	int a;
//	char arr[20];
//	char c;
//	double d;
//};
//
////�ṹ���ڽṹ��ĳ�ʼ��
//struct T
//{
//	char ch[10];
//	struct S s;
//	char* pc;
//};
//int main()
//{
//	char arr[] = "hello word\n";
//	struct T t = { "hehe",{100,"hello",'w',3.14},arr };
//	printf("%s\n", t.ch);//hehe
//	printf("%d\n", t.s.a);//100
//	return 0;
//}
//
//typedef struct stu//typedef--�����������������
//	//struct--�ṹ��ؼ��֣�stu--�ṹ���ǩ��struct stu--�ṹ������
//{
//	//��Ա����
//	char name[20];
//	short age;
//	char tele[12];
//	char sex[5];
//}stu;//��������λstu

//void print1(stu s)
//{
//	printf("name: %s\n", s.name);
//	printf("age:    %d\n", s.age);
//	printf("tele:    %s\n", s.tele);
//	printf("sex:    %s\n", s.sex);
//}
//void print2(stu* ps)
//{
//	printf("name:%s\n", ps->name);
//	printf("age:%d\n", ps->age);
//	printf("tele:%s\n", ps->tele);
//	printf("sex:%s\n", ps->sex);
//}
//int main()
//{
//	stu s = { "����",12,"1585555555","��" };
//	//��ӡ�ṹ������
//	//print2���ţ�����ṹ�������Ļ���print1�����˷ѿռ���˷�ʱ���
//	print1(s);
//	print2(&s);
//	return 0;
//}

//�ṹ��Ĵ��μǵ��ô���ַ 


//����ˮ���⣬һƿ��ˮһԪ��������ƿ���Ի�һƿ��ˮ������ʮԪ�������ж�����ˮ
int main() {
	int money = 0;//Ǯ
	int empty = 0;//��ƿ
	int total = 0;//��ˮ����
	scanf("%d", &money);

	if (money == 0)
		total = 0;
	else
		total = 2 * money - 1;

	//�����������
	//total = money;//���˶���Ǯ�����򵽶���ƿ
	//empty = money;//������ĵõ��Ŀ�ƿ����
	////������������
	//while (empty>=2) {	//��ƿ��������0����1�˾Ͳ����ٻ���
	//	total += empty / 2;//��������ƿ��һƿ��ˮ�����ˮ����
	//	empty = empty % 2+ empty / 2 ;//��ƿ��Ҫ�����ϴ�û�л���Ŀ�ƿ�ͻ������ֺȵ�������
	//}
	printf("%dԪ��Ǯһ���ܺȵ�%dƿ��ˮ",money, total);
	return 0;
}