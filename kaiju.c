#include "head/wzq.h"

//ָ�����ֲ���
void kaiju(void)
{
	printboard();
	char key1;
	char key2;
	int key3[2];
	if (model[1] == 3)
	{
		char c;
		c = getchar();
	}
#ifndef WIN32
	printf("\n    ");
	printf("����  z+i/d+����  ָ������");
	printf("\n         ");
	printf("���س�������");
#else
	printf("\n                    ");
	printf("����z+i/d+����ָ������");
	printf("\n                        ");
	printf("���س�������");
#endif
	while (1)
	{
		if (kbhit())
		{
			//ת������
			if ((key1 = getch()) == 'z')
			{
				printboard();
				printf(" %c", key1);
				key2 = getchar();
				key3[0] = getchar() - '0';
				key3[1] = getchar() - '0';
				if (key3[1] >= 0)
					key3[0] = key3[0] * 10 + key3[1];
				if (key3[0] > 13 || key3[0] < 1 || (key2 != 'i'&&key2 != 'd'))//������Ҫ�������
				{
					printboard();
					printf(" ��������");
#ifndef WIN32
					_printn printf("          ");
#else
					_printn _printspace
#endif
					printf("���س���������");
#ifdef WIN32
					while (getch() == '\r')
#else
					while (getch() == '\n')
#endif
					{
						return kaiju();
					}
				}
				if (key2 == 'i')
					return ikaiju(key3[0]);//����бָ���ֵ�ѡ��
				if (key2 == 'd')
					return dkaiju(key3[0]);//����ֱָ���ֵ�ѡ��
			}
#ifdef WIN32
			else if (key1 == '\r')//���˳�
#else
			else if (key1 == '\n')//���˳�
#endif
			{
				printboard();
				break;
			}
		}
	}
}

void ikaiju(int a)//бָ����
{
	Round = Round + 1;
	board[7][7] = 1;
	board[8][8] = 2;
	if (a >= 1 && a <= 5)
		board[9][10 - a] = 1;
	else if (a > 5 && a <= 8)
		board[8][13 - a] = 1;
	else if (a > 8 && a <= 10)
		board[7][MAXIUM - a] = 1;
	else if (a > 10 && a <= 12)
		board[6][17 - a] = 1;
	else if (a = 13)
		board[5][5] = 1;
	printboard();
	change();//�������ֻ���
	printboard();
}

void dkaiju(int a)//ֱָ����
{
	Round = Round + 1;
	board[7][7] = 1;
	board[7][8] = 2;
	if (a >= 1 && a <= 3)
		board[6 + a][9] = 1;
	else if (a > 3 && a <= 5)
		board[7 + (a - 3)][8] = 1;
	else if (a > 5 && a <= 7)
		board[7 + (a - 5)][7] = 1;
	else if (a > 7 && a <= 10)
		board[6 + (a - 7)][6] = 1;
	else if (a > 10 && a <= 13)
		board[6 + (a - 10)][5] = 1;
	printboard();
	change();//�������ֻ���
	printboard();

}

void change(void)//���ֻ���
{
	char key[2];
#ifndef WIN32
	printf("\n          ");
	printf("����hh���л���");
	printf("\n           ");
	printf("���س�������");
#else
	printf("\n                         ");
	printf("����hh���л���");
	printf("\n                        ");
	printf("���س�������");
#endif
	while (1)
	{
		if (kbhit())
		{
			//ת������
			printboard();
#ifdef WIN32
			if ((key[0] = getch()) != '\r')
#else
			if ((key[0] = getch()) != '\n')
#endif
			{
				printf(" %c", key[0]);

#ifdef WIN32
				if ((key[1] = getch()) != '\r')
#else
				if ((key[1] = getch()) != '\n')
#endif
					printf("%c", key[1]);
				else break;

				if (key[0] == 'h'&&key[1] == 'h')//��������hh
				{
					Round = Round + 1;//�׷��л����ڷ�
					break;
				}
			}
			else//����Ҫ��������
				break;
		}
	}
}
//ָ�����ֲ��ֽ���
