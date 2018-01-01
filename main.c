#include "head/wzq.h"

//main
int main(void)
{
	initial(); //初始化游戏
	while (1)
	{
		move();
	}
	return 0;
}

void initial(void) //初始化游戏
{
#ifndef WIN32
	printf("\033[0m\033[37;1m"); //设置颜色
#else
	system("chcp 65001");
	system("title 五子棋");				 //设置标题
	system("mode con cols=63 lines=34"); //设置窗口大小
	system("color E0");					 //设置颜色
#endif
	cls;
	xingqimodel = 0;
	//初始化行棋记录相关部分
	if (access("record", 0) == -1)
	{
		mkdirs("record");
	}
	head = newrecord();
	renow = newrecord();
	reback = newrecord();
	head->next = renow;
	renow->back = head;
	reback = renow->back;
	Round = 1;	 //第一回合
	modelchoose(); //模式选择

	cls;
	if (model[0] == 1) //若为新游戏
	{
		getfilename(); //获取文件名
		if (model[1] == 2 && model[2] == 2)
		{
			Addrecord(7, 7);
			Round++;
			printboard();
		} //若为人机模式且玩家执白,直接打印棋盘
		else
			kaiju(); //否则进入指定开局
	}
	else if (model[0] == 2) //若加载游戏,进入读棋谱模式
		readqipu();
	if (model[1] != 3)
		xingqimodel = 1;
	printf("开始游戏");
}

#ifndef WIN32
int kbhit(void) //当有键按下返回1,否则返回0,检测是否有按键
{
	struct termios oldt, newt;
	int ch;
	int oldf;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if (ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	return 0;
}

int getch(void)
{ //类似getchar,从输入读一个字符,不用按回车,且不会显示在屏幕上
	//比getchar,scanf更及时,可以按下就做出反应,且不输入也不耽误程序运行
	//我用于操作控制,如回放控制,悔棋等,其他所有输入任务也几乎由它承担
	//后加判断,如果输入符合要求,则printf在屏幕,且进入下一步,否则不显示,继续输入到符合要求为止
	struct termios tm, tm_old;
	int fd = STDIN_FILENO, c;
	if (tcgetattr(fd, &tm) < 0)
		return -1;
	tm_old = tm;
	cfmakeraw(&tm);
	if (tcsetattr(fd, TCSANOW, &tm) < 0)
		return -1;
	c = fgetc(stdin);
	if (kbhit())
	{
		c += getch();
	}
	if (tcsetattr(fd, TCSANOW, &tm_old) < 0)
		return -1;
	return c;
}
#endif
//结束
//main结束