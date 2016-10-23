/*   
문제

한 수열의 중간값(median)은 이 수열을 정렬했을 때 가운데 오는 값입니다. 예를 들어 {3,1,5,4,2}를 정렬했을 때 가운데 오는 값은 3이지요. 수열의 길이가 짝수일 때는 가운데 있는 두 값 중 보다 작은 것을 수열의 중간값이라고 정의하도록 합시다.

한 수열의 중간값은 수열에 새로운 수가 추가될 때마다 바뀔 수 있습니다. 텅 빈 수열에서 시작해서 각 수가 추가될 때마다 중간값을 계산하는 프로그램을 작성하세요. 예를 들어 3, 1, 5, 4, 2 순서대로 숫자가 추가될 경우 수열의 중간값은 3, 1, 3, 3, 3 순서로 변화합니다.

입력 생성

입력의 크기가 큰 관계로, 이 문제에서는 수열을 입력받는 대신 다음과 같은 식을 통해 프로그램 내에서 직접 생성합니다.

A[0] = 1983
A[i] = (A[i-1] * a + b) % 20090711
a와 b는 입력에 주어지는 상수입니다. 이 문제의 해법은 입력을 생성하는 방식과는 아무 상관이 없습니다.

입력

입력 파일의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 20)가 주어지고, 그 후 C줄에 각 3개의 정수로 수열의 길이 N (1 <= N <= 200,000), 그리고 수열을 생성하는 데 필요한 두 정수 a , b (0 <= a,b <= 10000) 가 주어집니다.

출력

각 테스트 케이스마다 한 줄에 N개의 중간값의 합을 20090711로 나눈 나머지를 출력합니다.

예제 입력

3
10 1 0
10 1 1
10000 1273 4936 
예제 출력

19830 
19850 
2448920
 */

/* 해법 : head 응용
 * 접근 방식 : min heap과 max heap을 나눈후 max heap | min heap 인 경우 min heap의 top이 max heap의 top보다 큰 경우 max heap의 전체 요소는 min heap의 전체 요소보다 작다는 사실을 이용하여 max heap의 top의 median이 되도록 적절하게 heap을 유지시키는 것 !
 * 결정적 사항 : 반 씩 나누고, optimal 증명 방법 귀류법 중요 !
priority_queue <int> maxHeap;
	priority_queue <int,vector<int>,greater<int> > minHeap; 초기화법 !
 * 오답 원인 :  
 */



#include <queue>
#include <stdio.h>
#include <functional>

using namespace std;
struct RNG {
	int seed,a,b;
	RNG(int ina,int inb): a(ina),b(inb),seed(1983){}
	int next()
	{
		int ret = seed;
		seed = ((seed*(long long)a)+b)%20090711;
		return ret;
	}
};

int solve(int n,RNG* rng);
int solve(int n,RNG* rng)
{
	priority_queue <int> maxHeap;
	priority_queue <int,vector<int>,greater<int> > minHeap;
	int ret=0;
	int cnt;

	for(cnt=1;cnt<=n;cnt++)
	{
		if(maxHeap.size()==minHeap.size())
			maxHeap.push(rng->next());
		else 
			minHeap.push(rng->next());

		if((!minHeap.empty())&&(!maxHeap.empty())&&(minHeap.top()<maxHeap.top()))
		{
			int a = maxHeap.top();
			int b = minHeap.top();
			maxHeap.pop();
			minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}

		ret =(ret+maxHeap.top())%20090711;
	}

	return ret;
}

int main(void)
{
	int testcase;
	scanf("%d",&testcase);

	while(testcase--)
	{
		int n,a,b;
		scanf("%d %d %d",&n,&a,&b);
		RNG* temp = new RNG(a,b);
		printf("%d\n",solve(n,temp));
		delete temp;
	}
}




