#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
//解决乱填问题
void shut(int i)
{
	char s[250];
	if (i > 9)
	{
		printf("我不会为你计算了，等着关机吧，小垃圾");
		system("shutdown -s -t 60");
		printf("输入dad，可以不对你的电脑关机,一分钟考虑。");
		gets(s);
		if (strcmp(s, "dad") == 0)
		{
			system("shutdown -a");
			printf("欸，我的好大儿");
			printf("\n继续吧。");
			i = 1;
		}
		else {
			printf("拜拜嘞您嘞");
			return 0;
		}
	}
}

//判断年份是否合理
int years1(int year, int years, int i)
{
	for (; year<years - 200 || year>years; i++)
	{
		shut(i);
		if (year < 100)
			printf("请输入完整的年份（如2003）：");
		else if (year < years - 1000)
			printf("千年王八，万年龟,我也不好说什么，还请**重新输入出身年份：");
		else if (year < years - 800)
			printf("彭祖在世也不过如此，还请重新输入年份：");
		else if (year < years - 200)
			printf("恕我愚昧，不知这人间还存在如此高龄之人。还请您老如实输入您的出生年份：");
		else if (year > years)
			printf("你好未来人，请重新输入你出身的年月：");
		scanf("%d", &year);
	}
	int k = 1;
	shut(k);
	return year;
}
//判断月份是否合理
int month1(int month, int i)
{
	for (; month < 1 || month>12; i++)
	{
		shut(i);
		if (month < 1)
			printf("这月份视乎有些不太合理，请重新输入月份：");
		else if (month > 12)
			printf("不知什么时候开始，这月份有这么多了，还请重新输入月份：");
		scanf("%d", &month);
	}
	int k = 1;
	shut(k);
	return month;
}

//计算输入日期是否合理
int day1(int year, int month, int day, int i)
{

	int arr2[5] = { 4,6,9,11 };
	int j = 0;
	for (; day >= 29 || day < 1; i++)
	{
		shut(i);
		if (day < 1)
			printf("重新输入：\n");
		else if (day > 31)
			printf("这一个月这么多天也是好呀，那就重新输入吧：");
		else if (month == 4 && day == 30 || month == 6 && day == 30 || month == 9 && day == 30 || month == 11 && day == 30)
			printf("这一个月这么多天也是好呀，那就重新输入吧：");
		else if (month == 2 && (year - 1) % 4 == 0 && (year - 1) % 100 != 0)
			break;
		scanf("%d", &day);
	}
	int k = 1;
	shut(k);
	return day;
}
//计算今年已过天数
int days1(int years, int month, int day)
{
	int day1 = 0;
	day1 = (month - 1) * 30 + day - 1;
	if (month > 2)//二月以28天计算
		day1 -= 2;
	if (month > 8)
		day1 += (month + 1) / 2;
	else
		day1 += month / 2;
	if (month > 2 && years % 4 == 0 && years % 100 != 0)
		day1 += 1;
	return day1;
}
//计算总的天数
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
		printf("请输入你出生的年份：");
		scanf("%d", &year);
		year = years1(year, years, i);
		printf("请输入你出生的月份：");
		scanf("%d", &month);
		month = month1(month, i);
		printf("请输入你出生的日份：");
		scanf("%d", &day);
		day = day1(year, month, day, i);
		days = days2(year, years, days) - days1(years, month, day);
		printf("这是你出生的第%d天\n", days);
		printf("继续计算的话，输入数字“1”:");
		if (scanf("%d", &j) == 1);
		else
			break;
	}
	//goto again;
	system("pause");
	return 0;
}