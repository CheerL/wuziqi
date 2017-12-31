#include "head/wzq.h"

//�ļ�������
void getfilename()//����ļ���
{
	getnowtime();//���ʱ���ַ���
	strcat(filename, "record/qipu ");
	strcat(filename, nowtime);
	strcat(filename, ".txt");//�õ������ļ��� ���� qipu 2015-1-1 1-1-1.txt
}

void dofile()//�Ѽ�¼д���ļ�
{
	file = fopen(filename, "at+");//�Կɶ�д���ļ�,���ļ��������,�������򴴽�(filenameΪǰ��õ����ļ���)
	if (file != NULL)//���ɹ����ļ�,����ʲôҲ����
	{
		char a[50] = "\n";//�ַ���aΪ��Ҫд���ļ�������,��ʼ��
		char r[3];
		char x[3], y[3];
		strcat(a, iitoa(Round, r, 10));//����غ���
		strcat(a, "\t");
		strcat(a, iitoa(renow->cursor.x + 1, x, 10));//���������
		strcat(a, " ");
		strcat(a, iitoa(renow->cursor.y + 1, y, 10));//����������
		strcat(a, " ");
		strcat(a, " ");
		strcat(a, "\t");
		strcat(a, nowtime);//����ʱ��
		fwrite(a, strlen(a), 1, file);//д���ļ�
		fclose(file);//�ر��ļ�
	}
}

void del()//����ʱɾ���ļ����һ��
{
	FILE *fin, *fout;//�ļ�ָ��
	//������	
	int c;
	int count = 0;
	int ncount = 0;

	fin = fopen(filename, "r");//��ֻ�����ļ�(��ǰ��¼�ļ�)
	//�����ж�����
	while (1) {
		c = fgetc(fin);
		if (EOF == c) break;
		if ('\n' == c) count++;
	}

	fclose(fin);//�ر�

	fin = fopen(filename, "r");//���´��ļ�
	fout = fopen("t.tmp", "w");//��һ����ʱ�ļ�
	//����ǰ��¼�ļ�������ȫд����ʱ�ļ�,�������һ��
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
	fclose(fin);//�ص������ļ�
	fclose(fout);
	remove(filename);//ɾ����¼�ļ�
	rename("t.tmp", filename);//����ʱ�ļ�������Ϊ��¼�ļ�ԭ��������
}

void readqipu()//������ģʽ
{
	readmodel = 1;//��ģʽ����
	char c;
	int count = 0;
	int ncount = 0;
	char x[2], y[2];
	int i = 0, j = 0;
	file = fopen(filename, "r");//���ļ�
	//����Ϊ�ҵ��ļ�ÿ�м�¼�µĺ�������,�ǵ��ַ�����
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
				if (i == 1)	i = x[0] - '0';//�������ַ���������ݸĳ�int
				else i = 10 + (int)x[1] - 48;
				if (j == 1)	j = y[0] - '0';
				else j = 10 + (int)y[1] - 48;
				Addrecord(i - 1, j - 1);//��Ӽ�¼
				Round++;//�غ�����1
			}
		}
	}
	//���˶����ļ�,Ҳ�Ѽ�¼�������Ӧ���������������
	fclose(file);//�ص��ļ�
	readmodel = 0;//�˳�������ģʽ
	printboard();
	huifang();//����ط�ģʽ
}

void huifang()//�ط�
{
	char tempname[50];//��ʱ�ļ���,�洢ԭ�����ļ���(��ǰ��¼�ļ��ļ����ᱻ�ı�,�������tmp)
	strcpy(tempname, filename);
	strcat(filename, "tmp");
	//�طſ���
	while (1)
	{
		//getchar();
		printboard();
#ifdef WIN32
		printf("\n          ��������ƻط�,ESC�˳��طŲ��ӵ�ǰ��ʼ��Ϸ");
#else
		printf("\n��������ƻط�,ESC�˳��طŲ��ӵ�ǰ��ʼ��Ϸ"); 	
#endif	
		if (huifangkongzhi())//����طſ���
			break;
	}
	printboard();
	//�ѵ�ǰ�طŵ���λ�ú�ļ�¼��������ɾȥ
	reback = renow->back;
	reback->next = newrecord();
	renow = reback->next;
	renow->back = reback;
	//�˵�����ͷ,�غ�����Ϊ1
	renow = head->next;
	Round = 1;
	//д�����ļ�,����ǰ��¼��һ���ǿ�,�Ѽ�¼д���ļ���,��ǰ��¼�ƽ�����һ��
	while (renow->next != NULL)
	{
		dofile();
		renow = renow->next;
		Round++;
	}

	remove(tempname);//ɾ���ļ�
	rename(filename, tempname);//�������ļ�
	memset(filename, 0, sizeof(filename));//����ļ���
	strcpy(filename, tempname);//�Ļ�ԭ�����ļ���
}

int huifangkongzhi()//�طſ���
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
			case 183://��
			case 186://��
				if (renow->back->back != NULL)
				{
					renow = renow->back;//�˵���һ����¼
					board[renow->cursor.x][renow->cursor.y] = 0;
					Round--;
				}
				else
					goto A;
				break;
			case 184://��
			case 185://��
				if (renow->next != NULL)
				{

					board[renow->cursor.x][renow->cursor.y] = turn(Round);
					renow = renow->next;//�Ƶ���һ����¼
					Round++;
				}
#else
			case 72://��
			case 75://��
				if (renow->back->back != NULL)
				{
					renow = renow->back;
					board[renow->cursor.x][renow->cursor.y] = 0;
					Round--;
				}
				else
					goto A;
				break;
			case 80://��
			case 77://��
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
//�ļ������ֽ���
