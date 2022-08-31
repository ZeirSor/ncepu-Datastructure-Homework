//120211080526 张烁 20220418
/*
*	1. 基于读边法创建二叉树
*	2. 对二叉树进行层次遍历，并按层输出
*	3. 求二叉树的深度和宽度
*	4. 求二叉树上的奇数结点并保存在一个数组中
*	5. 求二叉树上值最大的结点，并输出该结点的指针
*	注意：二叉树保存整形数据
*/
/* 测试样例
			#,1,0
			1,2,0
			1,3,1
			2,1,0
			3,2,1
			#,#,#

			#,1,0
			1,2,1
			1,2,0
			2,1,1
			2,3,0
			1,2,0
			2,9,1
			#,#,#
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

//二叉链表
typedef struct DataType			//数据域
{
	int dt;
}DataType;

typedef struct BiTNode			//结点类型
{
	DataType Data;
	struct BiTNode* LeftChild;
	struct BiTNode* RightChild;
}BiTNode, * BiTree;

//链队列
//链队列的结点及指针类型
typedef struct QNode
{
	BiTree data;
	struct QNode* next;
}QNode, * QueuePtr;

//链队列类型
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;


//二叉树操作
int Create2(BiTree* bt);									//1.基于读边法先序遍历创建二叉树；
int* PreFindMaxInt(BiTree bt, int* max);					//5.找最大数
int Depth(BiTree bt);										//3.1.求深度；
int Width(BiTree bt);										//3.2.求宽度
int DeleteTree(BiTree& bt);									//释放内存
void LeverOrderTraverse(BiTree);							//层次遍历
void FindOdd(BiTree bt, char *arr, int *i);


//链队列操作
int InitQueue(LinkQueue* Q);
int EnQueue(LinkQueue* Q, BiTree e);
BiTree DeQueue(LinkQueue* Q);
int DestroyQueue(LinkQueue* Q);
int IsEmpty(LinkQueue Q);
int GetLengthQueue(LinkQueue Q);
BiTree GetHead(LinkQueue Q);


int main()
{
	BiTree BT;
	printf("·请创建二叉树（读边法创建，输入顺序依次为父节点、孩子节点、0/1\n");
	Create2(&BT);															 //1.基于读边法先序遍历创建二叉树；
	printf("·层次遍历结果为：");											 //2. 对二叉树进行层次遍历，并按层输出
	LeverOrderTraverse(BT);
	printf("\n");
	printf("·二叉树的深度为%d\n·二叉树的宽度为%d\n", Depth(BT), Width(BT));//3. 求二叉树的深度和宽度
	char arr[MAXSIZE];
	printf("·所有的奇数结点为：");											 //4. 求二叉树上的奇数结点并保存在一个数组中
	int* j = (int*)malloc(sizeof(int));
	FindOdd(BT, arr, j);
	for (int i = 0; i < (*j); i++)
		printf("%c ", arr[i]);
	printf("\n");
	int* max = (int*)malloc(sizeof(int));
	*max = BT->Data.dt;
	PreFindMaxInt(BT, max);
	printf("·二叉树上值最大的数为：%d\n·其指针为：%x\n", *max, max);		 //5. 求二叉树上值最大的结点，并输出该结点的指针
	printf("\n");
	DeleteTree(BT);
	return 0;
}


//二叉树操作
int Create2(BiTree* bt)
{
	LinkQueue Q;
	InitQueue(&Q);
	*bt = NULL;
	char father, child;
	int flag;
	printf("\t");
	scanf("%c,%c,%d", &father, &child, &flag);
	getchar();
	while ( child != '#' )
	{
		BiTree p = (BiTree)malloc(sizeof(BiTNode));
		p->Data.dt = (int)(child-'0');
		p->LeftChild = p->RightChild = NULL;
		EnQueue(&Q, p);
		if ( father == '#')
			*bt = p;
		else
		{
			BiTree s = GetHead(Q);
			while (s->Data.dt != (int)(father-'0'))
			{
				DeQueue(&Q);
				s = GetHead(Q);
			}
			if (flag == 0)
				s->LeftChild = p;
			else s->RightChild = p;
		}
		printf("\t");
		scanf("%c,%c,%d", &father, &child, &flag);
		getchar();
	}
	return OK;
}

int DeleteTree(BiTree& bt)
{
	if (bt->LeftChild)
	{
		DeleteTree(bt->LeftChild);
	}
	if (!(bt->LeftChild && bt->RightChild))
	{
		free(bt);
		bt = NULL;
		return 0;
	}if (bt->RightChild)
	{
		DeleteTree(bt->RightChild);
	}
}

int* PreFindMaxInt(BiTree bt, int* max)
{
	if (bt)
	{
		if (*max<=bt->Data.dt)
			*max = bt->Data.dt;
		max = PreFindMaxInt(bt->LeftChild, max);
		max = PreFindMaxInt(bt->RightChild, max);
	}
	return max;
}

int Depth(BiTree bt)
{
	if (!bt)
		return 0;
	else
	{
		int DepLeft = Depth(bt->LeftChild);
		int DepRight = Depth(bt->RightChild);
		if (DepLeft >= DepRight)
			return DepLeft + 1;
		else
			return DepRight + 1;
	}
}

void LeverOrderTraverse(BiTree root)		//层次遍历
{
	LinkQueue Q ;
	InitQueue(&Q);
	if (root == NULL)				//二叉树为空，结束遍历
		return;						
	EnQueue(&Q, root);				//根指针入队
	while (!IsEmpty(Q))				//队列非空
	{
		BiTree q = DeQueue(&Q);			//出队并取出对头
		printf("%d ",q->Data.dt);		//访问（输出出队结点信息）
		if (q->LeftChild != NULL)		//左孩子入队
			EnQueue(&Q, q->LeftChild);
		if (q->RightChild != NULL)		//右孩子入队
			EnQueue(&Q,q->RightChild);
	}
}

int Width(BiTree bt)
{
	int width = 0;
	int len = 0;
	int i;
	LinkQueue Q;
	InitQueue(&Q);
	BiTree p;
	if (!bt)
		return 0;
	EnQueue(&Q, bt);
	while (!IsEmpty(Q))
	{
		len = GetLengthQueue(Q);
		width = len > width ? len : width;
		for (i = 0; i < len; i++)
		{
			p = DeQueue(&Q);
			if (p->LeftChild)
				EnQueue(&Q, p->LeftChild);
			if (p->RightChild)
				EnQueue(&Q, p->RightChild);
		}
	}
	return width;
}

void FindOdd(BiTree root, char *arr, int *i)
{
	int j = 1;
	LinkQueue Q;
	InitQueue(&Q);
	if (root == NULL)				
		return ;
	EnQueue(&Q, root);				
	*i = 0;
	while (!IsEmpty(Q))				
	{
		BiTree q = DeQueue(&Q);			
		if (q->Data.dt % 2 == 1)
			arr[(*i)++] = (char)(q->Data.dt+'0');
		if (q->LeftChild != NULL)		
			EnQueue(&Q, q->LeftChild);	
		if (q->RightChild != NULL)		
			EnQueue(&Q, q->RightChild);	
		j++;
	}
	return ;
}

//链队列
int InitQueue(LinkQueue* Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		exit(0);
	Q->front->next = NULL;
	return 1;
}

int EnQueue(LinkQueue* Q, BiTree e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(0);
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return 1;
}

BiTree DeQueue(LinkQueue* Q)
{
	if (Q->front == Q->rear)
		return 0;
	QueuePtr p = Q->front->next;
	Q->front->next = p->next;

	if (Q->rear == p)
		Q->rear = Q->front;

	BiTree q = p->data;
	free(p);
	return q;
}

int DestroyQueue(LinkQueue* Q)
{
	QueuePtr p;
	while (Q->front)
	{
		p = Q->front->next;
		free(Q->front);
		Q->front = p;
	}
	return 1;
}

int IsEmpty(LinkQueue Q)
{
	if (Q.front == Q.rear)
		return 1;
	else 
		return 0;
}

int GetLengthQueue(LinkQueue Q)
{
	QueuePtr p = Q.front;
	int j = 0;
	while (p != Q.rear)
	{
		p = p->next;
		j++;
	}
	return j;
}

BiTree GetHead(LinkQueue Q)
{
	
	if (IsEmpty(Q))
		return NULL;
	BiTree p; //= (BiTree)malloc(sizeof(BiTNode));
	p = Q.front->next->data;
	return p;
}