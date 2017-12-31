#include "head/wzq.h"

//棋盘部分
char* getStyle(int i, int j)//获取坐标对应位置的内容
{
#ifndef WIN32
	if(!readmodel)	
	{
		if (i == reback->cursor.x&&j == reback->cursor.y)
		{
			if (board[i][j] == 1)//黑子当前落子
			{
				if (i == 14)
					return "\033[30m★\033[37;1m";
				else//边缘位置
				{
					switch (j)
					{
					case 0:
						;
					case 14:
						return "\033[30m★\033[37;1m━";
						break;
					default:
						return "\033[30m★\033[37;1m─";
						break;
					}
				}
			}
			else//白子当前落子
			{
				if (i == 14)
					return "★";
				else//边缘位置
				{
					switch (j)
					{
					case 0:
						;
					case 14:
						return "★━";
						break;
					default:
						return "★─";
						break;
					}
				}
			}
		}
	}
	if (board[i][j] == 1)//1为黑子
	{
		if (i == 14)
			return "\033[30m●\033[37;1m";//"●".其他为颜色设置
		else//边缘位置
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "\033[30m●\033[37;1m━";
				break;
			default:
				return "\033[30m●\033[37;1m─";
				break;
			}
		}
	}
	else if (board[i][j] == 2)//2为白子
	{
		if (i == 14)
			return "●";
		else
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "●━";
				break;
			default:
				return "●─";
				break;
			}
		}
	}
	else if (board[i][j] == 3)
	{
		if (i == 14)
			return "╳";
		else//边缘位置
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "╳━";
				break;
			default:
				return "╳─";
				break;
			}
		}
	}
#else
	if (!readmodel)
	{
		if (i == reback->cursor.x&&j == reback->cursor.y)
		{
			if (board[i][j] == 1)//黑子当前落子
			{
				if (i == 14)
					return "★";
				else//边缘位置
				{
					switch (j)
					{
					case 0:
						;
					case 14:
						return "★━";
						break;
					default:
						return "★─";
						break;
					}
				}
			}
			else if(board[i][j] == 2)//白子当前落子
			{
				if (i == 14)
					return "☆";
				else//边缘位置
				{
					switch (j)
					{
					case 0:
						;
					case 14:
						return "☆━";
						break;
					default:
						return "☆─";
						break;
					}
				}
			}
		}
	}
	if (board[i][j] == 1)//1为黑子
	{
		if (i == 14)
			return "●";
		else
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "●━";
				break;
			default:
				return "●─";
				break;
			}
		}
	}
	else if (board[i][j] == 2)//2为白子
	{
		if (i == 14)
			return "○";
		else//边缘位置
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "○━";
				break;
			default:
				return "○─";
				break;
			}
		}
	}
	else if (board[i][j] == 3)
	{
		if (i == 14)
			return "╳";
		else//边缘位置
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "╳━";
				break;
			default:
				return "╳─";
				break;
			}
		}
	}

#endif
	else if (board[i][j] == 0)//未落子的位置
	{
		//边缘
		if (i == 0 && j == 0)
			return "┗━";
		else if (i == MAXIUM - 1 && j == 0)
			return "┛";
		else if (i == MAXIUM - 1 && j == MAXIUM - 1)
			return "┓";
		else if (i == 0 && j == MAXIUM - 1)
			return "┏━";
		else if (i == 0)
			return "┠─";
		else if (i == MAXIUM - 1)
			return "┨";
		else if (j == 0)
			return "┷━";
		else if (j == MAXIUM - 1)
			return "┯━";

		return "┼─";//中间的空位
	}
	return NULL;
}

void printboard()//打印棋盘函数
{
	cls;
	int i, j;
#ifndef WIN32
	_printn//宏定义 换行
	printf("%2d", MAXIUM);//第一行
	for (i = 0; i < MAXIUM; i++) { printf(getStyle(i, 14)); }_printn
		for (j = 13; j > 0; j--)//其他行
		{
			printf("%2d", j + 1);
			for (i = 0; i < MAXIUM; i++){ printf(getStyle(i, j)); }_printn
		}

	printf("%2d", 1);//最后一行
	for (i = 0; i < MAXIUM; i++) { printf(getStyle(i, 0)); }

	_printn printf(" ");//字母
	for (i = 0; i < MAXIUM; i++) { printf("%2c", i + 'a'); }

	_printn  //回合信息 _turns为黑白方判断 getdate为显示时间(见最开始宏定义)
		_turns printf("        "); getdate; _printn 
	if(xingqimodel) tishi();
	_printspace
#else
	printf("%2d", MAXIUM);//第一行
	for (i = 0; i < MAXIUM; i++) { printf(getStyle(i, 14)); }
	printf("\n  ┃");  for (i = 0; i<MAXIUM - 2; i++){ printf("  │"); } printf("  ┃\n");//中间的
	for (j = 13; j > 0; j--)//其他行
	{
		printf("%2d", j + 1);
		for (i = 0; i < MAXIUM; i++){ printf(getStyle(i, j)); }
		printf("\n  ┃"); for (i = 0; i<MAXIUM - 2; i++){ printf("  │"); } printf("  ┃\n");//中间的
	}
	printf("%2d", 1);//最后一行
	for (i = 0; i < MAXIUM; i++) { printf(getStyle(i, 0)); }
	_printn
		for (i = 0; i < MAXIUM; i++) { printf("%4c", i + 'a'); }//字母
	_printn  printf("               "); _turns printf("           "); getdate; _printn//回合信息
	if(xingqimodel) tishi();
	_printspace

#endif
}

void getnowtime()//获得当前时间(字符串形式)
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	char year[5], mon[3], day[3], hour[3], min[3], sec[3];
	//以上部分获得一个结构,里面有当前的 年 月 日 时 分 秒 (int)(度娘教的函数)

	if ((p->tm_hour + 8) >= 24)//东八区,小时数加8,若超过24进一天
	{
		p->tm_hour -= 24;
		p->tm_mday++;
	}

	strcat(nowtime, iitoa(1900 + p->tm_year, year, 10));//iitoa(a,b,c)为把 数字a 在 c进制 下转化为 字符串b 的函数
	strcat(nowtime, "-");								//strcat(a,b)为把 字符串b 的内容加到 字符串a 最后的函数
	strcat(nowtime, iitoa(1 + p->tm_mon, mon, 10));
	strcat(nowtime, "-");
	strcat(nowtime, iitoa(p->tm_mday, day, 10));
	strcat(nowtime, " ");
	strcat(nowtime, iitoa(p->tm_hour + 8, hour, 10));
	strcat(nowtime, "-");
	strcat(nowtime, iitoa(p->tm_min, min, 10));
	strcat(nowtime, "-");
	strcat(nowtime, iitoa(p->tm_sec, sec, 10));//得到完整的时间字符串 如 2015-1-1 1-1-1
}

char *iitoa(int num, char *str, int radix)//iitoa(a,b,c)为把 数字a 在 c进制 下转化为 字符串b 的函数(度娘加1)
{
	char  string[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char* ptr = str;
	int denom = 0;  //余数
	int count = -1;
	int i;
	int j;

	while (num >= radix)
	{
		denom = num % radix;
		num /= radix;
		*ptr++ = string[denom];
		count++;
	}

	if (num >= 0)
	{
		*ptr++ = string[num];
		count++;
	}

	*ptr = '\0';
	j = count;

	for (i = 0; i < (count + 1) / 2; i++)
	{
		int temp = str[i];
		str[i] = str[j];
		str[j--] = temp;
	}

	return str;
}

void tishi()
{
#ifndef WIN32
	printf("  输入坐标后回车以落子  按z悔棋\n") ;
#else
	printf("                  输入坐标后回车以落子  按z悔棋\n") ;
#endif
}
//棋盘部分结束
