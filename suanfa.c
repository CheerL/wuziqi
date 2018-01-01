#include "head/wzq.h"

//算法部分
int san, si;

void mainsuanfa(void) //电脑下棋算法
{
	if (Round == 1) //第一回合直接下h8
		Addrecord(7, 7);
	else if (Round == 2) //第二回合
	{
		if (board[7][7] == 0) //若h8无字子,下到h8
			Addrecord(7, 7);
		else //有子则下到i9
			Addrecord(8, 8);
	}
	else
	{
		/*
		先对当前局面进行判断,对每一个未落子的位置,求若在此处落子的得分;
		保存所有最好得分位置,把这些位置用Best[255][2]存下来,共w个(0到w-1);
		若w=0,则和棋(只可能是棋盘下满了),若w大于0,则对这些最好位置进行选择;
		若在Best[q]处下子,求对方按同样算法的最好得分 (q从0取到w-1);
		当取到对方最好得分中最低分,记下这个q,存入待选数组daixuan[255];
		当取遍0到w-1,得到i个q,随机取一个为bestnum(即使w=1,也可以进行上述操作);
		则Best[bestnum]为能让自己得分最高同时对方得分最低的落子位置,在相应位置落子并退出;
		(本来是可以用相同的方式继续判断求更准确的最好位置,但是偷懒用随机选了.)
		*/
		srand((unsigned int)time(NULL)); //随机函数
		int i, j;
		int s, t;
		int q = 0, w = 0;							  //计数器
		int now[3] = {0, 0, 0};						  //当前得分
		int best[3] = {-1000000, -1000000, -1000000}; //当前最好得分 (初始化很低的分数方便覆盖)
		int fbest = 100000000;						  //对方最好得分中最低分  (初始化很高的分数方便覆盖)
		int Best[255][2];							  //存最好位置的数组,Best[i][0]为横坐标,Best[i][1]为纵坐标
		int daixuan[255];							  //待选数组
		int bestnum;
		int k = turn(Round); //回合判断

		for (i = 0; i < MAXIUM; i++) //取遍棋盘
			for (j = 0; j < MAXIUM; j++)
			{
				if (board[i][j] == 0 || (board[i][j] == 3 && k == 2)) //若可以下子
				{
					now[0] = getscore(i, j, k); //打分
					if (best[0] < now[0])		//若当前得分比最好得分高,替代
					{
						best[0] = now[0];
						Best[0][0] = i;
						Best[0][1] = j;
						w = 1; //计数器清零
					}
					else if (best[0] == now[0]) //若当前得分比等于最好得分,增加
					{
						Best[w][0] = i;
						Best[w][1] = j;
						w++; //计数器加1
					}
				}
			}
		if (w == 0)
		{
			printf("平局\n");
			return replay();
		}
		for (q = 0; q < w; q++) //对w个最好位置进行选择
		{
			board[Best[q][0]][Best[q][1]] = k; //假设在相应位置落子
			for (s = 0; s < MAXIUM; s++)	   //取遍棋盘
				for (t = 0; t < MAXIUM; t++)
				{
					if (board[s][t] == 0 || (board[s][t] == 3 && k == 2)) //若可以下子
					{
						now[1] = getscore(s, t, 3 - k); //打分
						if (best[1] <= now[1])
						{
							board[s][t] = 3 - k;
							for (i = 0; i < MAXIUM; i++)
								for (j = 0; j < MAXIUM; j++)
								{
									if (board[s][t] == 0 || (board[s][t] == 3 && k == 2))
									{
										now[2] = getscore(s, t, k);
										if (best[2] < now[2])
											best[2] = now[2];
									}
								}
							board[s][t] = 0;
							now[1] -= best[2];
							if (best[1] < now[1])
								best[1] = now[1];
						}
					}
				}

			if (fbest > best[1]) //判断对方最高得分是否最低,若是,替代
			{
				fbest = best[1];
				daixuan[0] = q; //将该位置覆盖为待选数组的第一个
				i = 1;			//计数器清零
			}
			else if (fbest == best[1]) //若等于最低得分
				daixuan[i++] = q;	  //加入待选数组,同时计数器加1

			board[Best[q][0]][Best[q][1]] = 0; //将假设下的子去掉
		}
		if (i) //若i大于0,即不止一个最佳位置,随机选择一个
			bestnum = (int)(rand() % i);
		else //若只有一个
			bestnum = 0;

		Addrecord(Best[daixuan[bestnum]][0], Best[daixuan[bestnum]][1]); //添加行棋记录
		if (model[3] == 1)
			jinshou(); //禁手判断
	}
}

int getscore(int i, int j, int k) //判分函数,i,j为坐标,k为回合判断的值(黑方为1,白方为2)
{
	/*
	形成5连为胜,每个子可以成为5连组合的第1个子,第2个子,……,第5个子(横向为例,+表示当前子,+----,-+---,……,----+);
	且有横,竖,左斜,右斜4个方向,即一个子最多可以在20个5连组合中(5连组合是我自己起的名字-_-,应该不会很难理解吧);
	每个子的得分为 对每个己方5连组合的贡献的得分和+中断对方五连组合的得分和;
	*/

	int n = 0;		//得分
	int count = 0;  //当前统计的5连组合中自己子的个数
	int ncount = 0; //当前统计的5连组合中对方子的个数
	int t, p;
	for (p = 0; p < 5; p++) //向上下(p确定5连组合的位置,p越大组合越靠下)
	{
		if (j - p < 0) //若最低位置已近低于棋盘下界,跳出循环,统计其他方向的得分
			break;
		else if (j - p + 4 >= MAXIUM) //若最高位置高于棋盘的上界,忽略后续部分,p直接加1,统计位置低一些的组合的得分
			continue;
		else //位置正常
		{
			for (t = 0; t < 5; t++) //统计五连组合中的每个子
			{
				if (board[i][j - p + t] == k)
					count++; //若为己方的
				else if (board[i][j - p + t] == 3 - k || board[i][j - p + t] == 3)
					ncount++; //若为对方的
			}
			n += jiafen(count, ncount);  //当前分数加上对己方的得分
			n += njiafen(count, ncount); //当前分数加上终结对方的得分
			count = ncount = 0;			 //计数器清零
		}
	}

	for (p = 0; p < 5; p++) //向左右
	{
		if (i - p < 0)
			break;
		else if (i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j] == k)
					count++;
				else if (board[i - p + t][j] == 3 - k || board[i][j - p + t] == 3)
					ncount++;
			}
			n += jiafen(count, ncount);
			n += njiafen(count, ncount);
			count = ncount = 0;
		}
	}

	for (p = 0; p < 5; p++) //向左下右上
	{
		if (j - p < 0 || i - p < 0)
			break;
		else if (j - p + 4 >= MAXIUM || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j - p + t] == k)
					count++;
				else if (board[i - p + t][j - p + t] == 3 - k || board[i][j - p + t] == 3)
					ncount++;
			}
			n += jiafen(count, ncount);
			n += njiafen(count, ncount);
			count = ncount = 0;
		}
	}

	for (p = 0; p < 5; p++) //向左下右上
	{
		if (j + p >= MAXIUM || i - p < 0)
			break;
		else if (j + p - 4 < 0 || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++) //向左上右下
			{
				if (board[i - p + t][j + p - t] == k)
					count++;
				if (board[i - p + t][j + p - t] == 3 - k || board[i][j - p + t] == 3)
					ncount++;
			}

			n += jiafen(count, ncount);
			n += njiafen(count, ncount);
			count = ncount = 0;
		}
	}
	if (n < 5000) //若分数很低时,考虑落子位置,给予一定的分数,落子越中间分数越高
	{
		if (i <= 7)
			n += i + 1;
		else
			n += MAXIUM - i;
		if (j <= 7)
			n += j + 1;
		else
			n += MAXIUM - j;
	}
	return n; //返回得分
}

int jiafen(int n, int m) //对己方的得分
{
	int p = 0;			  //分数
	if (m == 0 && n != 0) //当5连组合中没有对方的子,且己方有子(若己方无子得0分)
	{
		switch (n)
		{ //子越多分数越高
		case 4:
			p = 9999999;
			break;
		case 3:
			p = 99999;
			break;
		case 2:
			p = 999;
			break;
		case 1:
			p = 99;
			break;
		default:
			p = 0;
			break;
		}
	}
	return p; //返回得分
}

int njiafen(int n, int m) //终结对方的得分
{
	int p = 0;
	if (n == 0 && m != 0) //当5连组合中有对方的子,且没有己方的子,
						  //考虑这种5连组合的时候,不用想是否两头都堵住了,只要有一个己方的子,
						  //该组合对方就不可能成5,只能在其他组合中找机会.
	{
		switch (m)
		{
		case 4:
			p = 8888888;
			break;
		case 3:
			p = 88888;
			break;
		case 2:
			p = 888;
			break;
		case 1:
			p = 8;
			break;
		default:
			p = 0;
			break;
		}
	}
	return p; //返回得分
}

void jinshou()
{
	int i, j;
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
		{
			if (Round % 2)
			{
				if (board[i][j] == 3)
					board[i][j] = 0;
			}
			else
			{
				if (board[i][j] == 0)
					board[i][j] = getjin(i, j, 1);
			}
		}
}

void qimingzihaomafan(int n, int m)
{
	if (m == 0 && n != 0)
	{
		switch (n)
		{
		case 3:
			si++;
			break;
		case 2:
			san++;
			break;
		default:
			break;
		}
	}
}

int getjin(int i, int j, int k)
{
	int huosan = 0;
	int huosi = 0;
	int count = 0;  //当前统计的5连组合中自己子的个数
	int ncount = 0; //当前统计的5连组合中对方子的个数
	int t, p;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++) //向上下(p确定5连组合的位置,p越大组合越靠下)
	{
		if (j - p < 0) //若最低位置已近低于棋盘下界,跳出循环,统计其他方向的得分
			break;
		else if (j - p + 4 >= MAXIUM) //若最高位置高于棋盘的上界,忽略后续部分,p直接加1,统计位置低一些的组合的得分
			continue;
		else //位置正常
		{
			for (t = 0; t < 5; t++) //统计五连组合中的每个子
			{
				if (board[i][j - p + t] == k)
					count++; //若为己方的
				else if (board[i][j - p + t] == 3 - k)
					ncount++; //若为对方的
			}
			qimingzihaomafan(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si > 0)
		huosi++;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++) //向左右
	{
		if (i - p < 0)
			break;
		else if (i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j] == k)
					count++;
				else if (board[i - p + t][j] == 3 - k)
					ncount++;
			}
			qimingzihaomafan(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si > 0)
		huosi++;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++) //向左下右上
	{
		if (j - p < 0 || i - p < 0)
			break;
		else if (j - p + 4 >= MAXIUM || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j - p + t] == k)
					count++;
				else if (board[i - p + t][j - p + t] == 3 - k)
					ncount++;
			}
			qimingzihaomafan(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si > 0)
		huosi++;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++) //向左下右上
	{
		if (j + p >= MAXIUM || i - p < 0)
			break;
		else if (j + p - 4 < 0 || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++) //向左上右下
			{
				if (board[i - p + t][j + p - t] == k)
					count++;
				if (board[i - p + t][j + p - t] == 3 - k)
					ncount++;
			}
			qimingzihaomafan(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si > 0)
		huosi++;
	san = 0;
	si = 0;
	if (huosan > 1 || huosi > 1)
		return 3;
	else
		return 0;
}
//算法部分结束