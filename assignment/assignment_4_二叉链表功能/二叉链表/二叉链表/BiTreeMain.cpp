//120211080526 张烁 20220415
/*
	定义二叉链表，结点上的data为字符串。

	写一个程序完成功能：
		1.基于先序遍历创建二叉链表；
		2.基于任务分析法实现后序遍历；
		3.求二叉树上值最大的字符串，并输出；
		4.求叶子结点个数；
		5.求结点个数； 
		6.求深度； 
		7.查找给定值所在结点，并返回结点指针；
		8.凹入法输出二叉树。
*/
#include "header.h"
#include "binary_tree_Operating.h"


int main()
{
	BiTree BT;
	printf("·请创建二叉树（前序创建;'#'代表结点为空;换行代表创建完一个结点）\n");
	Create(BT);											//1.基于先序遍历创建二叉链表；
	printf("·后续遍历结果为：");
	Postorder_iter(BT);									//2.基于任务分析法实现后序遍历；
	printf("\n");
	char* max = BT->Data.str;
	/*char max[MAXSIZE];*/
	max = PreFindMaxStr(BT, max);
	//strcpy(max, BT->Data.str);
	//PreFindMaxStr3(BT, max);
	printf("·二叉树上值最大的字符串为：%s", max);		//3.求二叉树上值最大的字符串，并输出；
	printf("\n");
	int count1 = 0;										//4.求叶子结点个数；
	LeafCount(BT, &count1);
	printf("·二叉树上叶子节点数为：%d", count1);
	printf("\n");													
	printf("·二叉树上节点数为：%d", SumNode(BT));		//5.求结点个数；
	printf("\n");
	printf("·二叉树上的深度为：%d", Depth(BT));		//6.求深度； 
	printf("\n");
	printf("\n");
	printf("  请输入要查找的结点：");
	char str[10];
	scanf("%s", str);
	printf("·所查结点的地址为%x", Find(BT, str));		//7.查找给定值所在结点，并返回结点指针；
	printf("\n");
	printf("\n");
	printf("·凹入法输出二叉树结果为：\n");				//8.凹入法输出二叉树。
	DentDispBiTree(BT,0,BT->Data.str);
	DeleteTree(BT);
	return 0;	
}