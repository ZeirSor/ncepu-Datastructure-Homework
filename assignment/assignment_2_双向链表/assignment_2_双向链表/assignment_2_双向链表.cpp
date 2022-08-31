//120211080526 计算机2105 张烁
/*
*		Q3：整数序列保存在双向链表中，实现如下操作：（20分）
*		（1）创建；
*		（2）遍历输出；
*		（3）按值查找；
*		（4）按位序插入；
*		（5）按位序删除；
*/
/*
	测试样例
		初始化 5 2 7 3  3  6  4  9 7 0 8 1 6      13个
			   1 9 9 1  27 8  16 2 3 5 7 7		  12个
			   2 3 0 57 8  52 8  8 8 0 0 2357	  12个
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

typedef struct DulNode
{
	struct DulNode* prior;
	int data;
	struct DulNode* next;
}DulNode, *DuLinkList;

int InitDuLinkList(DuLinkList* L)
{
	*L = (DuLinkList)malloc(sizeof(DulNode));
	if (*L == NULL) {
		printf("申请空间失败！\n");
			exit(0);
	}
	(*L)->next = (*L)->prior = *L;
	printf("创建空表成功!\n");
	return 1;
}

int InputDuLink(DuLinkList L)
{
	DuLinkList p = L;
	int n;
	printf("请输入个数：");
	scanf("%d", &n);
	int i;
	for (i = 0; i < n ; i++) {
		DuLinkList s = (DuLinkList)malloc(sizeof(DulNode));
		scanf("%d", &s->data);
		s->next = p->next;		//后继
		p->next = s;
		s->prior = p;			//前驱
		p->next->prior = s;
		p = p->next;
	}
	return 1;
}

int GetPosAcoNum(DuLinkList L)
{
	DuLinkList p = L->next;
	int e;
	printf("请输入要查找的值:");
	scanf("%d", &e);
	int sta = 1;
	int pos = 1;
	while (p->next!=L)
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

int DisDuLink(DuLinkList L)
{
	DuLinkList p = L->next;
	while (p->next != L->next) {
		printf("%d ", p->data);
		p = p->next;
	}
	return 1;
}

int DuDelete(DuLinkList L)
{
	DuLinkList p = L;
	int j = 0;
	int i;
	printf("请输入要删除的位置：");
	scanf("%d", &i);

	while (p->next != L && j < i - 1) {
		p = p->next;
		++j;
	}

	if (j<i - 1 || j >i - 1){
		printf("链表为空或位置不合理！\n");
		return 0;
	}

	DuLinkList q = p->next;
	p->next = q->next;
	q->next->prior = p;
	free(q);
	return 1;
}

int DuInsert(DuLinkList L)
{
	DuLinkList p = L;		//临时指针，指向头结点
	DuLinkList New_p;		//用于指向新节点
	int j = 0;
	int i;
	printf("请输入要插入的位置：");
	scanf("%d", &i);

	while (p->next != L && j < i - 1) {
		p = p->next;
		j++;
	}

	if (j<i - 1 || j>i - 1) {
		printf("位置不合理！\n");
		return 0;
	}

	int e;
	printf("请输入要插入的数：");
	scanf("%d", &e);
	DuLinkList s = (DuLinkList)malloc(sizeof(DulNode));
	s->data = e;

	s->next = p->next;		//后继
	p->next = s;

	s->prior = p;			//前驱
	p->next->prior = s;
	return 1;
}

int main()
{
	DuLinkList L = (DuLinkList)malloc(sizeof(DulNode));
	printf("--------------------------功能界面--------------------------\n");
	printf("------------------------双向循环链表------------------------\n");
	printf("	1. 初始化；\n");
	printf("	2. 初始化后输入元素；\n");
	printf("	3. 遍历输出；\n");
	printf("	4. 按值查找；\n");
	printf("	5. 按位序插入；\n");
	printf("	6. 按位序删除；\n");
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
				InitDuLinkList(&L);
				break;
			case 2:
				InputDuLink(L);
				break;
			case 3:
				printf("\n");
				printf("		");
				DisDuLink(L);
				printf("\n");
				break;
			case 4:
				printf("\n");
				GetPosAcoNum(L);
				
				break;
			case 5:
				printf("\n");
				DuInsert(L);
				
				break;
			case 6:
				printf("\n");
				DuDelete(L);
				
				break;
			case 0:
				return 0;
				break;
			default:
				printf("\n");
				printf("输入错误，请重新输入！\n");
				break;
		}
	
		printf("\n");
	}
	return 0;

}

