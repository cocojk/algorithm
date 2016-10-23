#include <stdio.h>
#include <string.h>

int mem[100];
int N;

int dynamic(int start)
{
	if(start==N-1)
		return 1;

	if(start==N)
		return 1;

	int* ret = &mem[start];

	if(*ret!=-1)
		return *ret;

	return *ret = (dynamic(start+1)+dynamic(start+2))%1000000007;
}


int main(void)
{
	int testcase;
	scanf("%d",&testcase);

	while(testcase--)
	{
		memset(mem,-1,sizeof(mem));
		
		scanf("%d",&N);
		printf("%d\n",dynamic(0));
		
	}
}

