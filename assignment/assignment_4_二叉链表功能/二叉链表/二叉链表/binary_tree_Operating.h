#pragma once
#define _BINARY_TREE_OPERATING_H 
#include "header.h"
#define MAXSIZE 100

//��������
typedef struct DataType			//������
{
	char str[MAXSIZE];
}DataType,ElemType;
typedef struct BiTNode			//�������
{
	DataType Data;
	struct BiTNode* LeftChild;
	struct BiTNode* RightChild;
}BiTNode, * BiTree;

//��ջ
typedef struct
{
	BiTree ptr;				//ָ����ڵ��ָ��
	int task;				//�������� 1Ϊ���� 0Ϊ���ʣ������
}ET;
typedef struct StackNode
{
	ET data;
	struct StackNode* next;
}SNode, * LinkStack;

//������
//�����еĽ�㼰ָ������
typedef struct QNode
{
	ElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

//����������
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//����˫�ױ�ʾ��
#define MAXSIZE 100

typedef int TElemType;

typedef struct PTNode	//���ṹ
{
	ElemType data;
	int parent;			//˫��λ��
	//int FirstChild;		//����λ��
	//int RightSib;		//���ֵ�λ��
}PTNode;

typedef struct
{
	PTNode nodes[MAXSIZE];
	int r, n;			//��λ�úͽ����
}PTree;

//���ĺ��ӱ�ʾ��
typedef int TElemType;

typedef struct CTNode			//���ӽ��
{
	int child;
	struct CTNode* next;
}CTNode, *ChildPtr;

typedef struct					//˫�׽��
{
	TElemType data;
	ChildPtr firstchild;
}CTBox;

typedef struct					//���ṹ
{
	CTBox nodes[MAXSIZE];
	int r, n;					//������͸��ڵ�λ��
}CTree;

//����˫�׺��ӱ�ʾ��
typedef int TElemType;

typedef struct CTNode			//���ӽ��
{
	int child;
	struct CTNode* next;
}CTNode, * ChildPtr;

typedef struct					//˫�׽��
{
	TElemType data;
	int parent;
	ChildPtr firstchild;		//������ͷָ��
}CTBox;

typedef struct					//������
{
	CTBox nodes[MAXSIZE];
	int r, n;					//������͸��ڵ�λ��
}CPTree;


typedef struct CSNode
{
	TElemType data;
	struct CSNode* firstchild, * nextsibling;
}CSNode, * CSTree;

int CreateChildLink(CTree* T);	//��������Ĵ��� ���߷�

int InitLinkStack(LinkStack* S);
int IsLinkStackEmpty(LinkStack S);
ET GetLinkStackTop(LinkStack S);
int PushLinkStack(LinkStack* S, ET e);
int PopLinkStack(LinkStack* S, ET e);



int Create(BiTree& bt);							//1.�����������������������
void Postorder_iter(BiTree T);					//2.�������������ʵ�ֺ��������
int DeleteTree(BiTree& bt);						//�ͷ��ڴ�
char* PreFindMaxStr(BiTree bt, char* max);		//������ַ���1
void PreFindMaxStr2(BiTree bt, char** max);		//������ַ���2
void PreFindMaxStr3(BiTree bt, char* max);		//������ַ���3
void LeafCount(BiTree bt, int *count);
int SumNode(BiTree bt);
int Depth(BiTree bt);
BiTree Find(BiTree bt, char *find);
void DentDispBiTree(BiTree bt, int level, const char* c);


//void Input(BiTNode *bt, char *ch);
//void PreOrderIterative(BiTNode* root);
//void InOrderIterative(BiTNode* root);
//void PostOrderIterative(BiTNode* root);

void LeavePath(CSTree T, LinkStack S);			//�����Ҷ�ӽڵ�·�����㷨

void CreateCSTree(CSTree* T);					//���߷����������ֵ�����

CSTree InsertCSTree(CSTree *T, char fa, char ch);	//���Ĳ����㷨

CSTree InsertNode(CSTree* T, char ch);

int DelCSTree(CSTree* T);		//����ɾ����ɾ��ָ����㣩

int DelNode(CSTree T);

