#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


#define MAXIUM 15

#ifdef WIN32
	#include <conio.h>
	#include <io.h>
    #include <direct.h>
    #define mkdirs(path) _mkdir(path)
	#define _printspace printf("                            ");
	#define sleep _sleep(sleeptime);
	#define cls system("cls");

#else
	#include <unistd.h>  
	#include <getopt.h>
	#include <sys/select.h>
	#include <termios.h>
	#include <fcntl.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #define mkdirs(path) mkdir(path, 0777)
	#define _printspace printf("             ");
	#define cls system("clear");

	int getch(void);
	int kbhit(void);
#endif

FILE* file;//ָ���ļ���ָ��
int board[MAXIUM][MAXIUM];//����
int Round;//�غ���
int model[4];//��Ϸģʽ
int sleeptime;//������ս��ͣʱ��
char filename[50];//�ļ���
char nowtime[50];//��ǰʱ��
int readmodel;//����¼ģʽ
int xingqimodel;//����ģʽ

struct cursor{//����ṹ
	int x, y;
};
struct cursor cursor;//���ӵ�λ��

typedef struct record{//�����¼
	struct cursor cursor;//����ṹ
	struct record* next;//ָ����һ����¼��ָ��
	struct record* back;//ָ����һ����¼��ָ��
}Record;

struct record* head;//����ͷ
struct record* renow;//��ǰ��¼
struct record* reback;//��һ����¼


#define pause printf("�����������\n");getch(); 
#define _printn printf("\n");//���ĵĺ궨��
#define _turns  if (Round % 2) printf("�ڷ��غ�");else  printf("�׷��غ�");//�ڰ׷��غ��ж�
#define getdate memset(nowtime,0,sizeof(nowtime));getnowtime(); printf("%s",nowtime)//��ȡ��ǰʱ��
//memset����������� getnowtime������˵��

//������������
void backrecord();
void printboard();
void readqipu(void);
char* getStyle(int i, int j);
int iswin();
void win();
void initial(void);
void move();
void change(void);
void dkaiju(int a);
void ikaiju(int a);
void kaiju(void);
void getnowtime();
int turn(int r);
int getscore(int i, int j, int k);
int panfen(char temp);
char fanhui(int i, int j, int k);
void clearrecord(struct record* head);
void Addrecord(int i, int j);
struct record* newrecord();
void modelchoose(void);
char* iitoa(int num, char *str, int radix);
void dofile();
void getfilename();
char charrecord();
void del();
void mainsuanfa(void);
int jiafen(int n, int m);
int njiafen(int n, int m);
void replay();
void huifang();
int huifangkongzhi();
void tishi();
void jinshou();
int getjin(int i, int j, int k);
void qimingzihaofan(int n,int m);
//�����������ֽ���
//ͷ�ļ����ֽ���
