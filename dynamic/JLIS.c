/*
   문제

   어떤 수열에서 0개 이상의 숫자를 지운 결과를 원 수열의 부분 수열이라고 부릅니다. 예를 들어 '4 7 6'은 '4 3 7 6 9'의 부분 수열입니다. 중복된 숫자가 없고 오름 차순으로 정렬되어 있는 부분 수열들을 가리켜 증가 부분 수열이라고 부르지요. 예를 들어 '3 6 9'는 앞의 수열의 증가 부분 수열입니다.

   두 개의 정수 수열 A 와 B 에서 각각 증가 부분 수열을 얻은 뒤 이들을 크기 순서대로 합친 것을 합친 증가 부분 수열이라고 부르기로 합시다. 이 중 가장 긴 수열을 합친 LIS(JLIS, Joined Longest Increasing Subsequence)이라고 부릅시다. 예를 들어 '1 3 4 7 9' 은 '1 9 4' 와 '3 4 7' 의 JLIS입니다. '1 9' 와 '3 4 7' 을 합쳐 '1 3 4 7 9'를 얻을 수 있기 때문이지요.

   A 와 B 가 주어질 때, JLIS의 길이를 계산하는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 c ( 1 <= c <= 50 ) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 A 와 B 의 길이 n 과 m 이 주어집니다 (1 <= n,m <= 100). 다음 줄에는 n 개의 정수로 A 의 원소들이, 그 다음 줄에는 m 개의 정수로 B 의 원소들이 주어집니다. 모든 원소들은 32비트 부호 있는 정수에 저장할 수 있습니다.

   출력

   각 테스트 케이스마다 한 줄에, JLIS 의 길이를 출력합니다.

   예제 입력

   3
   3 3
   1 2 4
   3 4 7
   3 3
   1 2 3
   4 5 6
   5 3
   10 20 30 1 2
   10 20 30
   예제 출력

   5
   6
   5
 */

/* 해법 : dynamic programming
 * 접근 방식 : 
 * 결정적 사항 : running time 분석후 코딩하자.
 * 오답 원인 : 코딩 자체는 좋았으나, running time 분석 실패 
 */

#include <stdio.h>
#include <string.h>

int jlis(int indexA,int indexB);
const long long NEGINF = 0x8000000000000000;
int n,m;
int A[100];
int B[100];
int memoization[101][101];
#define max(i,j) ((i)>(j))?(i):(j)

int jlis(int indexA,int indexB)
{
	int * ret = &memoization[indexA+1][indexB+1];
	int nextA,nextB;
	int temp;

	if(*ret!=-1)
		return *ret;

	*ret = 2;
	long long a = (indexA==-1?NEGINF:A[indexA]);
	long long b = (indexB==-1?NEGINF:B[indexB]);
	long long maxElement = max(a,b);

	for(nextA=indexA+1;nextA<n;nextA++)
		if(maxElement<A[nextA])
		{
			temp = jlis(nextA,indexB)+1;
			*ret = max(*ret,temp);
		}
	for(nextB=indexB+1;nextB<m;nextB++)
		if(maxElement<B[nextB])
		{
			temp = jlis(indexA,nextB)+1;
			*ret = max(*ret,temp);
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

		scanf("%d %d",&n,&m);
		for(i=0;i<n;i++)
		{
			scanf("%d",&A[i]);
		}

		for(i=0;i<m;i++)
		{
			scanf("%d",&B[i]);
		}

		printf("%d\n",jlis(-1,-1)-2);
	}
}









