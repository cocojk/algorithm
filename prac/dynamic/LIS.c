/*
문제

어떤 정수 수열에서 0개 이상의 숫자를 지우면 이 수열의 부분 수열 (subsequence) 를 얻을 수 있다. 예를 들어 10 7 4 9 의 부분 수열에는 7 4 9, 10 4, 10 9 등이 있다. 단, 10 4 7 은 원래 수열의 순서와 다르므로 10 7 4 9 의 부분 수열이 아니다.

어떤 부분 수열이 순증가할 때 이 부분 수열을 증가 부분 수열 (increasing subsequence) 라고 한다. 주어진 수열의 증가 부분 수열 중 가장 긴 것의 길이를 계산하는 프로그램을 작성하라.

어떤 수열의 각 수가 이전의 수보다 클 때, 이 수열을 순증가 한다고 한다.

입력

입력의 첫 줄에는 테스트 케이스의 수 C (<= 50) 가 주어진다. 각 테스트 케이스의 첫 줄에는 수열에 포함된 원소의 수 N (<= 500) 이 주어진다. 그 다음 줄에 수열이 N개의 정수가 주어진다. 각 정수는 1 이상 100,000 이하의 자연수이다.

출력

각 테스트케이스마다 한 줄씩, 주어진 수열의 가장 긴 증가 부분 수열의 길이를 출력한다.

예제 입력

3
4
1 2 3 4
8
5 4 3 2 1 6 7 8 
8
5 6 7 8 1 2 3 4
예제 출력

4
4
4
 */

/* 해법 : dynamic programming
 * 접근 방식 : 
 * 결정적 사항 : running time 분석후 코딩하자.
 * 오답 원인 : 코딩 자체는 좋았으나, running time 분석 실패 
 */

#include <stdio.h>
#include <string.h>

int memoization[500];
int sequence[500];
int N;

#define max(i,j) ((i)>(j))?(i):(j)
int dynamic(int start)
{
	int* ret = &memoization[start+1];
	int next;
	int temp;
	if(*ret!=-1) return *ret;

	*ret = 1;

	for(next=start+1;next<N;next++)
	{
		if(start==-1||sequence[start]<sequence[next])
		{
			temp = dynamic(next)+1;
			*ret = max(*ret,temp);
		}
	}

	return *ret;
}

	

int main(void)
{
	int testcase;
	int i;
	scanf("%d",&testcase);


	while(testcase--)
	{
		memset(memoization,-1,sizeof(memoization));
		
		scanf("%d",&N);
		for(i=0;i<N;i++)
		{
			scanf("%d",&sequence[i]);
		}

		printf("%d\n",dynamic(-1)-1);

	}
}





