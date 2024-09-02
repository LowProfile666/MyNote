<center><h1>贪吃蛇</h1></center>

[TOC]

第一次使用`graphics`库，一些不认识的函数在最后面有解释。

以下代码都是在VS2022中编写。

# 1、具体实现的效果

+ 按键控制移动
+ 空格实现暂停
+ 可以穿墙
+ 记录分数，达到目标分数后退出

如图：

![snake 00_00_00-00_00_35](https://gitee.com/zsm666/image-bed/raw/master/img/%E8%B4%AA%E5%90%83%E8%9B%87%E5%8A%A8%E5%9B%BE.gif)

程序还是比较粗糙，还有很多地方可以更改。

---

# 2、准备

知识点：结构体、数组、循环、函数、easyx。

需要使用到easyx绘图库，需要去[官网](https://easyx.cn/)下载，选择对应的版本安装即可。

> EasyX 是什么

EasyX Graphics Library 是针对 Visual C++ 的免费绘图库，支持 VC6.0 ~ VC2022，简单易用，学习成本极低，应用领域广泛。目前已有许多大学将 EasyX 应用在教学当中。

“下载 -> 安装 -> 使用”，全过程不超过一分钟。具体安装步骤请[参考](https://easyx.cn/setup)。

EasyX 含有一些简单的函数集合，几乎不用学习，直接翻看参考手册就可以直接使用。[在线参考手册](https://docs.easyx.cn](https://docs.easyx).cn/)。

因为easyx主要是针对C++的，所以在用的时候，要把源文件的后缀名从`.c`改成`.cpp`，然后再用C语言写就没问题，不然的话用不了。

---

# 3、整体思路

+ 首先需要一个图形窗口，游戏在这个窗口里面运行；
+ 食物和蛇是两个结构，需要定义两个结构体；
+ 食物是随机刷新的；
+ 要想通过键盘控制蛇的移动，必须要获取按下的键的键值。

这次主要的新内容是easyx和graphics库的使用。

代码中有很多地方用到坐标，坐标默认的原点在窗口的左上角，X 轴向右为正，Y 轴向下为正。如图：

![image-20230219112727803](https://gitee.com/zsm666/image-bed/raw/master/img/%E5%9D%90%E6%A0%87%E7%B3%BB.png)

---

# 4、宏定义

先定义一下需要的常量。

```c
#define SNAKE_MAXSIZE 500  // 蛇的最大长度
#define SCORE_MAXSIZE 100  // 最大得分数
#define HEIGHT 640  // 窗口的高度
#deifne WIDE 480  // 窗口的宽度
// 因为食物和蛇的身体都是小圆圈，也可以将食物和蛇的半径定义为常量使用。
```

----

# 5、定义蛇、食物、方向

> 定义蛇

```c
struct Snake{
    int r;  // 半径
    int len;  // 节数，身体长度
    int score;  // 分数
    int speed;  // 速度，也就是一次移动多远距离
    int dirction;  // 方向，上下左右
    POINT coord[SNAKE_MAXSIZE];  // 坐标(coordinate)，保存蛇的每节身子的坐标
}snake;
```

`int r`：蛇是由多个小圆组成的，蛇的每一节身体就是一个无边框实心小圆，这个小圆需要一个半径来控制蛇的粗细；

`int len`：还需要一个长度属性来记录蛇的长度，方便后面给蛇的每一节身体进行绘制；

`int score`：将玩家得到的分数也记录在蛇体内；

`int speed`：控制蛇移动的速度，其实就是一次移动多远的距离，这个应该半径有关系。

`int dirction`：记录蛇移动的方向（上下左右）。

`POINT coord[SNAKE_MAXSIZE]`：保存蛇每一节身体的坐标，以`coord[0]`作为蛇头。

POINT也是一个结构体。<a id="point1" href="#point2">详情</a>。

> 定义食物

```c
struct Food{
    int r;  // 半径
    int x;  // 横坐标
    int y;  // 纵坐标
    bool flag;  // 标记是否被吃
}food;
```

`int r`：食物也是由实心小圆构成，也需要半径；

`int x; int y`：直接用两个变量保存坐标信息，因为食物永远都是只有一个点出现。

`bool flag`：标记是否被吃掉，没有被吃掉就绘制出来，被吃掉了就重新生成一个食物。

> 定义方向

```c
enum Dirction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
```

使用枚举类型，分别为上、下、左、右，用来标记蛇移动的方向。

---

# 6、初始化

首先要将游戏窗口、蛇、食物的属性进行初始化。

```c
void gameInit(){
    // 先初始化一个游戏窗口
    initgraph(WIDE, HEIGHT);
    
    // 初始化蛇
	snake.size = 2;
	snake.r = 3;
	snake.speed = snake.r * 2;
	snake.score = 0;  // 初始得分
    // 初始化每节身体的坐标
	for (int i = 0; i < snake.size; i++) {
		snake.coordinate[i].x = (snake.size - i) * 2 * snake.r;
		snake.coordinate[i].y = HEIGHT / 2;  // 纵坐标为窗口的中间
	}
	snake.dirction = RIGHT;

	// 初始化食物
	foodInit();
    
    // 设置蛇和食物的颜色
	setfillcolor(RGB(255, 210, 81));
}
```

+ `initgraph(int wide, int height, int flag)`：这个函数用于初始化绘图窗口。<span id="initgraph1" ><a href="#initgraph2">详情</a></span>。

+ `snake.speed = snake.r * 2;`：因为半径和每次移动距离是有关系的，蛇的移动本质上就是圆形的移动，后一个圆形移动到前一个圆形的位置，而具体坐标上移动是以圆心的坐标来移动的。

  比如固定半径为5，每次移动为1，那么每次移动蛇的每一节身体的圆心会移动一个位置，但是圆形是有半径的，所以就会导致蛇的身体显示堆积在一起，因为它们圆心的距离只有1，但是半径有5。所以这里的半径应该与每次移动距离联系起来。

  因为每次移动是后一个圆的圆心移动到前一个圆的圆心，所以实际上是移动了两个半径的距离，所以可以把每次移动的距离设置为两个半径的大小。

+ `snake.coordinate[i].x = (snake.size - i) * 2 * snake.r;`：在初始化每节身体坐标时，因为我们是以`coord[0]`为蛇头的，所以`coord[0]`应该在最前面，也就是它的横坐标值最大，用`snake.size - i`控制越靠后的身体圆心横坐标越小。由半径和移动距离的关系可知，每节身体初始间距也应该有两个半径的距离，所以`(snake.size - i) * 2 * snake.r`表示每个圆心的横坐标。

+ `foodInit()`：初始化食物，这是一个自定义的函数，因为后续还会用到该函数，避免代码重复编写。

  ```c
  void foodInit() {
  	// 设置随机数种子
  	// srand(GetTickCount());  // GetTickCount()获取系统开机到现在所经过的毫秒数
  	srand((unsigned)time(NULL));  // 设置随机数种子
  	food.r = snake.r;
  	food.x = rand() % (WIDE - food.r) + food.r;
  	food.y = rand() % (HEIGHT - food.r) + food.r;
  	food.flag = true;
  }
  ```

  食物是随机生成的，所以它的横纵坐标就应该是用随机数生成，使用随机数时有个公式：`rand() % (A - a) + a`是生成范围为【a，A）的随机数。而食物也是一个圆形，它的位置也是由圆心坐标决定，而且还有半径，所以为了食物能够显示完全（不会被窗口边界遮挡），圆心的最小最大横纵坐标都应该离窗口边界有一个半径的距离。

  `rand()`和`srand()`函数都需要包含`stdlib.h`头文件，`time()`还需要包含`time.h`文件。

+ `setfillcolor(RGB(255, 210, 81));`：设置颜色。<span id="setfillcolor1"><a href="#setfillcolor2">详情</a></span>。

---

# 7、图形绘制

初始化完后，就可以将窗口、蛇、食物画出来了。

```c
void gameDraw() {
	// 双缓冲防止卡顿
	BeginBatchDraw();

	// 设置背景颜色
	setbkcolor(RGB(0, 108, 190));
	cleardevice();

	// 画蛇
	for (int i = 0; i < snake.size; i++) {
		solidcircle(snake.coordinate[i].x, snake.coordinate[i].y, snake.r);
	}
	// 画食物
	if (food.flag)
		solidcircle(food.x, food.y, food.r);

	// 画分数
	char tmp[20] = "";
	sprintf_s(tmp, "目标分数：%d", SCORE_MAXSIZE);
	outtextxy(0, 0, tmp);
	sprintf_s(tmp, "分数：%d", snake.score);
	outtextxy(0, 20, tmp);
	EndBatchDraw();
}
```

+ `BeginBatchDraw()`：相当于一次缓冲，可防止界面卡顿，先把所有图画好，得到指令（`EndBatchDraw()`）后在输出画好的图。<span id="BeginBatchDraw1"><a href="#BeginBatchDraw2">详情</a></span>。
+ `setbkcolor(RGB(0, 108, 190));`：设置背景颜色。<span id="setbkcolor1"><a href="#setbkcolor2">详情</a></span>。
+ `cleardevice()`：使用当前背景色清空绘图设备。<span id="cleardevice1"><a href="#cleardevice2">详情</a></span>。
+ `solidcircle(snake.coordinate[i].x, snake.coordinate[i].y, snake.r);`：画出蛇的每节身体和食物（圆）。<span id="solidcircle1"><a href="#solidcircle2">详情</a></span>。
+ `sprintf_s(tmp, "目标分数：%d", SCORE_MAXSIZE);`：格式化tmp字符串为“目标分数：100”。<span id="sprintf1"><a href="#sprintf2">详情</a></span>。
+ `outtextxy(0, 0, tmp);`：在(0, 0)的位置上输出tmp这个字符串。<span id="outtextxy1"><a href="#outtextxy2">详情</a></span>。
+ `EndBatchDraw();`：将画好的图输出。<span id="EndBatchDarw1"><a href="#EndBatchDarw2">详情</a></span>。

图形绘制好后，就可以在主函数中一直调用了。

---

# 8、蛇的移动

蛇的移动，本质上就是移动第一个圆心（蛇头），然后将第二个圆心移动到之前第一个圆心的位置，往后以此类推，完成移动操作。所以这个功能的实现主要点在每个圆心的坐标上，把圆心的坐标改了，然后再调用`gameDraw()`方法重新绘制就可以了。

移动时，需要判断当前的移动方向，然后对应的修改横纵坐标。

+ 往右：纵坐标不变，横坐标加上每次移动的距离；
+ 往左：纵坐标不变，横坐标减去每次移动的距离；
+ 向上：横坐标不变，纵坐标减去每次移动的距离；
+ 向下：横坐标不变，纵坐标加上每次移动的距离。

同时，要想实现可以穿墙操作的话，就还需要判断一次，当蛇头碰到边界时，就会从对面的边界出来，其实就是将对应的坐标变成最大或最小：

+ 碰到上边界(y == 0)，从下边界出来(y == HEIGHT)；
+ 碰到下边界，从上边界出来；
+ 碰到左边界(x == 0)，从右边界出来(x == WIDE)；
+ 碰到右边界，从左边界出来。

```c
void snakeMove() {
	// 改身体的每个圆心的坐标
	for (int i = snake.size - 1; i > 0; i--) {
		snake.coordinate[i] = snake.coordinate[i - 1];
	}
	// 改蛇头的坐标
	switch (snake.dirction) {
	case UP:
		snake.coordinate[0].y -= snake.speed;
		if (snake.coordinate[0].y + snake.r <= 0)
			snake.coordinate[0].y = HEIGHT;
		break;
	case DOWN:
		snake.coordinate[0].y += snake.speed;
		if (snake.coordinate[0].y + snake.r >= HEIGHT)
			snake.coordinate[0].y = 0;
		break;
	case LEFT:
		snake.coordinate[0].x -= snake.speed;
		if (snake.coordinate[0].x + snake.r <= 0)
			snake.coordinate[0].x = WIDE;
		break;
	case RIGHT:
        snake.coordinate[0].x += snake.speed;
		if (snake.coordinate[0].x + snake.r >= WIDE)
			snake.coordinate[0].x = 0;
		break;
	}
}
```

---

# 9、键盘控制

蛇可以移动后，还需要实现通过键盘来改变移动方向和空格键暂停。

这个时候就需要判断用户是否有按键的操作，如果没有就不改变游戏状态，如果有的话，再通过键值来判断用户想执行的上下左右还是暂停。规定用`w\a\s\d，↑\←\↓\→`来控制方向。↑、↓、←、→的键值分别为72、80、75、77。

同时在移动蛇的时候需要考虑实际性：蛇在向一个方向移动时，不能改变方向成相反的方向。也就是说，蛇在向下移动时，当按了向上键后，它不能改变方向，所以需要在改变方向时判断一下当前蛇的移动方向。

```c
void directionChange() {
	// 判断是否有按键操作
	if (_kbhit()) {  // 如果有按键操作，返回真
		switch (_getch()) {
			// 72,80,75,77，上下左右箭头的 键值
		case 'w':
		case 'W':
		case 72:
			if (snake.dirction != DOWN)
				snake.dirction = UP;
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dirction != UP)
				snake.dirction = DOWN;
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dirction != RIGHT)
				snake.dirction = LEFT;
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dirction != LEFT)
				snake.dirction = RIGHT;
			break;
		case ' ':  // 空格暂停
			while (1) {
				if (_getch() == ' ')  // 再按空格继续
					return;
			}
			// system("pause");  // 这个也是暂停，但是可以按任何键继续
		}
	}	
}
```

+ `kbhit()`：检测用户是否有按键操作。<a href="#kbhit2" id="kbhit1">详情</a>。 
+ `getch()`：拿到用户按下的键的键值。<a href="#getch2" id="getch1">详情</a>。 

暂停部分的逻辑是：按下空格后，会进入一个死循环，当前游戏界面就不会再刷新；当你再按下一次空格后，才会退出这个死循环，回到主函数继续游戏。

`kbhit()`和`getch()`在VS2022中会被要求写为`_getch()`和`_kbhit()`。

```apl
错误 C4996 'getch': The POSIX name for this item is deprecated. Instead, use the ISO C and C++ conformant name: _getch. See online help for details.
```

---

# 10、吃食物

是否吃到食物是以蛇头是否碰到食物来判断的。

如果用蛇头和食物的圆心坐标是否相等来判断是否吃到食物的话，会发现，因为蛇头和食物都是圆形而不是圆点，所以看起来蛇头碰到了食物但是并没有吃到食物，所以不应该用两个点的坐标来进行判断，而是使用一个范围值。

用蛇头圆心坐标，判断是否进入食物圆的范围内，来判断是否吃到食物。

吃到食物的话，要把蛇的长度加一，分数加10，并且将当前食物的flag属性改为false，标志已被吃过了。

```c
void eatFood() {
	if (food.flag &&
		snake.coordinate[0].x >= food.x - food.r && snake.coordinate[0].x <= food.x + food.r &&
		snake.coordinate[0].y >= food.y - food.r && snake.coordinate[0].y <= food.y + food.r) {
			snake.size++;
			snake.score += 10;
			food.flag = false;
	}
	if (!food.flag) {
		foodInit();
	}
}
```

---

# 11、主函数

在主函数里面，首先初始化游戏，然后使用一个死循环来一直刷新游戏界面，在循环里面调用上面写到的移动、变向、吃食函数，同时判断当前的分数是否已经到了目标分数，如果到了目标分数，就在窗口中间打印“恭喜通关”祝福语，然后暂停3秒后关闭游戏。

```c
int main() {
	gameInit();
	while (1) {
		snakeMove();
		directionChange();
		eatFood();
		if (snake.score >= SCORE_MAXSIZE) {
			char temp[10] = "";
			sprintf_s(temp, "恭喜过关!");
			outtextxy(WIDE / 2 - 5, HEIGHT / 2, temp);
			Sleep(3000);
			return 0;
		}
		gameDraw();
		Sleep(50);
	}
	return 0;
}
```

+ `Sleep(50);`：设置停留时间，太短了的话窗口刷新非常快，就是蛇移动的非常快，太慢了蛇移动就会非常慢。

---

# 12、完整代码

```c
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
// 以下是添加背景音乐需要的
// #include<mmsystem.h>
// #pragma comment(lib,"winmm.lib")

#define SNAKE_MAXSIZE 500  // 蛇的最大节数
#define HEIGHT 480  // 窗口的高度
#define WIDE 640  // 窗口的宽度
#define SCORE_MAXSIZE 100

// 蛇的结构体
struct Snake {
	int size;  // 节数
	int dirction;  // 方向
	int speed;  // 速度
	int score;  // 分数
	int r;
	POINT coordinate[SNAKE_MAXSIZE];  // 坐标
}snake;

// 食物的结构
struct Food {
	int x;  // 横坐标
	int y;  // 纵坐标
	int r;  // 半径
	bool flag;  // 标志
}food;

// 移动的方向
enum Dirction {
	UP,
	LEFT,
	RIGHT,
	DOWN
};

// 初始化食物
void foodInit() {
	// 设置随机数种子
	// srand(GetTickCount());  // GetTickCount()获取系统开机到现在所经过的毫秒数
	srand((unsigned)time(NULL));
	food.r = snake.r;
	food.x = rand() % (WIDE - 2 * food.r) + food.r;
	food.y = rand() % (HEIGHT - 2 * food.r) + food.r;
	// printf("%d %d\n", food.x, food.y);
	food.flag = true;
}

// 初始化
void gameInit() {
	// 播放背景音乐
	// 这里字符串报错的话，去项目-属性-高级-字符集里，改成多字节字符集
	// mciSendString("open ./res/snake/snake_bgm.mp3 alias BGM", 0, 0, 0);
	// mciSendString("play BGM repeat", 0, 0, 0);

	// 初始化图形窗口
	initgraph(WIDE, HEIGHT/*, SHOWCONSOLE*/);

	// 初始化蛇
	snake.size = 12;
	snake.r = 5;
	snake.speed = snake.r * 2;
	snake.score = 0;
	for (int i = 0; i < snake.size; i++) {
		snake.coordinate[i].x = (snake.size - i) * 2 * snake.r;
		snake.coordinate[i].y = HEIGHT / 2;
		// printf("% d % d\n", snake.coordinate[i].x, snake.coordinate[i].y);
	}
	snake.dirction = RIGHT;

	// 初始化食物
	foodInit();

	// 设置蛇和食物的颜色
	setfillcolor(RGB(255, 210, 81));
}

// 图形绘制
void gameDraw() {
	// 双缓冲防止卡顿
	BeginBatchDraw();

	// 设置背景颜色
	setbkcolor(RGB(0, 108, 190));
	cleardevice();

	// 画蛇
	for (int i = 0; i < snake.size; i++) {
		solidcircle(snake.coordinate[i].x, snake.coordinate[i].y, snake.r);
	}
	// 画食物
	if (food.flag)
		solidcircle(food.x, food.y, food.r);

	// 画分数
	char tmp[20] = "";
	sprintf_s(tmp, "目标分数：%d", SCORE_MAXSIZE);
	outtextxy(0, 0, tmp);
	sprintf_s(tmp, "分数：%d", snake.score);
	outtextxy(0, 20, tmp);
	EndBatchDraw();
}

// 移动蛇
void snakeMove() {
	// 身子跟着头移动
	for (int i = snake.size - 1; i > 0; i--) {
		snake.coordinate[i] = snake.coordinate[i - 1];
	}
	// 头移动
	switch (snake.dirction) {
	case UP:
		snake.coordinate[0].y -= snake.speed;
		if (snake.coordinate[0].y + snake.r <= 0)
			snake.coordinate[0].y = HEIGHT;
		break;
	case DOWN:
		snake.coordinate[0].y += snake.speed;
		if (snake.coordinate[0].y + snake.r >= HEIGHT)
			snake.coordinate[0].y = 0;
		break;
	case LEFT:
		snake.coordinate[0].x -= snake.speed;
		if (snake.coordinate[0].x + snake.r <= 0)
			snake.coordinate[0].x = WIDE;
		break;
	case RIGHT:
		snake.coordinate[0].x += snake.speed;
		if (snake.coordinate[0].x + snake.r >= WIDE)
			snake.coordinate[0].x = 0;
		break;
	}
}

// 通过按键改变移动方向
void directionChange() {
	// 判断是否有按键操作
	if (_kbhit()) {  // 如果有按键操作，返回真
		switch (_getch()) {
			// 72,80,75,77，上下左右箭头的 键值
		case 'w':
		case 'W':
		case 72:
			if (snake.dirction != DOWN)
				snake.dirction = UP;
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dirction != UP)
				snake.dirction = DOWN;
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dirction != RIGHT)
				snake.dirction = LEFT;
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dirction != LEFT)
				snake.dirction = RIGHT;
			break;
		case ' ':
			while (1) {
				if (_getch() == ' ')
					return;
			}
			// system("pause");
		}
	}	
}

// 吃食物
void eatFood() {
	if (food.flag &&
		snake.coordinate[0].x >= food.x - food.r &&
		snake.coordinate[0].x <= food.x + food.r &&
		snake.coordinate[0].y >= food.y - food.r &&
		snake.coordinate[0].y <= food.y + food.r) {
			snake.size++;
			snake.score += 10;
			food.flag = false;
	}
	if (!food.flag) {
		foodInit();
	}
}

int main() {
	gameInit();
	while (1) {
		snakeMove();
		directionChange();
		eatFood();
		if (snake.score >= SCORE_MAXSIZE) {
			char temp[10] = "";
			sprintf_s(temp, "恭喜过关!");
			outtextxy(WIDE / 2 - 5, HEIGHT / 2, temp);
			Sleep(3000);
			return 0;
		}
		gameDraw();
		Sleep(50);
	}
	return 0;
}
```



---

# 扩展

<span id="point2">POINT</span>：

在`windf.h`文件中，POINT是如下定义：

```c
typedef struct tagPOINT
{
    LONG  x;  
    LONG  y;
} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;
```

`long x`：指定点x的坐标；

`long y`：指定点y的坐标。

[点击返回](#point1)

---

<span id="initgraph2">`initgraph(int wide, int height, int flag)`</span>这个函数用于初始化绘图窗口。

源代码：

```cpp
HWND initgraph(
	int width,
	int height,
	int flag = NULL
);
```

+ `width`：绘图窗口的宽度。

+ `height`：绘图窗口的高度。

+ `flag`：绘图窗口的样式，默认为 NULL。可为以下值：

+ | 值             | 含义                           |
  | -------------- | ------------------------------ |
  | EX_DBLCLKS     | 在绘图窗口中支持鼠标双击事件。 |
  | EX_NOCLOSE     | 禁用绘图窗口的关闭按钮。       |
  | EX_NOMINIMIZE  | 禁用绘图窗口的最小化按钮。     |
  | EX_SHOWCONSOLE | 显示控制台窗口。               |

[点击返回](#initgraph1)

---

<span id="setfillcolor2">`void setfillcolor(COLORREF color);`</span>：这个函数用于设置当前设备绘图背景色。

+ `color`：指定要设置的背景颜色。

在设置背景色之后，并不会改变现有背景色，而是只改变背景色的值，之后再执行绘图语句，例如 `outtextxy`，会使用新设置的背景色值。如果需要修改全部背景色，可以在设置背景色后执行 `cleardevice() `函数。

`RGB`：RGB 宏用于将红、绿、蓝颜色分量合成颜色。RGB 宏在 Windows SDK 中定义。

```c
COLORREF RGB(
	BYTE byRed,		// 颜色的红色部分
	BYTE byGreen,	// 颜色的绿色部分
	BYTE byBlue		// 颜色的蓝色部分
);
```

+ `byRed`：颜色的红色部分，取值范围：0~255。
+ `byGreen`：颜色的绿色部分，取值范围：0~255。
+ `byBlue`：颜色的蓝色部分，取值范围：0~255。

+ 返回值：返回合成的颜色。

[点击返回](#setfillcolor1)

---

<span id="BeginBatchDraw2">`void BeginBatchDraw();`</span>：这个函数用于开始批量绘图。执行后，任何绘图操作都将暂时不输出到绘图窗口上，直到执行 `FlushBatchDraw `或 `EndBatchDraw `才将之前的绘图输出。

[点击返回](#BeginBatchDraw1)

---

<span id="setbkcolor2">`void setbkcolor(COLORREF color);`</span>：这个函数用于设置当前设备绘图背景色。

+ `color`：指定要设置的背景颜色。

在设置背景色之后，并不会改变现有背景色，而是只改变背景色的值，之后再执行绘图语句，例如 `outtextxy`，会使用新设置的背景色值。如果需要修改全部背景色，可以在设置背景色后执行 `cleardevice() `函数。

[点击返回](#setbkcolor1)

---

<span id="cleardevice2">`void cleardevice();`</span>：这个函数使用当前背景色清空绘图设备。

[点击返回](#cleardevice1)

---

<span id="solidcircle2">`void solidcircle(int x, int y, int radius);`</span>：这个函数用于画无边框的填充圆。

+ `x`：圆心 x 坐标。
+ `y`：圆心 y 坐标。
+ `radius`：圆的半径。

该函数使用当前填充样式绘制无外框的填充圆。

[点击返回](#solidcircle1)

----

<span id="sprintf2">`int sprintf(char *str, const char *format, ...)`</span>：发送格式化输出到 `str` 所指向的字符串。

+ `str`：这是指向一个字符数组的指针，该数组存储了 C 字符串。
+ `format`：这是字符串，包含了要被写入到字符串 `str` 的文本。它可以包含嵌入的 `format `标签，`format `标签可被随后的附加参数中指定的值替换，并按需求进行格式化。

该函数详情可见[sprintf](https://www.runoob.com/cprogramming/c-function-sprintf.html)。在vs2022中，`sprintf`会被判定为不安全，建议使用`sprintf_s`。

[点击返回](#sprintf1)

---

<span id="outtextxy2">`void outtextxy(int x, int y, LPCTSTR str);`</span>：这个函数用于在指定位置输出字符串。

+ `x`：字符串输出时头字母的 x 轴的坐标值。
+ `y`：字符串输出时头字母的 y 轴的坐标值。
+ `str`：待输出的字符串的指针。

该函数不会改变当前位置。

字符串常见的编码有两种：MBCS 和 Unicode。VC6 新建的项目默认为 MBCS 编码，VC2008 及高版本的 VC 默认为 Unicode  编码。LPCTSTR 可以同时适应两种编码。为了适应两种编码，请使用 TCHAR 字符串及相关函数。

默认情况下，输出字符串的背景会用当前背景色填充。使用函数 `setbkmode `可以设置文字的背景部分保持透明或使用背景色填充。

[点击返回](#outtextxy1)

---

<span id="EndBatchDarw2">`void EndBatchDraw();`</span>：这个函数用于结束批量绘制，并执行未完成的绘制任务。

[点击返回](#EndBatchDarw1)

---

<span id="kbhit2">`int kbhit(void);`</span>： 检查当前是否有键盘输入，若有则返回一个非0值，否则返回0。

包含头文件： `include <conio.h>`。

[点击返回](#kbhit1)

---

<span id="getch2">`int getch(void)`</span>：从stdio流中读字符，即从控制台读取一个字符，但不显示在屏幕上。返回读取的字符。

这个函数是一个不回显函数，当用户按下某个字符时，函数自动读取，无需按回车，这个函数并非标准函数，要注意移植性！

Windows下`getch()`在`conio.h`的头文件中，要使用`getch()`函数需要引用`conio`头文件。

[点击返回](#getch1)

