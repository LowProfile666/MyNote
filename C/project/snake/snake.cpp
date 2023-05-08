#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
// #include<mmsystem.h>
// #pragma comment(lib,"winmm.lib")

#define SNAKE_MAXSIZE 500  // �ߵ�������
#define HEIGHT 480  // ���ڵĸ߶�
#define WIDE 640  // ���ڵĿ��
#define SCORE_MAXSIZE 100

// �ߵĽṹ��
struct Snake {
	int size;  // ����
	int dirction;  // ����
	int speed;  // �ٶ�
	int score;  // ����
	int r;
	POINT coordinate[SNAKE_MAXSIZE];  // ����
}snake;

// ʳ��Ľṹ
struct Food {
	int x;  // ������
	int y;  // ������
	int r;  // �뾶
	bool flag;  // ��־
}food;


// �ƶ��ķ���
enum Dirction {
	UP,
	LEFT,
	RIGHT,
	DOWN
};
// ��ʼ��ʳ��
void foodInit() {
	// �������������
	// srand(GetTickCount());  // GetTickCount()��ȡϵͳ�����������������ĺ�����
	srand((unsigned)time(NULL));
	food.r = snake.r;
	food.x = rand() % (WIDE - 2 * food.r) + food.r;
	food.y = rand() % (HEIGHT - 2 * food.r) + food.r;
	// printf("%d %d\n", food.x, food.y);
	food.flag = true;
}
// ��ʼ��
void gameInit() {
	// ���ű�������
	// �����ַ�������Ļ���ȥ��Ŀ-����-�߼�-�ַ�����ĳɶ��ֽ��ַ���
	// mciSendString("open ./res/snake/snake_bgm.mp3 alias BGM", 0, 0, 0);
	// mciSendString("play BGM repeat", 0, 0, 0);

	// ��ʼ��ͼ�δ���
	initgraph(WIDE, HEIGHT/*, SHOWCONSOLE*/);

	

	// ��ʼ����
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

	// ��ʼ��ʳ��
	foodInit();

	// �����ߺ�ʳ�����ɫ
	setfillcolor(RGB(255, 210, 81));
}


// ͼ�λ���
void gameDraw() {
	// ˫�����ֹ����
	BeginBatchDraw();

	// ���ñ�����ɫ
	setbkcolor(RGB(0, 108, 190));
	cleardevice();

	// ����
	for (int i = 0; i < snake.size; i++) {
		solidcircle(snake.coordinate[i].x, snake.coordinate[i].y, snake.r);
	}
	// ��ʳ��
	if (food.flag)
		solidcircle(food.x, food.y, food.r);

	// ������
	char tmp[20] = "";
	sprintf_s(tmp, "Ŀ�������%d", SCORE_MAXSIZE);
	outtextxy(0, 0, tmp);
	sprintf_s(tmp, "������%d", snake.score);
	outtextxy(0, 20, tmp);
	EndBatchDraw();
}

// �ƶ���
void snakeMove() {
	// ���Ӹ���ͷ�ƶ�
	for (int i = snake.size - 1; i > 0; i--) {
		snake.coordinate[i] = snake.coordinate[i - 1];
	}
	// ͷ�ƶ�
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

// ͨ�������ı��ƶ�����
void directionChange() {
	// �ж��Ƿ��а�������
	if (_kbhit()) {  // ����а���������������
		switch (_getch()) {
			// 72,80,75,77���������Ҽ�ͷ�� ��ֵ
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

// ��ʳ��
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
			sprintf_s(temp, "��ϲ����!");
			outtextxy(WIDE / 2 - 5, HEIGHT / 2, temp);
			Sleep(3000);
			return 0;
		}
		gameDraw();
		Sleep(10);
	}
	return 0;
}