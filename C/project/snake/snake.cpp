#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
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
		Sleep(10);
	}
	return 0;
}