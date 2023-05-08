#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//结构
//是一些值的集合，这些值称为成员变量。结构体的每个成员可以是不同类型的变量。


//struct stu
//	//struct--结构体关键字，stu--结构体标签，struct stu--结构体类型
//{
//	//成员变量
//	char name[20];
//	short age;
//	char tlte[12];
//	char sex[5];
//}s1,s2,s3;//s1,s2,s3是三个全局的结构体变量
//typedef struct stu//typedef--给这个类型重新起名
//	//struct--结构体关键字，stu--结构体标签，struct stu--结构体类型
//{
//	//成员变量
//	char name[20];
//	short age;
//	char tlte[12];
//	char sex[5];
//}stu;//重新起名位stu
//
//int main()
//{
//	//初始化
//	struct stu s1 = { "张三",20,"15760656503","男" };//创建变量 ，局部
//	stu s2 = { "李四",20,"15583782236","男" };
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
////结构体内结构体的初始化
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
//typedef struct stu//typedef--给这个类型重新起名
//	//struct--结构体关键字，stu--结构体标签，struct stu--结构体类型
//{
//	//成员变量
//	char name[20];
//	short age;
//	char tele[12];
//	char sex[5];
//}stu;//重新起名位stu

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
//	stu s = { "张三",12,"1585555555","男" };
//	//打印结构体数据
//	//print2更优，如果结构体变量大的话，print1可能浪费空间大，浪费时间多
//	print1(s);
//	print2(&s);
//	return 0;
//}

//结构体的传参记得用传地址 


//喝汽水问题，一瓶汽水一元，两个空瓶可以换一瓶汽水，给二十元，可以有多少汽水
int main() {
	int money = 0;//钱
	int empty = 0;//空瓶
	int total = 0;//汽水总数
	scanf("%d", &money);

	if (money == 0)
		total = 0;
	else
		total = 2 * money - 1;

	//买回来的数量
	//total = money;//给了多少钱就能买到多少瓶
	//empty = money;//喝完买的得到的空瓶数量
	////换回来的数量
	//while (empty>=2) {	//空瓶数最后等于0或者1了就不能再换了
	//	total += empty / 2;//用两个空瓶换一瓶汽水后的汽水总数
	//	empty = empty % 2+ empty / 2 ;//空瓶数要加上上次没有换完的空瓶和换回来又喝掉的数量
	//}
	printf("%d元的钱一共能喝到%d瓶汽水",money, total);
	return 0;
}