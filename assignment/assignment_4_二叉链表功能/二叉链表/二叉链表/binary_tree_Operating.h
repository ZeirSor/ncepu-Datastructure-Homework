#pragma once
#define _BINARY_TREE_OPERATING_H 
#include "header.h"
#define MAXSIZE 100

//二叉链表
typedef struct DataType			//数据域
{
	char str[MAXSIZE];
}DataType,ElemType;
typedef struct BiTNode			//结点类型
{
	DataType Data;
	struct BiTNode* LeftChild;
	struct BiTNode* RightChild;
}BiTNode, * BiTree;

//链栈
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

//链队列
//链队列的结点及指针类型
typedef struct QNode
{
	ElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

//链队列类型
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//树的双亲表示法
#define MAXSIZE 100

typedef int TElemType;

typedef struct PTNode	//结点结构
{
	ElemType data;
	int parent;			//双亲位置
	//int FirstChild;		//长子位置
	//int RightSib;		//右兄弟位置
}PTNode;

typedef struct
{
	PTNode nodes[MAXSIZE];
	int r, n;			//根位置和结点数
}PTree;

//树的孩子表示法
typedef int TElemType;

typedef struct CTNode			//孩子结点
{
	int child;
	struct CTNode* next;
}CTNode, *ChildPtr;

typedef struct					//双亲结点
{
	TElemType data;
	ChildPtr firstchild;
}CTBox;

typedef struct					//树结构
{
	CTBox nodes[MAXSIZE];
	int r, n;					//结点数和根节点位置
}CTree;

//树的双亲孩子表示法
typedef int TElemType;

typedef struct CTNode			//孩子结点
{
	int child;
	struct CTNode* next;
}CTNode, * ChildPtr;

typedef struct					//双亲结点
{
	TElemType data;
	int parent;
	ChildPtr firstchild;		//孩子链头指针
}CTBox;

typedef struct					//树类型
{
	CTBox nodes[MAXSIZE];
	int r, n;					//结点数和根节点位置
}CPTree;


typedef struct CSNode
{
	TElemType data;
	struct CSNode* firstchild, * nextsibling;
}CSNode, * CSTree;

int CreateChildLink(CTree* T);	//孩子链表的创建 读边法

int InitLinkStack(LinkStack* S);
int IsLinkStackEmpty(LinkStack S);
ET GetLinkStackTop(LinkStack S);
int PushLinkStack(LinkStack* S, ET e);
int PopLinkStack(LinkStack* S, ET e);



int Create(BiTree& bt);							//1.基于先序遍历创建二叉链表；
void Postorder_iter(BiTree T);					//2.基于任务分析法实现后序遍历；
int DeleteTree(BiTree& bt);						//释放内存
char* PreFindMaxStr(BiTree bt, char* max);		//找最大字符串1
void PreFindMaxStr2(BiTree bt, char** max);		//找最大字符串2
void PreFindMaxStr3(BiTree bt, char* max);		//找最大字符串3
void LeafCount(BiTree bt, int *count);
int SumNode(BiTree bt);
int Depth(BiTree bt);
BiTree Find(BiTree bt, char *find);
void DentDispBiTree(BiTree bt, int level, const char* c);


//void Input(BiTNode *bt, char *ch);
//void PreOrderIterative(BiTNode* root);
//void InOrderIterative(BiTNode* root);
//void PostOrderIterative(BiTNode* root);

void LeavePath(CSTree T, LinkStack S);			//求根到叶子节点路径的算法

void CreateCSTree(CSTree* T);					//读边法创建孩子兄弟链表

CSTree InsertCSTree(CSTree *T, char fa, char ch);	//树的插入算法

CSTree InsertNode(CSTree* T, char ch);

int DelCSTree(CSTree* T);		//树的删除（删除指定结点）

int DelNode(CSTree T);

