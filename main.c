#include "head/wzq.h"

//main
int main(void)
{
	initial();//��ʼ����Ϸ
	while (1)
	{
		move();
	}
}

void initial(void)//��ʼ����Ϸ
{
#ifndef WIN32
	printf("\033[0m\033[37;1m");//������ɫ
#else
	system("title ������");//���ñ���
	system("mode con cols=63 lines=34");//���ô��ڴ�С
	system("color E0");//������ɫ
#endif
	cls;
	xingqimodel=0;
	//��ʼ�������¼��ز���
	if (access("record", 0) == -1) {
        mkdirs("record");
    }
	head = newrecord();
	renow = newrecord();
	reback = newrecord();
	head->next = renow;
	renow->back = head;
	reback = renow->back;
	Round = 1;//��һ�غ�
	modelchoose();//ģʽѡ��

	cls;
	if (model[0] == 1)//��Ϊ����Ϸ
	{
		getfilename();//��ȡ�ļ���
		if (model[1] == 2 && model[2] == 2)	{ Addrecord(7, 7); Round++; printboard(); }//��Ϊ�˻�ģʽ�����ִ��,ֱ�Ӵ�ӡ����
		else	kaiju();//�������ָ������
	}
	else if (model[0] == 2)//��������Ϸ,���������ģʽ
		readqipu();
	if (model[1] != 3)
		xingqimodel = 1;
	printf("��ʼ��Ϸ");
	
}

#ifndef WIN32
int kbhit(void)//���м����·���1,���򷵻�0,����Ƿ��а���
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

int getch(void) {  //����getchar,�������һ���ַ�,���ð��س�,�Ҳ�����ʾ����Ļ��
	//��getchar,scanf����ʱ,���԰��¾�������Ӧ,�Ҳ�����Ҳ�������������
	//�����ڲ�������,��طſ���,�����,����������������Ҳ���������е�
	//����ж�,����������Ҫ��,��printf����Ļ,�ҽ�����һ��,������ʾ,�������뵽����Ҫ��Ϊֹ
	struct termios tm, tm_old;
	int fd = STDIN_FILENO, c;
	if (tcgetattr(fd, &tm) < 0)
		return -1;
	tm_old = tm;
	cfmakeraw(&tm);
	if (tcsetattr(fd, TCSANOW, &tm) < 0)
		return -1;
	c = fgetc(stdin);
	if (kbhit()){
		c += getch();
	}
	if (tcsetattr(fd, TCSANOW, &tm_old) < 0)
		return -1;
	return c;
}
#endif
//����
//main����