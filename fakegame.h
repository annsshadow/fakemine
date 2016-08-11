/*************************************************************************
	> File Name: fakegame.h
	> Author: shadowwen-annsshadow
	> Mail: cravenboy@163.com
	> Created Time: Thu 11 Aug 2016 09:34:16 AM HKT
 ************************************************************************/

void gameInitailize()
{
    int i = 0, j = 0;
    int allMines = ALL_MINES;
    //设置随机值
    srand((unsigned int)time(NULL));

    //雷区地图初始化
    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            minesMap[i][j].beCovered = true;
            minesMap[i][j].minesNum = 0;
        }
    }

    //放置惊天雷！
    while(allMines)
    {
        i = rand() % ROW;
        j = rand() % COLUMN;

        if(minesMap[i][j].minesNum == 0)
        {
            //这个‘-1’就作为判断惊天雷的依据了
            minesMap[i][j].minesNum = -1;
            --allMines;
        }
    }

    //光标位置初始化
    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            cursorPos[i][j].x = j * 6 + 3;
            cursorPos[i][j].y = i * 2 + 1;
        }
    }
}

void countMines()
{
    int i = 0, j = 0, m = 0, n = 0;
    //以格子为中心周围的雷数
    int minesNum = 0;

    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            //遇到惊天雷就放弃统计吧
            if(minesMap[i][j].minesNum == -1)
                continue;
            minesNum = 0;
            //九宫格嘛，那3次好了
            for(m = -1; m <= 1; ++m)
            {
                //行溢出了没，不能算没有的哦
                if(i + m < 0 || i + m >= ROW)
                {
                    continue;
                }

                for(n = -1; n <= 1; ++n)
                {
                    //这次就是看列溢出了没
                    if(j + n < 0 || j + n >= COLUMN)
                    {
                        continue;
                    }
                    //周边有惊天雷赶紧加起来
                    if(minesMap[i + m][j + n].minesNum == -1)
                    {
                        ++minesNum;
                    }
                }
            }
            minesMap[i][j].minesNum = minesNum;
        }
    }
}

void keyBoardInput()
{
    bool lose;
    int key1 = getch();

    /*****************************
    测试之后才知道方向键两个字节
    第一个字节ASCII 0x00e0 224
    第二个字节分别是：
    上：0x0048 72
    下：0x0050 80
    左：0x012b 75
    右：0x012d 77
    *****************************/

    if(key1 == 224)
    {
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
                printf("|              诶哟,还差一点点哦！ ╥﹏╥                   |\n");
                printf("|                 按\"r\"重玩，Esc不玩啦。                    |\n");
                printf("[%c]-------------------------------------------------------[%c]\n", MINE, MINE);
                setColor(10);
                Sleep(1000);
                char key3 = getch();

                if(key3 == 'r' || key3 == 'R')
                {
                    //重来，跟main中过程是一样的
                    setColor(10);
                    gameInitailize();
                    countMines();
                    printMap();
                }
            }
            //剩余的格子比雷还要多，可以继续玩
            else if(leftBlocksNum > ALL_MINES)
            {
                setColor(13);
                printf("|                    哎哟，挺不错哦~ (￣0 ￣)               |\n");
                printf("[%c]-------------------------------------------------------[%c]\n", MINE, MINE);
                setColor(10);
            }
            //来到这你已经赢了
            else
            {
                setColor(13);
                printf("|                    哟，恭喜你赢了(/≧▽≦/)               |\n");
                printf("|                  按\"r\"重玩，Esc就不玩啦。                 |\n");
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
            gameOver("\t\t\t啦啦啦~很逗很扯吧~最后感谢你的玩耍呀（≧Д≦）\n\n\n\n\n\n\n\n");

        default:
            break;
        }
    }
}


void setCurPos(int y, int x)
{
    //在窗口缓冲中定义每个位置的状态
    COORD currentPosition;
    currentPosition.Y = y;
    currentPosition.X = x;
    //所以现在的位置是在{y,x}
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
}

void moveCursor(int y, int x)
{
    //限定能走的地方
    if((x >= 0 && x < COLUMN) && (y >= 0 && y < ROW))
    {
        setCurPos(cursorPos[y][x].y, cursorPos[y][x].x);
        index_x = x;
        index_y = y;
    }
}

bool checkResult(int y, int x)
{
    int i = 0, j = 0;

    //检测有没有溢出地图了
    if(x < 0 || x >= COLUMN || y < 0 || y >= ROW)
    {
        return false;
    }

    //就是你了！被选中的格子！
    minesMap[y][x].beCovered = false;

    //被惊天雷炸了
    if(minesMap[y][x].minesNum == -1)
    {
        minesMap[y][x].minesNum = 9;
        return true;
    }

    //如果没有雷，就当作空格吧
    if(minesMap[y][x].minesNum > 0 && minesMap[y][x].minesNum < 9)
    {
        return false;
    }

    //九宫格，3x3咯
    for(i = -1; i <= 1; ++i)
    {
        //检查一下在这一行溢出了没吧
        if(y + i < 0 || y + i >= ROW)
        {
            continue;
        }

        for(j = -1; j <= 1; ++j)
        {
            //这次就到列了吧
            if(x + j < 0 || x + j >= COLUMN)
            {
                continue;
            }
            //如果下一个是没开过的，就检查它吧
            if(minesMap[y + i][x + j].beCovered)
            {
                minesMap[y + i][x + j].beCovered = false;
                checkResult(y + i, x + j);
            }
        }
    }

    return false;
}

void printMap()
{
    system("cls");
    char help0[] = "←↑↓→";
    char help1[] = "动啊";
    char help2[] = "Space / Enter";
    char help3[] = "点击啊";
    char help4[] = "Esc 不玩啦";
    //因为要输出提示，所以地图不能太大了，10x10就差不多了
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
    printf("[开]--");
    setColor(10);

    for(k = 1; k < COLUMN - 1; ++k)
    {
        printf("+-----");
    }
    setColor(11);
    printf("+--[心]\n");
    setColor(10);

    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            if(minesMap[i][j].beCovered)
            {
                ++leftBlocksNum;
                //这个输出的就是格子被覆盖的时候输出的图形，可以换成1-6试试
                //1-4是正方形的4个角，5-6是双竖线和双横线
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
    printf("[就]--");
    setColor(10);

    for(k = 1; k < COLUMN - 1; ++k)
    {
        printf("+-----");
    }
    setColor(11);
    printf("+--[好]\n");
    setColor(10);
}

void delLine(int y)
{
    HANDLE hOutput;
    //窗口缓存信息
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    DWORD len, nw;
    //用MSDN上的TCHAR类型跪了，换成char就好
    char fillchar = ' ';
    //定位光标
    COORD startPosition = {0, y};
    //获取输出句柄
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    //获取窗口缓冲中的信息
    GetConsoleScreenBufferInfo(hOutput, &sbi);
    //窗口缓冲的位置，这里取得X值
    len = sbi.dwSize.X;
    //从特定的位置用特定的字符去填充窗口的缓冲特定次数
    //成功返回非0值，一般都成功，就不判断了
    FillConsoleOutputCharacter(hOutput, fillchar, len, startPosition, &nw);
}
