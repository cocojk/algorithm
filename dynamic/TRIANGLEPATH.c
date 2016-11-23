/*
   문제

   6
   1  2
   3  7  4
   9  4  1  7
   2  7  5  9  4
   위 형태와 같이 삼각형 모양으로 배치된 자연수들이 있습니다. 맨 위의 숫자에서 시작해, 한 번에 한 칸씩 아래로 내려가 맨 아래 줄로 내려가는 경로를 만들려고 합니다. 경로는 아래 줄로 내려갈 때마다 바로 아래 숫자, 혹은 오른쪽 아래 숫자로 내려갈 수 있습니다. 이 때 모든 경로 중 포함된 숫자의 최대 합을 찾는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C(C <= 50)가 주어집니다. 각 테스트 케이스의 첫 줄에는 삼각형의 크기 n(2 <= n <= 100)이 주어지고, 그 후 n줄에는 각 1개~n개의 숫자로 삼각형 각 가로줄에 있는 숫자가 왼쪽부터 주어집니다. 각 숫자는 1 이상 100000 이하의 자연수입니다.

   출력

   각 테스트 케이스마다 한 줄에 최대 경로의 숫자 합을 출력합니다.

   예제 입력

   2
   5
   6
   1  2
   3  7  4
   9  4  1  7
   2  7  5  9  4
   5
   1 
   2 4
   8 16 8
   32 64 32 64
   128 256 128 256 128
   예제 출력

   28
   341
 */

/* 해법 : dynamic programming
 * 접근 방식 : subproblem optimality
 * 결정적 사항 :
 * 오답 원인 : 경우의 수 프로그램 실패 
 */


#include <stdio.h>
#include <string.h>

int T[100][100];
int Input[100][100];
int N;

#define MAX(i,j) ((i)>(j))?(i):(j)
int dynamic(int y,int x);
inline int max(int i,int j);
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

int main(void)
{
	int testcase;
	int i,j;

	scanf("%d",&testcase);

	while(testcase--)
	{
		scanf("%d",&N);
		memset(T,-1,sizeof(T));
		for(i=0;i<N;i++)
		{
			for(j=0;j<(i+1);j++)
			{
				scanf("%d",&Input[i][j]);
			}
		}



		printf("%d\n",dynamic(0,0));

	}

}











