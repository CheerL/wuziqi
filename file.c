#include "head/wzq.h"

//文件处理部分
void getfilename()//获得文件名
{
	getnowtime();//获得时间字符串
	strcat(filename, "record/qipu ");
	strcat(filename, nowtime);
	strcat(filename, ".txt");//得到完整文件名 例如 qipu 2015-1-1 1-1-1.txt
}

void dofile()//把记录写入文件
{
	file = fopen(filename, "at+");//以可读写打开文件,若文件存在则打开,不存在则创建(filename为前面得到的文件名)
	if (file != NULL)//若成功打开文件,否则什么也不做
	{
		char a[50] = "\n";//字符串a为将要写入文件的内容,初始化
		char r[3];
		char x[3], y[3];
		strcat(a, iitoa(Round, r, 10));//加入回合数
		strcat(a, "\t");
		strcat(a, iitoa(renow->cursor.x + 1, x, 10));//加入横坐标
		strcat(a, " ");
		strcat(a, iitoa(renow->cursor.y + 1, y, 10));//加入纵坐标
		strcat(a, " ");
		strcat(a, " ");
		strcat(a, "\t");
		strcat(a, nowtime);//加入时间
		fwrite(a, strlen(a), 1, file);//写入文件
		fclose(file);//关闭文件
	}
}

void del()//悔棋时删除文件最后一行
{
	FILE *fin, *fout;//文件指针
	//计数器	
	int c;
	int count = 0;
	int ncount = 0;

	fin = fopen(filename, "r");//以只读打开文件(当前记录文件)
	//数出有多少行
	while (1) {
		c = fgetc(fin);
		if (EOF == c) break;
		if ('\n' == c) count++;
	}

	fclose(fin);//关闭

	fin = fopen(filename, "r");//重新打开文件
	fout = fopen("t.tmp", "w");//打开一个临时文件
	//将当前记录文件的内容全写到临时文件,除了最后一行
	while (1)
	{
		c = fgetc(fin);
		if (c == '\n')
		{
			ncount++;
			if (ncount == count)
				break;
		}
		fputc(c, fout);
	}
	fclose(fin);//关掉两个文件
	fclose(fout);
	remove(filename);//删除记录文件
	rename("t.tmp", filename);//把临时文件重命名为记录文件原来的名字
}

void readqipu()//读棋谱模式
{
	readmodel = 1;//改模式参数
	char c;
	int count = 0;
	int ncount = 0;
	char x[2], y[2];
	int i = 0, j = 0;
	file = fopen(filename, "r");//打开文件
	//以下为找到文件每行记录下的横纵坐标,记到字符串里
	while ((c = fgetc(file)) != EOF)
	{
		if (c == '	')
		{
			c = fgetc(file);
			count++;
			i = j = ncount = 0;
		}
		if (count % 2)
		{
			if (c == ' ')
			{
				c = fgetc(file);
				ncount++;
			}
			if (ncount == 0)
				x[i++] = c;
			else if (ncount == 1)
				y[j++] = c;
			else if (ncount == 2)
			{
				if (i == 1)	i = x[0] - '0';//把坐标字符串里的内容改成int
				else i = 10 + (int)x[1] - 48;
				if (j == 1)	j = y[0] - '0';
				else j = 10 + (int)y[1] - 48;
				Addrecord(i - 1, j - 1);//添加记录
				Round++;//回合数加1
			}
		}
	}
	//至此读完文件,也把记录链表和相应的棋盘内容完成了
	fclose(file);//关掉文件
	readmodel = 0;//退出读棋谱模式
	printboard();
	huifang();//进入回放模式
}

void huifang()//回放
{
	char tempname[50];//临时文件名,存储原来的文件名(当前记录文件文件名会被改变,最后会加上tmp)
	strcpy(tempname, filename);
	strcat(filename, "tmp");
	//回放控制
	while (1)
	{
		//getchar();
		printboard();
#ifdef WIN32
		printf("\n          方向键控制回放,ESC退出回放并从当前开始游戏");
#else
		printf("\n方向键控制回放,ESC退出回放并从当前开始游戏"); 	
#endif	
		if (huifangkongzhi())//进入回放控制
			break;
	}
	printboard();
	//把当前回放到的位置后的记录链表内容删去
	reback = renow->back;
	reback->next = newrecord();
	renow = reback->next;
	renow->back = reback;
	//退到链表头,回合数改为1
	renow = head->next;
	Round = 1;
	//写入新文件,当当前记录下一个非空,把记录写进文件里,当前记录推进到下一个
	while (renow->next != NULL)
	{
		dofile();
		renow = renow->next;
		Round++;
	}

	remove(tempname);//删除文件
	rename(filename, tempname);//重命名文件
	memset(filename, 0, sizeof(filename));//清空文件名
	strcpy(filename, tempname);//改回原来的文件名
}

int huifangkongzhi()//回放控制
{
	int key1;
	while (1)
	{
		if (kbhit())
		{
			A:switch (key1 = getch())
			{

			case 27://ESC
				return 1;
#ifndef WIN32
			case 183://上
			case 186://左
				if (renow->back->back != NULL)
				{
					renow = renow->back;//退到上一个记录
					board[renow->cursor.x][renow->cursor.y] = 0;
					Round--;
				}
				else
					goto A;
				break;
			case 184://下
			case 185://右
				if (renow->next != NULL)
				{

					board[renow->cursor.x][renow->cursor.y] = turn(Round);
					renow = renow->next;//推到下一个记录
					Round++;
				}
#else
			case 72://上
			case 75://左
				if (renow->back->back != NULL)
				{
					renow = renow->back;
					board[renow->cursor.x][renow->cursor.y] = 0;
					Round--;
				}
				else
					goto A;
				break;
			case 80://下
			case 77://右
				if (renow->next != NULL)
				{

					board[renow->cursor.x][renow->cursor.y] = turn(Round);
					renow = renow->next;
					Round++;
				}
#endif
				else
					goto A;
				break;
			default:
				break;
			}
			return 0;
		}
	}
}
//文件处理部分结束
