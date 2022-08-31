// 120211080526 张烁 20220410
/*
*	Q4：写程序，进行排队问题模拟（要求：定义循环队列）。
*
*						****银行排队问题简单模拟****
*		基本假设：
*			1. 银行有三个窗口
*			2. 每个用户服务时长为0-30min
*			3. 每0-5分钟内会随机来一个用户
*			4. 将银行关门时，在排队的用户继续服务，不接受新来的客户
*
*		操作：
*			1. 银行服务时长（min）自己输入
*			2. 用户由随机数生成来模拟
*			3. 定义循环队列及其基本操作
*/
/*	测试样例
		总服务时长（min）
			30
			60
			120
			240
			480
*/
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define  ERROR 0
# define  OK 1
# define  TURE 1
# define  FALSE 0

typedef struct TimeData
{
	int Number;
	int WIN;
	int Arrive; //到达时间
	int Wait;	//等待时间
	int Leave;	//离开时间
	int Serve;	//办理业务时间
	int Start;	//开始办理时间
}TimeData;				//队列节点类型(每个用户的时间数据)

typedef struct SqQueue
{		//循环队列定义
	TimeData* base;
	int front;			//头指针
	int rear;			//尾指针
}SqQueue;


// query
int InitQueue(SqQueue* Q);
int QueueLength(SqQueue Q);
int GetShortestQueue(SqQueue* Q);
int InQueue(SqQueue* q, TimeData e);
int IsEmpty(SqQueue q);
int PopQueue(SqQueue*, TimeData* r);
int DeleteQueue(SqQueue* q);

int querying();

void PrintMenu();

# define MAXQSIZE 50 //等待队列最多排50人;

int main()
{
	PrintMenu();
	querying();
	return 0;
}

int InitQueue(SqQueue* Q) //循环队列初始化
{
	(*Q).base = (TimeData*)malloc(sizeof(TimeData) * MAXQSIZE);
	if (!(*Q).base)
		exit(0);
	(*Q).front = 0;
	(*Q).rear = 0;
	return OK;
}

int QueueLength(SqQueue Q) //循环队列长度
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

int GetShortestQueue(SqQueue* Q)
{
	int min = 20;
	int idx = 0;
	for (int i = 0; i < 3; i++)
	{
		if (QueueLength(Q[i]) < min)
		{
			min = QueueLength(Q[i]);
			idx = i;
		}
	}
	return idx;
}

int InQueue(SqQueue* q, const TimeData e) //循环队列入队
{
	if ((q->rear + 1) % MAXQSIZE == q->front)
		return ERROR;
	q->base[q->rear] = e;
	q->rear = (q->rear + 1) % MAXQSIZE;
	return OK;
}

int IsEmpty(const SqQueue q) //判断队列为空
{
	if (q.front == q.rear)
		return TURE;
	return FALSE;
}

int PopQueue(SqQueue* q, TimeData* r)
{
	if (q->rear + 1 == q->front)
	{
		return ERROR;
	}
	*r = q->base[q->front];

	q->front = (q->front + 1) % MAXQSIZE;
	return OK;
}

int DeleteQueue(SqQueue* q)
{
	free(q->base);
	return OK;
}

const char* Cl = "客户编号";
const char* Sw = "服务窗口";
const char* Bt = "开始办理时间";
const char* At = "到达时间";
const char* St = "服务时间";
const char* Lt = "离开时间";

// int Close = 0; //	判断是否关门
int TotalWaitTime = 0;
int TotalClient = 0; //用户总数

int OpenTime = 0;
int OffTime;


void GetRandTime(int* RandServeTime, int* RandIntervalTime)
{
	unsigned int n = 0;
	srand((unsigned)time(NULL) + (unsigned)rand());
	*RandServeTime = rand() % 30 + 1; 				//办理业务时间在1-30min之间
	*RandIntervalTime = rand() % 5 + 1; 			//间隔不超过5分钟
}


int Waiting(SqQueue* q)
{
	return 0;
}

void PrintPersonInfo(TimeData t)
{
	// TODO: 输出
	printf("\t%-15d%-15d%-15d%-15d%-15d%-15d\n", t.Number, t.WIN, t.Arrive, t.Start, t.Leave, t.Serve);
}

void PrintMenu()
{
	printf("\n");
	printf("        ******************************************\n");
	printf("        ******************* 银行 *****************\n");
	printf("        ******************* 排队 *****************\n");
	printf("        ******************* 模拟 *****************\n");
	printf("        ******************************************\n");
	printf("\n");
}
int querying()
{
	int Num = 1;
	int next_time = -1;
	int nowTime = 0;
	int totalTime = 120;
	printf("\t请输入服务总时间：");
	scanf("%d", &totalTime);
	OffTime = totalTime;
	printf("\n");
	TimeData* windows[3] = { NULL };

	int i; //三个窗口初始化
	SqQueue waitingSq;
	InitQueue(&waitingSq);

	printf("  关门前的用户：\n");
	printf("	银行关门前已经在办理业务的:\n");
	printf("\t%-15s%-15s%-15s%-15s%-15s%-15s\n", Cl, Sw, At, Bt, Lt, St);
	while (totalTime > nowTime)
	{
		if (next_time < nowTime)
		{
			TimeData person;
			int randIntervalTime = 0;
			GetRandTime(&(person.Serve), &randIntervalTime);

			next_time = nowTime + randIntervalTime;
			person.Arrive = nowTime;
			person.Start = 0;
			person.Leave = 0;
			person.Wait = 0;
			person.Number = 1;
			InQueue(&waitingSq, person);
		}
		for (int i = 0; i < 3; i++)
		{
			if (windows[i] != NULL)
			{
				int handle_time = nowTime - windows[i]->Start;
				if (handle_time >= windows[i]->Serve)
				{
					windows[i]->WIN = i + 1;
					windows[i]->Number = Num;
					windows[i]->Leave = nowTime;
					PrintPersonInfo(*windows[i]);
					free(windows[i]);
					windows[i] = NULL;
					Num++;
				}
				else
				{
				}
			}
			else
			{
				if (!IsEmpty(waitingSq))
				{
					windows[i] = (TimeData*)malloc(sizeof(TimeData));
					PopQueue(&waitingSq, windows[i]);
					windows[i]->Start = nowTime;
				}
				else
				{
				}
			}
		}
		nowTime++;
	}
	return 0;
}

