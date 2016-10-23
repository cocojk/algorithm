/*
문제

깊이가 n 미터인 우물의 맨 밑바닥에 달팽이가 있습니다. 이 달팽이는 우물의 맨 위까지 기어올라가고 싶어하는데, 달팽이의 움직임은 그 날의 날씨에 좌우됩니다. 만약 비가 내리면 달팽이는 하루에 2미터를 기어올라갈 수 있지만, 날이 맑으면 1미터밖에 올라가지 못합니다.

여름 장마가 찾아와, 앞으로 m 일간 각 날짜에 비가 올 확률이 정확히 75%일 전망입니다. m 일 안에 달팽이가 우물 끝까지 올라갈 확률을 계산하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C(1≤C≤50) 가 주어집니다. 그 후 각 줄에 우물의 깊이 n(1≤n≤1000)과 장마 기간의 길이 m(1≤m≤1000) 이 주어집니다.

출력

각 테스트 케이스마다 한 줄에 m일 안에 달팽이가 우물을 탈출할 수 있을 확률을 출력합니다. 10−7 이하의 상대/절대 오차가 있는 답은 정답으로 인정됩니다.

예제 입력

4
5 4
5 3
4 2
3 2
예제 출력

0.9960937500
0.8437500000
0.5625000000
0.9375000000

*/

/* 해법 : dynamic programming
 * 접근 방식 : 
 * 결정적 사항 : running time 분석후 코딩하자.
 * 오답 원인 : 코딩 자체는 좋았으나, running time 분석 실패 
 */

#include <stdio.h>
#include <string.h>

int N,M;
double mem[1000][1000];

double dynamic(int days,int remain)
{
	if(days==M)
	{
//		printf("days %d remian %d\n",days,remain);
		return (remain<=0)?1:0;
	}

	if(remain<=0)
	{
//		printf("days %d remain %d\n",days,remain);
		return 1;
	}

	double* ret = &mem[days][remain];

	if(*ret!=-1)
	{
//	printf("days %d remian %d value %lf\n",days,remain,*ret);
		return *ret;
	}
	
	return *ret = 0.25*dynamic(days+1,remain-1)+0.75*dynamic(days+1,remain-2);
//	printf("days %d remian %d value %lf\n",days,remain,*ret);
//	return *ret;
}

int main(void)
{

	int testcase;
	int i,j;

	scanf("%d",&testcase);

	while(testcase--)
	{
		scanf("%d %d",&N,&M);
		for(i=0;i<1000;i++)
		{
			for(j=0;j<1000;j++)
				mem[i][j]=-1;
		}
		
		printf("%.10lf\n",dynamic(0,N));
	}
}




