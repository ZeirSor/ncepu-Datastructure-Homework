//120211080526 张烁 20220416
/*
*	定义二叉链表，结点上的data为字符串。
*
*	写一个程序完成功能：
*		1.基于先序遍历创建二叉链表；
*		2.基于任务分析法实现后序遍历；
*		3.求二叉树上值最大的字符串，并输出；
*		4.求叶子结点个数；
*		5.求结点个数；
*		6.求深度；
*		7.查找给定值所在结点，并返回结点指针；
*		8.凹入法输出二叉树。
*/
/*	测试样例
	TEST 1
			A
			B
			#
			E
			#
			#
			Z
			D
			#
			#
			F
			#
			#
			Z
	TEST 2
			Root
			Left1
			Left2
			#
			#
			Right2
			Left4
			#
			#
			#
			Right1
			Left3
			#
			#
			Right3
			#
			Right4
			#
			#
			Right2
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

typedef struct DataType			//数据域
{
	char str[MAXSIZE];
}DataType;

typedef struct BiTNode			//结点类型
{
	DataType Data;
	struct BiTNode* LeftChild;
	struct BiTNode* RightChild;
}BiTNode, * BiTree;

typedef struct
{
	BiTree ptr;				//指向根节点的指针
	int task;				//任务性质 1为遍历 0为访问（输出）
}ET;
typedef struct StackNode
{
	ET data;
	struct StackNode* next;
}SNode, * LinkStack;

//栈操作
int InitLinkStack(LinkStack* S);
int IsLinkStackEmpty(LinkStack S);
ET GetLinkStackTop(LinkStack S);
int PushLinkStack(LinkStack* S, ET e);
int PopLinkStack(LinkStack* S, ET e);

//二叉树操作
int Create(BiTree& bt);										//1.基于先序遍历创建二叉链表；
void Postorder_iter(BiTree T);								//2.基于任务分析法实现后序遍历；
char* PreFindMaxStr(BiTree bt, char* max);					//3.找最大字符串1
void LeafCount(BiTree bt, int* count);						//4.求叶子结点个数；
int SumNode(BiTree bt);										//5.求结点个数；
int Depth(BiTree bt);										//6.求深度； 
BiTree Find(BiTree bt, char* find);							//7.查找给定值所在结点，并返回结点指针；
void DentDispBiTree(BiTree bt, int level, const char* c);	//8.凹入法输出二叉树。
int DeleteTree(BiTree& bt);									//释放内存

int main()
{
	BiTree BT;
	printf("·请创建二叉树（前序创建;'#'代表结点为空;换行代表创建完一个结点）\n");
	Create(BT);											//1.基于先序遍历创建二叉链表；
	printf("·后续遍历结果为：");
	Postorder_iter(BT);									//2.基于任务分析法实现后序遍历；
	printf("\n");
	char* max = BT->Data.str;
	/*char max[MAXSIZE];*/
	max = PreFindMaxStr(BT, max);
	//strcpy(max, BT->Data.str);
	//PreFindMaxStr3(BT, max);
	printf("·二叉树上值最大的字符串为：%s", max);		//3.求二叉树上值最大的字符串，并输出；
	printf("\n");
	int count1 = 0;										//4.求叶子结点个数；
	LeafCount(BT, &count1);
	printf("·二叉树上叶子节点数为：%d", count1);
	printf("\n");
	printf("·二叉树上节点数为：%d", SumNode(BT));		//5.求结点个数；
	printf("\n");
	printf("·二叉树上的深度为：%d", Depth(BT));		//6.求深度； 
	printf("\n");
	printf("\n");
	printf("  请输入要查找的结点：");
	char str[10];
	scanf("%s", str);
	printf("·所查结点的地址为%x", Find(BT, str));		//7.查找给定值所在结点，并返回结点指针；
	printf("\n");
	printf("\n");
	printf("·凹入法输出二叉树结果为：\n");				//8.凹入法输出二叉树。
	DentDispBiTree(BT, 0, BT->Data.str);
	DeleteTree(BT);
	return 0;
}


//二叉树操作
int Create(BiTree& bt)
{
	char ch[MAXSIZE];
	printf("\t");
	gets_s(ch);
	if (strcmp(ch, "#") == 0)
		bt = NULL;
	else
	{
		bt = (BiTree)malloc(sizeof(BiTNode));
		strcpy((bt)->Data.str, ch);
		(bt)->LeftChild = NULL;
		(bt)->RightChild = NULL;

		Create((bt)->LeftChild);
		Create((bt)->RightChild);
	}
	return OK;
}

void Postorder_iter(BiTree T)
{
	LinkStack S;
	InitLinkStack(&S);		//初始化栈

	ET e;
	BiTNode* p;
	e.ptr = T;
	e.task = 1;
	PushLinkStack(&S, e);

	while (!IsLinkStackEmpty(S))
	{
		e = GetLinkStackTop(S);
		PopLinkStack(&S, e);
		if (e.task == 0)					//访问
		{
			printf("%s ", e.ptr->Data.str);
		}
		else                                //遍历
		{
			e.task = 0;
			PushLinkStack(&S, e);			//访问根节点

			p = e.ptr;						//维护当前指针

			e.ptr = p->RightChild;			//访问右子树

			if (e.ptr)
			{
				e.task = 1;					//布置任务
				PushLinkStack(&S, e);
			}

			e.ptr = p->LeftChild;			//访问左子树
			if (e.ptr)
			{
				e.task = 1;
				PushLinkStack(&S, e);
			}
		}
	}
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

char* PreFindMaxStr(BiTree bt, char* max)
{
	if (bt)
	{
		if (strcmp(max, bt->Data.str) <= 0)
			max = bt->Data.str;
		max = PreFindMaxStr(bt->LeftChild, max);
		max = PreFindMaxStr(bt->RightChild, max);
	}
	return max;
}

void LeafCount(BiTree bt, int* count)
{
	if (!bt)
		return;
	if (!bt->LeftChild && !bt->RightChild)
		(*count)++;
	LeafCount(bt->LeftChild, count);
	LeafCount(bt->RightChild, count);
}

int SumNode(BiTree bt)
{
	if (!bt)
		return 0;
	else
	{
		int left = SumNode(bt->LeftChild);
		int right = SumNode(bt->RightChild);
		return left + right + 1;
	}
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

BiTree Find(BiTree bt, char* find)
{
	if (!bt)
		return NULL;
	if (strcmp(find, bt->Data.str) == 0)
		return bt;
	if (Find(bt->LeftChild, find))
		return Find(bt->LeftChild, find);
	else
		return Find(bt->RightChild, find);
}

void DentDispBiTree(BiTree bt, int level, const char* c)		//lever为二叉树的层次，c为树根的标志
{
	int i, k;
	if (bt)
	{
		for (i = 1; i < level; i++)
			putchar(' ');
		printf("%s(%s)+", bt->Data.str, c);
		for (k = i; k < 20; k++)
			putchar('-');
		putchar('\n');
		DentDispBiTree(bt->LeftChild, level + 4, "L");
		DentDispBiTree(bt->RightChild, level + 4, "R");
	}
}


//栈操作
int InitLinkStack(LinkStack* S)
{
	*S = NULL;
	return OK;
}

int IsLinkStackEmpty(LinkStack S)
{
	if (S == NULL)
		return 1;
	else
		return 0;
}

int PushLinkStack(LinkStack* S, ET e)
{
	LinkStack p = (LinkStack)malloc(sizeof(SNode));
	if (p == NULL)
		return 0;
	p->data = e;
	p->next = *S;
	*S = p;
	return 1;
}

int PopLinkStack(LinkStack* S, ET e)
{
	LinkStack p = *S;
	if (p == NULL)
		return 0;
	*S = p->next;
	e = p->data;
	free(p);
	return 1;
}

ET GetLinkStackTop(LinkStack S)
{
	return S->data;
}