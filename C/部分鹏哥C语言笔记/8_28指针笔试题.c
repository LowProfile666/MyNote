#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>


//int main()
//{
//	int a[5] = { 1,2,3,4,5 };
//	int* ptr = (int*)(&a + 1);
//	printf("%d %d", *(a + 1), *(ptr - 1));//2 5
//	//*（a+1）表示第二个元素
//	//&a + 1 表示跳过整个数组，还是个数组地址，在元素5的后面
//	//ptr-1 指的是数组中的5的地址，*（ptr-1）就是访问的元素5
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
////假设p的值为0x100000，如下表达式的值分别是多少
////已知结构体Test类型的变量大小是20个字节
//int main()
//{
//	//指针+-整数，取决于指针类型
//	p = (struct Test*)0x100000;
//	printf("%p\n", p + 0x1);//00000014，地址打印会把位数补齐
//	//0x1==1,所以p + 0x1等于加了一个结构体指针==0x100000+20==0x100000+0x100014
//	printf("%p\n", (unsigned long)p+0x1);//00000001
//	//这里相当于+1
//	printf("%p\n", (unsigned int*)p + 0x1);//00000004
//	//这里相当于+4
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
//							//逗号表达式
//	int a[3][2] = { (0,1),(2,3),(4,5) };//所以相当于只存了1，3，5
//	int* p;
//	p = a[0];//(0,1)的地址
//	printf("%d", p[0]);//p[0]==*(p+0)
//	return 0;
//}


//
//int main()
//{
//	//画图
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
//创键顺序表
void createList(L* P)
{
	int num;

	printf("请输入元素个数：\n");
	do {
		scanf("%d", &num);
		if (num <= 0)
			printf("输入错误！请重新输入：\n");
	} while (num <= 0);
	printf("请输入顺序表元素：\n");
	for (int i = 0; i < num; i++) {
		
		scanf("%d", &(P->arr[i]));
	}
	P->length = num;
}
//遍历顺序表
void printList(L* p) {
	int count = 0;
	for (int i = 0; i < p->length; i++) {
		printf("%3d ", p->arr[i]);
		count++;
		if (count == 10) {//十个一排
			printf("\n");
			count = 0;
		}
	}
}
//查找元素
void find(L* p) {
	printf("请输入你想查找的元素：\n");
	int intput;
	scanf("%d",&intput);
	for (int i = 0; i < p->length; i++) {
		if (intput == p->arr[i]) {
			printf("找到了，下标是%d", i);
			return;
		}
	}
	printf("找不到！");
}
//排序
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
//判断对称
void F(L* p) {
	for (int i = 0; i < p->length/2; i++) {
		if (p->arr[i] != p->arr[p->length - 1]) {
			printf("不对称！");
			return;
		}
	}
	printf("对称！");
}
//插入元素
int C(L* p) {
	printf("请输入你要插入的元素：\n");
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
	printf("插入新元素后的顺序表：\n");
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
	F(&p);//是否对称
	C(&p);//插入
	return 0;
}
