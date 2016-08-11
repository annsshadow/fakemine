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
    //�������ֵ
    srand((unsigned int)time(NULL));

    //������ͼ��ʼ��
    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            minesMap[i][j].beCovered = true;
            minesMap[i][j].minesNum = 0;
        }
    }

    //���þ����ף�
    while(allMines)
    {
        i = rand() % ROW;
        j = rand() % COLUMN;

        if(minesMap[i][j].minesNum == 0)
        {
            //�����-1������Ϊ�жϾ����׵�������
            minesMap[i][j].minesNum = -1;
            --allMines;
        }
    }

    //���λ�ó�ʼ��
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
    //�Ը���Ϊ������Χ������
    int minesNum = 0;

    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            //���������׾ͷ���ͳ�ư�
            if(minesMap[i][j].minesNum == -1)
                continue;
            minesNum = 0;
            //�Ź������3�κ���
            for(m = -1; m <= 1; ++m)
            {
                //�������û��������û�е�Ŷ
                if(i + m < 0 || i + m >= ROW)
                {
                    continue;
                }

                for(n = -1; n <= 1; ++n)
                {
                    //��ξ��ǿ��������û
                    if(j + n < 0 || j + n >= COLUMN)
                    {
                        continue;
                    }
                    //�ܱ��о����׸Ͻ�������
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
    ����֮���֪������������ֽ�
    ��һ���ֽ�ASCII 0x00e0 224
    �ڶ����ֽڷֱ��ǣ�
    �ϣ�0x0048 72
    �£�0x0050 80
    ��0x012b 75
    �ң�0x012d 77
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
                printf("|              ��Ӵ,����һ���Ŷ�� �i�n�i                   |\n");
                printf("|                 ��\"r\"���棬Esc��������                    |\n");
                printf("[%c]-------------------------------------------------------[%c]\n", MINE, MINE);
                setColor(10);
                Sleep(1000);
                char key3 = getch();

                if(key3 == 'r' || key3 == 'R')
                {
                    //��������main�й�����һ����
                    setColor(10);
                    gameInitailize();
                    countMines();
                    printMap();
                }
            }
            //ʣ��ĸ��ӱ��׻�Ҫ�࣬���Լ�����
            else if(leftBlocksNum > ALL_MINES)
            {
                setColor(13);
                printf("|                    ��Ӵ��ͦ����Ŷ~ (��0 ��)               |\n");
                printf("[%c]-------------------------------------------------------[%c]\n", MINE, MINE);
                setColor(10);
            }
            //���������Ѿ�Ӯ��
            else
            {
                setColor(13);
                printf("|                    Ӵ����ϲ��Ӯ��(/�R���Q/)               |\n");
                printf("|                  ��\"r\"���棬Esc�Ͳ�������                 |\n");
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
            gameOver("\t\t\t������~�ܶ��ܳ���~����л�����ˣѽ���R���Q��\n\n\n\n\n\n\n\n");

        default:
            break;
        }
    }
}


void setCurPos(int y, int x)
{
    //�ڴ��ڻ����ж���ÿ��λ�õ�״̬
    COORD currentPosition;
    currentPosition.Y = y;
    currentPosition.X = x;
    //�������ڵ�λ������{y,x}
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
}

void moveCursor(int y, int x)
{
    //�޶����ߵĵط�
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

    //�����û�������ͼ��
    if(x < 0 || x >= COLUMN || y < 0 || y >= ROW)
    {
        return false;
    }

    //�������ˣ���ѡ�еĸ��ӣ�
    minesMap[y][x].beCovered = false;

    //��������ը��
    if(minesMap[y][x].minesNum == -1)
    {
        minesMap[y][x].minesNum = 9;
        return true;
    }

    //���û���ף��͵����ո��
    if(minesMap[y][x].minesNum > 0 && minesMap[y][x].minesNum < 9)
    {
        return false;
    }

    //�Ź���3x3��
    for(i = -1; i <= 1; ++i)
    {
        //���һ������һ�������û��
        if(y + i < 0 || y + i >= ROW)
        {
            continue;
        }

        for(j = -1; j <= 1; ++j)
        {
            //��ξ͵����˰�
            if(x + j < 0 || x + j >= COLUMN)
            {
                continue;
            }
            //�����һ����û�����ģ��ͼ������
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
    char help0[] = "��������";
    char help1[] = "����";
    char help2[] = "Space / Enter";
    char help3[] = "�����";
    char help4[] = "Esc ������";
    //��ΪҪ�����ʾ�����Ե�ͼ����̫���ˣ�10x10�Ͳ����
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
    printf("[��]--");
    setColor(10);

    for(k = 1; k < COLUMN - 1; ++k)
    {
        printf("+-----");
    }
    setColor(11);
    printf("+--[��]\n");
    setColor(10);

    for(i = 0; i < ROW; ++i)
    {
        for(j = 0; j < COLUMN; ++j)
        {
            if(minesMap[i][j].beCovered)
            {
                ++leftBlocksNum;
                //�������ľ��Ǹ��ӱ����ǵ�ʱ�������ͼ�Σ����Ի���1-6����
                //1-4�������ε�4���ǣ�5-6��˫���ߺ�˫����
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
    printf("[��]--");
    setColor(10);

    for(k = 1; k < COLUMN - 1; ++k)
    {
        printf("+-----");
    }
    setColor(11);
    printf("+--[��]\n");
    setColor(10);
}

void delLine(int y)
{
    HANDLE hOutput;
    //���ڻ�����Ϣ
    CONSOLE_SCREEN_BUFFER_INFO sbi;
    DWORD len, nw;
    //��MSDN�ϵ�TCHAR���͹��ˣ�����char�ͺ�
    char fillchar = ' ';
    //��λ���
    COORD startPosition = {0, y};
    //��ȡ������
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    //��ȡ���ڻ����е���Ϣ
    GetConsoleScreenBufferInfo(hOutput, &sbi);
    //���ڻ����λ�ã�����ȡ��Xֵ
    len = sbi.dwSize.X;
    //���ض���λ�����ض����ַ�ȥ��䴰�ڵĻ����ض�����
    //�ɹ����ط�0ֵ��һ�㶼�ɹ����Ͳ��ж���
    FillConsoleOutputCharacter(hOutput, fillchar, len, startPosition, &nw);
}
