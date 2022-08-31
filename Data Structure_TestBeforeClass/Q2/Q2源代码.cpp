//	120211080526 计算机2105 张烁 20220418
//	
/*
*	图书基本信息保存在单链表中，
*	图书信息有三个成员{书号，书名，价格，出版年份，数量}，
*	完成：
*		1. 将三本书的信息保存在单链表中
*		2. 输出完整的图书列表；
*		3. 查找最贵的书，并输出；
*		4. 根据书名进行查找，并输出完整信息；
*		5. 根据输入的年，删除所有在该年份前出版的图书
*		6. 根据给定书名，修改对应的数量
*		7. 插入一条数据到指定位置。
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0

const char* WZ = "位置";
const char* SH = "书号";
const char* SM = "书名";
const char* JG = "价格";
const char* NF = "出版年份";
const char* SL = "数量";

typedef struct
{
	int Pos;
	char ISBN[100];
	char BookName[100];
	int Price;
	int Year;
	int Num;
}DT;

typedef struct Link
{
	DT data;
	struct Link* next;
}LNode,*LinkList;

void PriHead()
{
	printf("%-15s%-20s%-25s%-15s%-15s%-15s\n", WZ, SH, SM, JG, NF, SL);
}

void Print(LinkList L)
{
	PriHead();
	LinkList p = L->next;
	int j = 0;
	while (p)
	{
		printf("%-15d%-20s%-25s%-15d%-15d%-15d\n", ++j, p->data.ISBN, p->data.BookName, p->data.Price, p->data.Year, p->data.Num);
		p = p->next;
	}
	return;
}

int Init(LinkList* L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	if (!(*L))
		return 0;
	else
	{
		(*L)->next == NULL;
		printf("创建成功！\n");
		return 1;
	}
}

int Insert(LinkList* L,LinkList *R)
{
	int j = 0;
	int n;
	printf("请输入要插入的数量：");
	scanf("%d", &n);
	printf("请依次输入书号，书名，价格，出版年份，数量（中间用空格隔开）\n");
	for (int i = 0; i < n; i++)
	{
		LinkList s = (LinkList)malloc(sizeof(LNode));
		s->data.Pos = ++j;
		scanf("%s %s %d %d %d", s->data.ISBN, s->data.BookName, &s->data.Price, &s->data.Year, &s->data.Num);
		s->next = NULL;
		(*R)->next = s;
		(*R) = s;
	}
	return 1;
}

void FindGui(LinkList L)
{
	LinkList p = L->next;
	LinkList J = p;
	int max = 0;
	while (p)
	{
		if (p->data.Price > max)
		{
			max = p->data.Price;
			J = p;
		}
		p = p->next;
	}
	printf("最贵的书为：\n");
	PriHead();
	printf("%-15d%-20s%-25s%-15d%-15d%-15d\n", J->data.Pos, J->data.ISBN, J->data.BookName, J->data.Price, J->data.Year, J->data.Num);
}

void FindName(LinkList L)
{
	printf("请输入要查找的书名：\n");
	char FN[100];
	scanf("%s", FN);
	LinkList p = L->next;
	while (p)
	{
		if (strcmp(p->data.BookName, FN) == 0)
		{
			printf("该书完整信息为：\n");
			PriHead();
			printf("%-15d%-20s%-25s%-15d%-15d%-15d\n", p->data.Pos, p->data.ISBN, p->data.BookName, p->data.Price, p->data.Year, p->data.Num);
		}
		p = p->next;
	}
	return;
}

void ModifyNum(LinkList* L)
{
	printf("请输入要修改信息的书名：\n");
	char FN[100];
	scanf("%s", FN);
	LinkList p = (*L)->next;
	while (p)
	{
		if (strcmp(p->data.BookName, FN) == 0)
		{
			printf("请输入新的数量：");
			scanf("%d", &p->data.Num);
			return;
		}
		p = p->next;
	}
	return;
}

void DelYear(LinkList *L)
{
	printf("请输入截至删除的年份：\n");
	int Del;
	scanf("%d", &Del);
	LinkList p = (*L);
	LinkList q;
	while (p->next)
	{
		if (p->next->data.Year < Del)
		{
			q = p->next;
			p->next = q->next;
			free(q);
		}
		else
		{
			p = p->next;
		}
	}
	return;
}

void InsertPos(LinkList* L)
{
	LinkList p = (*L);
	int j = 0;
	int pos;
	printf("请输入要插入的位置：");
	scanf("%d", &pos);
	while(j < pos - 1 && p)
	{
		p = p->next;
		j++;
	}
	printf("请依次输入书号，书名，价格，出版年份，数量（中间用空格隔开）\n");
	LinkList s = (LinkList)malloc(sizeof(LNode));
	scanf("%s %s %d %d %d", s->data.ISBN, s->data.BookName, &s->data.Price, &s->data.Year, &s->data.Num);
	s->next = p->next;
	p->next = s;
}

void Destory(LinkList* L)
{
	LinkList p = (*L)->next;
	while (p)
	{
		(*L)->next = p->next;
		free(p);
		p = (*L)->next;
	}
	printf("信息已清空！");
}

int main()
{
	LinkList L,R;
	Init(&L);
	printf("\n");
	R = L;
	Insert(&L, &R);
	Print(L);
	printf("\n");
	FindGui(L);
	printf("\n");
	FindName(L);
	printf("\n");
	DelYear(&L);
	printf("删除后的完整信息为：\n");
	Print(L);
	printf("\n");
	ModifyNum(&L);
	Print(L);
	printf("\n");
	InsertPos(&L);
	Print(L);
	printf("\n");
	Destory(&L);
	printf("\n");
	return 0;
}

//printf("%-25d%-25s%-25s%-25d%-25d%-25d", );