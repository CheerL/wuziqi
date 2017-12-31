#include "head/wzq.h"

//运行部分
int turn(int r)//从回合数返回一个值来决定黑白方,用于落子等
{
	if (r % 2)
		return 1;//黑方
	else
		return 2;//白方
}

void move()//落子
{
	int c;
	if (model[1] == 3)//机机对战
	{
		mainsuanfa();//调用算法电脑下一步棋
		win(cursor.x, cursor.y);//判断胜负
		printboard();
#ifndef WIN32
		printf("\n           按回车键暂停\n            按ESC退出");
#else
		printf("\n                        按回车键暂停\n                          按ESC退出");
#endif
		if (kbhit())
		{
#ifndef WIN32
			if ((c = getch()) == '\n')
#else
			if ((c = getch()) == '\r')
#endif
			{ 
#ifndef WIN32
				printf("\n         按任意键回到游戏\n"); 
#else
				cls;
				printboard();
				printf("\n                       按任意键回到游戏\n");
#endif
				while (1)	{ if (getch() != 0) break; }
			}//回车
			else if (c == 27) return replay();//ESC重新游戏
		}
		
		sleep(sleeptime);//暂停
	}
	else
	{

		int key1, key2, key3;
		int num;
		if (kbhit())//当有按键
		{
			printboard();
			printf(" ");
			key1 = getch();
			if (key1 == 27)//按ESC重新开始
				replay();
			else if (key1 == 'z')//按z悔棋
			{
				if (reback->back != NULL)//上一个记录不是空时
				{
					backrecord();//悔棋
					if (model[1] == 2)//当人机时
						backrecord();//再悔一步棋
					printboard();
				}
			}
			else if (key1 <= 'o'&&key1 >= 'a')//第一个输入是a到o中的某个字母
			{
				printf("%1c", key1);
			A: key2 = getch();
				if ((key2 >= '1'&&key2 <= '9') || (key2 >= 'a'&&key2 <= 'f'))//第二个输入是1到9或者a到f
				{
					printf("%c", key2);
#ifndef WIN32
					if ((key3 = getch()) != '\r')//第三个输入不是回车则继续输入
#else
					if ((key3 = getch()) != '\n')//第三个输入不是回车则继续输入
#endif
					{
						if (key2 == '1')//只有当第二个输入是1才继续输入
						{
							printf("%c", key3);
#ifndef WIN32
							while (getch() == '\r')//输入第三个字符后，只有当再输入回车才继续运行下去
#else
							while (getch() == '\n')//输入第三个字符后，只有当再输入回车才继续运行下去
#endif
								break;
						}
					}

					//转换key2，key3为数字

					if (key2 <= 'f'&&key2 >= 'a')					//当输入的是a到f
						num = key2 - 'a' + 10;
					else if (key3 >= '0' && key3 <= '5'&&key2 == '1')//当输入的是10到15
						num = 10 * (key2 - '0') + (key3 - '0');
					else											//当输入的是1到9
						num = key2 - '0';

					if (!board[key1 - 'a'][num - 1])				//当输入的对应位置没有落子
					{
						Addrecord(key1 - 'a', num - 1);	//添加行棋记录
						if (model[3]==1)
							jinshou();//禁手判断
						win(cursor.x, cursor.y);	//判断胜负
						if (model[1] == 2)			//当人机模式
						{
							mainsuanfa();			//调用算法电脑下一步棋
							win(cursor.x, cursor.y);		//判断胜负
							printboard();
						}
						else		//当人人模式
							printboard();
					}
				}
				else goto A;				//当第二个输入不符合要求则重新输入
			}

		}

	}
}

void modelchoose(void)//模式选择
{
	W:printf("按1开始新游戏\n按2加载棋谱\n按3查看帮助\n按ESC退出程序\n");
	while (model[0] != 1 && model[0] != 2&& model[0]!=3 && model[0]!=-21)
	{
		model[0] = getch() - '0';
	}
	if(model[0]!=-21)
		printf("%d\n", model[0]);
	else
		replay();

	if (model[0] == 3)
	{
		FILE* help;
		char line[100];
		help = fopen("src/README.txt", "r");

		if (help != NULL)
		{
			cls;
			int i = 0;
			while (fgets(line, 100, help))
			{
				printf("%s", line);
				i++;
				if(i > 15)
				{
					if (getch() != 0)
					{
						i = 0;
					}
				}
			}
			while (1)	
			{
				if (getch() != 0)
				{
					cls;
					break;
				}
			}
		}
		model[0] = 0;
		fclose(help);
		goto W;
	}
	if (model[0] == 2)
	{
	A:	printf("输入文件名(例: qipu 2015-1-1 1-1-1.txt)\n");
		char tmpname[50];
		scanf("%[^\n]", &tmpname);
		strcat(filename, "record/");
		strcat(filename, tmpname);
		if (strstr(tmpname, ".txt") == NULL){
			strcat(filename, ".txt");
		}
		file = fopen(filename, "r");
		if (file == NULL)
		{
			getchar();
			memset(filename, 0, sizeof(filename));
			int t = 0;
			printf("文件不存在\n按1重新输入文件名\n按2开始新游戏\n");
			while (t != 1 && t != 2)
			{
				t = getch() - '0';
			}
			printf("%d\n", t);
			if (t == 1)
				goto A;
			else
			{
				model[0] = 1;
				goto B;
			}
		}
		else
			fclose(file);
		printf("按1开始人人对战\n按2开始人机对战\n按ESC回到上一层\n");
		while (model[1] != 1 && model[1] != 2 && model[1] != 27 - '0')
		{
			model[1] = getch() - '0';
		}
		if (model[1]!=-21)
			printf("%d\n", model[1]);
		else
		{
			model[0] = 0;
			model[1] = 0;
			printf("\n");
			goto W;
		}
	}

	if (model[0] == 1)
	{
	B:	printf("按1开始人人对战\n按2开始人机对战\n按3开始机机对战(测试模式)\n按ESC回到上一层\n");
		while (model[1] != 1 && model[1] != 2 && model[1] != 3 && model[1] != 27 - '0')
		{
			model[1] = getch() - '0';
		}
		if (model[1] != -21)
			printf("%d\n", model[1]);
		else
		{
			model[0] = 0;
			model[1] = 0;
			printf("\n");
			goto W;
		}
		if (model[1] == 2)
		{
			printf("按1选择黑方\n按2选择白方\n按ESC回到上一层\n");
			while (model[2] != 1 && model[2] != 2 && model[2] != 27 - '0')
			{
				model[2] = getch() - '0';
			}
			if (model[2]!=-21)
				printf("%d\n", model[2]);
			else
			{
				model[1] = 0;
				model[2] = 0;
				printf("\n");
				goto B;
			}
		}
		else if (model[1] == 3)
		{
#ifndef WIN32
			printf("希望电脑多久下一步棋(s)\n");
			scanf("%d", &sleeptime);
#else
			printf("希望电脑多久下一步棋(ms)\n");
			scanf("%d", &sleeptime);
#endif
		}
	}
	printf("按1选择黑方禁手\n按2不禁手\n");
	while (model[3] != 1 && model[3] != 2)
	{
		model[3] = getch() - '0';
	}
	printf("%d\n", model[3]);
}

void win(int a, int b)//判断胜负
{
	if (iswin(a, b))//若获胜
	{
		if (turn(Round) == 1)//判断哪方获胜
		{
			printboard();
			printf("黑方胜利");
		}
		else
		{
			printboard();
			printf("白方胜利");
		}
		replay();//重新开始游戏
	}
	Round++;//否则回合数加1
}

int iswin(int a, int b)//判断胜负(a,b为坐标)
{
	int w = 1, x = 1, y = 1, z = 1;
	int	i;
	int k = turn(Round);
	for (i = 1; i<5; i++)if (b + i<MAXIUM&&board[a][b + i] == k)w++; else break;//向下检查
	for (i = 1; i<5; i++)if (b - i >= 0 && board[a][b - i] == k)w++; else break;//向上检查
	if (w >= 5)return 1;

	for (i = 1; i<5; i++)if (a + i<MAXIUM&&board[a + i][b] == k)x++; else break;//向右检查
	for (i = 1; i<5; i++)if (a - i >= 0 && board[a - i][b] == k)x++; else break;//向左检查
	if (x >= 5)return 1;

	for (i = 1; i<5; i++)if (a + i<MAXIUM&&b + i<MAXIUM&&board[a + i][b + i] == k)y++; else break;//向右下检查
	for (i = 1; i<5; i++)if (a - i >= 0 && b - i >= 0 && board[a - i][b - i] == k)y++; else break;//向左上检查
	if (y >= 5)return 1;

	for (i = 1; i<5; i++)if (a + i<MAXIUM&&b - i >= 0 && board[a + i][b - i] == k)z++; else break;//向右上检查
	for (i = 1; i<5; i++)if (a - i >= 0 && b + i<MAXIUM&&board[a - i][b + i] == k)z++; else break;//向左下检查
	if (z >= 5)return 1;

	return 0;//若没有检查到五连，则返回0,表示还没达成胜利
}

void replay()//重新开始游戏
{
	int i;
	printf("\n按1重新开始游戏      按2退出\n");
	int t=0;
	while (t != 1 && t != 2)
	{
		t = getch() - '0';
	}
	printf("%d\n", t);
	if (t == 1)//若重新开始
	{
		memset(model, 0, sizeof(model));//清空本局设置
		memset(nowtime, 0, sizeof(nowtime));
		memset(filename, 0, sizeof(filename));
		for (i = 0; i < MAXIUM; i++)
			memset(board[i], 0, sizeof(board[i]));//清空棋盘
		initial();//进入初始化
	}
	else{		//否则跳出程序
		pause;
		exit(0);
	}
}

void backrecord()//悔棋
{

	board[reback->cursor.x][reback->cursor.y] = 0;//上一个落子位置清零
	reback = reback->back;//上上个记录赋值给上一个记录
	renow->back = reback;//当前记录的上个记录指向 原来的上上个记录
	reback->next = renow;//当前记录的上个记录(原来的上上个记录)的下个记录指向当前记录 !@#$%^&*(   反正是在操作记录链表,绕口令似的
	Round--;//回合数减1
	del();//删除文件中相应记录
}
//运行部分结束

char* join(char *s1, char *s2)  
{  
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator  
    //in real code you would check for errors in malloc here  
    if (result == NULL) exit (1);  
  
    strcpy(result, s1);  
    strcat(result, s2);  
  
    return result;  
}