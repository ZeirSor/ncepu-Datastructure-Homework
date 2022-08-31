#include "querying.h"
#include "header.h"

const char* Cl = "客户编号";
const char* Sw = "服务窗口";
const char* Bt = "开始办理时间";
const char* At = "到达时间";
const char* Wt = "等待时间";
const char* St = "服务时间";
const char* Lt = "离开时间";

// int Close = 0; //	判断是否关门
int TotalWaitTime = 0;
int TotalClient = 0; //用户总数
int j = 1;
int OpenTime = 0;
int OffTime;


void GetRandTime(int* RandServeTime, int* RandIntervalTime)
{
	unsigned int n = 0;
	srand((unsigned)time(NULL) + (unsigned)rand());
	*RandServeTime = rand() % 30 + 1; //办理业务时间在1-30之间
	*RandIntervalTime = rand() % 5 + 1; //间隔不超过20分钟
}


int Waiting(SqQueue* q)
{
	return 0;
}

void PrintPersonInfo(TimeData t)
{
	// TODO: 输出
	printf("%d %d %d %d\n", t.Arrive, t.Start, t.Leave, t.Serve);
}

int querying()
{
	int next_time = -1;
	int nowTime = 0;
	int totalTime = 120;
	printf("\t请输入服务总时间：");
	// scanf_s("%d", &totalTime);
	OffTime = totalTime;

	TimeData* windows[3] = {NULL};

	int i; //三个窗口初始化
	SqQueue waitingSq;
	InitQueue(&waitingSq);

	printf("关门前的用户：\n");
	printf("	银行关门前已经在办理业务的:\n");
	// printf("\t%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", Cl, Sw, Bt, At, Wt, St, Lt);
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
			InQueue(&waitingSq, person);
		}
		for (int i = 0; i < 3; i++)
		{
			if (windows[i] != NULL)
			{
				int handle_time = nowTime - windows[i]->Start;
				if (handle_time >= windows[i]->Serve)
				{
					windows[i]->Leave = nowTime;
					PrintPersonInfo(*windows[i]);
					free(windows[i]);
					windows[i] = NULL;
				}
				else
				{
				}
			}
			else
			{
				if (!IsEmpty(waitingSq))
				{
					windows[i] = malloc(sizeof(TimeData));
					PopQueue(&waitingSq, windows[i]);
					windows[i]->Start = nowTime;
				}
				else
				{
				}
			}
		}
		nowTime ++;
	}
	return 0;
}
