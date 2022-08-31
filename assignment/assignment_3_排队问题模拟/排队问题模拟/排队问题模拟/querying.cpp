#include "querying.h"
#include "header.h"

SqQueue Win[3];			//三个窗口
const char* Cl = "客户编号";
const char* Sw = "服务窗口";
const char* Bt = "开始办理时间";
const char* At = "到达时间";
const char* Wt = "等待时间";
const char* St = "服务时间";
const char* Lt = "离开时间";
int ServeTime, WaitTime;
int TotalTime, NowTime = 0;
int LeaveTime[3] = { 0, 0, 0 };
int RespectiveWinSum[3] = { 0, 0, 0 };
int Close = 0;			//	判断是否关门
int TotalWaitTime = 0;
int TotalClient = 0;	//用户总数
int j = 1;
int OpenTime = 0;
int OffTime;
unsigned int RandServeTime;
unsigned int RandIntervalTime;


void GetRandTime(unsigned int* RandServeTime, unsigned int* RandIntervalTime)
{
	unsigned int n = 0;
	srand((unsigned)time(NULL) + (unsigned)rand());
	*RandServeTime = rand() % 30 + 1;		//办理业务时间在1-30之间
	*RandIntervalTime = rand() % 20 + 1;    //间隔不超过20分钟
	if (TotalTime < NowTime)
	{				//判断是否到了关门时间
		Close = 0;
	}
}


int querying()
{
	printf("\t请输入服务总时间：");
	scanf("%d", &TotalTime);
	OffTime = TotalTime;

	int i;						//三个窗口初始化
	for (i = 0; i < 3; i++)
	{
		InitQueue(&Win[i]);
	}

	printf("关门前的用户：\n");
	printf("\t银行关门前已经在办理业务的:\n");
	printf("\t%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", Cl, Sw, Bt, At, Wt, St, Lt);
	while (TotalTime > NowTime)
	{

		GetRandTime(&RandServeTime, &RandIntervalTime);
		int shortest = GetShortestQueue(Win);
		
		if (!Close)
		{
			TimeData* data = (TimeData*)malloc(sizeof(TimeData));
			data->Arrive = NowTime;

			data->Serve = RandServeTime;
			if (LeaveTime[shortest] == 0 || NowTime > LeaveTime[shortest])
			{
				data->Leave = NowTime + RandServeTime;
				data->Wait = RandServeTime;
				data->Start = NowTime;
			}
			else
			{
				data->Leave = LeaveTime[shortest] + RandServeTime;
				data->Wait = LeaveTime[shortest] - NowTime + RandServeTime;
				data->Start = LeaveTime[shortest];
			}
			NowTime += RandServeTime;//当前时间
			LeaveTime[shortest] = data->Leave;
			RespectiveWinSum[shortest] = RespectiveWinSum[shortest] + 1;
			InQueue(&Win[shortest], *data);
		}
	}
}