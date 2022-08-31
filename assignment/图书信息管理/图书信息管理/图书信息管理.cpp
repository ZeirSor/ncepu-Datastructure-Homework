//	120211080526 计算机2105 张烁
//	Visual Studio 2019
/*
*	实现图书信息管理，具体要求如下：
*
*	定义图书结构体类型ElemType，至少包括三个属性（书号，书名，价格）；
*	定义图书顺序表SqList（ElemType指针，表长，容量）。
*
*	功能：1、初始化创建一个空表（提示：需要分配存储空间）；
*		  2、插入一条新的图书信息到表中第i个元素；
*		  3、删除表中第i条图书信息；
*		  4、按书名进行查找，并返回找到的图书的完整信息；
*		  5、查找表中的第i条图书信息；
*		  6、输出顺序表中的所有图书信息（注意排版清楚美观）；
*		  7、修改指定图书信息的价格；
*		  8、自己分析，扩展有意义的功能。
*
*	主函数中定义顺序表变量L，通过调用各功能函数顺序完成以下操作：
*		1. 初始化创建空表L，
*		2. 连续插入3条数据到表头，
*		3. 输出顺序表，
*		4. 插入一条数据使其成为表中第3条数据，
*		5. 输出顺序表，
*		6. 根据指定的书名进行删除；
*		7. 输出顺序表；
*		8. 按书名进行查找，并输出查找到的图书完整信息;
*		9. 按书名查找后进行对应记录价格的修改；
*		10.输出修改后全部图书信息。
*/

/*	测试样例
	ISBN				书名					定价
	9787302257646		程序设计基础			25
	9787302219972		单片机技术及应用		32
	9787302203513		编译原理				46
	9787811234923		汇编语言程序设计教程	21
	9787512100831		计算机操作系统			17
	9787302265436		计算机导论实验指导		18
	9787302180630		实用数据结构			29
	9787302225065		数据结构(C语言版)		38
	9787302171676		C#面向对象程序设计		39
	9787302250692		c语言程序设计			42
	9787302150664		数据库原理				35
	9787302260806		Java编程与实践			56
	9787302252887		Java程序设计与应用教程	39
	9787302198505		嵌入式操作系统及编程	25
	9787302169666		软件测试				24
	9787811231557		Eclipse基础与应用		35
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define OVERFLOW -2
#define ListIncrement 2
typedef int Status;
int n;

typedef struct
{
	char ISBN[15];
	char BookName[50];
	float price;
}TBook;

typedef struct
{
	TBook* data;
	int length;
	int listsize;
}SqList;

TBook* newbase;

Status InitList(SqList* L,int n);	//初始化
Status InputList(SqList* L,int i);	//输入图书信息
Status DisplayList(SqList* L);		//输出图书信息
Status ListInsert(SqList* L);		//插入图书信息
Status DeListAcoName(SqList* L);	//根据书名删除图书信息
Status DeListAcoNum(SqList* L);		//根据序号删除图书信息
Status GetName(SqList* L);			//根据书名查找图书
Status GetSeNum(SqList* L);			//根据序号查找图书
Status GetNum(SqList* L);			//输出图书总数
Status MdfPrice(SqList* L);			//修改图书价格
Status IsEmpty(SqList* L);			//判断表格是否为空
Status DestroyList(SqList* L);		//销毁图书信息；

int main(int argc, char* argv[])
{
	SqList* L = (SqList*)malloc(sizeof(SqList));
	printf("--------------------------功能界面--------------------------\n");
	printf("------------------------图书信息管理------------------------\n");
	printf("1. 初始化创建空表L；\n");
	printf("2. 初始化后输入图书信息；\n");
	printf("3. 输出全部图书信息；\n");
	printf("4. 插入图书信息\n");
	printf("5. 根据指定的书名进行删除；\n");
	printf("6. 根据指定的序号进行删除；\n");
	printf("7. 按书名进行查找，并输出查找到的图书完整信息；\n");
	printf("8. 按序号进行查找，并输出查找到的图书完整信息；\n");
	printf("9. 按书名查找后进行对应记录价格的修改；\n");
	printf("10.输出图书总数。\n");
	printf("11.销毁所有图书信息。\n");
	printf("12.退出。\n");


	while (1)
	{
		int fun;
		printf("------------------------请输入功能对应数字：");
		scanf_s("%d", &fun);
		getchar();
		switch (fun)
		{
		case 12:
			return 0;
		case 1:
			printf("请输入图书数量：");
			scanf_s("%d", &n);
			InitList(L,n);
			break;
		case 2:
			if (!IsEmpty(L))
			{
				int i;
				printf("请依次输入书号（ISBN）、书名、价格：\n");
				for (i = 0; i < n; i++)
				{
					InputList(L,i);
				}
			}
			else printf("线性表不存在，请选择初始化（1）\n");
			break;
		case 3:
			if (!IsEmpty(L))
				DisplayList(L);
			else printf("线性表不存在，请选择初始化（1）\n");
			break;
		case 4:
			if (!IsEmpty(L))
			{
				ListInsert(L);
			}
			else printf("线性表不存在，请选择新建表格（0）\n");
			break;
		case 5:
			if (!IsEmpty(L))
			{
				DeListAcoName(L);
			}
			else printf("线性表不存在，请选择初始化（1）\n");
			break;
		case 6:
			if (!IsEmpty(L))
			{
				DeListAcoNum(L);
			}
			else printf("线性表不存在，请选择初始化（1）\n");
			break;
		case 7:
			if (!IsEmpty(L))
				GetName(L);
			else
			{
				DestroyList(L);
				printf("线性表不存在，请选择初始化（1）\n");
			}
			break;
		case 8:
			if (!IsEmpty(L))
			{
				GetSeNum(L);
			}
			else
			{
				DestroyList(L);
				printf("线性表不存在，请选择初始化（1）\n");
			}
			break;
		case 9:
			if (!IsEmpty(L))
			{
				MdfPrice(L);
			}
			else
			{
				DestroyList(L);
				printf("线性表不存在，请选择初始化（1）\n");
			}
			break;
		case 10:
			if (!IsEmpty(L))
			{
				GetNum(L);
			}
			else
			{
				DestroyList(L);
				printf("线性表不存在，请选择初始化（1）\n");
			}
			break;
		case 11:
			DestroyList(L);
			printf("销毁成功！请选择重新初始化（1）或者退出（12）\n");
			break;
		default:
			printf("输入错误，请重新输入！\n");
		}
		printf("\n");
	}
	return 0;
}

Status InitList(SqList* L,int n)
{
	L->data = (TBook*)malloc(sizeof(TBook)*n);

	if (!L->data)
	{
		printf("Create failed!");
		exit(0);
	}
	L->length = 0;
	L->listsize = n;

	printf("Successfully creat!Please initialize the Sequence List\n");
	//printf("Listsize:%d\n", L->listsize);
	//printf("Length:%d\n", L->length);
	return OK;
}

Status InputList(SqList* L,int i)
{

	scanf_s("%s", L->data[i].ISBN, 15);
	scanf_s("%s", L->data[i].BookName, 50);
	scanf_s("%f", &L->data[i].price);

	L->length += 1;
	return 1;
}

Status DisplayList(SqList* L)
{
	int i;
	const char *Is = "ISBN";
	const char *Na = "书名";
	const char *Pr = "价格";
	printf("%-20s%-25s%-25s\n", Is, Na, Pr);
	for (i = 0; i < L->length; i++)
	{
		printf("%-20s%-25s%-10.2f\n", L->data[i].ISBN, L->data[i].BookName, L->data[i].price);
	}
	return 1;
}

Status ListInsert(SqList* L)
{
	int i;
	printf("Please input the position i you want to insert： ");
	int b = 1;
	while (b)
	{
		scanf_s("%d", &i);
		if (i < 1 || i > L->length + 1)
		{
			printf("插入的位置不合理！请重新输入！\n");
		}
		else b = 0;
	}
	newbase = (TBook*)malloc(sizeof(TBook));
	if (L->length == L->listsize)
	{
		newbase = (TBook*)realloc(L->data, (L->listsize + ListIncrement) * sizeof(TBook));
		if (!L->data)
		{
			printf("Recreate failed!\n");
			exit(0);
		}
		L->data = newbase;
		L->listsize += ListIncrement;
	}

	int j;
	for (j = L->length; j >= i; j--)
	{
		L->data[j] = L->data[j - 1];
	}
	printf("请依次输入书号（ISBN）、书名、价格：\n");
	InputList(L,i-1);
	printf("插入成功！\n");

	return OK;
}

Status DeListAcoName(SqList* L)
{
	int i, j;
	printf("Please input the Bookname you want to delete： ");
	int b = 1;
	char FindName[50] = { 0 };

	while (b)
	{
		scanf_s("%s", FindName,50);
		for (i = 0; i < L->length; i++)
		{
			if ( strcmp(L->data[i].BookName, FindName) == 0 )
			{
				b = 0;
				break;
			}
		}
		if (i == L->length)
			printf("删除的图书不存在！请重新输入！\n");
	}

	for (j = i; j < L->length - 1; j++)
	{
		L->data[j] = L->data[j + 1];
	}
	L->length -= 1;
	printf("删除成功！\n");

	if (L->length == 0)
		DestroyList(L);

	return OK;
}

Status DeListAcoNum(SqList* L)
{
	int i;
	printf("Please input the position i you want to delete： ");
	int b = 1;
	while (b)
	{
		scanf_s("%d", &i);
		if (i < 1 || i > L->length)
		{
			printf("删除的位置不合理！请重新输入！\n");
		}
		else b = 0;
	}

	int j;
	for (j = i - 1; j < L->length - 1; j++)
	{
		L->data[j] = L->data[j + 1];
	}
	L->length -= 1;
	printf("删除成功！\n");

	if (L->length == 0)
		DestroyList(L);

	return OK;
}

Status GetName(SqList* L)
{
	const char* Is = "ISBN";
	const char* Na = "书名";
	const char* Pr = "价格";

	printf("请输入要查找的书名：");
	char FindName[50] = { 0 };
	scanf_s("%s", FindName, 50);
	int i;
	for (i = 0; i < L->length; i++)
	{
		if (strcmp(FindName, L->data[i].BookName) == 0)
		{			
			printf("%-20s%-25s%-25s\n", Is, Na, Pr);
			printf("%-20s%-25s%-10.2f\n", L->data[i].ISBN, L->data[i].BookName, L->data[i].price);
			return 1;
		}
	}
	printf("查找的书名不存在！\n");
	return 0;
}

Status GetSeNum(SqList* L)
{
	int i;
	const char* Is = "ISBN";
	const char* Na = "书名";
	const char* Pr = "价格";
	printf("请输入你要查找图书序号：");
	scanf_s("%d", &i);
	if (i >= 0 && i <= L->length)
	{
		printf("第%d条图书信息为\n", i);
		printf("%-20s%-25s%-25s\n", Is, Na, Pr);
		printf("%-20s%-25s%-10.2f\n", L->data[i-1].ISBN, L->data[i-1].BookName, L->data[i-1].price);
	}
	
	else printf("该序号图书不存在，请重新输入！");
	return 0;
}

Status GetNum(SqList* L)
{
	printf("图书总数为：“%d”\n", L->length);
	return OK;
}

Status MdfPrice(SqList* L)
{
	const char* Is = "ISBN";
	const char* Na = "书名";
	const char* Pr = "价格";

	printf("请输入要修改价格的书名：");
	char FindName[50] = { 0 };
	scanf_s("%s", FindName, 50);
	int i;
	float NewPrice;
	for (i = 0; i < L->length; i++)
	{
		if (strcmp(FindName, L->data[i].BookName) == 0)
		{
			printf("该图书的信息为：\n");
			printf("%-20s%-25s%-25s\n", Is, Na, Pr);
			printf("%-20s%-25s%-10.2f \n", L->data[i].ISBN, L->data[i].BookName, L->data[i].price);
			
			printf("请输入新价格：");
			scanf_s("%f", &NewPrice);
			L->data[i].price = NewPrice;
			printf("修改后图书信息为：\n");
			printf("%-20s%-25s%-25s\n", Is, Na, Pr);
			printf("%-20s%-25s%-10.2f\n", L->data[i].ISBN, L->data[i].BookName, L->data[i].price);
			return OK;
		}
	}
	printf("查找的书名不存在！\n");
	return 0;
}

Status IsEmpty(SqList* L)
{
	if (L->length == 0 && L->listsize == 0)
		return 1;
	else return 0;
}

Status DestroyList(SqList* L)
{
	if (L->data)
	{
		free(L->data);
		L->data = NULL;
		L->length = 0;
		L->listsize = 0;
	}
	return OK;
}