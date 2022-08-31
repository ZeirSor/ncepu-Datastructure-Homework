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

const char* Ti = "����ʱ��";
const char* He = "���ݱ���";
const char* Re = "�Ķ���";
const char* Li = "������";
const char* po = "λ��";

int Init(LinkList* L)
{
	*L = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
	printf("	�����ɹ�!\n");
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
	printf("	������ؼ��ʣ�");
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
	printf("        **************** ѧϰǿ�� ****************\n");
	printf("        ******************************************\n");
}

int Clear(LinkList* L)
{
	(*L)->next = NULL;
	printf("��ճɹ���\n");
	return 1;
}

int IsEmpty(LinkList L)
{
	if (L->next == NULL)
	{
		printf("����Ϊ�գ��������Ϣ��\n");
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
	printf("	1. ��ʼ��\n");
	printf("	2. ������Ϣ\n");
	printf("	3. ���\n");
	printf("	4. �����������\n");
	printf("	5. �ؼ��ֲ��Ҳ����\n");
	printf("	6. ɾ����Ϣ\n");
	printf("	7. ���\n");
	printf("	8. �˳�\n");
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
			printf("	Ҫɾ����(1/0)");
			scanf("%d", &yn);
			while (yn) {
				int Dp;
				printf("	������Ҫɾ����λ��");
				scanf("%d", &Dp);
				Del(&L, Dp);
				int YN;
				printf("    ������(1/0)\n     ");
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
			printf("	������Ҫɾ����λ��:");
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