#include "header.h"
#include "binary_tree_Operating.h"
// 4 541 84 15 45 15 45 5 46 46 45 45 #
//边遍历边创建
//虚结点--扩展二叉树
//先输入根节点，若为“#”则为空
//否则将输入字符给根节点
//然后依次递归建立左右子树
//基于前序遍历创建二叉链表
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

void DentDispBiTree(BiTree bt, int level, const char *c)		//lever为二叉树的层次，c为树根的标志
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
	scanf("%d", &T->n);		//读入结点数
	T->r = 0;				//根位置
	for (int i = 0; i < T->n; i++)
	{
		scanf("%d", &T->nodes[i].data);
		T->nodes[i].firstchild = NULL;
		int f, c;
		scanf("%d%d", &f, &c);
		while (c != -1)		//循环读边
		{
			ChildPtr s = (ChildPtr)malloc(sizeof(CTNode));	
			s->child = c;		//单链表的头插法
			s->next = NULL;
			s->next = T->nodes[f].firstchild;
			T->nodes[f].firstchild = s;
			scanf("%d%d", &f, &c);
		}
	}
}


//求根到叶子节点路径的算法
void LeavePath(CSTree T, LinkStack S)
{
	if (T)
	{
		PushLinkStack(&S, T->data);
		if (!T->firstchild)
			PrintStack(&S);				//输出路径
		else
			for (CSTree p = T->firstchild; p; p = p->nextsibling)
				LeavePath(p, S);
		PopLinkStack(&S);				//删除路径最后一个结点
	}
}


void CreateCSTree(CSTree* T)		//读边法创建孩子兄弟链表
{
	*T = NULL;
	char fa, ch;
	for (scanf("%c%c", &fa, &ch); ch != '#'; scanf("%c%c", &fa, &ch))
	{
		CSTree p = (CSTree)malloc(sizeof(CSNode));
		CSTree s, r;	//s用来保存队头元素；r用来保存上一次的链接点

		p->data = ch;
		p->firstchild = NULL;
		p->nextsibling = NULL;		//创建结点

		EnQueue(Q, p);				//指针入队

		if (fa == '#')		//所建为根节点
			*T = p;
		else				//非根节点的情况
		{

			GetHead(Q, s);

			while (s->data != fa)
			{
				DeQueue(Q, s);
				GetHead(Q, s);
			}
			if ((s->data == fa))		//链接第一个孩子结点
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
	}
}

CSTree InsertNode(CSTree* T, char ch)			//寻找插入位置
{
	CSTree s = (CSTree)malloc(sizeof(CSNode));
	CSTree p, q;		//p，q用来寻找插入位置
	s->data = ch;
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

CSTree InsertCSTree(CSTree* T, char fa, char ch)	//树的插入算法
{
	CSTree s, p;		//s用来保存插入结点；
	if (*T == NULL)
		return 0;
	else
	{
		if (fa == (*T)->data)		//找到父节点
			return InsertNode(T, ch);
		else if (p = InsertCSTree(&((*T)->firstchild), fa, ch))
			return p;
		else 
			return InsertCSTree(&((*T)->nextsibling), fa, ch));
	}
}

int DelCSTree(CSTree* T, char e)		//树的删除（删除指定结点）
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

////引用创建
//BiTNode* Create(BiTree &bt)				//多加了一个'#'
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
//		Create(bt->LeftChild);		//这里返回值不用赋值
//		Create(bt->RightChild);
//	}
//	return bt;
//}

////非递归先序遍历
//void preOrderIterative(BiTNode* root)
//{
//	if (root == NULL)
//		return;
//	LinkStack nodeStack;		//创建一个栈保存结点
//	push(&nodeStack, root);		//根节点进栈
//
//	while (!IsEmpty(nodeStack))	//非空时迭代
//	{
//		BiTNode* node = top(nodeStack);	//保存栈顶结点
//		printf("%d", node->data);			//访问栈顶数据
//		pop(&nodeStack);					//栈顶结点出栈
//		
//		//子节点入栈
//		if (node->RightChild)				//考虑栈学先进后出的特点
//			push(node->RightChild);			//所以是先右子树进栈
//		if (node->LeftChild)				//遍历时才能左子树先出栈
//			push(node->LeftChild);
//	}
//}
//
////非递归中序遍历
//void InOrderIterative(BiTNode* root)
//{
//	if (root == NULL)
//		return;
//	LinkStack nodeStack;			//创建一个栈保存结点
//	BiTNode* currentNode = root;	//维护一个当前结点指针
//
//	while (currentNode || !IsEmpty(nodeStack))
//	{
//		//当前结点非空，或栈非空时迭代处理
//		while (currentNode)				//找到最深左子树
//		{
//			push(nodeStack, currentNode);
//			currentNode = currentNode->LeftChild;
//		}
//		//左子树已经访问完
//		currentNode = top(nodeStack);			//取栈顶结点
//		printf("%c", currentNode->data);		//访问结点数据
//		pop(&nodeStack);						//出栈
//		currentNode = currentNode->RightChild;	//将当前结点改为右子节点
//	}
//}
//
//
////非递归后序遍历
//void PostOrderIterative(BiTNode* root)
//{
//	if (root == NULL)
//		return;
//	LinkStack nodeStack;			//创建一个栈保存结点
//	BiTNode* currentNode = root;	//维护一个当前结点指针
//	BiTNode* visitedNode = root;	//保存上一次访问的结点
//	
//	//当前结点非空，或栈非空时迭代处理
//	while (currentNode  || !IsEmpty(nodeStack))
//	{
//		while (currentNode)			//沿左子树方向入栈
//		{
//			push(&nodeStack, currentNode);
//			currentNode = currentNode->LeftChild;
//		}
//		currentNode = top(nodeStack);	//取栈顶元素
//
//		//栈顶元素有右子树且未被访问
//		if (currentNode->RightChild && currentNode->RightChild != visitedNode)
//		{
//			currentNode = currentNode->RightChild;
//		}
//		else	//右子树为空或被访问过
//		{
//			printf("%d", currentNode->data);	//访问结点数据
//			visitedNode = currentNode;			//记录当前访问的结点
//			currentNode = NULL;					//当前结点设置为空，防止重复访问左子树
//			pop(&nodeStack);					//出栈
//		}
//	}
//}

