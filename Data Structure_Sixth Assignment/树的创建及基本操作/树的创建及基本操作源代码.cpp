//120211080526 张烁
/*
	树的创建及基本操作。
	字符串采用树的孩子兄弟链表进行存储，完成功能：
	1）创建孩子兄弟链表；
	2）给定（双亲，孩子），进行插入；
	3）根据给定值进行删除；
	4）采用凹入表法进行输出；
	5）根据给定值，求根到该结点的路径
*/

/*	测试样例
			一
				#
				a7
				a7
				b7
				a7
				c7
				a7
				d7
				c7
				e7
				c7
				f7
				d7
				m7
				d7
				n7
				#
				#
				a7
				k7
				c7
				m7

			二
				#
				a7
				a7
				b7
				a7
				c7
				a7
				d7
				a7
				e7
				c7
				f7
				d7
				j7
				e7
				l7
				f7
				g7
				f7
				h7
				f7
				i7
				j7
				k7
				l7
				m7
				h7
				y7
				h7
				z7
				m7
				n7
				z7
				F!
				#
				#
				l7
				x7
				j7
				F!
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct CSNode
{
	char CSTdata[20];
	struct CSNode* firstchild, * nextsibling;
}CSNode, * CSTree;

typedef struct QNode
{
	CSTree Qdata;
	struct QNode* next;
}QNode, * Qptr;

typedef struct
{
	Qptr front, rear;
}Queue;

typedef struct SNode
{
	CSTree Sdata;
	struct SNode* next;
}SNode, * Stack;

int level = 3;

void InitQueue(Queue* Q)
{
	Q->front = Q->rear = (QNode*)malloc(sizeof(QNode));
	Q->front->next = NULL;
}

void EnQueue(Queue* Q, CSTree e)
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

CSTree GetHead(Queue Q)
{
	if (!IsEmpty(Q))
		return Q.front->next->Qdata;
	return NULL;
}

void IniteStack(Stack* S)
{
	*S = NULL;
}

void Push(Stack* S, CSTree e)
{
	SNode* p = (SNode*)malloc(sizeof(SNode));
	p->Sdata = e;
	p->next = *S;
	*S = p;
}

void Pop(Stack* S)
{
	SNode* p = *S;
	if (*S == NULL)
		return;
	*S = p->next;
	free(p);
}

int isEmptyS(Stack S)
{
	if (S == NULL)
		return 1;
	return 0;
}

void PrintStack(Stack S)
{
	SNode* p = S;
	while (p->next)
	{
		printf("%s->", p->Sdata->CSTdata);
		p = p->next;
	}
	printf("%s", p->Sdata->CSTdata);
}

CSTree getTop(Stack S)
{
	if (!isEmptyS(S))
		return S->Sdata;
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

void CreateCSTree(CSTree* T)		//读边法创建孩子兄弟链表
{
	*T = NULL;
	char fa[20], ch[20];
	Queue Q;
	InitQueue(&Q);
	
	CSTree P = (CSTree)malloc(sizeof(CSNode));
	CSTree r = (CSTree)malloc(sizeof(CSNode));		// r用来保存上一次的链接点
	printf("\t");
	scanf("%s", fa);
	printf("\t");
	scanf("%s", ch);
	getchar();
	strcpy(P->CSTdata, ch);
	P->firstchild = NULL;
	P->nextsibling = NULL;		//创建结点
	EnQueue(&Q, P);				//指针入队
	if (strcmp(fa, "#") == 0)		//所建为根节点
		*T = P;
	
	while (strcmp(ch, "#") != 0)
	{
		CSTree p = (CSTree)malloc(sizeof(CSNode));
		printf("\t");
		scanf("%s", fa);
		printf("\t");
		scanf("%s", ch);
		getchar();
		CSTree s;	//s用来保存队头元素；
		strcpy(p->CSTdata, ch);
		p->firstchild = NULL;
		p->nextsibling = NULL;		//创建结点
		EnQueue(&Q, p);				//指针入队
						//非根节点的情况
		s = GetHead(Q);
		while (strcmp(s->CSTdata, fa) != 0)		//找父节点
		{
			DeQueue(&Q);
			s = GetHead(Q);
		}

		if (s->firstchild == NULL)		//链接第一个孩子结点
		{
			s->firstchild = p;
			r = p;
		}
		else						//链接其他孩子结点
		{
			r->nextsibling = p;
			r = p;
		}
	}
	return;
}

CSTree InsertNode(CSTree* T, char *ch)			//寻找插入位置
{
	CSTree s = (CSTree)malloc(sizeof(CSNode));
	CSTree p, q;		//p，q用来寻找插入位置
	strcpy(s->CSTdata, ch);
	s->firstchild = s->nextsibling = NULL;		//创建结点

	if ((*T)->firstchild == NULL)		//插入位置恰好为第一个孩子
		(*T)->firstchild = s;
	else								//插入不为第一个孩子
	{
		p = (*T)->firstchild;
		q = p->nextsibling;
		while (q)				//寻找插入位置
		{
			p = q;
			q = q->nextsibling;
		}
		p->nextsibling = s;
	}
	return *T;
}

CSTree InsertCSTree(CSTree* T, char *fa, char *ch)	//树的插入算法
{
	CSTree s, p;		//s用来保存插入结点；
	if (*T == NULL)
		return 0;
	else
	{
		if (strcmp(fa,(*T)->CSTdata) == 0)		//找到父节点
			return InsertNode(T, ch);
		else if (p = InsertCSTree(&((*T)->firstchild), fa, ch))
			return p;
		else
			return InsertCSTree(&((*T)->nextsibling), fa, ch);
	}
}

int DelNode(CSTree T)
{
	if (T)
	{
		DelNode(T->firstchild);
		DelNode(T->nextsibling);
		free(T);
	}
	return 1;
}

int DelCSTree(CSTree* T, char *e)		//树的删除（删除指定结点）
{
	CSTree q;
	if (!(*T))
		return 0;
	else
	{
		if (strcmp(e, (*T)->CSTdata) == 0)
		{
			q = *T;
			*T = (*T)->nextsibling;
			q->nextsibling = NULL;
			DelNode(q);
			return 1;
		}
		DelCSTree(&((*T)->firstchild), e);
		DelCSTree(&((*T)->nextsibling), e);
	}
}

void DispTree(CSTree T, int level)
{
	int i, j;
	if (!T)
		return;
	for (i = 1; i < level; i++)
		putchar(' ');
	printf("%s+", T->CSTdata);
	for (j = i + 1; j < 40; j++)			
		putchar('-');
	putchar('\n');
	DispTree(T->firstchild, level + 3);		
	DispTree(T->nextsibling, level);		
}

int FindSuccess(CSTree T, char *e)
{
	if (strcmp(T->CSTdata, e) == 0)
		return 1;
	return 0;
}

int flag = 1;

void OutputGivenPath(CSTree T, Stack *S, char *e)
{
	Push(S, T);
	if (FindSuccess(T, e))
	{
		flag = 0;
		return;
	}
		
	if(T->firstchild && flag)
		OutputGivenPath(T->firstchild, S, e);
	if (T->nextsibling && flag)
	{
		Pop(S);
		OutputGivenPath(T->nextsibling, S, e);
	}
	return ;
}

int main()
{
	CSTree tree;
	
	printf("请按照从上到下、从左到右的顺序依次输入父结点（换行）、子节点（换行）\n");
	CreateCSTree(&tree);				//创建孩子兄弟链表；
	DispTree(tree, level);				//采用凹入表法进行输出；
	printf("\n");

	char fa[20], ch[20];						//给定（双亲，孩子），进行插入；
	printf("请输入父节点和插入值：\n");
	printf("\t");
	scanf("%s", fa);
	printf("\t");
	scanf("%s", ch);
	InsertCSTree(&tree, fa, ch);
	DispTree(tree, level);				//采用凹入表法进行输出；
	printf("\n");
	
	char de[20];							//根据给定值进行删除；
	getchar();
	printf("请输入要删除的结点：\n");
	printf("\t");
	scanf("%s", de);
	DelCSTree(&tree, de);
	
	DispTree(tree, level);				//采用凹入表法进行输出；
	printf("\n");
	
	char e[20];								//根据给定值，求根到该结点的路径
	Stack S = (Stack)malloc(sizeof(SNode));
	Stack S2 = (Stack)malloc(sizeof(SNode));
	IniteStack(&S);
	IniteStack(&S2);
	getchar();
	printf("请输入路径的子节点：\n");		
	printf("\t");
	scanf("%s", e);
	printf("该路径为：");
	OutputGivenPath(tree, &S, e);
	Stack p = S;
	while (p)
	{
		Push(&S2, getTop(S));
		p = p->next;
		Pop(&S);
	}
	PrintStack(S2);
	printf("\n");

	return 0;
}