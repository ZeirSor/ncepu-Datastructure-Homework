//120211080526 张烁
/*
	二叉树的层次遍历及应用。
	字符串数据采用二叉链表存储，完成功能：
		1）基于层次读边法创建二叉链表；
		2）进行层次遍历，并输出；
		3）基于层次法求二叉树的宽度。
*/

/*
	测试样例
			一  #
				a1
				0
				a1
				b1
				0
				a1
				c1
				1
				b1
				d1
				0
				b1
				e1
				1
				#
				#
				#

			二  #
				a1
				0
				a1
				c1
				0
				a1
				d1
				1
				c1
				e1
				1
				d1
				f1
				0
				d1
				g1
				1
				g1
				h1
				1
				#
				#
				#
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* input();
typedef struct BiNode
{
	char data[20];
	struct BiNode* lc;
	struct BiNode* rc;
}BiNode, *BiTree;

typedef struct QNode
{
	BiTree Qdata;
	struct QNode* next;
}QNode, *Qptr;

typedef struct
{
	Qptr front, rear;
}Queue;

void InitQueue(Queue* Q)
{
	Q->front = Q->rear = (QNode*)malloc(sizeof(QNode));
	Q->front->next = NULL;
}

void EnQueue(Queue* Q, BiNode* e)
{
	QNode* p = (QNode*)malloc(sizeof(QNode));
	p->Qdata = e;
	
	p->next = Q->rear->next;
	Q->rear->next = p;
	Q->rear = p;
}

void DeQueue(Queue* Q)
{
	QNode* p = Q->front->next;
	if (Q->front == Q->rear)
		return;
	if (Q->front->next == Q->rear)
		Q->rear = Q->front;
	Q->front->next = p->next;
	
	free(p);
}

int IsEmpty(Queue Q)
{
	if (Q.front == Q.rear)
		return 1;
	return 0;
}

BiTree GetHead(Queue Q)
{
	if (!IsEmpty(Q))
		return Q.front->next->Qdata;
	return NULL;
}

int GetLengthQueue(Queue Q)
{
	Qptr p = Q.front;
	int j = 0;
	while (p != Q.rear)
	{
		p = p->next;
		j++;
	}
	return j;
}

int ReadEdgeCreate(BiTree* bt)
{
	printf("请依次输入父结点（换行）、子节点（换行）、数字0代表创建左子树、1代表右子树（换行）；首次输入父节点为“#”\n");
	Queue Q;
	InitQueue(&Q);
	*bt = NULL;
	char father[20], child[20];
	int flag;
	printf("\t");
	scanf("%s", father);
	printf("\t");
	scanf("%s", child);
	printf("\t");
	scanf("%d", &flag);
	getchar();
	while (strcmp(child, "#")!=0)
	{
		BiTree p = (BiTree)malloc(sizeof(BiNode));
		strcpy(p->data, child) ;
		p->lc = p->rc = NULL;
		EnQueue(&Q, p);
		if (!strcmp(father, "#"))
			*bt = p;
		else
		{
			BiTree s = GetHead(Q);
			while (strcmp(s->data, father)!= 0)
			{
				DeQueue(&Q);
				s = GetHead(Q);
			}
			if (flag == 0)
				s->lc = p;
			else s->rc = p;
		}
		printf("\t");
		scanf("%s", father);
		printf("\t");
		scanf("%s", child);
		printf("\t");
		scanf("%d", &flag);
		getchar();
	}
	return 1;
}

void LeverOrderTraverse(BiTree root)		//层次遍历
{
	printf("\n");
	printf("层次遍历结果为：");
	Queue Q;
	InitQueue(&Q);
	if (root == NULL)				//二叉树为空，结束遍历
		return;
	EnQueue(&Q, root);				//根指针入队
	while (!IsEmpty(Q))				//队列非空
	{
		BiTree q = GetHead(Q);
		DeQueue(&Q);			//出队并取出对头
		printf("%s ", q->data);		//访问（输出出队结点信息）
		if (q->lc != NULL)		//左孩子入队
			EnQueue(&Q, q->lc);
		if (q->rc != NULL)		//右孩子入队
			EnQueue(&Q, q->rc);
	}
}

void Width(BiTree bt)
{
	int width = 0;
	int len = 0;
	int i;
	Queue Q;
	InitQueue(&Q);
	BiTree p;
	if (!bt)
		return ;
	EnQueue(&Q, bt);
	while (!IsEmpty(Q))
	{
		len = GetLengthQueue(Q);
		width = len > width ? len : width;
		for (i = 0; i < len; i++)
		{
			p = GetHead(Q);
			DeQueue(&Q);
			if (p->lc)
				EnQueue(&Q, p->lc);
			if (p->rc)
				EnQueue(&Q, p->rc);
		}
	}
	printf("\n二叉树的宽度为：%d\n", width);
	return;
}


int main()
{
	BiTree bt;
	ReadEdgeCreate(&bt);
	LeverOrderTraverse(bt);
	Width(bt);
	return 0;
}