/* 
문제

대 성황이었던 지난 알고스팟 연간 모의고사 이후 프로그래밍 대회의 열기는 날로 뜨거워져 올해는 10만명이 넘는 사람들이 참가 신청을 할 것으로 예상되고 있습니다. 그러나 채점관을 할 자원 봉사자는 예년과 똑같이 5명뿐이라, 이 사람들을 대회에 다 참가시킬 수는 없습니다. 따라서 올해에도 참가 신청을 한 사람 중 진정한 프로그래밍 너드들만을 대회에 참가할 수 있도록 받아 주기로 했습니다.

종만의 새로운 이론에 따르면, 어떤 사람의 너드 지수는 다음 두 가지 값에 의해 결정됩니다.

알고스팟 온라인 채점 시스템에서 푼 문제의 수 p
밤 새면서 지금까지 끓여먹은 라면 그릇 수 q
이 이론에 따르면 어떤 참가 신청자 a 의 문제 수 pa 와 그릇 수 qa 를 다른 참가 신청자 b 의 문제 수 pb 와 그릇 수 qb 에 각각 비교했을 때, pa < pb, qa < qb 라면 참가 신청자 a 는 너드일 가능성이 없습니다. 조직위는 너드일 가능성이 있는 사람들만을 대회에 받아주기로 했습니다.

한 사람의 참가 가능 여부는 다른 사람들에 의해 결정되기 때문에, 대회에 참가할 수 있는 사람의 수는 새로운 사람이 참가 신청을 할 때마다 계속 바뀝니다. 예를 들어 다음과 같은 4명의 사람들이 순서대로 참가 신청을 했다고 합시다.

참가자	종만	재훈	효승	광규
문제 수	72	57	74	64
라면 그릇 수	50	67	55	60
종만과 재훈이 순서대로 대회 참가 신청을 하면 대회에 참가할 수 있는 사람의 수는 각각 1, 2 로 늘어나지만, 효승이는 문제 수도 라면 그릇 수도 종만보다 많으므로 효승이 참가 신청을 한 시점에서 종만은 더 이상 대회에 참가할 수 없습니다. 따라서 이 네 명이 참가 신청을 할 때마다 참가 가능자의 수는 1, 2, 2, 3으로 변합니다.

이렇게 각 사람이 참가 신청을 할 때마다 대회에 참가할 수 있는 사람들의 수가 어떻게 변하는지 계산하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 참가 신청한 사람들의 수 N (1 <= N <= 50000) 이 주어집니다. 그 후 N 줄에 각 2개의 정수로 각 사람의 문제 수 pi 와 라면 그릇 수 qi 가 참가 신청한 순서대로 주어집니다 (0 <= pi,qi <= 100000) . 두 사람의 문제 수나 라면 그릇 수가 같은 경우는 없다고 가정해도 좋습니다.
입력의 양이 많으므로 가능한 빠른 입력 함수를 사용하는 것이 좋습니다.

출력

각 사람이 참가 신청을 할 때마다 대회 참가 자격이 되는 사람의 수를 계산한 뒤, 각 테스트 케이스마다 그 합을 출력합니다.

예제 입력

2
4
72 50
57 67
74 55
64 60
5
1 5
2 4
3 3
4 2
5 1
예제 출력

8
15
 
 */

/* 해법 : 포함영역 지우기 !!
 * 접근 방식 : 
 * 결정적 사항 : 
 * 오답 원인 :  
 */


#include <map>
#include <stdio.h>

using namespace std;
map<int,int> p;
int solve(int x,int y);
int isOccupy(int x,int y);
void removeOccupied(int x,int y);
int isOccupy(int x,int y)
{
	map<int,int>::iterator it = p.lower_bound(x);
	if(it==p.end())
		return 0;

	return (it->second>y);
}

void removeOccupied(int x,int y)
{
	map<int,int>::iterator it = p.lower_bound(x);
	if(it==p.begin())
		return;
	it--;

	while(1)
	{
		if(it->second>y)
			break;

		if(it==p.begin())
		{
			p.erase(it);
			break;
		}
		else 
		{
			map<int,int>::iterator temp= it;
			temp--;
			p.erase(it);
			it = temp;
		}
	}
}

int solve(int x,int y)
{
	if(isOccupy(x,y))
		return p.size();
	removeOccupied(x,y);
	p[x]=y;
	return p.size();
}


int main(void)
{
	int testcase;
	int i,x,y,answer;
	scanf("%d",&testcase);
	
	while(testcase--)
	{
		answer=0;
		scanf("%d",&i);
		while(i--)
		{
			scanf("%d %d",&x,&y);
			answer+=solve(x,y);
		}

		printf("%d\n",answer);
		p.clear();
	}
}




