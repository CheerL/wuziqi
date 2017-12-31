#include "head/wzq.h"

//记录处理部分(链表结构)
struct record* newrecord()//创造新记录节点
{
	struct record* r = (struct record*)malloc(sizeof(struct record));//申请一个节点对象
	r->next = NULL;//给予前后节点初值NULL
	r->back = NULL;
	return r;//返回记录指针
}

void Addrecord(int i, int j)//添加记录
{
	renow->cursor.x = i;//记录坐标
	renow->cursor.y = j;

	if (!readmodel)//当不是读棋谱模式,写入文件
		dofile();
	board[i][j] = turn(Round);//相应位置落子
	cursor.x = i;
	cursor.y = j;

	renow->next = newrecord();//创建下一个记录节点

	reback = renow;//当前记录推至下一个记录节点	
	renow = renow->next;
	renow->back = reback;
}
//记录处理部分结束
