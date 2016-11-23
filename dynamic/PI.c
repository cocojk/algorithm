
#include <stdio.h>
#include <string.h>

int mem[10000];
int num[10000];
int N;

#define MAXNUM 40000
#define min(i,j) ((i)<(j))?(i):(j)
int decision(int offset,int size);
int pi(int offset);
int pi(int offset)
{
	int i;
	int temp;
	int* ret = &mem[offset];

	if(offset==N)
		return 0;

	if(*ret!=-1)
		return *ret;
	
	*ret = MAXNUM;

	// 3 자리
	if(offset+3<=N)
	{
		temp = pi(offset+3)+decision(offset,3);
//		printf("decision(%d,%d) %d\n",offset,3,decision(offset,3));
		*ret = min(*ret,temp);
	}

	if(offset+4<=N)
	{
		// 4 자리
		temp = pi(offset+4)+decision(offset,4);
//		printf("decision(%d,%d) %d\n",offset,4,decision(offset,4));
		*ret = min(*ret,temp);
	}

	
	if(offset+5<=N)
	{
		// 5 자리 
		temp = pi(offset+5)+decision(offset,5);
//		printf("decision(%d,%d) %d\n",offset,5,decision(offset,5));
		*ret = min(*ret,temp);
	}
	
//	printf("offset %d :%d\n",offset,*ret);
	return *ret;
}

int decision(int offset,int size)
{
	int i;
	int temp;
	

	// level 1
	for(i=0;i<size-1;i++)
	{
		if(num[offset+i]!=num[offset+i+1])
			break;
	}

	if(i==(size-1))
		return 1;

	// level 2
	for(i=0;i<size-1;i++)
	{
		if((num[offset+i+1]-num[offset+i])!=1)
			break;
	}

	if(i==(size-1))
		return 2;

	for(i=0;i<size-1;i++)
	{
		if((num[offset+i]-num[offset+i+1])!=1)
			break;
	}

	if(i==(size-1))
		return 2;


	// level 4 
	for(i=2;i<size;i++)
	{
		if(num[offset+i]!=num[offset+i-2])
			break;
	}

	if(i==size)
		return 4;
		


	// level 5
	temp = num[offset+1]-num[offset];
	for(i=1;i<size-1;i++)
	{
		if(num[offset+i+1]-num[offset+i]!=temp)
			break;
	}

	if(i==(size-1))
		return 5;

	// level 10
	return 10;
}
	
int main(void)
{
	int testcase;
	char temp[10001];
	int i;

	scanf("%d",&testcase);
	while(testcase--)
	{
		memset(mem,-1,sizeof(mem));
		scanf("%s",&temp);
		N = strlen(temp);
		for(i=0;i<N;i++)
		{
			num[i] = temp[i] -'0';
		}	
		
//		printf("N: %d\n",N);
		printf("%d\n",pi(0));
	}
}





