/*************************************************************************
	> File Name: fakemine.c
	> Author: shadowwen-annsshadow
	> Mail: cravenboy@163.com
	> Created Time: Thu 11 Aug 2016 09:32:39 AM HKT
 ************************************************************************/

/*********************************
*   Fakemine by C on Windows
*   Execute Environment：Windows7-64bit
*   Complier：Codeblocks-16.01
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
