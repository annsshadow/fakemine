/*************************************************************************
	> File Name: fakesetting.h
	> Author: shadowwen-annsshadow
	> Mail: cravenboy@163.com
	> Created Time: Thu 11 Aug 2016 09:34:08 AM HKT
 ************************************************************************/

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
    char introductions3[] = "Author��shadowwen-annsshadow��thank you �r(������)�q";

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
