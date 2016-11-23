#include <stdio.h>
#include <string.h>

int T[100][100];
int countCache[100][100];
int Input[100][100];
int N;

#define MAX(i,j) ((i)>(j))?(i):(j)
int dynamic(int y,int x);
inline int max(int i,int j);
int countDynamic(int y,int x);
int dynamic(int y,int x)
{
	if(y==(N-1))
		return Input[y][x];
	
	int* ret = &T[y][x];

	if(*ret!=-1) 
		return *ret;
	
	return *ret = (max(dynamic(y+1,x),dynamic(y+1,x+1))+Input[y][x]);
}

inline int max(int i,int j)
{
	return MAX(i,j);
}

int countDynamic(int y,int x)
{
	if(y==N-1)
		return 1;

	int* ret = &countCache[y][x];
	
	if(*ret!=-1)
		return *ret;

	*ret =0;
	if(dynamic(y+1,x)>=dynamic(y+1,x+1))
		*ret += countDynamic(y+1,x);

	if(dynamic(y+1,x)<=dynamic(y+1,x+1))
		*ret += countDynamic(y+1,x+1);

	return *ret;
}

int main(void)
{
	int testcase;
	int i,j;

	scanf("%d",&testcase);

	while(testcase--)
	{
		scanf("%d",&N);
		memset(T,-1,sizeof(T));
		memset(countCache,-1,sizeof(countCache));
		for(i=0;i<N;i++)
		{
			for(j=0;j<(i+1);j++)
			{
				scanf("%d",&Input[i][j]);
			}
		}



		printf("%d\n",countDynamic(0,0));

	}

}












