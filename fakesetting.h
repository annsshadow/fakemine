/*************************************************************************
	> File Name: fakesetting.h
	> Author: shadowwen-annsshadow
	> Mail: cravenboy@163.com
	> Created Time: Thu 11 Aug 2016 09:34:08 AM HKT
 ************************************************************************/

void setColor(unsigned short color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    //对设置之后的输出有效
    SetConsoleTextAttribute(hCon, color);
};

void welcomeToMyGame()
{
    int i = 0;
    char introductions0[] = "FakeMine";
    char introductions1[] = "--";
    char introductions2[] = "Version 2.0";
    char introductions3[] = "Author：shadowwen-annsshadow，thank you ╮(￣▽￣)╭";

    //控制台窗口默认大小是80*25，所以能达到最大的位置是[79,24]
    for(i = 0; i <= 5; ++i)
    {
        //每次输出之前都清屏，就会有看起来是动的效果
        system("cls");
        //纵坐标不断加，形成向下效果
        setCurPos(i, (80 - strlen(introductions0)) / 2);
        printf("%s", introductions0);
        //缓冲一下，太快了看不到呢
        Sleep(50);
    }

    //为了对称，从边边78开始到中间39好了
    for(i = 78; i >= 39; --i)
    {
        //上面用了5行了，大于它吧
        setCurPos(7, i);
        printf("%s", introductions1);
        setCurPos(7, 78 - i);
        printf("%s", introductions1);
        Sleep(40);
    }

    //从左边一步步进入屏幕中间
    for(i = 0; i <= (80 - strlen(introductions2)) / 2; ++i)
    {
        //要删除这一行缓冲的原因：
        //上一次循环的输出会影响到下一次，如输出VVVVVVVVVVersion1.0
        //换成中文就不会，中文要两个字节才能显示完整呀
        delLine(9);
        //这里就会有闪闪发亮的效果哦
        Sleep(10);
        setCurPos(9, i);
        printf("%s", introductions2);
        Sleep(50);
    }

    //从底部进入
    for(i = 24; i >= 12; --i)
    {
        setCurPos(i, (80 - strlen(introductions3)) / 2);
        printf("%s", introductions3);
        Sleep(20);
        //删除上一次的缓冲，不加1的话最后一行就会残留，其它都不见了
        delLine(i + 1);
        Sleep(50);
    }

    Sleep(500);
    char help0[] = "动啊：←↑↓→╮(╯▽╰)╭";
    char help1[] = "点击啊：Space / Enter (ΘェΘ)";
    char help2[] = "不玩啦：Esc (＞﹏＜)";
    char help3[] = "<<愿你玩的开心 _(:з」∠)_>>";
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

void gameOver(char *str)
{
    setColor(12);
    system("cls");
    setCurPos(10, 0);
    int i = 0;

    do
    {
        //逐字输出
        printf("%c", str[i]);
        Sleep(60);
    }
    while(str[i++]);
    setColor(15);
    system("pause");
    //随意终止程序并返回给OS，0是正常的
    exit(0);
}
