/*********************************
*  c����������+��������װ�ɨ��
*  Author��AnnsShadoW
*  Version��2.0
*  Time��2015-11-29
********************************/

/********************************
*   ���л�����Windows7-64bit
*   ���뻷����Codeblocks-16.01
********************************/

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
void setColor(unsigned short color);
//��ͷ�Ļ�ӭ��������
void welcomeToMyGame();
//��Ϸ��ͼ��ʼ��
void gameInitailize();
//��ĳ����Ϊ���ļ��㾪��������
void countMines();
//��ȡ���̵�����
void keyBoardInput();
//ָ������λ��
void setCurPos(int y, int x);
//�ƶ�����λ��
void moveCursor(int y, int x);
//���ÿһ���Ľ��
bool checkResult(int y, int x);
//�����Ϸ����
void printMap();
//��Ϸ�˳���ġ�������
void gameOver(char *str);
//ɾ��������һ�еĻ���
void delLine(int y);


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

void setColor(unsigned short color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    //������֮��������Ч
    SetConsoleTextAttribute(hCon, color);
};

void welcomeToMyGame()
{
    int i = 0;
    char introductions0[] = "FakeMine";
    char introductions1[] = "--";
    char introductions2[] = "Version 2.0";
    char introductions3[] = "Author��AnnsShadow��thank you �r(������)�q";

    //����̨����Ĭ�ϴ�С��80*25�������ܴﵽ����λ����[79,24]
    for(i = 0; i <= 5; ++i)
    {
        //ÿ�����֮ǰ���������ͻ��п������Ƕ���Ч��
        system("cls");
        //�����겻�ϼӣ��γ�����Ч��
        setCurPos(i, (80 - strlen(introductions0)) / 2);
        printf("%s", introductions0);
        //����һ�£�̫���˿�������
        Sleep(50);
    }

    //Ϊ�˶Գƣ��ӱ߱�78��ʼ���м�39����
    for(i = 78; i >= 39; --i)
    {
        //��������5���ˣ���������
        setCurPos(7, i);
        printf("%s", introductions1);
        setCurPos(7, 78 - i);
        printf("%s", introductions1);
        Sleep(40);
    }

    //�����һ����������Ļ�м�
    for(i = 0; i <= (80 - strlen(introductions2)) / 2; ++i)
    {
        //Ҫɾ����һ�л����ԭ��
        //��һ��ѭ���������Ӱ�쵽��һ�Σ������VVVVVVVVVVersion1.0
        //�������ľͲ��ᣬ����Ҫ�����ֽڲ�����ʾ����ѽ
        delLine(9);
        //����ͻ�������������Ч��Ŷ
        Sleep(10);
        setCurPos(9, i);
        printf("%s", introductions2);
        Sleep(50);
    }

    //�ӵײ�����
    for(i = 24; i >= 12; --i)
    {
        setCurPos(i, (80 - strlen(introductions3)) / 2);
        printf("%s", introductions3);
        Sleep(20);
        //ɾ����һ�εĻ��壬����1�Ļ����һ�оͻ������������������
        delLine(i + 1);
        Sleep(50);
    }

    Sleep(500);
    char help0[] = "���������������r(�s���t)�q";
    char help1[] = "�������Space / Enter (������)";
    char help2[] = "��������Esc (���n��)";
    char help3[] = "<<Ը����Ŀ��� _(:�١���)_>>";
    setCurPos(14, (80 - strlen(help0)) / 2);
    setColor(14);
    printf("%s", help0);
    setCurPos(15, (80 - strlen(help1)) / 2);
    printf("%s", help1);
    setCurPos(16, (80 - strlen(help2)) / 2);
    printf("%s", help2);
    setCurPos(17, (80 - strlen(help3)) / 2);
    setColor(15);
    printf("%s", help3);
    getch();
}

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

void gameOver(char *str)
{
    setColor(12);
    system("cls");
    setCurPos(10, 0);
    int i = 0;

    do
    {
        //�������
        printf("%c", str[i]);
        Sleep(60);
    }
    while(str[i++]);
    setColor(15);
    system("pause");
    //������ֹ���򲢷��ظ�OS��0��������
    exit(0);
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
