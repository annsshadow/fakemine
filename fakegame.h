/*************************************************************************
	> File Name: fakegame.h
	> Author: shadowwen-annsshadow
	> Mail: cravenboy@163.com
	> Created Time: Thu 11 Aug 2016 09:34:16 AM HKT
 ************************************************************************/

/**
* [gameInitailize set the maps + mine + cursor]
*/
void gameInitailize()
{
    int row_index = 0, column_index = 0;
    int allMines = ALL_MINES;
    //set the random seed
    srand((unsigned int)time(NULL));

    //initial the mine map
    for(row_index = 0; row_index < ROW; ++row_index)
    {
        for(column_index = 0; column_index < COLUMN; ++column_index)
        {
            minesMap[row_index][column_index].beCovered = true;
            minesMap[row_index][column_index].minesNum = 0;
        }
    }

    //set the mine randomly
    while(allMines)
    {
        row_index = rand() % ROW;
        column_index = rand() % COLUMN;

        if(minesMap[row_index][column_index].minesNum == 0)
        {
            //set '-1' means there is a mine under this location
            minesMap[row_index][column_index].minesNum = -1;
            --allMines;
        }
    }

    //set the cursor randomly
    for(row_index = 0; row_index < ROW; ++row_index)
    {
        for(column_index = 0; column_index < COLUMN; ++column_index)
        {
            cursorPos[row_index][column_index].x = column_index * 6 + 3;
            cursorPos[row_index][column_index].y = row_index * 2 + 1;
        }
    }
}

/**
 * [countMines count how many mines among every position ]
 */
void countMines()
{
    int row_index = 0, column_index = 0, row_increment = 0, column_increment = 0;
    //the number of mine near the current position
    int minesNum = 0;

    //count every position of map
    for(row_index = 0; row_index < ROW; ++row_index)
    {
        for(column_index = 0; column_index < COLUMN; ++column_index)
        {
            //if this position is mine, ignore
            if(minesMap[row_index][column_index].minesNum == -1)
                continue;
            //reset the mine number every turn
            minesNum = 0;
            //# # #
            //# p #
            //# # #
            for(row_increment = -1; row_increment <= 1; ++row_increment)
            {
                //pretend row overflow
                if(row_index + row_increment < 0 || row_index + row_increment >= ROW)
                {
                    continue;
                }

                for(column_increment = -1; column_increment <= 1; ++column_increment)
                {
                    //pretend column overflow
                    if(column_index + column_increment < 0 || column_index + column_increment >= COLUMN)
                    {
                        continue;
                    }
                    //count the mine number
                    if(minesMap[row_index + row_increment][column_index + column_increment].minesNum == -1)
                    {
                        ++minesNum;
                    }
                }
            }
            minesMap[row_index][column_index].minesNum = minesNum;
        }
    }
}

/**
 * [keyBoardInput get the keyboard and judge]
 * there are two bytes for each direction
 * first byte:ASCII 0x00e0 224
 * second byte:
 * up:0x0048 72
 * down:0x0050 80
 * left:0x012b 75
 * right:0x012d 77
 */
void keyBoardInput()
{
    bool lose;
    //get the first byte for each direction
    int key1 = getch();

    if(key1 == 224)
    {
        //get the second byte for each direction
        int key2 = getch();

        switch(key2)
        {
        case UP:
            moveCursor(index_y - 1, index_x);
            break;

        case DOWN:
            moveCursor(index_y + 1, index_x);
            break;

        case LEFT:
            moveCursor(index_y, index_x - 1);
            break;

        case RIGHT:
            moveCursor(index_y, index_x + 1);
            break;

        default:
            break;
        }
    }
    //for other control key info
    else
    {
        switch(key1)
        {
        case ENTER:
        case SPACE:
            lose = checkResult(index_y, index_x);
            system("cls");
            printMap();

            if(lose)
            {
                setColor(13);
                printf("|             Unfortunately almost you can win              |\n");
                printf("|        Press \"r\" to play again or \"Esc\" to quit           |\n");
                printf("[%c]-------------------------------------------------------[%c]\n", MINE, MINE);
                setColor(10);
                Sleep(1000);
                char key3 = getch();

                if(key3 == 'r' || key3 == 'R')
                {
                    //reset the game just like the "main"
                    setColor(10);
                    gameInitailize();
                    countMines();
                    printMap();
                }
            }
            //if the left blocks number is more than the left mines, go on
            else if(leftBlocksNum > ALL_MINES)
            {
                setColor(13);
                printf("|                      Good job~Keep going                  |\n");
                printf("[%c]-------------------------------------------------------[%c]\n", MINE, MINE);
                setColor(10);
            }
            //now you win
            else
            {
                setColor(13);
                printf("|                   Congratulations! You win!               |\n");
                printf("|       Press \"r\" to play again or \"Esc\" to quit            |\n");
                printf("[%c]-------------------------------------------------------[%c]\n", MINE, MINE);
                setColor(10);
                Sleep(1000);
                char key3 = getch();

                if(key3 == 'r' || key3 == 'R')
                {
                    setColor(10);
                    gameInitailize();
                    countMines();
                    printMap();
                }
            }

            break;

        case ESC:
            system("cls");
            gameOver("\t\t\tIs it funny? Whatever, thank you for your playing\n\n\n\n\n\n\n\n");

        default:
            break;
        }
    }
}

/**
 * [setCurPos set the current cursor for playing window]
 * @param y [coordinate Y]
 * @param x [coordinate X]
 */
void setCurPos(int y, int x)
{
    //set current position for playing window
    COORD currentPosition;
    currentPosition.Y = y;
    currentPosition.X = x;
    //so the cursor is {y,x} now
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
}

/**
 * [moveCursor move and record the cursor position]
 * @param y [coordinate Y]
 * @param x [coordinate X]
 */
void moveCursor(int y, int x)
{
    //pretend overflow
    if((x >= 0 && x < COLUMN) && (y >= 0 && y < ROW))
    {
        setCurPos(cursorPos[y][x].y, cursorPos[y][x].x);
        index_x = x;
        index_y = y;
    }
}

/**
 * [checkResult check the result for every step]
 * @param  y [coordinate Y]
 * @param  x [coordinate X]
 * @return   [true:gameover, false:keep going]
 */
bool checkResult(int y, int x)
{
    int row_increment = 0, column_increment = 0;

    //pretend overflow
    if(x < 0 || x >= COLUMN || y < 0 || y >= ROW)
    {
        return false;
    }

    //make this block be open
    minesMap[y][x].beCovered = false;

    //if there is a mine under this block
    if(minesMap[y][x].minesNum == -1)
    {
        minesMap[y][x].minesNum = 9;
        return true;
    }

    //if there is no mine under this block,just keep going
    if(minesMap[y][x].minesNum > 0 && minesMap[y][x].minesNum < 9)
    {
        return false;
    }

    //# # #
    //# p #
    //# # #
    for(row_increment = -1; row_increment <= 1; ++row_increment)
    {
        //pretend row overflow
        if(y + row_increment < 0 || y + row_increment >= ROW)
        {
            continue;
        }

        for(column_increment = -1; column_increment <= 1; ++column_increment)
        {
            //pretend column overflow
            if(x + column_increment < 0 || x + column_increment >= COLUMN)
            {
                continue;
            }
            //if the block haven't check, do it
            if(minesMap[y + row_increment][x + column_increment].beCovered)
            {
                minesMap[y + row_increment][x + column_increment].beCovered = false;
                checkResult(y + row_increment, x + column_increment);
            }
        }
    }

    return false;
}

/**
 * [printMap print the gudie and the map]
 */
void printMap()
{
    system("cls");
    char help0[] = "Direction Key: left,up,down,right";
    char help1[] = "Move";
    char help2[] = "Space / Enter";
    char help3[] = "Click";
    char help4[] = "Esc : to quit";
    //the map should not be too big, because need to print the guide
    //10 * 10 is ok
    setColor(14);
    setCurPos(4, 62);
    printf("%s", help0);
    setCurPos(6, 62);
    printf("%s", help1);
    setCurPos(9, 62);
    printf("%s", help2);
    setCurPos(11, 62);
    printf("%s", help3);
    setCurPos(14, 62);
    printf("%s", help4);
    setCurPos(0, 0);
    setColor(10);

    int i = 0, j = 0, k = 0;
    leftBlocksNum = 0;
    setColor(11);
    printf("[f]---");
    setColor(10);

    for(k = 1; k < COLUMN - 1; ++k)
    {
        printf("+-----");
    }
    setColor(11);
    printf("+---[a]\n");
    setColor(10);

    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            if(minesMap[i][j].beCovered)
            {
                ++leftBlocksNum;
                //this is how the block should be look like when it is covered
                //1-4 is every corner for a square
                //5 is double vertical line
                //6 is double horizontal line
                printf("|  %c  ", 3);
            }
            else if(minesMap[i][j].minesNum == -1 || minesMap[i][j].minesNum == 9)
            {
                printf("|  %c  ", MINE);
            }
            else if(minesMap[i][j].minesNum == 0)
            {
                printf("|  %c  ", ' ');
            }
            else
            {
                printf("|  %d  ", minesMap[i][j].minesNum);
            }
        }

        printf("|\n");

        if(i < ROW - 1)
        {
            for(k = 0; k < COLUMN; ++k)
            {
                printf("+-----");
            }

            printf("+\n");
        }
    }
    setColor(11);
    printf("[k]---");
    setColor(10);

    for(k = 1; k < COLUMN - 1; ++k)
    {
        printf("+-----");
    }
    setColor(11);
    printf("+---[e]\n");
    setColor(10);
}

/**
 * [deleteLine delete the buffer line for playing window]
 * @param y [coordinate Y]
 */
void deleteLine(int y)
{
    HANDLE handle_output;

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    DWORD length, nw;
    //TCHAR couldn't use on MSDN, so use char
    char fillchar = ' ';
    //set the start position of cursor where want to delete
    COORD startPosition = {0, y};
    //get the output handle
    handle_output = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(handle_output, &csbi);
    //the position of window buffer, which is X
    length = csbi.dwSize.X;
    //use character to fill with window buffer by some times from specific position
    //success : not zero, actually it will success so just do it without judge
    FillConsoleOutputCharacter(handle_output, fillchar, length, startPosition, &nw);
}
