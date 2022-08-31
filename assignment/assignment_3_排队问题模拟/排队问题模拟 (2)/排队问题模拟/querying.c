#include "querying.h"
#include "header.h"

const char* Cl = "�ͻ����";
const char* Sw = "���񴰿�";
const char* Bt = "��ʼ����ʱ��";
const char* At = "����ʱ��";
const char* Wt = "�ȴ�ʱ��";
const char* St = "����ʱ��";
const char* Lt = "�뿪ʱ��";

// int Close = 0; //	�ж��Ƿ����
int TotalWaitTime = 0;
int TotalClient = 0; //�û�����
int j = 1;
int OpenTime = 0;
int OffTime;


void GetRandTime(int* RandServeTime, int* RandIntervalTime)
{
	unsigned int n = 0;
	srand((unsigned)time(NULL) + (unsigned)rand());
	*RandServeTime = rand() % 30 + 1; //����ҵ��ʱ����1-30֮��
	*RandIntervalTime = rand() % 5 + 1; //���������20����
}


int Waiting(SqQueue* q)
{
	return 0;
}

void PrintPersonInfo(TimeData t)
{
	// TODO: ���
	printf("%d %d %d %d\n", t.Arrive, t.Start, t.Leave, t.Serve);
}

int querying()
{
	int next_time = -1;
	int nowTime = 0;
	int totalTime = 120;
	printf("\t�����������ʱ�䣺");
	// scanf_s("%d", &totalTime);
	OffTime = totalTime;

	TimeData* windows[3] = {NULL};

	int i; //�������ڳ�ʼ��
	SqQueue waitingSq;
	InitQueue(&waitingSq);

	printf("����ǰ���û���\n");
	printf("	���й���ǰ�Ѿ��ڰ���ҵ���:\n");
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
