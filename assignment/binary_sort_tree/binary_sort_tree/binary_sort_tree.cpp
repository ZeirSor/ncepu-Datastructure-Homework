#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

typedef struct BSTNode
{
	int data;
	struct BSTNode* lchild;
	struct BSTNode* rchild;
}BSTNode, * BSTNodePtr;

void BSTInsert(BSTNode** T, int data)
{
	if (*T == NULL) {
		*T = (BSTNodePtr)malloc(sizeof(BSTNode));
		(*T)->data = data;
		(*T)->lchild = NULL;
		(*T)->rchild = NULL;
	}
	else if (data < (*T)->data) {
		BSTInsert(&(*T)->lchild, data);
	}
	else if (data > (*T)->data) {
		BSTInsert(&(*T)->rchild, data);
	}
	else return;
}

const char* BST_Search(BSTNode* T, int key)
{
	if (T) {
		if (T->data == key)
			return "SEARCH SUCCESS!";
		else if (T->data > key) {
			BST_Search(T->lchild, key);
		}
		else if (T->data < key) {
			BST_Search(T->rchild, key);
		}
	}
	else {
		return "SEARCH FAIL!";
	}
}

void delNode(BSTNode** T)
{
	BSTNode* s;
	BSTNode* rightDeepest;
	BSTNode* rightDeepest_pri;
	if ((*T)->lchild == NULL ) {
		s = (*T);
		(*T) = (*T)->rchild;
		free(s);
	}
	else if ((*T)->rchild == NULL) {
		s = (*T);
		(*T) = (*T)->lchild;
		free(s);
	}
	else if ((*T)->lchild && (*T)->lchild) {
		rightDeepest = (*T)->lchild;
		rightDeepest_pri = (*T)->lchild;
		while (rightDeepest) {
			rightDeepest_pri = rightDeepest;
			rightDeepest = rightDeepest->rchild;
		}
		if (rightDeepest) {
			(*T)->data = rightDeepest->data;
			rightDeepest_pri->rchild = rightDeepest->lchild;
			free(rightDeepest);
		}
		else {
			(*T)->data = rightDeepest_pri->data;
			(*T)->lchild = rightDeepest_pri->lchild;
			free(rightDeepest_pri);
		}	
	}
	return;
}

const char* Delete(BSTNode** T, int key)
{
	if (*T) {
		if ((*T)->data == key) {
			delNode(&(*T));
			return "SUCCESSFULLY DELETE!";
		}
		else if ((*T)->data < key)
			Delete(&(*T)->rchild, key);
		else if ((*T)->data > key)
			Delete(&(*T)->lchild, key);
	}
	else {
		return "NOT EXSIST!";
	}
}

void preOrder(BSTNode* T)
{
	if (T) {
		printf("\t%d", T->data);
		preOrder(T->lchild);
		preOrder(T->rchild);
	}
}

void inOrder(BSTNode* T)
{
	if (T) {
		preOrder(T->lchild);
		printf("\t%d", T->data);
		preOrder(T->rchild);
	}
}

void postOrder(BSTNode* T)
{
	if (T) {
		preOrder(T->lchild);
		printf("\t%d", T->data);
		preOrder(T->rchild);
	}
}

int main(int argc, char* argv[])
{
	BSTNode* T = NULL;
	int init[10] = { 62,88,58,47,35,73,51,99,37,93 };
	for (int i = 0; i < 10; i++) {
		BSTInsert(&T, init[i]);
	}
	printf("\nPREORDER\t");
	preOrder(T);
	printf("\n\n");

	printf("INORDER \t");
	inOrder(T);
	printf("\n\n");

	printf("POSTORDER\t");
	postOrder(T);		
	printf("\n\n");

	puts(BST_Search(T, 99));
	puts(BST_Search(T, 27));
	puts(BST_Search(T, 47));
	puts(BST_Search(T, 100));

	puts(Delete(&T, 73));
	puts(Delete(&T, 100));
	puts(Delete(&T, 62));
	puts(Delete(&T, 73));
	puts(Delete(&T, 51));
	puts(Delete(&T, 47));
	puts(Delete(&T, 35));
	puts(Delete(&T, 99));

	return 0;
}

//OUTPUT
//		PREORDER                62      58      47      35      37      51      88      73      99      93
//
//		INORDER                 58      47      35      37      51      62      88      73      99      93
//
//		POSTORDER               58      47      35      37      51      62      88      73      99      93
//
//		SEARCH SUCCESS!
//		SEARCH FAIL!
//		SEARCH SUCCESS!
//		SEARCH FAIL!
//		SUCCESSFULLY DELETE!
//		NOT EXSIST!
//		SUCCESSFULLY DELETE!
//		NOT EXSIST!
//		SUCCESSFULLY DELETE!
//		SUCCESSFULLY DELETE!
//		SUCCESSFULLY DELETE!
//		SUCCESSFULLY DELETE!