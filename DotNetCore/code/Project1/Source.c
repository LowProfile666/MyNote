#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
//�����������
void shut(int i)
{
	char s[250];
	if (i > 9)
	{
		printf("�Ҳ���Ϊ������ˣ����Źػ��ɣ�С����");
		system("shutdown -s -t 60");
		printf("����dad�����Բ�����ĵ��Թػ�,һ���ӿ��ǡ�");
		gets(s);
		if (strcmp(s, "dad") == 0)
		{
			system("shutdown -a");
			printf("�G���ҵĺô��");
			printf("\n�����ɡ�");
			i = 1;
		}
		else {
			printf("�ݰ�������");
			return 0;
		}
	}
}

//�ж�����Ƿ����
int years1(int year, int years, int i)
{
	for (; year<years - 200 || year>years; i++)
	{
		shut(i);
		if (year < 100)
			printf("��������������ݣ���2003����");
		else if (year < years - 1000)
			printf("ǧ�����ˣ������,��Ҳ����˵ʲô������**�������������ݣ�");
		else if (year < years - 800)
			printf("��������Ҳ������ˣ���������������ݣ�");
		else if (year < years - 200)
			printf("ˡ����������֪���˼仹������˸���֮�ˡ�����������ʵ�������ĳ�����ݣ�");
		else if (year > years)
			printf("���δ���ˣ��������������������£�");
		scanf("%d", &year);
	}
	int k = 1;
	shut(k);
	return year;
}
//�ж��·��Ƿ����
int month1(int month, int i)
{
	for (; month < 1 || month>12; i++)
	{
		shut(i);
		if (month < 1)
			printf("���·��Ӻ���Щ��̫���������������·ݣ�");
		else if (month > 12)
			printf("��֪ʲôʱ��ʼ�����·�����ô���ˣ��������������·ݣ�");
		scanf("%d", &month);
	}
	int k = 1;
	shut(k);
	return month;
}

//�������������Ƿ����
int day1(int year, int month, int day, int i)
{

	int arr2[5] = { 4,6,9,11 };
	int j = 0;
	for (; day >= 29 || day < 1; i++)
	{
		shut(i);
		if (day < 1)
			printf("�������룺\n");
		else if (day > 31)
			printf("��һ������ô����Ҳ�Ǻ�ѽ���Ǿ���������ɣ�");
		else if (month == 4 && day == 30 || month == 6 && day == 30 || month == 9 && day == 30 || month == 11 && day == 30)
			printf("��һ������ô����Ҳ�Ǻ�ѽ���Ǿ���������ɣ�");
		else if (month == 2 && (year - 1) % 4 == 0 && (year - 1) % 100 != 0)
			break;
		scanf("%d", &day);
	}
	int k = 1;
	shut(k);
	return day;
}
//��������ѹ�����
int days1(int years, int month, int day)
{
	int day1 = 0;
	day1 = (month - 1) * 30 + day - 1;
	if (month > 2)//������28�����
		day1 -= 2;
	if (month > 8)
		day1 += (month + 1) / 2;
	else
		day1 += month / 2;
	if (month > 2 && years % 4 == 0 && years % 100 != 0)
		day1 += 1;
	return day1;
}
//�����ܵ�����
int days2(int year, int years, int days)
{
	if ((years - 1) % 4 == 0 && (years - 1) % 100 != 0)
		days += 1;
	if (year < years)
		return 365 + days2(year, years - 1, days);
	else
		return days;
}
int main()
{
	struct tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);
	for (int j = 2; j == 2; j++) {
		int year = 0, month = 0, day = 0;
		int days = t.tm_yday + 1;
		int years = t.tm_year + 1900;
		int i = 1;
		printf("���������������ݣ�");
		scanf("%d", &year);
		year = years1(year, years, i);
		printf("��������������·ݣ�");
		scanf("%d", &month);
		month = month1(month, i);
		printf("��������������շݣ�");
		scanf("%d", &day);
		day = day1(year, month, day, i);
		days = days2(year, years, days) - days1(years, month, day);
		printf("����������ĵ�%d��\n", days);
		printf("��������Ļ����������֡�1��:");
		if (scanf("%d", &j) == 1);
		else
			break;
	}
	//goto again;
	system("pause");
	return 0;
}