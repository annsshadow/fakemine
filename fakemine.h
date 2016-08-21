/*************************************************************************
	> File Name: fakemine.h
	> Author: shadowwen-annsshadow
	> Mail: cravenboy@163.com
	> Created Time: Thu 11 Aug 2016 09:33:52 AM HKT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

//define the ASCII for each action or something
//MINE : is ‘*’
#define MINE            42
#define ESC             27
#define ENTER           13
#define SPACE           32
#define UP              72
#define DOWN            80
#define LEFT            75
#define RIGHT           77

//define the condition
#define bool int
#define true 1
#define false 0

//define the map size and the number of all mines
#define ROW             10
#define COLUMN          10
#define ALL_MINES     10

//the current position of cursor
typedef struct currentPosition_struct
{
    int x;
    int y;
} currentPosition;

//for each block
typedef struct blockCondition_struct
{
    //whether is it cover or has been open
    bool beCovered;
    //how many mines among itself
    int minesNum;
} blockCondition;

//the array for each position of cursor
currentPosition cursorPos[ROW][COLUMN];

//the array for how mines distribute on map
blockCondition minesMap[ROW][COLUMN];

//how many block have left
int leftBlocksNum = ROW * COLUMN;

//the coordinate of cursor on cursorPosition and minesMap
int index_x = 0, index_y = 0;

/**
 * [setColor set the console window color]
 * @param color [first digital is for foreground color,second digital is background color]
 */
void setColor(unsigned short color);

/**
 * [welcomeToMyGame the fake "flash" welcome]
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

/**
 * [gameOver print the string one by one and exit]
 * @param str [point to string]
 */
void gameOver(char *str);

/**
 * [deleteLine delete the buffer line for playing window]
 * @param y [coordinate Y]
 */
void deleteLine(int y);
