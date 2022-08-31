#include "StackOperations.h"
#include "binary_tree_Operating.h"
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