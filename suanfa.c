#include "head/wzq.h"

//�㷨����
int san, si;

void mainsuanfa(void)//���������㷨
{
	if (Round == 1)//��һ�غ�ֱ����h8
		Addrecord(7, 7);
	else if (Round == 2)//�ڶ��غ�
	{
		if (board[7][7] == 0)//��h8������,�µ�h8
			Addrecord(7, 7);
		else				//�������µ�i9
			Addrecord(8, 8);
	}
	else
	{
		/*
		�ȶԵ�ǰ��������ж�,��ÿһ��δ���ӵ�λ��,�����ڴ˴����ӵĵ÷�;
		����������õ÷�λ��,����Щλ����Best[255][2]������,��w��(0��w-1);
		��w=0,�����(ֻ����������������),��w����0,�����Щ���λ�ý���ѡ��;
		����Best[q]������,��Է���ͬ���㷨����õ÷� (q��0ȡ��w-1);
		��ȡ���Է���õ÷�����ͷ�,�������q,�����ѡ����daixuan[255];
		��ȡ��0��w-1,�õ�i��q,���ȡһ��Ϊbestnum(��ʹw=1,Ҳ���Խ�����������);
		��Best[bestnum]Ϊ�����Լ��÷����ͬʱ�Է��÷���͵�����λ��,����Ӧλ�����Ӳ��˳�;
		(�����ǿ�������ͬ�ķ�ʽ�����ж����׼ȷ�����λ��,����͵�������ѡ��.)
		*/
		srand((unsigned int)time(NULL));//�������
		int i, j;
		int s, t;
		int q = 0, w = 0;//������
		int now[3] = { 0, 0 ,0};//��ǰ�÷�
		int best[3] = { -1000000, -1000000, -1000000 };//��ǰ��õ÷� (��ʼ���� �� �ķ������㸲��)
		int fbest = 100000000;//�Է���õ÷�����ͷ�  (��ʼ���� �� �ķ������㸲��)
		int Best[255][2];//�����λ�õ�����,Best[i][0]Ϊ������,Best[i][1]Ϊ������
		int daixuan[255];//��ѡ����
		int bestnum;
		int k = turn(Round);//�غ��ж�

		for (i = 0; i < MAXIUM; i++)//ȡ������
			for (j = 0; j < MAXIUM; j++)
			{
				if (board[i][j] == 0 || (board[i][j] == 3&&k==2))//����������
				{
					now[0] = getscore(i, j, k);//���
					if (best[0] < now[0])//����ǰ�÷ֱ���õ÷ָ�,���
					{
						best[0] = now[0];
						Best[0][0] = i;
						Best[0][1] = j;
						w = 1;				//����������
					}
					else if (best[0] == now[0])//����ǰ�÷ֱȵ�����õ÷�,����
					{
						Best[w][0] = i;
						Best[w][1] = j;
						w++;				//��������1
					}
				}
			}
		if (w == 0)
		{
			printf("ƽ��\n");
			return replay();
		}
		for (q = 0; q < w; q++)//��w�����λ�ý���ѡ��
		{
			board[Best[q][0]][Best[q][1]] = k;//��������Ӧλ������
			for (s = 0; s < MAXIUM; s++)//ȡ������
				for (t = 0; t < MAXIUM; t++)
				{
					if (board[s][t] == 0 || (board[s][t] == 3 && k == 2))//����������
					{
						now[1] = getscore(s, t, 3 - k);//���
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

			if (fbest > best[1])//�ж϶Է���ߵ÷��Ƿ����,����,���
			{
				fbest = best[1];
				daixuan[0] = q;//����λ�ø���Ϊ��ѡ����ĵ�һ��
				i = 1;//����������
			}
			else if (fbest == best[1])//��������͵÷�
				daixuan[i++] = q;//�����ѡ����,ͬʱ��������1

			board[Best[q][0]][Best[q][1]] = 0;//�������µ���ȥ��
		}
		if (i)//��i����0,����ֹһ�����λ��,���ѡ��һ��
			bestnum = (int)(rand() % i);
		else//��ֻ��һ��
			bestnum = 0;

		Addrecord(Best[bestnum][0], Best[bestnum][1]);//��������¼
		if (model[3] == 1)
			jinshou();//�����ж�
	}
}

int getscore(int i, int j, int k)//�зֺ���,i,jΪ����,kΪ�غ��жϵ�ֵ(�ڷ�Ϊ1,�׷�Ϊ2)
{
	/*
	�γ�5��Ϊʤ,ÿ���ӿ��Գ�Ϊ5����ϵĵ�1����,��2����,����,��5����(����Ϊ��,+��ʾ��ǰ��,+----,-+---,����,----+);
	���к�,��,��б,��б4������,��һ������������20��5�������(5����������Լ��������-_-,Ӧ�ò����������);
	ÿ���ӵĵ÷�Ϊ ��ÿ������5����ϵĹ��׵ĵ÷ֺ�+�ж϶Է�������ϵĵ÷ֺ�;
	*/

	int n = 0;//�÷�
	int count = 0;//��ǰͳ�Ƶ�5��������Լ��ӵĸ���
	int ncount = 0;//��ǰͳ�Ƶ�5������жԷ��ӵĸ���
	int t, p;
	for (p = 0; p < 5; p++)//������(pȷ��5����ϵ�λ��,pԽ�����Խ����)
	{
		if (j - p < 0)//�����λ���ѽ����������½�,����ѭ��,ͳ����������ĵ÷�
			break;
		else if (j - p + 4 >= MAXIUM)//�����λ�ø������̵��Ͻ�,���Ժ�������,pֱ�Ӽ�1,ͳ��λ�õ�һЩ����ϵĵ÷�
			continue;
		else//λ������
		{
			for (t = 0; t < 5; t++)//ͳ����������е�ÿ����
			{
				if (board[i][j - p + t] == k)	count++;//��Ϊ������
				else if (board[i][j - p + t] == 3 - k || board[i][j - p + t] == 3)	ncount++;//��Ϊ�Է���
			}
			n += jiafen(count, ncount);//��ǰ�������϶Լ����ĵ÷�
			n += njiafen(count, ncount);//��ǰ���������ս�Է��ĵ÷�
			count = ncount = 0;//����������
		}
	}

	for (p = 0; p < 5; p++)//������
	{
		if (i - p < 0)
			break;
		else if (i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j] == k)	count++;
				else if (board[i - p + t][j] == 3 - k || board[i][j - p + t] == 3)	 ncount++;
			}
			n += jiafen(count, ncount);
			n += njiafen(count, ncount);
			count = ncount = 0;
		}
	}

	for (p = 0; p < 5; p++)//����������
	{
		if (j - p < 0 || i - p < 0)
			break;
		else if (j - p + 4 >= MAXIUM || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j - p + t] == k)	count++;
				else if (board[i - p + t][j - p + t] == 3 - k || board[i][j - p + t] == 3)	 ncount++;
			}
			n += jiafen(count, ncount);
			n += njiafen(count, ncount);
			count = ncount = 0;
		}
	}

	for (p = 0; p < 5; p++)//����������
	{
		if (j + p >= MAXIUM || i - p < 0)
			break;
		else if (j + p - 4 <0 || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)//����������
			{
				if (board[i - p + t][j + p - t] == k)	count++;
				if (board[i - p + t][j + p - t] == 3 - k || board[i][j - p + t] == 3)	 ncount++;
			}

			n += jiafen(count, ncount);
			n += njiafen(count, ncount);
			count = ncount = 0;
		}
	}
	if (n < 5000)//�������ܵ�ʱ,��������λ��,����һ���ķ���,����Խ�м����Խ��
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
	return n;//���ص÷�
}

int jiafen(int n, int m)//�Լ����ĵ÷�
{
	int p = 0;//����
	if (m == 0 && n != 0)//��5�������û�жԷ�����,�Ҽ�������(���������ӵ�0��)
	{
		switch (n){//��Խ�����Խ��
		case 4: p = 9999999; break;
		case 3: p = 99999; break;
		case 2: p = 999; break;
		case 1: p = 99; break;
		default: p = 0; break;
		}
	}
	return p;//���ص÷�
}

int njiafen(int n, int m)//�ս�Է��ĵ÷�
{
	int p = 0;
	if (n == 0 && m != 0)//��5��������жԷ�����,��û�м�������,
		//��������5����ϵ�ʱ��,�������Ƿ���ͷ����ס��,ֻҪ��һ����������,
		//����϶Է��Ͳ����ܳ�5,ֻ��������������һ���.
	{
		switch (m){
		case 4: p = 8888888; break;
		case 3: p = 88888; break;
		case 2: p = 888; break;
		case 1: p = 8; break;
		default: p = 0; break;
		}
	}
	return p;//���ص÷�
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
		switch (n){
		case 3: 
			si++; break;
		case 2: 
			san++; break;
		default:  break;
		}
	}
}

int getjin(int i, int j, int k)
{
	int huosan = 0;
	int huosi = 0;
	int count = 0;//��ǰͳ�Ƶ�5��������Լ��ӵĸ���
	int ncount = 0;//��ǰͳ�Ƶ�5������жԷ��ӵĸ���
	int t, p;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++)//������(pȷ��5����ϵ�λ��,pԽ�����Խ����)
	{
		if (j - p < 0)//�����λ���ѽ����������½�,����ѭ��,ͳ����������ĵ÷�
			break;
		else if (j - p + 4 >= MAXIUM)//�����λ�ø������̵��Ͻ�,���Ժ�������,pֱ�Ӽ�1,ͳ��λ�õ�һЩ����ϵĵ÷�
			continue;
		else//λ������
		{
			for (t = 0; t < 5; t++)//ͳ����������е�ÿ����
			{
				if (board[i][j - p + t] == k)	count++;//��Ϊ������
				else if (board[i][j - p + t] == 3 - k)	ncount++;//��Ϊ�Է���
			}
			qimingzihaomafan(count,ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si>0)
		huosi++;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++)//������
	{
		if (i - p < 0)
			break;
		else if (i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j] == k)	count++;
				else if (board[i - p + t][j] == 3 - k)	 ncount++;
			}
			qimingzihaomafan(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si>0)
		huosi++;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++)//����������
	{
		if (j - p < 0 || i - p < 0)
			break;
		else if (j - p + 4 >= MAXIUM || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)
			{
				if (board[i - p + t][j - p + t] == k)	count++;
				else if (board[i - p + t][j - p + t] == 3 - k)	 ncount++;
			}
			qimingzihaomafan(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si>0)
		huosi++;
	san = 0;
	si = 0;
	for (p = 0; p < 5; p++)//����������
	{
		if (j + p >= MAXIUM || i - p < 0)
			break;
		else if (j + p - 4 <0 || i - p + 4 >= MAXIUM)
			continue;
		else
		{
			for (t = 0; t < 5; t++)//����������
			{
				if (board[i - p + t][j + p - t] == k)	count++;
				if (board[i - p + t][j + p - t] == 3 - k)	 ncount++;
			}
			qimingzihaomafan(count, ncount);
			count = 0;
			ncount = 0;
		}
	}
	if (san > 1)
		huosan++;
	if (si>0)
		huosi++;
	san = 0;
	si = 0;
	if ( huosan > 1 || huosi > 1)
		return 3;
	else
		return 0;
}
//�㷨���ֽ���