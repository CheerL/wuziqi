#include "head/wzq.h"

//��¼������(����ṹ)
struct record* newrecord()//�����¼�¼�ڵ�
{
	struct record* r = (struct record*)malloc(sizeof(struct record));//����һ���ڵ����
	r->next = NULL;//����ǰ��ڵ��ֵNULL
	r->back = NULL;
	return r;//���ؼ�¼ָ��
}

void Addrecord(int i, int j)//��Ӽ�¼
{
	renow->cursor.x = i;//��¼����
	renow->cursor.y = j;

	if (!readmodel)//�����Ƕ�����ģʽ,д���ļ�
		dofile();
	board[i][j] = turn(Round);//��Ӧλ������
	cursor.x = i;
	cursor.y = j;

	renow->next = newrecord();//������һ����¼�ڵ�

	reback = renow;//��ǰ��¼������һ����¼�ڵ�	
	renow = renow->next;
	renow->back = reback;
}
//��¼�����ֽ���
