#include <stdio.h>
#include <string.h>


int N;
int mem[200][100];
int input[200][100];

#define MAX(i,j) ((i)>(j))?(i):(j)

int dynamic(int level,int offset)
{
	int temp1,temp2,temp3;
	if(level==(2*N-1))
		return 0;

	int* ret = &mem[level][offset];

	if(*ret!=-1)
		return *ret;
	
	temp1 = dynamic(level+1,offset);
	temp2 = dynamic(level+1,offset+1);
	temp1 = MAX(temp1,temp2);
	temp1 += input[level][offset];
	return *ret = temp1;
}

int main(void)
{
	int testcase;
	int i,j;
	scanf("%d",&testcase);

	while(testcase--)
	{
		scanf("%d",&N);
		memset(mem,-1,sizeof(mem));
		memset(input,0,sizeof(input));
		for(i=0;i<N;i++)
		{
			for(j=0;j<i+1;j++)
			{
				scanf("%d",&input[i][j]);
			}
		}

		for(i=0;i<N-1;i++)
		{
			for(j=i+1;j<N;j++)
			{
				scanf("%d",&input[N+i][j]);
			}
		}


		

		printf("%d\n",dynamic(0,0));
	}
}








