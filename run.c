#include "head/wzq.h"

//���в���
int turn(int r)//�ӻغ�������һ��ֵ�������ڰ׷�,�������ӵ�
{
	if (r % 2)
		return 1;//�ڷ�
	else
		return 2;//�׷�
}

void move()//����
{
	int c;
	if (model[1] == 3)//������ս
	{
		mainsuanfa();//�����㷨������һ����
		win(cursor.x, cursor.y);//�ж�ʤ��
		printboard();
#ifndef WIN32
		printf("\n           ���س�����ͣ\n            ��ESC�˳�");
#else
		printf("\n                        ���س�����ͣ\n                          ��ESC�˳�");
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
				printf("\n         ��������ص���Ϸ\n"); 
#else
				cls;
				printboard();
				printf("\n                       ��������ص���Ϸ\n");
#endif
				while (1)	{ if (getch() != 0) break; }
			}//�س�
			else if (c == 27) return replay();//ESC������Ϸ
		}
		
		sleep(sleeptime);//��ͣ
	}
	else
	{

		int key1, key2, key3;
		int num;
		if (kbhit())//���а���
		{
			printboard();
			printf(" ");
			key1 = getch();
			if (key1 == 27)//��ESC���¿�ʼ
				replay();
			else if (key1 == 'z')//��z����
			{
				if (reback->back != NULL)//��һ����¼���ǿ�ʱ
				{
					backrecord();//����
					if (model[1] == 2)//���˻�ʱ
						backrecord();//�ٻ�һ����
					printboard();
				}
			}
			else if (key1 <= 'o'&&key1 >= 'a')//��һ��������a��o�е�ĳ����ĸ
			{
				printf("%1c", key1);
			A: key2 = getch();
				if ((key2 >= '1'&&key2 <= '9') || (key2 >= 'a'&&key2 <= 'f'))//�ڶ���������1��9����a��f
				{
					printf("%c", key2);
#ifndef WIN32
					if ((key3 = getch()) != '\r')//���������벻�ǻس����������
#else
					if ((key3 = getch()) != '\n')//���������벻�ǻس����������
#endif
					{
						if (key2 == '1')//ֻ�е��ڶ���������1�ż�������
						{
							printf("%c", key3);
#ifndef WIN32
							while (getch() == '\r')//����������ַ���ֻ�е�������س��ż���������ȥ
#else
							while (getch() == '\n')//����������ַ���ֻ�е�������س��ż���������ȥ
#endif
								break;
						}
					}

					//ת��key2��key3Ϊ����

					if (key2 <= 'f'&&key2 >= 'a')					//���������a��f
						num = key2 - 'a' + 10;
					else if (key3 >= '0' && key3 <= '5'&&key2 == '1')//���������10��15
						num = 10 * (key2 - '0') + (key3 - '0');
					else											//���������1��9
						num = key2 - '0';

					if (!board[key1 - 'a'][num - 1])				//������Ķ�Ӧλ��û������
					{
						Addrecord(key1 - 'a', num - 1);	//��������¼
						if (model[3]==1)
							jinshou();//�����ж�
						win(cursor.x, cursor.y);	//�ж�ʤ��
						if (model[1] == 2)			//���˻�ģʽ
						{
							mainsuanfa();			//�����㷨������һ����
							win(cursor.x, cursor.y);		//�ж�ʤ��
							printboard();
						}
						else		//������ģʽ
							printboard();
					}
				}
				else goto A;				//���ڶ������벻����Ҫ������������
			}

		}

	}
}

void modelchoose(void)//ģʽѡ��
{
	W:printf("��1��ʼ����Ϸ\n��2��������\n��3�鿴����\n��ESC�˳�����\n");
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
	A:	printf("�����ļ���(��: qipu 2015-1-1 1-1-1.txt)\n");
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
			printf("�ļ�������\n��1���������ļ���\n��2��ʼ����Ϸ\n");
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
		printf("��1��ʼ���˶�ս\n��2��ʼ�˻���ս\n��ESC�ص���һ��\n");
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
	B:	printf("��1��ʼ���˶�ս\n��2��ʼ�˻���ս\n��3��ʼ������ս(����ģʽ)\n��ESC�ص���һ��\n");
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
			printf("��1ѡ��ڷ�\n��2ѡ��׷�\n��ESC�ص���һ��\n");
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
			printf("ϣ�����Զ����һ����(s)\n");
			scanf("%d", &sleeptime);
#else
			printf("ϣ�����Զ����һ����(ms)\n");
			scanf("%d", &sleeptime);
#endif
		}
	}
	printf("��1ѡ��ڷ�����\n��2������\n");
	while (model[3] != 1 && model[3] != 2)
	{
		model[3] = getch() - '0';
	}
	printf("%d\n", model[3]);
}

void win(int a, int b)//�ж�ʤ��
{
	if (iswin(a, b))//����ʤ
	{
		if (turn(Round) == 1)//�ж��ķ���ʤ
		{
			printboard();
			printf("�ڷ�ʤ��");
		}
		else
		{
			printboard();
			printf("�׷�ʤ��");
		}
		replay();//���¿�ʼ��Ϸ
	}
	Round++;//����غ�����1
}

int iswin(int a, int b)//�ж�ʤ��(a,bΪ����)
{
	int w = 1, x = 1, y = 1, z = 1;
	int	i;
	int k = turn(Round);
	for (i = 1; i<5; i++)if (b + i<MAXIUM&&board[a][b + i] == k)w++; else break;//���¼��
	for (i = 1; i<5; i++)if (b - i >= 0 && board[a][b - i] == k)w++; else break;//���ϼ��
	if (w >= 5)return 1;

	for (i = 1; i<5; i++)if (a + i<MAXIUM&&board[a + i][b] == k)x++; else break;//���Ҽ��
	for (i = 1; i<5; i++)if (a - i >= 0 && board[a - i][b] == k)x++; else break;//������
	if (x >= 5)return 1;

	for (i = 1; i<5; i++)if (a + i<MAXIUM&&b + i<MAXIUM&&board[a + i][b + i] == k)y++; else break;//�����¼��
	for (i = 1; i<5; i++)if (a - i >= 0 && b - i >= 0 && board[a - i][b - i] == k)y++; else break;//�����ϼ��
	if (y >= 5)return 1;

	for (i = 1; i<5; i++)if (a + i<MAXIUM&&b - i >= 0 && board[a + i][b - i] == k)z++; else break;//�����ϼ��
	for (i = 1; i<5; i++)if (a - i >= 0 && b + i<MAXIUM&&board[a - i][b + i] == k)z++; else break;//�����¼��
	if (z >= 5)return 1;

	return 0;//��û�м�鵽�������򷵻�0,��ʾ��û���ʤ��
}

void replay()//���¿�ʼ��Ϸ
{
	int i;
	printf("\n��1���¿�ʼ��Ϸ      ��2�˳�\n");
	int t=0;
	while (t != 1 && t != 2)
	{
		t = getch() - '0';
	}
	printf("%d\n", t);
	if (t == 1)//�����¿�ʼ
	{
		memset(model, 0, sizeof(model));//��ձ�������
		memset(nowtime, 0, sizeof(nowtime));
		memset(filename, 0, sizeof(filename));
		for (i = 0; i < MAXIUM; i++)
			memset(board[i], 0, sizeof(board[i]));//�������
		initial();//�����ʼ��
	}
	else{		//������������
		pause;
		exit(0);
	}
}

void backrecord()//����
{

	board[reback->cursor.x][reback->cursor.y] = 0;//��һ������λ������
	reback = reback->back;//���ϸ���¼��ֵ����һ����¼
	renow->back = reback;//��ǰ��¼���ϸ���¼ָ�� ԭ�������ϸ���¼
	reback->next = renow;//��ǰ��¼���ϸ���¼(ԭ�������ϸ���¼)���¸���¼ָ��ǰ��¼ !@#$%^&*(   �������ڲ�����¼����,�ƿ����Ƶ�
	Round--;//�غ�����1
	del();//ɾ���ļ�����Ӧ��¼
}
//���в��ֽ���

char* join(char *s1, char *s2)  
{  
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator  
    //in real code you would check for errors in malloc here  
    if (result == NULL) exit (1);  
  
    strcpy(result, s1);  
    strcat(result, s2);  
  
    return result;  
}