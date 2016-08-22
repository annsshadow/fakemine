/*************************************************************************
	> File Name: fakesetting.h
	> Author: shadowwen-annsshadow
	> Mail: cravenboy@163.com
	> Created Time: Thu 11 Aug 2016 09:34:08 AM HKT
 ************************************************************************/

/**
* [setColor set the console window color]
* @param color [first digital is for foreground color,second digital is background color]
*/
void setColor(unsigned short color)
{
    HANDLE handle_control = GetStdHandle(STD_OUTPUT_HANDLE);
    //useful for later actions after set
    SetConsoleTextAttribute(handle_control, color);
};

/**
 * [welcomeToMyGame the fake "flash" welcome]
 */
void welcomeToMyGame()
{
    int i = 0;
    char introductions0[] = "FakeMine";
    char introductions1[] = "--";
    char introductions2[] = "Version 2.0";
    char introductions3[] = "Author£ºshadowwen-annsshadow";

    //the default size of console window is 80 * 25
    //so how far we can reach is [79,24]
    for(i = 0; i <= 5; ++i)
    {
        //before each print, clear the screen, so can see the dynamic effect
        system("cls");
        //increase coordinate Y every time, so can see it is falling
        setCurPos(i, (80 - strlen(introductions0)) / 2);
        printf("%s", introductions0);
        //avoid too fast to see
        Sleep(50);
    }

    //for symmetry, from edge 78 to middle 39
    for(i = 78; i >= 39; --i)
    {
        //because it has been used 5 lines before, just more than it
        setCurPos(7, i);
        printf("%s", introductions1);
        setCurPos(7, 78 - i);
        printf("%s", introductions1);
        Sleep(40);
    }

    //from left side to middle step by step
    for(i = 0; i <= (80 - strlen(introductions2)) / 2; ++i)
    {
        //the last output will effect this time, like VVVVVVVVVVersion2.0
        //but if print chinese will not effect, so delete the last line
        deleteLine(9);
        //this can be shiny by sleep
        Sleep(10);
        setCurPos(9, i);
        printf("%s", introductions2);
        Sleep(50);
    }

    //from bottom to middle
    for(i = 24; i >= 12; --i)
    {
        setCurPos(i, (80 - strlen(introductions3)) / 2);
        printf("%s", introductions3);
        Sleep(20);
        //if don't +1, the final line will remain and others disappear
        deleteLine(i + 1);
        Sleep(50);
    }

    Sleep(500);
    char help0[] = "Move by Direction Key : left,up,down,right";
    char help1[] = "Click : Space / Enter";
    char help2[] = "Quit : Esc";
    char help3[] = "<<Hope you have fun~>>";
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

/**
 * [gameOver print the string one by one and exit]
 * @param str [point to string]
 */
void gameOver(char *str)
{
    setColor(12);
    system("cls");
    setCurPos(10, 0);
    int i = 0;

    do
    {
        //print the string one by one
        printf("%c", str[i]);
        Sleep(60);
    }
    while(str[i++]);
    setColor(15);
    system("pause");
    exit(0);
}
