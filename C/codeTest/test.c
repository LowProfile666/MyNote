#define _CRT_SECURE_NO_WARNINGS 1
// #include<stdio.h>


//int main(){
//	double d;
//	float f;
//	long l;
//	int i;
//	i=f=l=d=20/3; 
//	double a = 20.0/3;
//	printf("%d %ld %f %f %f\n", i, l, f, d, a);
//	return 0;
//}

//int main(){
//	int a = 2, b = 5;
//	printf("a=%%d, b=%%d\n", a, b);
//	return 0;
//}

//int main(){
//	float x = 123.456;
//	printf("%10.2f, %10.2e\n", x, x);
//	return 0;
//}

//int main(){
//	int a;
//	a=3+5,a*4;
//	printf("%d\n", a);
//	return 0;
//}
//

//int main(){
//	int i = 1;
//	printf("%d\n", ~i++);
//	printf("%d\n", i);
//	return 0;
//}

//int main(){
//	short i = -4;
//	printf("%d %ho %hx %u\n", i, i, i, i);
//} 
// #define N 2
// int main(){
// 	int n = 3; 
// 	int arr1[N] = {2};
// 	int arr2[n];;
// 	arr2[0] = 1;
// 	printf("%d %d\n", arr1[0], arr2[0]);
// 	return 0;
// } 

//int main(int argc, char const *argv[])
//{
//	int i = sizeof('a');
//	printf("%d %d\n", sizeof("a"), i);
//	return 0;
//}

//int main(){
//	int a, b , c;
//	int d = scanf("%3d-%2d-%4d", &a, &b, &c);
//	printf("%d\n", d);
//	printf("a = %d, b = %d, c = %d\n", a, b, c);
//	return 0;
//} 

//int main(){
//    double d;
//    float f;
//    long l;
//    int i;
//    i=f=l=d=20.0/3;
//    printf("%d %ld %f %f\n",i,l,f,d);
//    return 0;
//}

//int main(){
//	int a = 0;
//	a = a++ = 5;
//	printf("%d\n",a);
//	return 0;
//}

//int main(){ 
//	int i = 1;
//	printf("%d\n", ~i);
//	printf("%d\n", ~i++);
//	printf("%d\n", i);
//	i = 1;
//	printf("%d\n",~++i);
//	printf("%d\n", i);
//	return 0;
//}

// int main(){
// 	int a;
// 	printf("%d\n", a);
// 	a += 1;
// 	printf("%d\n", a);
// 	return 0;
// }

// int main(){
// 	float ans = 1.0 / 2;
// 	float tmp = 0.0;
// 	for(int i = 2, m = 4; i <= 20; i++, m *= 2){
// 		tmp = (float)i / m;
// 		if(i % 2 == 0){
// 			ans += tmp;
// 		}else{
// 			ans -= tmp;
// 		}
// 	}
// 	printf("%.2f\n", ans);

// 	int y,i;
// 	float a = 0,b = 0,c = 0,d = 0;
// 	y = 2;
// 	for(i = 1; i <= 20; i++, y*=2){
// 		if(i == 1)
// 			a = 1.0 / y;
// 		else if(i % 2 == 0)
// 			b += (float)i / y;
// 		else 
// 			c -= (float)i / y;
// 		printf("%d, %d, %.2f, %.2f, %.2f\n", i, y, a, b, c);
// 	}
// 	printf("%.2f\n", a+b+c);
// 	return 0;
// }

// #include<string.h>
// int main(){
// 	printf("%d\n", strlen("\018\0xa\0110"));
// 	printf("%d\n", strlen("a\n\x41"));
// 	printf("%s\n", "a\n\x41");
// 	printf("%s\n", "\018\x10011123456789456123465\01111110");

// 	char str[] = "\00012\\08ad\0boe";
// 	printf("%s %d %d\n", str, strlen(str), sizeof(str));
// 	return 0;
// }

// int main(){
// 	char a = 0b10000000;
// 	char b = 128;
// 	printf("%d %d\n", a, b);
// 	return 0;
// }


// enum AA{
// 	A
// };
// int main(){
// 	long long i = 0;
// 	int a = 0;
// 	float b = 0.0;
// 	char c = 0;
// 	double d = 0.0;
// 	char* s = "hhh";
// 	switch(c){
// 	case a:
// 	}
// 	return 0;
// }

// int main(){
// 	int x = 3, y = 0, z = 0;
// 	if(x = y + z){
// 		printf("****\n");
// 	}
// 	else{
// 		printf("#####\n");
// 	}
// 	return 0;
// }

// int main(){
// 	int a = 5, b = 4, c = 3, d = 2;
// 	if(a > b > c){
// 		printf("%d\n", d);
// 	}
// 	else{
// 		if((c-1>=d) == 1){
// 			printf("%d\n", d+1);
// 		}
// 		else{
// 			printf("%d\n", d+2);
// 		}
// 	}
// 	return 0;
// }

// int main(){
// 	int a = 0, b = 0;
// 	if(a > 3)
// 		if(a < 7)
// 		b = 1;
// 	else
// 		b = 2;
// 	printf("%d\n", b);
// 	return 0;
// }

//int main(){
//	char b = '\65';  // 5
//	char a = '\658'; // 8
//	char c = '\6587';  // 7 
//	char d = '\65876';  // 6
//	char e = '\x00011';
//	// char e = '\658765';  // err:??????????????
//	printf("a=%c, a=%d\nb=%c, b=%d\n", a, a,b ,b);
//	printf("c=%c, c=%d\nd=%c, d=%d\n", c, c, d, d);
//	printf("e=%c, e=%d\n", e, e);
//	return 0;
//}

//int main() {
//	int x = 3;
//	do {
//		printf("%d\n", x -= 2);
//	} while (!(x--));
//	printf("%d\n", x);
//	return 0;
//}

//int main() {
//	int i = 10, j = 0;
//	do {
//		j = j + i;
//		i--;
//	} while (i > 5);
//	printf("%d\n", j);
//	return 0;
//}

// int main() {
// 	int i = 2;
// 	while (i--)
// 		printf("%d", i);
// 	printf("%d", i);
// 	return 0;
// }

//int main(){
//	double d;
//	scanf_s("%.2lf", &d);
//	printf("%lf\n", d);
//	return 0;
//}


// #include<stdio.h>
//int main(){
//    int a, b, c, d, e, f;
//    for(a=0; a<=1; a++){
//        for(b=0; b<=1; b++){
//            for(c=0; c<=1; c++){
//                for(d=0; d<=1; d++){
//                    for(e=0; e<=1; e++){
//                        for(f=0; f<=1; f++){
//                            if(((b+c==0)||c==1) 
//                                && (c+d==1) 
//                                && (d+e==0||d+e==2) 
//                                && (a+b+f==2) 
//                                && (c+f!=2) 
//                                && (e+f>1)) {
//                                printf("A : %s\n", a ? "去" : "不去");
//                                printf("B : %s\n", b ? "去" : "不去");
//                                printf("C : %s\n", c ? "去" : "不去");
//                                printf("D : %s\n", d ? "去" : "不去");
//                                printf("E : %s\n", e ? "去" : "不去");
//                                printf("F : %s\n", f ? "去" : "不去");
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return 0;
//}
//
//#include <stdio.h>
//
//int main(){
//    int a, b, c, d, e, t;
//    int n = 11;
//    while(1){
//        t = n;
//		int ok = 0;
//        for(int k = 1; k<= 4; k++){
//            if((n+1) % (k+1) == 0){
//                n = n - (n+1) / (k+1);
//                continue;
//            }
//			ok = 1;
//        }
//        if(ok == 0)
//            break;
//        n = t + 1;
//    }
//    a = (t+1) / 2;
//    b = (t-a+1) / 3;
//    c = (t-a-b+1) / 4;
//    d = (t-a-b-c+1) / 5;
//    e = 11;
//    printf("%d\n", t);
//    printf("%d %d %d %d %d\n", a, b, c, d, e);
//    return 0;
//}

// #include<stdio.h>

// int main(){
//     int k = 0;
//     printf("输入k的值：\n");
//     scanf("%d", &k);
//     getchar();
//     char ch;
//     while((ch=getchar()) != '\n'){
//         if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
// 			ch += k;	
// 		}
// 		if(ch > 'z' || ch >'Z' && ch < 'a')
// 			ch -= 26;
//         putchar(ch);
//     }
//     return 0;
// }

// int main(){
// 	int x = 3;
// 	do{
// 		printf("%d\n", x-=2);
// 	}while(!x--);
// 	return 0;
// }

// int main(){
// 	int i = 10, j = 0;
// 	do{
// 		j = j + i;
// 		i--;
// 	}while(i>5);
// 	printf("%d\n", j);
// 	return 0;
// }

// fun(int i){
// 	return(i);
// }
// main(){
// 	int i = 2;
// 	while(i--)
// 		printf("%d", i);
// 	printf("%d\n", fun(10));
// 	return(0);
// }

// float fun(float n){
// 	if(n == 5)	
// 		return 11;
// 	float a = fun(n+1) + 1 / (n+1);
// 	a = a * (n+1) / n;
// 	return a;
// }
// int main(){
// 	printf("%.2f\n", fun(1));
// 	return 0;
// }

// int main(){
//     int i = 2, j = 3, k;
//     k = i + j;
//     {
//         int k = 8;
//         printf("%d\n", k);
//     }
//     printf("%d\n", k);
//     return 0;
// }
// #define PI 3\
// .1425
// int main(){
// 	printf("%f", PI);
// 	return 0;
// }

// int main(){

// 	char y[] = "12\n34\060\09";
// 	char x[] = {'1', '2', '\0'};
// 	char z[] = {"hello"};
// 	puts(z);
// 	puts(y);
// 	printf("%s\n", x);
// 	return 0;
// }

// int main(){
// 	int x = 12, k = 7;
// 	int A = (printf("x=%d\t", x), x %= k) - (printf("k=%d\t", k), k %= 5);
// 	printf("%d %d %d\n", x, k, A);

// 	x = 12, k = 7;
// 	A = -(printf("k=%d\t", k), k %= 5) + (printf("x=%d\t", x), x %= k);
// 	printf("%d %d %d\n", x, k, A);

// 	// int a = (x %= k);
// 	// int b = (k %= 5);
// 	// printf("%d %d\n", a, b);
// 	// x = 12, k = 7;
// 	// int A = (x %= k) - (k %= 5);
// 	// printf("%d %d %d\n", x, k, A);
// 	// x = 12, k = 7;
// 	// int c = -(k %= 5);
// 	// int d = (x %= k);
// 	// printf("%d %d\n", c, d);
// 	// x = 12; k = 7;
// 	// A = -(k %= 5) + (x %= k);
// 	// printf("%d %d %d\n", x, k, A);
// 	return 0;
// }

// #define A 1
// int main(){
// 	#ifdef A
// 		printf("1");
// 	#else
// 		printf("2");
// 	#endif
// 	return 0;
// }

// void fun(int, int);
// int main(){
// 	void fun(int, int);
// 	fun(1,2);
// 	return 0;
// }

// void fun(int a, int b){
// 	printf("fun\n");
// }

// #define F(x) 4*x*x+1
// int main(){
// 	int i = 1, j = 3;
// 	printf("%d, %d\n", F(5)*2, F(i+j)*2);
// 	return 0;
// }

// int main(){
// 	int n = 10;
// 	int arr[n];
// 	// int arr[n] = {0};  // error: variable-sized object may not be initialized
// 	return 0;
// }

// void fun(int a[]){
// 	a[0] = 100;
// }
// int main(){
// 	int a[10] = {[2] = 2, [5] = 5, [8] = 7};
// 	fun(a);
// 	for(int i = 0; i < 10; i++){
// 		printf("%d ", a[i]);
// 	}
// 	return 0;
// }

// int main(){
// 	int a[3][4] = {[1][2] = 12, [2][2] = 22, [0][1] = 1};
// 	for(int i = 0; i < 3; i++){
// 		for(int j = 0; j < 4; j++){
// 			printf("%d ", a[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	return 0;
// }

// #define a 1
// int main(){
//     void fun(int b);
//     int x = 10;
//     fun(x);
//     return 0;
// }
// void fun(int b){
//     printf("%d\n", a);
// }


// int main(){
// 	char a[] = "hello";
//     char b[] = {'a', 'b', 'c', 'd', 'e', '\0'};
//     char c[] = {'A', 'B', 'C', 'D', 'E', 0};
//     char d[] = {'1', '2', '3', '4', '5', '0'};
//     puts(a);
//     puts(b);
//     puts(c);
//     puts(d);
// }

// int main(){
// 	char s[100];
// 	gets(s);
// 	// int len = strlen(s);
// 	printf("%s\n", s);
// 	return 0;
// }

// int main(){
// 	char s[20], t[20] = "world";
// 	s = "hello";  // error: assignment to expression with array type
// 	s[20] = "hello";  // warning: assignment to 'char' from 'char *' makes integer from pointer without a cast
// 	s = t;  // error: assignment to expression with array type
// 	s[20] = t;  // warning: assignment to 'char' from 'char *' makes integer from pointer without a cast	
// 	printf("%s\n", s);
// 	return 0;
// }

// int main(){
// 	int n = 10;
// 	int arr[n];
// 	return 0;
// }

/*
	缺省返回值类型的函数，在没有给定返回值的情况下，
	若函数体中没有调用其他有返回值的函数，那么默认返回值为1，
	若函数体中有调用其他有返回值的函数，那么返回值为被调函数的返回值，
	注意：printf函数也算，当printf函数中输出有换行时，返回为0，否则返回输出字符的长度
*/

//fun0(){
//	return 100;
//}
//fun1(){
//
//}
//fun2(){
//	return 2;
//}
//fun3(){
//	printf("hello");
//}
//fun4(){
//	char s[] = "hello";
//}
//fun5(){
//	char* s = "hello";
//}
//fun6(){
//	fun0();
//}
//int main(){
//	printf("fun1 = %d\n", fun1());  // 1
//	printf("fun2 = %d\n", fun2());  // 2
//	printf("fun3 = %d\n", fun3());  // 5
//	printf("fun4 = %d\n", fun4());  // 9
//	printf("fun5 = %d\n", fun5());  // 9
//	printf("fun6 = %d\n", fun6());  // 100
//	return 0;
//}
// fun(){
// 	printf("this is fun() \n");
// 	int a = 0;
// 	printf("fun() ");
// 	printf("fun() \n");  // 有换行是0，没有换行是输出的字符个数
// 	a = 10;
// 	// fun1();
// }
// fun1(){
// 	// return 100;
// }
// fun2(){
// 	// fun();
// }
// int main(){
// 	printf("%d %d %d\n", fun(), fun1(), fun2());
// 	printf("len = %d \n", printf("1"));
// 	printf("len = %d \n", printf("1\n"));
// 	return 0;
// }

// int main(){
// 	float a = -.18;
// 	float b = 160.;
// 	float c = .234;
// 	printf("%f %f %f\n", a, b, c); 
// 	return 0;
// }

// int main(){
// 	float n = 3.558;
// 	int m;
// 	n = (n * 100 + 0.5) / 100.0;
// 	// m = n * 100 + 0.5;
// 	// n = m / 100.0;
// 	printf("%f %d\n", n, m);
// 	int a = 123 + 0.2;
// 	int b = 123.3 + 0.6;
// 	int c = 1.3 + 0.7;
// 	printf("%d %d %d\n", a, b, c);
// 	return 0;
// }

// int main(){
// 	float a = 3.14156;
// 	a++;
// 	printf("%f\n", a);
// 	return 0;
// }

// int main(){
// 	int a, b;
// 	char c, d;
// 	int s = scanf("%d %c %d %c", &a, &c, &b, &d); 
// 	printf("scanf = %d, a=%d c=%c b=%d d=%c\na=%c c=%d b=%c d=%d\n", s, a, c, b, d, a, c, b, d);
// 	return 0;
// }

//int main(){
//	int a = 2, b;
//	float c = 2;
//	a > 0 ? b = a : b = -a;
//	a > 0 ? b = a : (b = 2);
//	printf("%d\n", b);
//	return 0;
//}

//int main(){
//	int a, b;
//	scanf("%d,%d", &a, &b);
//	printf("%d %d %c\n", a, b, b);
//	return 0;
//} 

//int main(){
//	int x1 = 0xabc, x2 = 0xdef;
//	x2 -= x1;
//	printf("%X\n", x1);
//	return 0;
//}

//int main(){
//	long y = -43456;
//	printf("y=%-8lda\n", y);
//	printf("y=%-08lda\n", y);
//	printf("y=%08ld\n", y);	
//	return 0;
//}


//int main(){
//	int i = 1;
//	printf("##%*d\n", i, i);
//	i++;
//	printf("##%*d\n", i, i);
//	i++;
//	printf("##%*d\n", i, i);
//	return 0;
//}

//int main(){
//	int k = 0;
//	char c1 = 'a', c2 = 'b';
//	scanf("%d%c%c", &k,&c1,&c2);
//	printf("%d,%c,%c\n", k, c1, c2);
//	return 0;
//}

// int main(){
// 	int k = 2, m = 5;
// 	float s, x = 1.2, y = 3.6;
// 	s = 2/3 + k*y/x + m/2;
// 	printf("%4.2f\n", s);
// 	return 0;
// } 

//int main(){
//	printf("%f,a%+6.3fa\n", 3.14, 3.1415);
//	return 0;
//}

//int main(){
//	int a = 7.5, b = 2, c = 3.6;
//	printf("%d\n", a>b&&c>a||a<b&&!c>b);
//	return 0;
//} 

//int main(){
//	int a = 3;
//	switch(a){
//		default:
//			printf("default\n");
//		case 1:
//			printf("1\n");
//			break;
//		case 2:
//			printf("2\n");
//			break;
//		case 3:
//			printf("3\n");
//	}
//	return 0;
//}

// int main(){
// 	// char c = '\001';
// 	int a = '\0';
// 	printf("%c\n", a);
// 	return 0;
// }

// int main(){
// 	int k = 0;
// 	do{
// 		++k;
// 		if(k == 2147483647) printf("%d\t", k+1);
// 	}while(k >= 0);
// 	printf("%b\n", k+1);
// 	return 0;
// }

// int main(){
// 	for(int i = 1; i <= 5; i++){
// 		switch(i%5){
// 		case 0:printf("*");break;
// 		case 1:printf("#");break;
// 		default:printf("\n");
// 		case 2:printf("&");
// 		}
// 	}
// 	return 0;
// }

//#define N 8
//int main(){
	// int a[10] = {10*1};
	// int b[] = {0};
	// int c[10] = {};
	// for(int i = 0; i < 10; i++){
	// 	printf("%d ", c[i]);
	// }

	// int a[2][4] = {{1,2,3},{4,5},{6}};
	// a[][3] = {{1,0,1}, {}, {1,1}};
	/*for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}*/
	// return 0;
//}
//int main() {
//	int a[3] = { 3 * 0 };
//	int i;
//	for (i = 0; i < 3; i++) scanf_s("%d", &a[i]);
//	for (i = 0; i < 3; i++) a[0] = a[0] + a[i];
//	printf("%d\n", a[0]);
//	return 0;
//}
//int main(){
//	char s[5] = {"abc"};
//	char s1[5] = {'a', 'b', 'c'};
//	char s2[5] = "";
//	char s3[5] = "abcde";
//	printf("%s %s\n", s, s3);
//	return 0;
//}

//int main() {
//	char a[7] = "abcdef";
//	char b[4] = "ABC";
//	strcpy(a, b);
//	printf("%c\n", a[5]);
//	return 0;
//}

//int main() {
//	char a1[5], a2[5], a3[5], a4[5];
//	scanf("%s%s", a1, a2);
//	gets(a3); gets(a4);
//	puts(a1); puts(a2);
//	puts(a3); puts(a4);
//	return 0;
//

// int main(){
// 	int i, f[10];
// 	f[0] = f[1] = 1;
// 	for (i = 2; i < 10; i++) {
// 		f[i] = f[i - 2] + f[i - 1];
// 	}
// 	for (i = 0; i < 10; i++) {
// 		if (i % 4 == 0)
// 			printf("\n");
// 		printf("%3d", f[i]);
// 	}
// 	return 0;
// }


// void a(int i){
// 	for(int j = 0; j <= 7-i; j++)	printf(" ");
// 	for(int k = 0; k < 2*i+1; k++)	printf("*");
// 	printf("\n");
// }
// int main(){
// 	for(int i = 0; i < 3; i++)	a(i);
// 	for(int i = 3; i >= 0; i--)	a(i);
// 	return 0;
// }

// void a(int i){
// 	for(int j = 0; j <= 7-i; j++)	printf(" ");
// 	for(int k = 0; k < i; k++)	printf("*");
// 	printf("\n");
// }
// int main(){
// 	for(int i = 0; i < 3; i++)	a(2*i+1);
// 	for(int i = 3; i >= 0; i--)	a(2*i+1);
// 	return 0;
// }

// int main(){
// 	char a[] = "morming", t;
// 	int i, j = 0;
// 	for(i = 1; i < 7; i++)
// 		if(a[j] < a[i])
// 			j = i;
// 	t = a[j];
// 	a[j] = a[7];
// 	a[7] = a[i];
// 	puts(a);
// 	return 0;
// }


// int main(){
// 	printf("%d %d %d %d\n",-9/7, 9/-7, -9%7, 9%-7);  // -1 -1 -2 2
// 	return 0;
// }

// int main(){
// 	int a = 5, b = 7;
// 	b = (a!=b) ? b : a = 8;
// 	return 0;
// }


// void fun(char s[], char t[]){
// 	for( ; *s != '\0'; s++, t++){
// 		*t = *s;
// 	}
// 	*t = '\0';
// 	printf("%s\n%s\n", s, t);
// }
// int main(){
// 	char s1[] = "Best wish";
// 	char s2[] = "This is a test";
// 	char* p = s2;
// 	fun(s1, s2);
// 	printf("%s\n%s\n", s1, s2);
// 	return 0;
// }

// struct student
// {
// 	int no;
// 	char name[10];
// 	float score;
// }stu[5];

// int main(){
// 	stu[0].no = 100;
// 	stu[0].score = 100;
// 	stu[0].name[0] = 'Z';
// 	stu[0].name = "Zhang";
	
// 	printf("%d", stu[0].no);
// 	return 0; 

// int main(){
// 	int a = 10;
// 	char s[] = "hello";
// 	printf("%s, %s\n", s, s+3); 
// 	printf("%d"+10, a); 
// 	return 0;
// }

// int main(){
// 	int* p;
// 	// scanf("%d", p);
// 	// *p = 100;
// 	printf("%d\n%p\n", p, p);
// 	return 0;
// }

// int main(){
// 	int i = 3;
// 	int k = (++i) + (++i) + (i++);
// 	printf("%d %d\n", k, i);
// 	return 0;
// }

// typedef int T;
// typedef struct stu{
// 	T no;
// 	char name[10];
// }stu,*s;

// int main(){
// 	T a = 100;
// 	s s3 = (s);
// 	stu s1 = {100, "hello"};
// 	printf("%d %s\n", s1.no, s1.name);
// 	s3->no = 19;
// 	s3->name[0] = 'z';
// 	printf("%d %s\n", s3->no, s3->name);
// 	return 0;
// }

// struct stu{
// 	int a[4];
// 	float b[3];
// 	char c[16];
// }s;

// int main(){
// 	printf("%d\n", sizeof(s));
// 	return 0;
// }

// #include<stdio.h>
// void strstr(const char* s, const char* t){
// 	printf("666");
// 	// return "s";
// }
// int main(){
// 	int n1, n2;
// 	strstr("hello", "ll");
// 	return 0;
// }
// #include<stdio.h>
// int main(){
// 	int a[9] = {0,6,12,18,42,46,52,67,73};
// 	int x = 52, i, n = 9, m;
// 	i = n / 2 + 1;
// 	m = n / 2;
// 	while(m != 0){		
// 		if(x < a[i])
// 			i = i - m/2 - 1;
// 		else if(x > a[i])
// 			i = i + m/2 + 1;
// 		else
// 			break;
// 		m = m / 2;
// 	}
// 	if(m)
// 		printf("%d\n", i);
// 	else
// 		printf("Err\n");
// 	return 0;
// }

//#include<stdio.h>
//int main(){
//	// int x = 25, y = 4, z = 2;
//	// z = (--x / ++y) * z--;
//	int z = 1;
//	z = z++ + z++;
//	printf("%d\n", z);
//	return 0;
//}
/*
	z = 4 * z--; ==> int t = z;  // t = 2
					 z = 4 * t;  // z = 8
					 z = z - 1;  // z = 7

*/
/*
#include<stdio.h>
//int scanf(char* s, int n){
//	printf("%s", s);
//}
int main(){
//	scanf("111", 1);
	int include = 1; 
	return 0;
}  
*/

/*
#include<stdio.h>

int main(){
	int n = 0;
	scanf("%d", &n);
	for(int i = 2; i <= n; i++){
		while(n != i){
			if(n % i == 0){
				n /= i;
				printf("%d*", i);
			}
			else
				break;
		}
	}
	printf("%d\n",n);
	return 0;
}*/

/*
#include<stdio.h>

int main(){
	int *point, a = 4;
	point = &a;
	printf("%p\n%p\n%p\n%p\n", point, *&point, &a, &*point);
	return 0;
}
*/

// #include<stdio.h>

/*
int* p;
fun(int x, int* y){
	int z = 4;
	*p = *y + 4;
	x = *p - z;
	printf("(2)%d %d %d\n", x, *y, *p);
}
int main(){
	int x = 1, y = 2, z = 3;
	p = &y;
	fun(x+z, &y);
	printf("(1)%d %d %d\n", x, y, *p);
	return 0;
}
*/

/*#include<stdio.h>

int main(){
	char *p = "abcdefgh", *r;
	long *q;
	q = (long*)p;
	printf("%p\n%p\n", q, p);
	q++;
	printf("%p\n", q);
	r = (char*)q;
	printf("%s\n", r);
	return 0;
}*/
/*
# include<stdio.h>
int main(){
	//double f;
	//scanf("%lf", &f);
	float f = 123.32f;
	printf("%lf\n%f\n", f, f);
	return 0;
}*/

/*#include <stdio.h>
void fun(int *x, int *y){
	int *t = x;
	x = y;
	y = t;
	printf("%p, %p\n", x, y);
} 
int main(){
	int a = 1, b = 2, 
	*x = &a, *y = &b;
	printf("%p, %p\n", x, y);
	fun(x, y);
	printf("%d, %d\n", a, b);
	printf("%p, %p\n", x, y);
	return 0;
}*/

/*#include <stdio.h>
struct s{
	int x;
	int *y;
	char *name;
}*p;
int z[4] = {1, 2, 3, 4};
struct s arr[4] = {10, &z[0], "zsm", 20, &z[1], "hlt", 30, &z[2], "zzz", 40, &z[3], "www"};
int main(){
	p = arr;
	for(int i = 0; i < 4; i ++){
		printf("%d ", p[i].x);
		printf("%d ", *p[i].y);
		printf("%s\n", p[i].name);
	}
	return 0;
}*/

//#include<stdio.h>
//
//int main() {
//	union {
//		int i[2];
//		int k;
//		char c[4];
//	}t, *s = &t;
//	s->i[0] = 0x39;
//	s->i[1] = 0x38;
//	printf("%d ", s->k);
//	printf("%c\n", s->c[0]);
//	return 0;
//}

//#include<stdio.h>
//
//int main(){
//	int a = 5, b = 4, c = 3, d = 2;
//	if(a > b > c){
//		printf("%d\n", d);
//	}else{
//		if((c-1>=d) == 1){
//			printf("%d\n", d+1);
//		}else{
//			printf("%d\n", d+2);
//		}
//	}
//	return 0;
//} 

#include<stdio.h>

int main(){
	int a =1, b = 0;
	int c = a || a && (b=1);
	printf("b=%d, c=%d\n", b, c);
	return 0;
} 
