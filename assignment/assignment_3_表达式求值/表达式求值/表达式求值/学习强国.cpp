#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct
{
	char time[10];
	char head[20];
	int read;
	int Like;
}Learn;

typedef struct node
{
	Learn data;
	struct node* next;
}LNode, * LinkList;

const char* Ti = "发布时间";
const char* He = "内容标题";
const char* Re = "阅读量";
const char* Li = "点赞量";
const char* po = "位置";

int Init(LinkList* L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
	printf("	创建成功!\n");
	return 1;
}

int Insert(LinkList* L)
{
	int n;
	printf("    Please input the number of the informtions:");
	scanf("%d", &n);
	int i;
	for (i = 0; i < n; i++)
	{
		LinkList s = (LinkList)malloc(sizeof(LNode));
		printf("  	");
		scanf("%s%s%d%d", &s->data.time, &s->data.head, &s->data.read, &s->data.Like);
		s->next = (*L)->next;
		(*L)->next = s;
	}
	printf("    Succeed!\n");
	return 1;
}

LinkList Pos(LinkList* L, LinkList s)
{
	LinkList p = *L;
	while (p->next != s) {
		p = p->next;
	}
	return p;
}

int Del(LinkList* L, int Dp)
{
	LinkList p = *L;
	int j = 0;
	while (p && j < Dp - 1) {
		p = p->next;
		j++;
	}

	LinkList q = p->next;
	p->next = q->next;
	free(q);
	return 1;

}

int sort(LinkList* L)
{
	LinkList p;
	p = (*L)->next;
	(*L)->next = NULL;
	while (p)
	{
		LinkList q = p->next;
		LinkList s = (*L);
		while (s->next != NULL && s->next->data.Like < p->data.Like) {
			s = s->next;
		}
		p->next = s->next;
		s->next = p;
		p = q;
	}
	return 1;
}

int Disp(LinkList L)
{
	printf("\n");
	LinkList p = L->next;
	printf("	%-15s%-15s%-15s%-15s%-15s\n", Ti, He, Re, Li, po);
	int j = 1;
	while (p)
	{
		printf("	%-15s%-15s%-15d%-15d%-15d\n", p->data.time, p->data.head, p->data.read, p->data.Like, j);
		p = p->next;
		j++;
	}
	printf("\n");
	return 1;
}

int Substring(char* main, char* sub)
{
	if (strstr(main, sub))
		return 1;
}

LinkList GetKeyWord(LinkList L)
{
	LinkList p = L->next;
	char keyword[100];
	printf("	请输入关键词：");
	scanf("%s", keyword);
	int sta = 1;
	int j = 1;
	while (p) {
		if (Substring(p->data.head, keyword)) {
			if (sta == 1) {
				printf("	%-15s%-15s%-15s%-15s%-15s\n", Ti, He, Re, Li, po);
				sta = 0;
			}
			printf("	%-15s%-15s%-15d%-15d%-15d\n", p->data.time, p->data.head, p->data.read, p->data.Like, j);

		}
		j++;
		p = p->next;

	}
	return p;
}

void PrintMenu()
{
	printf("\n");
	printf("        ******************************************\n");
	printf("        **************** 学习强国 ****************\n");
	printf("        ******************************************\n");
}

int Clear(LinkList* L)
{
	(*L)->next = NULL;
	printf("清空成功！\n");
	return 1;
}

int IsEmpty(LinkList L)
{
	if (L->next == NULL)
	{
		printf("链表为空！请插入信息！\n");
		return 1;
	}
	else 
		return 0;
}

int main()
{
	PrintMenu();
	LinkList L = (LinkList)malloc(sizeof(LNode));
	LinkList R = (LinkList)malloc(sizeof(LNode));
	LinkList Find = (LinkList)malloc(sizeof(LNode));
	int sta = 1;
	printf("	1. 初始化\n");
	printf("	2. 插入信息\n");
	printf("	3. 输出\n");
	printf("	4. 按点赞量输出\n");
	printf("	5. 关键字查找并输出\n");
	printf("	6. 删除信息\n");
	printf("	7. 清空\n");
	printf("	8. 退出\n");
	printf("\n");
	while (1)
	{
		int fun;
		printf("  Input The Corresponding Number:");
		scanf("%d", &fun);
		getchar();
		switch (fun)
		{
		case 1:
			Init(&L);
			break;
		case 2:
			Insert(&L);
			break;
		case 3:
			IsEmpty(L);
			Disp(L);
			break;
		case 4:
			IsEmpty(L);
			sort(&L);
			Disp(L);
			break;
		case 5:
			IsEmpty(L);
			GetKeyWord(L);
			int yn;
			printf("	要删除吗？(1/0)");
			scanf("%d", &yn);
			while (yn) {
				int Dp;
				printf("	请输入要删除的位置");
				scanf("%d", &Dp);
				Del(&L, Dp);
				int YN;
				printf("    继续吗？(1/0)\n     ");
				scanf("%d", &YN);
				printf("\n");
				if (YN == 1)
					continue;
				else if (YN == 0)
					break;
			}
			break;
		case 6:
			IsEmpty(L);
			int D;
			printf("	请输入要删除的位置:");
			scanf("%d", &D);
			Del(&L, D);
			printf("\n");
			break;
		case 7:
			Clear(&L);
			printf("\n");
			break;
		case 8:
			return 0;
		default:
			printf("ERROR!\n");
			break;
		}
	}
	return 0;
}