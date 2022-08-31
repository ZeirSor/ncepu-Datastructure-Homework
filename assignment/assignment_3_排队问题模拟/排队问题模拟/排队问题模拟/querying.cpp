#include "querying.h"
#include "header.h"

SqQueue Win[3];			//��������
const char* Cl = "�ͻ����";
const char* Sw = "���񴰿�";
const char* Bt = "��ʼ����ʱ��";
const char* At = "����ʱ��";
const char* Wt = "�ȴ�ʱ��";
const char* St = "����ʱ��";
const char* Lt = "�뿪ʱ��";
int ServeTime, WaitTime;
int TotalTime, NowTime = 0;
int LeaveTime[3] = { 0, 0, 0 };
int RespectiveWinSum[3] = { 0, 0, 0 };
int Close = 0;			//	�ж��Ƿ����
int TotalWaitTime = 0;
int TotalClient = 0;	//�û�����
int j = 1;
int OpenTime = 0;
int OffTime;
unsigned int RandServeTime;
unsigned int RandIntervalTime;


void GetRandTime(unsigned int* RandServeTime, unsigned int* RandIntervalTime)
{
	unsigned int n = 0;
	srand((unsigned)time(NULL) + (unsigned)rand());
	*RandServeTime = rand() % 30 + 1;		//����ҵ��ʱ����1-30֮��
	*RandIntervalTime = rand() % 20 + 1;    //���������20����
	if (TotalTime < NowTime)
	{				//�ж��Ƿ��˹���ʱ��
		Close = 0;
	}
}


int querying()
{
	printf("\t�����������ʱ�䣺");
	scanf("%d", &TotalTime);
	OffTime = TotalTime;

	int i;						//�������ڳ�ʼ��
	for (i = 0; i < 3; i++)
	{
		InitQueue(&Win[i]);
	}

	printf("����ǰ���û���\n");
	printf("\t���й���ǰ�Ѿ��ڰ���ҵ���:\n");
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
			NowTime += RandServeTime;//��ǰʱ��
			LeaveTime[shortest] = data->Leave;
			RespectiveWinSum[shortest] = RespectiveWinSum[shortest] + 1;
			InQueue(&Win[shortest], *data);
		}
	}
}