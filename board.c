#include "head/wzq.h"

//���̲���
char* getStyle(int i, int j)//��ȡ�����Ӧλ�õ�����
{
#ifndef WIN32
	if(!readmodel)	
	{
		if (i == reback->cursor.x&&j == reback->cursor.y)
		{
			if (board[i][j] == 1)//���ӵ�ǰ����
			{
				if (i == 14)
					return "\033[30m��\033[37;1m";
				else//��Եλ��
				{
					switch (j)
					{
					case 0:
						;
					case 14:
						return "\033[30m��\033[37;1m��";
						break;
					default:
						return "\033[30m��\033[37;1m��";
						break;
					}
				}
			}
			else//���ӵ�ǰ����
			{
				if (i == 14)
					return "��";
				else//��Եλ��
				{
					switch (j)
					{
					case 0:
						;
					case 14:
						return "�贈";
						break;
					default:
						return "�賓";
						break;
					}
				}
			}
		}
	}
	if (board[i][j] == 1)//1Ϊ����
	{
		if (i == 14)
			return "\033[30m��\033[37;1m";//"��".����Ϊ��ɫ����
		else//��Եλ��
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "\033[30m��\033[37;1m��";
				break;
			default:
				return "\033[30m��\033[37;1m��";
				break;
			}
		}
	}
	else if (board[i][j] == 2)//2Ϊ����
	{
		if (i == 14)
			return "��";
		else
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "��";
				break;
			default:
				return "��";
				break;
			}
		}
	}
	else if (board[i][j] == 3)
	{
		if (i == 14)
			return "�w";
		else//��Եλ��
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "�w��";
				break;
			default:
				return "�w��";
				break;
			}
		}
	}
#else
	if (!readmodel)
	{
		if (i == reback->cursor.x&&j == reback->cursor.y)
		{
			if (board[i][j] == 1)//���ӵ�ǰ����
			{
				if (i == 14)
					return "��";
				else//��Եλ��
				{
					switch (j)
					{
					case 0:
						;
					case 14:
						return "�贈";
						break;
					default:
						return "�賓";
						break;
					}
				}
			}
			else if(board[i][j] == 2)//���ӵ�ǰ����
			{
				if (i == 14)
					return "��";
				else//��Եλ��
				{
					switch (j)
					{
					case 0:
						;
					case 14:
						return "�";
						break;
					default:
						return "�";
						break;
					}
				}
			}
		}
	}
	if (board[i][j] == 1)//1Ϊ����
	{
		if (i == 14)
			return "��";
		else
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "��";
				break;
			default:
				return "��";
				break;
			}
		}
	}
	else if (board[i][j] == 2)//2Ϊ����
	{
		if (i == 14)
			return "��";
		else//��Եλ��
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "��";
				break;
			default:
				return "��";
				break;
			}
		}
	}
	else if (board[i][j] == 3)
	{
		if (i == 14)
			return "�w";
		else//��Եλ��
		{
			switch (j)
			{
			case 0:
				;
			case 14:
				return "�w��";
				break;
			default:
				return "�w��";
				break;
			}
		}
	}

#endif
	else if (board[i][j] == 0)//δ���ӵ�λ��
	{
		//��Ե
		if (i == 0 && j == 0)
			return "����";
		else if (i == MAXIUM - 1 && j == 0)
			return "��";
		else if (i == MAXIUM - 1 && j == MAXIUM - 1)
			return "��";
		else if (i == 0 && j == MAXIUM - 1)
			return "����";
		else if (i == 0)
			return "�ĩ�";
		else if (i == MAXIUM - 1)
			return "��";
		else if (j == 0)
			return "�۩�";
		else if (j == MAXIUM - 1)
			return "�ө�";

		return "�੤";//�м�Ŀ�λ
	}
	return NULL;
}

void printboard()//��ӡ���̺���
{
	cls;
	int i, j;
#ifndef WIN32
	_printn//�궨�� ����
	printf("%2d", MAXIUM);//��һ��
	for (i = 0; i < MAXIUM; i++) { printf(getStyle(i, 14)); }_printn
		for (j = 13; j > 0; j--)//������
		{
			printf("%2d", j + 1);
			for (i = 0; i < MAXIUM; i++){ printf(getStyle(i, j)); }_printn
		}

	printf("%2d", 1);//���һ��
	for (i = 0; i < MAXIUM; i++) { printf(getStyle(i, 0)); }

	_printn printf(" ");//��ĸ
	for (i = 0; i < MAXIUM; i++) { printf("%2c", i + 'a'); }

	_printn  //�غ���Ϣ _turnsΪ�ڰ׷��ж� getdateΪ��ʾʱ��(���ʼ�궨��)
		_turns printf("        "); getdate; _printn 
	if(xingqimodel) tishi();
	_printspace
#else
	printf("%2d", MAXIUM);//��һ��
	for (i = 0; i < MAXIUM; i++) { printf(getStyle(i, 14)); }
	printf("\n  ��");  for (i = 0; i<MAXIUM - 2; i++){ printf("  ��"); } printf("  ��\n");//�м��
	for (j = 13; j > 0; j--)//������
	{
		printf("%2d", j + 1);
		for (i = 0; i < MAXIUM; i++){ printf(getStyle(i, j)); }
		printf("\n  ��"); for (i = 0; i<MAXIUM - 2; i++){ printf("  ��"); } printf("  ��\n");//�м��
	}
	printf("%2d", 1);//���һ��
	for (i = 0; i < MAXIUM; i++) { printf(getStyle(i, 0)); }
	_printn
		for (i = 0; i < MAXIUM; i++) { printf("%4c", i + 'a'); }//��ĸ
	_printn  printf("               "); _turns printf("           "); getdate; _printn//�غ���Ϣ
	if(xingqimodel) tishi();
	_printspace

#endif
}

void getnowtime()//��õ�ǰʱ��(�ַ�����ʽ)
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = gmtime(&timep);
	char year[5], mon[3], day[3], hour[3], min[3], sec[3];
	//���ϲ��ֻ��һ���ṹ,�����е�ǰ�� �� �� �� ʱ �� �� (int)(����̵ĺ���)

	if ((p->tm_hour + 8) >= 24)//������,Сʱ����8,������24��һ��
	{
		p->tm_hour -= 24;
		p->tm_mday++;
	}

	strcat(nowtime, iitoa(1900 + p->tm_year, year, 10));//iitoa(a,b,c)Ϊ�� ����a �� c���� ��ת��Ϊ �ַ���b �ĺ���
	strcat(nowtime, "-");								//strcat(a,b)Ϊ�� �ַ���b �����ݼӵ� �ַ���a ���ĺ���
	strcat(nowtime, iitoa(1 + p->tm_mon, mon, 10));
	strcat(nowtime, "-");
	strcat(nowtime, iitoa(p->tm_mday, day, 10));
	strcat(nowtime, " ");
	strcat(nowtime, iitoa(p->tm_hour + 8, hour, 10));
	strcat(nowtime, "-");
	strcat(nowtime, iitoa(p->tm_min, min, 10));
	strcat(nowtime, "-");
	strcat(nowtime, iitoa(p->tm_sec, sec, 10));//�õ�������ʱ���ַ��� �� 2015-1-1 1-1-1
}

char *iitoa(int num, char *str, int radix)//iitoa(a,b,c)Ϊ�� ����a �� c���� ��ת��Ϊ �ַ���b �ĺ���(�����1)
{
	char  string[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char* ptr = str;
	int denom = 0;  //����
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
	printf("  ���������س�������  ��z����\n") ;
#else
	printf("                  ���������س�������  ��z����\n") ;
#endif
}
//���̲��ֽ���
