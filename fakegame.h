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
    //ÉèÖÃËæ»úÖµ
    srand((unsigned int)time(NULL));

    //À×ÇøµØÍ¼³õÊ¼»¯
    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            minesMap[i][j].beCovered = true;
            minesMap[i][j].minesNum = 0;
        }
    }

    //·ÅÖÃ¾ªÌìÀ×£¡
    while(allMines)
    {
        i = rand() % ROW;
        j = rand() % COLUMN;

        if(minesMap[i][j].minesNum == 0)
        {
            //Õâ¸ö¡®-1¡¯¾Í×÷ÎªÅÐ¶Ï¾ªÌìÀ×µÄÒÀ¾ÝÁË
            minesMap[i][j].minesNum = -1;
            --allMines;
        }
    }

    //¹â±êÎ»ÖÃ³õÊ¼»¯
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
    //ÒÔ¸ñ×ÓÎªÖÐÐÄÖÜÎ§µÄÀ×Êý
    int minesNum = 0;

    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            //Óöµ½¾ªÌìÀ×¾Í·ÅÆúÍ³¼Æ°É
            if(minesMap[i][j].minesNum == -1)
                continue;
            minesNum = 0;
            //¾Å¹¬¸ñÂï£¬ÄÇ3´ÎºÃÁË
            for(m = -1; m <= 1; ++m)
            {
                //ÐÐÒç³öÁËÃ»£¬²»ÄÜËãÃ»ÓÐµÄÅ¶
                if(i + m < 0 || i + m >= ROW)
                {
                    continue;
                }

                for(n = -1; n <= 1; ++n)
                {
                    //Õâ´Î¾ÍÊÇ¿´ÁÐÒç³öÁËÃ»
                    if(j + n < 0 || j + n >= COLUMN)
                    {
                        continue;
                    }
                    //ÖÜ±ßÓÐ¾ªÌìÀ×¸Ï½ô¼ÓÆðÀ´
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
    ²âÊÔÖ®ºó²ÅÖªµÀ·½Ïò¼üÁ½¸ö×Ö½Ú
    µÚÒ»¸ö×Ö½ÚASCII 0x00e0 224
    µÚ¶þ¸ö×Ö½Ú·Ö±ðÊÇ£º
    ÉÏ£º0x0048 72
    ÏÂ£º0x0050 80
    ×ó£º0x012b 75
    ÓÒ£º0x012d 77
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
                printf("|              ÚÀÓ´,»¹²îÒ»µãµãÅ¶£¡ ¨i©n¨i                   |\n");
                printf("|                 °´\"r\"ÖØÍæ£¬Esc²»ÍæÀ²¡£                    |\n");
                printf("[%c]-------------------------------------------------------[%c]\n", MINE, MINE);
                setColor(10);
                Sleep(1000);
                char key3 = getch();

                if(key3 == 'r' || key3 == 'R')
                {
                    //ÖØÀ´£¬¸úmainÖÐ¹ý³ÌÊÇÒ»ÑùµÄ
                    setColor(10);
                    gameInitailize();
                    countMines();
                    printMap();
                }
            }
            //Ê£ÓàµÄ¸ñ×Ó±ÈÀ×»¹Òª¶à£¬¿ÉÒÔ¼ÌÐøÍæ
            else if(leftBlocksNum > ALL_MINES)
            {
                setColor(13);
                printf("|                    °¥Ó´£¬Í¦²»´íÅ¶~ (£þ0 £þ)               |\n");
                printf("[%c]-------------------------------------------------------[%c]\n", MINE, MINE);
                setColor(10);
            }
            //À´µ½ÕâÄãÒÑ¾­Ó®ÁË
            else
            {
                setColor(13);
                printf("|                    Ó´£¬¹§Ï²ÄãÓ®ÁË(/¨R¨Œ¨Q/)               |\n");
                printf("|                  °´\"r\"ÖØÍæ£¬Esc¾Í²»ÍæÀ²¡£                 |\n");
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
            gameOver("\t\t\tÀ²À²À²~ºÜ¶ººÜ³¶°É~×îºó¸ÐÐ»ÄãµÄÍæË£Ñ½£¨¨R§¥¨Q£©\n\n\n\n\n\n\n\n");

        default:
            break;
        }
    }
}


void setCurPos(int y, int x)
{
    //ÔÚ´°¿Ú»º³åÖÐ¶¨ÒåÃ¿¸öÎ»ÖÃµÄ×´Ì¬
    COORD currentPosition;
    currentPosition.Y = y;
    currentPosition.X = x;
    //ËùÒÔÏÖÔÚµÄÎ»ÖÃÊÇÔÚ{y,x}
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
}

void moveCursor(int y, int x)
{
    //ÏÞ¶¨ÄÜ×ßµÄµØ·½
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

    //¼ì²âÓÐÃ»ÓÐÒç³öµØÍ¼ÁË
    if(x < 0 || x >= COLUMN || y < 0 || y >= ROW)
    {
        return false;
    }

    //¾ÍÊÇÄãÁË£¡±»Ñ¡ÖÐµÄ¸ñ×Ó£¡
    minesMap[y][x].beCovered = false;

    //±»¾ªÌìÀ×Õ¨ÁË
    if(minesMap[y][x].minesNum == -1)
    {
        minesMap[y][x].minesNum = 9;
        return true;
    }

    //Èç¹ûÃ»ÓÐÀ×£¬¾Íµ±×÷¿Õ¸ñ°É
    if(minesMap[y][x].minesNum > 0 && minesMap[y][x].minesNum < 9)
    {
        return false;
    }

    //¾Å¹¬¸ñ£¬3x3¿©
    for(i = -1; i <= 1; ++i)
    {
        //¼ì²éÒ»ÏÂÔÚÕâÒ»ÐÐÒç³öÁËÃ»°É
        if(y + i < 0 || y + i >= ROW)
        {
            continue;
        }

        for(j = -1; j <= 1; ++j)
        {
            //Õâ´Î¾Íµ½ÁÐÁË°É
            if(x + j < 0 || x + j >= COLUMN)
            {
                continue;
            }
            //Èç¹ûÏÂÒ»¸öÊÇÃ»¿ª¹ýµÄ£¬¾Í¼ì²éËü°É
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
    char help0[] = "¡û¡ü¡ý¡ú";
    char help1[] = "¶¯°¡";
    char help2[] = "Space / Enter";
    char help3[] = "µã»÷°¡";
    char help4[] = "Esc ²»ÍæÀ²";
    //ÒòÎªÒªÊä³öÌáÊ¾£¬ËùÒÔµØÍ¼²»ÄÜÌ«´óÁË£¬10x10¾Í²î²»¶àÁË
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
    printf("[¿ª]--");
    setColor(10);

    for(k = 1; k < COLUMN - 1; ++k)
    {
        printf("+-----");
    }
    setColor(11);
    printf("+--[ÐÄ]\n");
    setColor(10);

    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            if(minesMap[i][j].beCovered)
            {
                ++leftBlocksNum;
                //Õâ¸öÊä³öµÄ¾ÍÊÇ¸ñ×Ó±»¸²¸ÇµÄÊ±ºòÊä³öµÄÍ¼ÐÎ£¬¿ÉÒÔ»»³É1-6ÊÔÊÔ
                //1-4ÊÇÕý·½ÐÎµÄ4¸ö½Ç£¬5-6ÊÇË«ÊúÏßºÍË«ºáÏß
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
    printf("[¾Í]--");
    setColor(10);

    for(k = 1; k < COLUMN - 1; ++k)
    {
        printf("+-----");
    }
    setColor(11);
    printf("+--[ºÃ]\n");
    setColor(10);
}

void delLine(int y)
{
    HANDLE hOutput;
    //´°¿Ú»º´æÐÅÏ¢
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    DWORD len, nw;
    //ÓÃMSDNÉÏµÄTCHARÀàÐÍ¹òÁË£¬»»³Échar¾ÍºÃ
    char fillchar = ' ';
    //¶¨Î»¹â±ê
    COORD startPosition = {0, y};
    //»ñÈ¡Êä³ö¾ä±ú
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    //»ñÈ¡´°¿Ú»º³åÖÐµÄÐÅÏ¢
    GetConsoleScreenBufferInfo(hOutput, &sbi);
    //´°¿Ú»º³åµÄÎ»ÖÃ£¬ÕâÀïÈ¡µÃXÖµ
    len = sbi.dwSize.X;
    //´ÓÌØ¶¨µÄÎ»ÖÃÓÃÌØ¶¨µÄ×Ö·ûÈ¥Ìî³ä´°¿ÚµÄ»º³åÌØ¶¨´ÎÊý
    //³É¹¦·µ»Ø·Ç0Öµ£¬Ò»°ã¶¼³É¹¦£¬¾Í²»ÅÐ¶ÏÁË
    FillConsoleOutputCharacter(hOutput, fillchar, len, startPosition, &nw);
}
