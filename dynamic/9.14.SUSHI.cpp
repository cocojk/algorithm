/*
문제

문제 풀이 내기에서 모인 벌금이 많이 쌓여서 알고스팟 운영진들은 회식을 하러 회전초밥집에 갔습니다. 회전초밥집에 들어선 운영진들은 초밥은 먹지 않고 전략 회의를 시작했습니다. 회전초밥집에는 n종류의 메뉴가 있는데, 운영진들은 각 메뉴에 대해 선호도를 매겼습니다.

초밥	계란	연어	장어	대뱃살	스테이크	후라이드 치킨
가격	2500	3000	4000	5000	10000	15000
선호도	7	9	10	12	20	1
운영진들은 주어진 예산 안에서 선호도의 합을 최대한으로 하도록 초밥을 먹고 싶습니다. 각 종류의 초밥은 무한정으로 공급된다고 가정합시다. 이 때 얻을 수 있는 최대한의 선호도는 얼마일까요?

입력

입력의 첫 줄에는 테스트 케이스의 수 c(1 <= c <= 50)가 주어집니다. 각 테스트 케이스의 첫 줄에는 초밥의 종류 n(1 <= n <= 20)과 운영진들의 예산 m (1 <= m <= 2,147,483,647)이 주어집니다. 그 후 n 줄에 각 초밥의 가격과 선호도가 순서대로 주어집니다. 가격은 20,000 이하의 자연수로, 항상 100 의 배수입니다. 선호도는 20 이하의 자연수입니다.

출력

각 테스트 케이스별로 한 줄에 가능한 선호도의 최대 합을 출력합니다.

예제 입력

2
6 10000
2500 7
3000 9
4000 10
5000 12
10000 20
15000 1
6 543975612
2500 7
3000 9
4000 10
5000 12
10000 20
15000 1 
예제 출력

28
1631925
*/
#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

int n;
int m;
int prices [20];
int priority [20];
int c [201];

// 최대 만족도의 합을 반환한다.
// m과 prices[]는 이미 100으로 나뉘어 있다고 가정한다.
int eat ()
{
    int ret = 0;
    c[0] = 0;
    for (int budget = 1; budget <= m; budget++) {
        int cand = 0;
        for (int dish = 0; dish < n; dish++)
            if (budget >= prices[dish])
                cand = max (cand,c[(budget-prices[dish])%201] + priority[dish]);
        c[budget % 201] = cand;
        ret = max (ret,cand);
    }
    return ret;
}


int main (void)
{
    int testcase;

    cin >> testcase;

    while (testcase--)
    {
        cin >> n >> m;

        m = m/100;
        for (int i = 0; i < n ; i++)
        {
            cin >> prices[i] >> priority[i];
            prices[i] = prices[i]/100;
        }

        
        cout << eat () << endl;
    }
}