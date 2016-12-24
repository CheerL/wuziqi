#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


#define MAXIUM 15

#ifdef WIN32
#include <conio.h>
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
#define _printspace printf("             ");
#define cls system("clear");

int getch(void);
int kbhit(void);
#endif

FILE* file;//指向文件的指针
int board[MAXIUM][MAXIUM];//棋盘
int Round;//回合数
int model[4];//游戏模式
int sleeptime;//机机对战暂停时间
char filename[50];//文件名
char nowtime[50];//当前时间
int readmodel;//读记录模式
int xingqimodel;//行棋模式

struct cursor{//坐标结构
	int x, y;
};
struct cursor cursor;//落子的位置

typedef struct record{//行棋记录
	struct cursor cursor;//坐标结构
	struct record* next;//指向下一个记录的指针
	struct record* back;//指向上一个记录的指针
}Record;

struct record* head;//链表头
struct record* renow;//当前记录
struct record* reback;//上一个记录


#define pause printf("按任意键继续\n");getch(); 
#define _printn printf("\n");//无聊的宏定义
#define _turns  if (Round % 2) printf("黑方回合");else  printf("白方回合");//黑白方回合判断
#define getdate memset(nowtime,0,sizeof(nowtime));getnowtime(); printf("%s",nowtime)//获取当前时间
//memset用于清空数组 getnowtime后面再说明

//函数声明部分
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
//函数声明部分结束
//头文件部分结束
