/*************************************************************************
	> File Name: fakemine.h
	> Author: shadowwen-annsshadow
	> Mail: cravenboy@163.com
	> Created Time: Thu 11 Aug 2016 09:33:52 AM HKT
 ************************************************************************/

//用到的都导进去吧
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

//定义各种判断状态的ASCII码
//MINE是定义翻开格子中的‘*’号
#define MINE            42
#define ESC             27
#define ENTER           13
#define SPACE           32
#define UP              72
#define DOWN            80
#define LEFT            75
#define RIGHT           77

//定义类型状态，方便后续判断
#define bool int
#define true 1
#define false 0
#define ROW             10
#define COLUMN          10
#define ALL_MINES     15

//当前位置的结构体
typedef struct currentPosition_struct
{
    int x;
    int y;
} currentPosition;

//每一个小格的结构体
typedef struct blockCondition_struct
{
    //是否被覆盖了
    bool beCovered;
    //以它为中心周围的雷数
    int minesNum;
} blockCondition;

//光标的位置数组
currentPosition cursorPos[ROW][COLUMN];
//雷区地图的数组
blockCondition minesMap[ROW][COLUMN];
//剩下的格子数
int leftBlocksNum = ROW * COLUMN;
//光标在光标位置、雷区地图中的下标
int index_x = 0, index_y = 0;

//设置窗口前后背景色
void setColor(unsigned short color);
//开头的欢迎“动画”
void welcomeToMyGame();
//游戏地图初始化
void gameInitailize();
//以某格子为中心计算惊天雷数量
void countMines();
//获取键盘的输入
void keyBoardInput();
//指定光标的位置
void setCurPos(int y, int x);
//移动光标的位置
void moveCursor(int y, int x);
//检测每一步的结果
bool checkResult(int y, int x);
//输出游戏界面
void printMap();
//游戏退出后的“动画”
void gameOver(char *str);
//删除窗口中一行的缓冲
void delLine(int y);
