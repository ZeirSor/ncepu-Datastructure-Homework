#include "header.h"
#include "binary_tree_Operating.h"
// 4 541 84 15 45 15 45 5 46 46 45 45 #
//�߱����ߴ���
//����--��չ������
//��������ڵ㣬��Ϊ��#����Ϊ��
//���������ַ������ڵ�
//Ȼ�����εݹ齨����������
//����ǰ�����������������
//BiTNode root = Create(&root);
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
	InitLinkStack(&S);		//��ʼ��ջ

	ET e;	
	BiTNode* p;
	e.ptr = T;				
	e.task = 1;
	PushLinkStack(&S, e);

	while (!IsLinkStackEmpty(S))
	{
		e = GetLinkStackTop(S);
		PopLinkStack(&S, e);
		if (e.task == 0)					//����
		{
			printf("%s ", e.ptr->Data.str);
		}
		else                                //����
		{
			e.task = 0;
			PushLinkStack(&S, e);			//���ʸ��ڵ�

			p = e.ptr;						//ά����ǰָ��

			e.ptr = p->RightChild;			//����������
								
			if (e.ptr)
			{
				e.task = 1;					//��������
				PushLinkStack(&S, e);
			}
					
			e.ptr = p->LeftChild;			//����������
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


char* PreFindMaxStr(BiTree bt, char *max)
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


void PreFindMaxStr2(BiTree bt, char** max)
{
	if (bt)
	{
		if (strcmp(*max, bt->Data.str) <= 0)
			*max = bt->Data.str;
		PreFindMaxStr2(bt->LeftChild, max);
		PreFindMaxStr2(bt->RightChild, max);
	}
}

void PreFindMaxStr3(BiTree bt, char* max)
{
	if (bt)
	{
		if (strcmp(max, bt->Data.str) <= 0)
			strcpy(max, bt->Data.str);
		PreFindMaxStr3(bt->LeftChild, max);
		PreFindMaxStr3(bt->RightChild, max);
	}
}

void LeafCount(BiTree bt, int *count)
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

BiTree Find(BiTree bt, char *find)
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

void DentDispBiTree(BiTree bt, int level, const char *c)		//leverΪ�������Ĳ�Σ�cΪ�����ı�־
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

//int GetLinkStackTop(LinkStack S, char* e)
//{
//	if (S == NULL)
//		return 0;
//	*e = S->data.ptr->Data.str;
//	return 1;
//}

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

int CreateChildLink(CTree* T)
{
	scanf("%d", &T->n);		//��������
	T->r = 0;				//��λ��
	for (int i = 0; i < T->n; i++)
	{
		scanf("%d", &T->nodes[i].data);
		T->nodes[i].firstchild = NULL;
		int f, c;
		scanf("%d%d", &f, &c);
		while (c != -1)		//ѭ������
		{
			ChildPtr s = (ChildPtr)malloc(sizeof(CTNode));	
			s->child = c;		//�������ͷ�巨
			s->next = NULL;
			s->next = T->nodes[f].firstchild;
			T->nodes[f].firstchild = s;
			scanf("%d%d", &f, &c);
		}
	}
}


//�����Ҷ�ӽڵ�·�����㷨
void LeavePath(CSTree T, LinkStack S)
{
	if (T)
	{
		PushLinkStack(&S, T->data);
		if (!T->firstchild)
			PrintStack(&S);				//���·��
		else
			for (CSTree p = T->firstchild; p; p = p->nextsibling)
				LeavePath(p, S);
		PopLinkStack(&S);				//ɾ��·�����һ�����
	}
}


void CreateCSTree(CSTree* T)		//���߷����������ֵ�����
{
	*T = NULL;
	char fa, ch;
	for (scanf("%c%c", &fa, &ch); ch != '#'; scanf("%c%c", &fa, &ch))
	{
		CSTree p = (CSTree)malloc(sizeof(CSNode));
		CSTree s, r;	//s���������ͷԪ�أ�r����������һ�ε����ӵ�

		p->data = ch;
		p->firstchild = NULL;
		p->nextsibling = NULL;		//�������

		EnQueue(Q, p);				//ָ�����

		if (fa == '#')		//����Ϊ���ڵ�
			*T = p;
		else				//�Ǹ��ڵ�����
		{

			GetHead(Q, s);

			while (s->data != fa)
			{
				DeQueue(Q, s);
				GetHead(Q, s);
			}
			if ((s->data == fa))		//���ӵ�һ�����ӽ��
			{
				s->firstchild = p;
				r = p;
			}
			else						//�����������ӽ��
			{
				r->nextsibling = p;
				r = p;
			}

		}
	}
}

CSTree InsertNode(CSTree* T, char ch)			//Ѱ�Ҳ���λ��
{
	CSTree s = (CSTree)malloc(sizeof(CSNode));
	CSTree p, q;		//p��q����Ѱ�Ҳ���λ��
	s->data = ch;
	s->firstchild = s->nextsibling = NULL;		//�������
	
	if ((*T)->firstchild == NULL)		//����λ��ǡ��Ϊ��һ������
		(*T)->firstchild = s;
	else								//���벻Ϊ��һ������
	{
		p = (*T)->firstchild;
		q = p->nextsibling;
		while (q)				//Ѱ�Ҳ���λ��
		{
			p = q;
			q = q->nextsibling;
		}	
		
		p->nextsibling = s;
		
	}
	return *T;
}

CSTree InsertCSTree(CSTree* T, char fa, char ch)	//���Ĳ����㷨
{
	CSTree s, p;		//s������������㣻
	if (*T == NULL)
		return 0;
	else
	{
		if (fa == (*T)->data)		//�ҵ����ڵ�
			return InsertNode(T, ch);
		else if (p = InsertCSTree(&((*T)->firstchild), fa, ch))
			return p;
		else 
			return InsertCSTree(&((*T)->nextsibling), fa, ch));
	}
}

int DelCSTree(CSTree* T, char e)		//����ɾ����ɾ��ָ����㣩
{
	CSTree q;
	if (!(*T))
		return 0;
	else
	{
		if (e == (*T)->data)
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

int DelNode(CSTree T)
{
	if (T)
	{
		DelNode(T->firstchild);
		DelNode(T->nextsibling);
		free(T);
	}
}

int DelNode(CSTree T)
{

}

////���ô���
//BiTNode* Create(BiTree &bt)				//�����һ��'#'
//{
//	char ch[MAXSIZE];
//	scanf("%s", ch);		//gets(ch)??
//	Input(bt, ch);
//	if (strcmp(ch, "#") == 1)
//		bt = NULL;
//	else
//	{
//		bt = (BiTree)malloc(sizeof(BiTNode));
//		strcpy(bt->data.str, ch);
//		Create(bt->LeftChild);		//���ﷵ��ֵ���ø�ֵ
//		Create(bt->RightChild);
//	}
//	return bt;
//}

////�ǵݹ��������
//void preOrderIterative(BiTNode* root)
//{
//	if (root == NULL)
//		return;
//	LinkStack nodeStack;		//����һ��ջ������
//	push(&nodeStack, root);		//���ڵ��ջ
//
//	while (!IsEmpty(nodeStack))	//�ǿ�ʱ����
//	{
//		BiTNode* node = top(nodeStack);	//����ջ�����
//		printf("%d", node->data);			//����ջ������
//		pop(&nodeStack);					//ջ������ջ
//		
//		//�ӽڵ���ջ
//		if (node->RightChild)				//����ջѧ�Ƚ�������ص�
//			push(node->RightChild);			//����������������ջ
//		if (node->LeftChild)				//����ʱ�����������ȳ�ջ
//			push(node->LeftChild);
//	}
//}
//
////�ǵݹ��������
//void InOrderIterative(BiTNode* root)
//{
//	if (root == NULL)
//		return;
//	LinkStack nodeStack;			//����һ��ջ������
//	BiTNode* currentNode = root;	//ά��һ����ǰ���ָ��
//
//	while (currentNode || !IsEmpty(nodeStack))
//	{
//		//��ǰ���ǿգ���ջ�ǿ�ʱ��������
//		while (currentNode)				//�ҵ�����������
//		{
//			push(nodeStack, currentNode);
//			currentNode = currentNode->LeftChild;
//		}
//		//�������Ѿ�������
//		currentNode = top(nodeStack);			//ȡջ�����
//		printf("%c", currentNode->data);		//���ʽ������
//		pop(&nodeStack);						//��ջ
//		currentNode = currentNode->RightChild;	//����ǰ����Ϊ���ӽڵ�
//	}
//}
//
//
////�ǵݹ�������
//void PostOrderIterative(BiTNode* root)
//{
//	if (root == NULL)
//		return;
//	LinkStack nodeStack;			//����һ��ջ������
//	BiTNode* currentNode = root;	//ά��һ����ǰ���ָ��
//	BiTNode* visitedNode = root;	//������һ�η��ʵĽ��
//	
//	//��ǰ���ǿգ���ջ�ǿ�ʱ��������
//	while (currentNode  || !IsEmpty(nodeStack))
//	{
//		while (currentNode)			//��������������ջ
//		{
//			push(&nodeStack, currentNode);
//			currentNode = currentNode->LeftChild;
//		}
//		currentNode = top(nodeStack);	//ȡջ��Ԫ��
//
//		//ջ��Ԫ������������δ������
//		if (currentNode->RightChild && currentNode->RightChild != visitedNode)
//		{
//			currentNode = currentNode->RightChild;
//		}
//		else	//������Ϊ�ջ򱻷��ʹ�
//		{
//			printf("%d", currentNode->data);	//���ʽ������
//			visitedNode = currentNode;			//��¼��ǰ���ʵĽ��
//			currentNode = NULL;					//��ǰ�������Ϊ�գ���ֹ�ظ�����������
//			pop(&nodeStack);					//��ջ
//		}
//	}
//}

