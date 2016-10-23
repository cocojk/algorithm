#include <stdio.h>
#include <string.h>

/* 해법 : dynamic programming 기초
 * 접근 방식 : 기초 
 * 결정적 사항 : yes or no  만 판단하면 되기때문에, find value 추가 
 * 오답 원인 : X
 *
 */

int N;
int memorization[100][100];
int grid[100][100];
int dynamic(int i,int j);
int find;
#define max(i,j) ((i)>(j))?(i):(j)
int dynamic(int i,int j)
{
	if(find) return 1;
	if((i>=N)||(j>=N))
	{
		return 0;
	
	}
	else if((i==N-1)&&(j==N-1))
	{
		find =1;
		return 1;
	}

	int* value = &memorization[i][j];

	if(*value!=-1)
	{
		return *value;
	}
	else 
	{
		return *value = dynamic(i+grid[i][j],j)|dynamic(i,j+grid[i][j]);
	}
}


int main(void)
{
	int testcase;
	int i,j;
	scanf("%d",&testcase);
	
	while(testcase--)
	{
		scanf("%d",&N);
		find =0;
		memset(&memorization,-1,sizeof(memorization));
		for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
			{
				scanf("%d",&grid[i][j]);
			}
		}

		if(dynamic(0,0)==0)
		{
			puts("NO");
		}
		else 
		{
			puts("YES");
		}
	}
}

