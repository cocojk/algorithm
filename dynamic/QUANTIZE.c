#include <stdio.h>
#include <string.h>
#include <float.h>

int memoization[100][10];
int valueCache[100][100];
int N;
int sequence[100];
#define MIN(i,j) ((i)<(j))?(i):(j)
const int INF = 987654321;

int getCurrentVal(int start,int end);
int dynamic(int start,int setNum);

int dynamic(int start,int setNum)
{
	int i;
	int currentVal,minVal;
	int* ret;
	if(start==N)
	{
		return 0;
	}

	if(setNum==0)
	{
		return INF;
	}

	ret = &memoization[start][setNum];
	if(*ret!=-1)
	{
		return *ret;
	}
	
	minVal = 0x7fffffff;
	for(i=start;i<N;i++)
	{
		currentVal = getCurrentVal(start,i) + dynamic(i+1,setNum-1);
		minVal = MIN(minVal,currentVal);
	}


	return *ret = minVal;
}

int getCurrentVal(int start,int end)
{
	int i;
	int middle;
	int temp;

	if(start==end)
	{
		return 0;
	}

	int* ret = &valueCache[start][end];

	if(*ret!=-1)
	{
		return *ret;
	}

	middle=0;
	for(i=start;i<=end;i++)
	{
		middle +=sequence[i];
	}
	middle = (int)(0.5+(double)middle/(end-start+1));

	temp =0;
	for(i=start;i<=end;i++)
	{
		temp += (middle-sequence[i])*(middle-sequence[i]);
	}

	return *ret = temp;
}

int main(void)
{
	int testcase;
	int setNum;
	int i,j,temp;

	scanf("%d",&testcase);

	while(testcase--)
	{
		scanf("%d %d",&N,&setNum);


		memset(memoization,-1,sizeof(memoization));
		memset(valueCache,-1,sizeof(valueCache));
		for(i=0;i<N;i++)
		{
			scanf("%d",&sequence[i]);
		}

		for(i=0;i<N;i++)
		{
			for(j=0;j<(N-i-1);j++)
			{
				if(sequence[j]>sequence[j+1])
				{
					temp = sequence[j+1];
					sequence[j+1] = sequence[j];
					sequence[j] = temp;
				}
			}
		}


		if(setNum>=N)
		{
			puts("0");
		}
		else 
		{
			printf("%d\n",dynamic(0,setNum));
		}
	}
}


