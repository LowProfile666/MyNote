#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
/*
���ַ������ȣ�
strlen
���Ȳ������Ƶ��ַ���������
strcpy
strcat
strcmp
���������Ƶ��ַ���������
strncpy
strncat
strncmp
�ַ������ң�
strstr
strtok
������Ϣ���棺
strerror
�ַ�����
�ڴ����������
memcpy
memmove
memset
memcmp

C���Ա�����û���ַ������͵ģ��ַ���ͨ������ �����ַ��� �л��� �ַ����� �С�
�ַ������� ��������Щ���������޸ĵ��ַ�������
*/

/*
�������ܣ�
strlen
	size_t strlen(const char* str);
	�ַ����Ѿ�'\0'��Ϊ������־��strlen�������ص������ַ����е�'\0'ǰ����ֵ��ַ�������������\0��
	����ָ����ַ���������'\0'����
	ע�⺯���ķ���ֵ��size_t�����޷��ŵģ��״�
	size_t==unsigned int
	ѧ�����ַ���ģ��ʵ�֣�
	1.������
	2.�ݹ飬�������κα���
	3.ָ��-ָ��
*/
#include<string.h>
//int main() {
	//int len = strlen("abcdef");

	//char arr[] = { 'a','b','c','d','e','f' };
	//int len1 = strlen(arr);
	//printf("arr �ĳ����ǣ�%d\n", len1);     //���ֵ
	//printf("�ַ�����abcdef���ĳ����ǣ�%d\n", len);//6
	

	//��Ϊstrlen�������ص����޷����������������޷�������������޷����������Ա�Ȼ�Ǹ�����
	//ֵ��˵���ǣ��������������ͷ�ļ��Ļ����ͻ��ӡ��haha����������ͷ�ļ��ʹ�ӡhehe
//	if (strlen("abc") - strlen("abcdef") > 0)
//		printf("strlen���ص���һ���޷�������\n");
//	else
//		printf("strlen���ص���һ���з�������\n");
//	return 0;
//}

//ģ��ʵ��strlen 
//1��������
//int my_strlen(const char* arr) {
//	int count = 0;
//	while (*arr) {
//		count++;
//		arr++;
//	}
//	return count;
//}
////2.ָ��
//int my_strlen(const char* arr) {
//	char* front = arr;
//	char* rear = arr;
//	while (*rear) {
//		rear++;
//	}
//	return rear - front;
//	
//}
//3���ݹ�
//int my_strlen(const char* arr) {
//	if (*arr == '\0')
//		return 0;
//	return 1 + my_strlen(arr + 1);
//}
//int main() {
//	char arr[] = "aasdvs  daci";
//	int len=my_strlen(arr);
//	printf("arr �ĳ����ǣ�%d\n", len);
//	return 0;
//}

//int main() {
//	char arr1[20] = "abcde";
//	char arr2[20] = "sbc";
//	if (strcmp(arr1, arr2) == 0)
//		printf("���");
//	if (strcmp(arr1, arr2) > 0)
//		printf("����");
//	if (strcmp(arr1, arr2) < 0) {
//		printf("С��");
//	}
//}




/*
strcpy
	char* strcpy(char* destination,const char* source);
	Դ�ַ���������'\0'����
	�ὫԴ�ַ����е�'\0'������Ŀ��ռ�
	Ŀ��ռ�����㹻����ȷ���ܴ��Դ�ַ���
	Ŀ��ռ����ɱ�
*/
//ģ��ʵ��strcpy��ª��
//void my_strcpy(char* dest, char* src) {
//	while (*src != '\0') {
//		*dest = *src;
//		dest++;
//		src++;
//	}
//	*dest = *src;
//}
//ģ��ʵ��strcpy�����
//void my_strcpy(char* dest, const char* src) {
//	//���ѭ��������ֵ����*dest��ֵ������������src�����\0ʱ���ͻ��˳�ѭ����
//	while (*dest++ = *src++) {
//		;
//	}
//}
//
//int main() {
//	char arr1[] = "abcdefghikj";
//	char arr2[] = "hello";
//	strcpy(arr1, arr2);
//	printf("%s", arr1);//hello
//	return 0;
//}

//
//#define MAXSIZE 256
//typedef struct String {
//	char ch[MAXSIZE];
//	int length;
//}String;
//String S;
//String* s = &S;
//typedef struct SS {
//	int ch[MAXSIZE];
//	int length;
//}SS;
//SS a;
//SS* p = &a;
//int main() {
//	printf("%p\n", s);			0078A940
//	printf("%p\n", s->ch);		0078A940
//	printf("%p\n", s->ch+1);	0078A941
//	printf("%p\n", &S);			0078A940
//	printf("%p\n", &s->length);	0078AA40
//	printf("%p\n", p);			0078A520
//	printf("%p\n", p->ch);		0078A520
//	printf("%p\n", &a);			0078A520
//	printf("%p\n", &p->length);	0078A920
//	printf("%p\n", p->ch+1);	0078A524

//
//	return 0;
//}

//strcat
/*
char* strcat(char* destination,const char* source);
Դ�ַ���������'\0'����
Ŀ��ռ�����㹻��������Դ�ַ���������
Ŀ��ռ����ɸ���
�����Լ����Լ�׷��
*/
#include<assert.h>
//void my_strcat(char* dest, const char* src) {
//	assert(dest && src);
//	char* ret = dest;
//	//1���ҵ�Ŀ���ַ�����'\0'
//	while (*dest != '\0') {
//		dest++;
//	}
//	//2��׷��
//	while (*dest++ = *src++) {
//		;
//	}
//}
//int main() {
//	char arr1[30] = "hello";
//	char arr2[] = "world";
//	strcat(arr1, arr2);
//	printf("%s\n",arr1);
//	return 0;
//}


/*
strcmp
	int strcmp(const char* str1,const char* str2);
	��׼�涨��
		��һ���ַ������ڵڶ����ַ������򷵻ش���0������
		��һ���ַ������ڵڶ����ַ������򷵻ص���0������
		��һ���ַ���С�ڵڶ����ַ������򷵻�С��0������
*/
//int main() {
//	char* p1 = "abcd";
//	char* p2 = "abce";
//	int ret = strcmp(p1, p2);
//	printf("%d", ret);
//	return 0;
//}

//int my_strcmp(const char* str1, const char* str2) {
//	//�Ƚϣ�����һֱ��ȵ�'\0'ʱ�ͷ���0��˵���������
//	while (*str1 == *str2) {
//		if (*str1 == '\0')
//			return 0;
//		str1++;
//		str2++;
//	}
//	//�˳�ѭ����˵��ֻ�ܴ��ں�С����
//	if (*str1 > *str2)
//		return 1;//����
//	else
//		return -1;//С��
//}
//int main() {
//	char* p1 = "abc";
//	char* p2 = "abh";
//	int ret = strcmp(p1, p2);
//	printf("�������ֵ�ǣ�%d\n", ret);
//	if (ret > 0)
//		printf("�������ţ�p1>p2\n");
//	if (ret == 0)
//		printf("�������ţ�p1==p2\n");
//	if (ret < 0)
//		printf("�������ţ�p1<p2\n");
//	return 0;
//}
/*
strncpy

	char* strncpy(char* destination,const char* source,size_t num);
	����num�� �ַ���Դ�ַ�����Ŀ��ռ�
	���Դ�ַ����ĳ���С��num���򿽱����ַ�������Ŀ��ĺ���׷��0��ֱ��num��
*/
//char* my_strncpy(char* str1, const char* str2, int num) {
//	char* dest = str1;
//	//num��str2��ֵ������Ϊ0����һΪ0�˳�ѭ��
//	while (num && *str2) {
//		*str1 = *str2;
//		num--;
//		str1++;
//		str2++;
//	}
//	//����ѭ���˳�����û�а�'\0'������
//	if (num != 0) {
//		while (num--) {
//			*str1 = '\0';
//			str1++;
//		}
//	}
//	return dest;
//}
//int main() {
//	char arr1[20] = "abcdefeghi";
//	char arr2[] = "hello";
//	printf("ԭ����arr1��%s\n", arr1);
//	strncpy(arr1, arr2, 8);//arr2λ�������Ჹ'\0'
//	printf("������arr1��%s\n", arr1);
//	return 0;
//}
//char* my_strncpy(char* str1, const char* str2, int num) {
//	char* dest = str1;
//	
//	while (num && (*str1++=*str2++)) {
//		num--;
//	}
//	//����ѭ���˳����Ѿ�������'\0'
//	if (num) {
//		while (--num) {
//			*str1++ = '\0';
//		}
//	}
//	return dest;
//}

/*
strncat
	char* strncat(char* destination,const char* source,size_t num);
	��Ŀ���ַ�����'\0'��׷�ӣ��Ḳ�ǵ�ǰ'\0'����׷�������� һ��'\0'
	׷�ӵĳ��ȱ�Դ�ַ������Ļ���ֻ׷��һ��Դ�ַ���
*/
//char* my_strncat(char* str1, const char* str2, int num) {
//	char* dest = str1;
//	//����'\0'
//	while (*str1++) {
//		;
//	}
//	//�����һ����Ҫ���ȥ
//	str1--;
//	//����
//	while (num--&&(*str1++ = *str2++)) {
//		;
//	}
//	return dest;
//}
//int main() {
//	char arr1[20] = "hello\0xxxxxxxx";
//	char arr2[] = "world";
//	printf("ԭ�����ַ�����%s\n", arr1);
//	strncat(arr1, arr2, 8);
//	printf("�������ַ�����%s\n", arr1);
//}


/*
strncmp
	int strncmp(const char* str1,cosnt char* str2,size_t num);
	�Ƚ�ǰnum���ַ�
*/
//void F(double T, double k, double m) {
//	double s1, s2, s3;//ͻ��С�ݣ���ͻ������ϸ��
//	s1 = m * T;
//	s2 = s1 / 60;
//	s3 = s2 / 60;
//	double r = (double)k - s3;
//	printf("%lf\n", r);
//	if (r < 1) {
//		printf("Become a fool!\n");
//	}
//}
//int main() {
//	//��������ϸ������ͨ��ʱ��
//	double T = 2;
//	double k = 1;
//	double m = 236+1000;
//	F(T, k, m);
//	return 0;
//}

int main() {
	int n;
	scanf("%d", &n);
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += i;
	}
	printf("%d", sum);
}