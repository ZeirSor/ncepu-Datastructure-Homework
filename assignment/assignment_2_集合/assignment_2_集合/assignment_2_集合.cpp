//120211080526 计算机2105 张烁
/*
*      Q2：整数集合用单链表实现存储，实现如下操作：（30分）
*		（1）初始化集合
*		（2）插入一个数到集合指定位置
*		（3）按值删除集合中的元素
*		（4）按值在集合中进行查找
*		（5）清空集合
*		（6）求两个集合的交集
*		（7）求两个集合的并集
*		（8）求两个集合的差集
*		（9）输出集合
*/
/*
	测试样例
		初始化 5 2 7 3 3 6 4 9 7 0 8 1 6
		LA：1 9 9 1 27 8 16 2 3 5 7
		LB：2 0 3 8 52 57 2357

*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	int data;
	struct node* next;
}LNode, * LinkList;


int InitLink(LinkList* L, LinkList R)
{
	if ((*L) == NULL)
		return 0;

	(*L)->next = NULL;
	printf("创建空表成功!\n");
	return 1;
}

int InsertLink(LinkList* L, LinkList R)
{
	int n;
	LinkList Rear = (*L);
	printf("请输入要插入个数：");
	scanf("%d", &n);
	int i;
	for (i = 0; i < n; i++) {
		LinkList s = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &s->data);
		s->next = NULL;
		Rear->next = s;
		Rear = s;
	}
	return 1;
}

int DeleteLinkPos(LinkList* L)
{
	int e;
	printf("请输入要删除的值：");
	scanf("%d", &e);
	LinkList p = (*L)->next;
	LinkList q = p->next;
	while (q) {
		if (q->data == e) {
			p->next = q->next;
			free(q);
			q = p->next;
		}
		else {
			p = p->next;
			q = q->next;
		}
	}
	return 1;
}

int GetPosAcoNum(LinkList L)
{
	LinkList p = L->next;
	int e;
	printf("请输入要查找的值:");
	scanf("%d", &e);
	int sta = 1;
	int pos = 1;
	while (p)
	{
		if (p->data == e) {
			if (sta = 1) {
				printf("	该元素出现在");
				sta = 0;
			}
			printf("位置%d", pos);
		}
		pos++;
		p = p->next;
	}
	if (sta == 1) {
		printf("查无此数！\n");
		return 0;
	}
	printf("\n");
	return 1;					
}

int InsertLinkPos(LinkList* L)
{
	int i;
	printf("请输入要插入的位置：");
	scanf("%d", &i);
	int j = 1;
	LinkList p = (*L)->next;
	while ( p && j < i-1 ) {
		p = p->next;
		++j;
	}

	if (!p)
		return 0;

	LinkList s = (LinkList)malloc(sizeof(LNode));
	int e;
	printf("请输入要插入的数：");
	scanf("%d", &e);
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 1;
}

int ClearLink(LinkList L)
{
	LinkList p;
	while (L->next)
	{
		p = L->next;
		L->next = p->next;
		free(p);
	}
	printf("链表已清空！\n");
	return 1;
}

int TraverLinkList(LinkList L)
{
	if (L->next) {
		LinkList p = L->next;
		while (p) {
			printf("%d ", p->data);
			p = p->next;
		}
		printf("\n");
		return 1;
	}
	else printf("链表为空！\n");
	return 0;

}

int SortLink(LinkList* L)
{
	LinkList p = (*L)->next;
	(*L)->next = NULL;

	while(p) {
		LinkList s;
		LinkList q;
		s = (*L);
		q = p->next;
		while (s->next && s->next->data < p->data) {
			s = s->next;
		}
		p->next = s->next;
		s->next = p;
		p = q;
	}
	return 1;
}

int SortAndDelReapted(LinkList L)
{
	LinkList p, q;
	p = L->next;
	q = p->next;
	while (p && q)
	{
		if (p->data == q->data)
		{
			p->next = q->next;
			free(q);
			q = p->next;
		}
		else
		{
			p = q;
			q = p->next;
		}
		
	}
	return 1;
}

int Intersection(LinkList LA, LinkList LB)
{
	LinkList LC = (LinkList)malloc(sizeof(LNode));
	LC->next = NULL;
	LinkList pc = LC;
	LinkList pa = LA->next;
	LinkList pb = LB->next;
	while (pa && pb) {
		if (pa->data < pb->data) {
			pa = pa->next;
		}
		else if (pa->data > pb->data) {
			pb = pb->next;
		}
		else {
			LinkList s = (LinkList)malloc(sizeof(LNode));
			s->data = pa->data;
			s->next = pc->next;
			pc->next = s;
			pc = s;
			pa = pa->next;
			pb = pb->next;
		}
	}
	
	printf("集合Set_A为：\n");
	printf("		");
	TraverLinkList(LA);
	printf("集合Set_B为：\n");
	printf("		");
	TraverLinkList(LB);
	printf("集合Set_A与Set_B的交集为：\n");
	printf("		");
	TraverLinkList(LC);
	return 1;
}

int Union(LinkList LA, LinkList LB)
{
	LinkList LC = (LinkList)malloc(sizeof(LNode));
	LC->next = NULL;
	LinkList pc = LC;
	LinkList pa = LA->next;
	LinkList pb = LB->next;
	while (pa && pb) {
		if (pa->data < pb->data) {
			LinkList s = (LinkList)malloc(sizeof(LNode));
			s->data = pa->data;
			s->next = pc->next;
			pc->next = s;
			pc = s;
			pa = pa->next;
		}
		else if (pa->data > pb->data) {
			LinkList s = (LinkList)malloc(sizeof(LNode));
			s->data = pb->data;
			s->next = pc->next;
			pc->next = s;
			pc = s;
			pb = pb->next;
		}
		else {
			LinkList s = (LinkList)malloc(sizeof(LNode));
			s->data = pa->data;
			s->next = pc->next;
			pc->next = s;
			pc = s;
			pa = pa->next;
			pb = pb->next;
		}
	}
	if (pa)
		pc->next = pa;
	if (pb)
		pc->next = pb;

	printf("集合Set_A为：\n");
	printf("		");
	TraverLinkList(LA);
	printf("集合Set_B为：\n");
	printf("		");
	TraverLinkList(LB);
	printf("集合Set_A与Set_B的并集为：\n");
	printf("		");
	TraverLinkList(LC);
	return 1;
}

int Complement(LinkList LA, LinkList LB)
{
	LinkList LC = (LinkList)malloc(sizeof(LNode));
	LC->next = NULL;
	LinkList pc = LC;
	LinkList pa = LA->next;
	LinkList pb = LB->next;
	while (pa&&pb) {
		if (pa->data == pb->data) {
			pa = pa->next;
			pb = pb->next;
		}
		else if (pa->data < pb->data) {
			LinkList s = (LinkList)malloc(sizeof(LNode));
			s->data = pa->data;
			s->next = pc->next;
			pc->next = s;
			pc = s;
			pa = pa->next;
		}
		else if (pa->data > pb->data) {
			pb = pb->next;
		}
	}
	if (pa)
		pc->next = pa;


	printf("集合Set_A为：\n");
	printf("		");
	TraverLinkList(LA);
	printf("集合Set_B为：\n");
	printf("		");
	TraverLinkList(LB);
	printf("集合Set_A与Set_B的差集为：\n");
	printf("		");
	TraverLinkList(LC);
	return 1;
}

int main()
{
	LinkList LA = (LinkList)malloc(sizeof(LNode));
	LinkList LB = (LinkList)malloc(sizeof(LNode));
	LinkList LC = (LinkList)malloc(sizeof(LNode));
	LinkList Ra = LA;
	LinkList Rb = LB;
	printf("--------------------------功能界面--------------------------\n");
	printf("------------------------集合极其运算------------------------\n");
	printf("	1. 初始化创建空集合；\n");
	printf("	2. 初始化后输入集合元素；\n");
	printf("	3. 输出全部集合元素；\n");
	printf("	4. 插入一个数到集合指定位置；\n");
	printf("	5. 按值删除集合中的元素；\n");
	printf("	6. 按值在集合中进行查找；\n");
	printf("	7. 清空集合；\n");
	printf("	8. 进行集合运算；\n");
	printf("	9. 求两个集合的交集；\n");
	printf("	10.求两个集合的并集；\n");
	printf("	11.求两个集合的差集；\n");
	printf("	0. 退出。\n");

	while (1)
	{
		int fun;
		printf("------------------------请输入功能对应数字：");
		scanf_s("%d", &fun);
		getchar();
		switch (fun)
		{
			case 1:
				InitLink(&LA, Ra);
				break;
			case 2:
				InsertLink(&LA, Ra);
				break;
			case 3:
				TraverLinkList(LA);
				break;
			case 4:
				InsertLinkPos(&LA);
				break;
			case 5:
				DeleteLinkPos(&LA);
				break;
			case 6:
				GetPosAcoNum(LA);
				break;
			case 7:
				ClearLink(LA);
				break;
			case 8:
				InitLink(&LA, Ra);
				printf("	输入Set_A的元素：\n");
				InsertLink(&LA, Ra);
				SortLink(&LA);
				printf("				");
				TraverLinkList(LA);

				InitLink(&LB, Rb);
				printf("	输入Set_B的元素：\n");
				InsertLink(&LB, Rb);
				SortLink(&LB);
				printf("				");
				TraverLinkList(LB);
				break;
			case 9:
				Intersection(LA, LB);
				break;
			case 10:
				SortAndDelReapted(LA);
				SortAndDelReapted(LB);
				Union(LA, LB);
				break;
			case 11:
				SortAndDelReapted(LA);
				SortAndDelReapted(LB);
				Complement(LA, LB);
				break;
			case 0:
				return 0;
				break;
			default:
				printf("输入错误，请重新输入！\n");
				break;
			}
			printf("\n");
	}
	return 0;

}

