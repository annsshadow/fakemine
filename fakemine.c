/*************************************************************************
	> File Name: fakemine.c
	> Author: shadowwen-annsshadow
	> Mail: cravenboy@163.com
	> Created Time: Thu 11 Aug 2016 09:32:39 AM HKT
 ************************************************************************/

/*********************************
*   c语言命令行+方向键简易版扫雷
*   运行环境：Windows7-64bit
*   编译环境：Codeblocks-16.01
*********************************/

#include "fakemine.h"
#include "fakesetting.h"
#include "fakegame.h"

int main()
{
    setColor(10);
    system("cls");
    welcomeToMyGame();
    gameInitailize();
    countMines();
    printMap();

    for(;;)
    {
        setCurPos(cursorPos[index_y][index_x].y, cursorPos[index_y][index_x].x);
        keyBoardInput();
    }

    return EXIT_SUCCESS;
}
