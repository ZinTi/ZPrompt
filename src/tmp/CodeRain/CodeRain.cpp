﻿#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <graphics.h>

#define WIDTH 960
#define HEIGHT 640
#define STR_SIZE 20
#define STR_NUM 128
#define STR_WIDTH 15


typedef struct Rain
{
	int x;
	int y;
	int speed;
	TCHAR str[STR_SIZE];
}Rain;
Rain rain[STR_NUM];

// 随机生成一个字符
char CreateCh()
{
	char ch = 0;
	int flag = rand() % 3; // 0~2
	if (flag == 0)
		ch = rand() % 26 + 'a'; // 产生小写字母a~z
	else if (flag == 1)
		ch = rand() % 26 + 'A'; // 产生大写字母A~Z
	else
		ch = rand() % 10 + '0'; // 产生数字0~9

	return ch;
}
// 初始化结构体成员
void InitRain()
{
	// 初始化字符的位置和速度
	for (int i = 0; i < STR_NUM; ++i)
	{
		rain[i].x = i * STR_WIDTH;
		rain[i].y = rand() % HEIGHT;
		rain[i].speed = rand() % 5 + 5;
	}
	// 获取随机字符填充进数组
	for (int i = 0; i < STR_NUM; i++)
	{
		for (int j = 0; j < STR_SIZE; j++)
		{
			rain[i].str[j] = CreateCh();
		}
	}
}
// 输出到窗口中
void DrawRain()
{
	cleardevice();
	for (int i = 0; i < STR_NUM; i++)
	{
		for (int j = 0; j < STR_SIZE; j++)
		{
			outtextxy(rain[i].x, rain[i].y - STR_WIDTH * j, rain[i].str[j]);
			settextcolor(RGB(0, 255 - j * 13, 0));
		}
	}
}
// 移动字符
void MoveRain()
{
	for (int i = 0; i < STR_NUM; i++)
	{
		rain[i].y += rain[i].speed;
		if (rain[i].y - STR_WIDTH * STR_SIZE > HEIGHT)
		{
			rain[i].y = 0;
		}
	}
}
// 随机改变字符
void ChangeCh()
{
	for (int i = 0; i < STR_NUM; i++)
	{
		rain[rand() % STR_NUM].str[rand() % STR_SIZE] = CreateCh();
	}
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	srand((unsigned int)time(NULL)); // 初始化随机数种子
	initgraph(WIDTH, HEIGHT);
	InitRain();
	DWORD t1, t2;
	t1 = GetTickCount64();
	t2 = t1;
	while (1)
	{
		BeginBatchDraw(); // 双缓冲机制
		DrawRain();
		ChangeCh();
		if (t2 - t1 > 20)
		{
			MoveRain();
			t1 = t2;
		}
		t2 = GetTickCount64();
		EndBatchDraw();
	}
	getchar();
	closegraph();
	return 0;
}