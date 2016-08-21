/*************************************************************************
	> File Name: fakemine.h
	> Author: shadowwen-annsshadow
	> Mail: cravenboy@163.com
	> Created Time: Thu 11 Aug 2016 09:33:52 AM HKT
 ************************************************************************/

//�õ��Ķ�����ȥ��
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

//��������ж�״̬��ASCII��
//MINE�Ƕ��巭�������еġ�*����
#define MINE            42
#define ESC             27
#define ENTER           13
#define SPACE           32
#define UP              72
#define DOWN            80
#define LEFT            75
#define RIGHT           77

//��������״̬����������ж�
#define bool int
#define true 1
#define false 0
#define ROW             10
#define COLUMN          10
#define ALL_MINES     15

//��ǰλ�õĽṹ��
typedef struct currentPosition_struct
{
    int x;
    int y;
} currentPosition;

//ÿһ��С��Ľṹ��
typedef struct blockCondition_struct
{
    //�Ƿ񱻸�����
    bool beCovered;
    //����Ϊ������Χ������
    int minesNum;
} blockCondition;

//����λ������
currentPosition cursorPos[ROW][COLUMN];
//������ͼ������
blockCondition minesMap[ROW][COLUMN];
//ʣ�µĸ�����
int leftBlocksNum = ROW * COLUMN;
//����ڹ��λ�á�������ͼ�е��±�
int index_x = 0, index_y = 0;

//���ô���ǰ�󱳾�ɫ
/**
 * [setColor description]
 * @param color [description]
 */
void setColor(unsigned short color);
//��ͷ�Ļ�ӭ��������
/**
 * [welcomeToMyGame description]
 */
void welcomeToMyGame();


/**
 * [gameInitailize set the maps + mine + cursor]
 */
void gameInitailize();

/**
 * [countMines count how many mines among every position ]
 */
void countMines();

/**
 * [keyBoardInput get the keyboard and judge]
 */
void keyBoardInput();

/**
 * [setCurPos set the current cursor for playing window]
 * @param y [coordinate Y]
 * @param x [coordinate X]
 */
void setCurPos(int y, int x);

/**
 * [moveCursor move and record the cursor position]
 * @param y [coordinate Y]
 * @param x [coordinate X]
 */
void moveCursor(int y, int x);

/**
 * [checkResult check the result for every step]
 * @param  y [coordinate Y]
 * @param  x [coordinate X]
 * @return   [true:gameover, false:keep going]
 */
bool checkResult(int y, int x);

/**
 * [printMap print the gudie and the map]
 */
void printMap();
//��Ϸ�˳���ġ�������
/**
 * [gameOver description]
 * @param str [description]
 */
void gameOver(char *str);

/**
 * [delLine delete the buffer line for playing window]
 * @param y [coordinate Y]
 */
void delLine(int y);
