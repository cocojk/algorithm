/*
문제

계란 한 개에 _ _ _ _ _ _ _ _ _ _ _ _ _ 웨브바짐 달러!
계획 경제의 실패로 세계 최고의 인플레이션을 자랑하게 된 공산 국가 웨브바짐에서는 하루 중에도 물가가 계속 오르기 때문에 물건의 가격을 실시간으로 바꿔야 합니다. 웨브바짐에서 가장 큰 무가베 마트에서는 그래서 위와 같이 빈 칸만 쓰여 있는 광고판을 붙여놓고 계란 가격이 오름에 따라 (정확히는 웨브바짐 달러의 가치가 추락함에 따라) 실시간으로 숫자가 크게 적힌 플라스틱 판을 빈 칸에 갈아 끼웁니다. 예를 들어 계란 한 개에 35억 웨브바짐 달러라고 하면, 3이 쓰인 판 한 개, 5가 쓰인 판 한 개, 0이 쓰인 판 여덟 개를 빈칸에 순서대로 끼우는 것이죠.

무가베 마트에서 아르바이트를 하는 종욱이는 어느 날 곤란한 손님을 맞았습니다. 이 손님은 아까 사 갔던 계란을 환불하겠다고 돌아왔는데, 영수증을 잃어버린데다 계란을 얼마에 샀는지를 기억하지도 못한다고 하는군요. 계란 값은 그 사이 한 번 또 올랐기 때문에 광고판에 적힌 가격은 이미 바뀐 뒤입니다. 다행히 종욱이는 두 가지를 기억합니다.

마지막에 계란 가격이 올랐을 때, 종욱이는 광고판에 꽂힌 플라스틱 판의 순서만 바꿨습니다. 다른 플라스틱 판을 가져오거나 있던 플라스틱 판을 뺄 일은 없었다는 것이죠.
마지막 계란 가격을 보면서 '와 이거면 정확히 사탕 m개를 살 수 있구나' 라고 생각했습니다. 따라서 마지막 계란 가격은 m의 배수였습니다. (사탕 가격도 이미 올랐기 때문에 이걸 가지고 계란 가격을 계산할 수는 없습니다)
지금 계란 가격 e와 m이 주어질 때 가능한 이전 계란 가격이 몇 가지나 있는지 계산하는 프로그램을 작성하세요. 이전 계란 가격은 e 보다 항상 작아야 합니다.

입력

입력의 첫 줄에는 테스트 케이스의 수 c (c <= 50) 가 주어집니다. 그 후 c줄에 각각 2개의 자연수 e와 m (1 <= e <= 10^14, 2 <= m <= 20)이 주어집니다. 현재 계란 가격은 0으로 시작하지 않지만, 이전 계란 가격은 0으로 시작할 수 있습니다.

출력

각 테스트 케이스마다 한 줄에 가능한 가격의 수를 1,000,000,007 로 나눈 나머지를 출력하세요.

예제 입력

4
321 3
123 3
422 2
12738173912 7 
예제 출력

5
0
2
11033
*/
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>

using namespace std;

const int MOD = 1000000007;
// length
int n;
int m;
int memoization [1<<14][20];
int e [15];

// 과거 가격을 앞 자리부터 채워나가고 있다.
// solve()에서 현재 가격보다 작은 경우의 수에 대해서만 permutation을 수행하기 때문에 
// 주어진 used에 대해 앞으로의 permuation 해주면 된다.
// mod : 지금까지 만든 가격의 m에 대한 나머지 
// used : 지금까지 사용한 자릿수들의 집합 
int permutation (int mod,int used)
{
    // 중복 셈을 방지하기 위한 장치
    int visited[10];

    if ( used == ((1<<n) -1))
    {
        return (mod % m == 0) ? 1 : 0;
    }
    
    int* ret = &memoization[used][mod];

    if (*ret != -1)
        return *ret;

    int size = __builtin_popcount(used);

    memset(visited,0,sizeof(visited));

    *ret = 0;
    for (int i = 0; i < n; i ++)
    {
        if ( used & (1<<(n-1-i)) || visited[e[i]])
            continue;

        *ret = (*ret + permutation ((mod*10 +e[i])%m,(used | (1<<(n-1-i)))))%MOD;
        visited[e[i]]=1;
    }

    return *ret;
}

// 현재 가격 e보다 작은 값을 가질 수 있는 경우 permutation 호출 
int solve ()
{
    int ret = 0;
    int used = 0;
    int mod = 0;
    // 동일한 계산 방지를 위한 장치 
    int visited[10];
    for (int i = 0; i < n; i ++)
    {
        memset(visited,0,sizeof(visited));
        if (i != 0)
        {
            mod = (mod*10 + e[i-1] )% m;
            used = used |  (1 << (n-i));
        }

        for (int j = i +1 ; j < n; j ++)
        {
            if (e[j] < e[i] && (!visited[e[j]]))
            {
            //          printf("mod : %d used : %x %d\n",mod,used|(1<<n-1-j),permutation((mod*10+e[j])%m,used | (1<<(n-1-j))));
                ret = (ret + permutation( (mod*10 + e[j])%m,used | (1<<(n-1-j))))%MOD;
                visited[e[j]] = 1;
            }
        }
    }

    return ret;
}

int main (void)
{
    int testcase;
    string input;
    cin >> testcase;

    while (testcase--)
    {
        cin >> input >> m;
        memset(memoization,-1,sizeof(memoization));
        n = input.size();
        for (int i = 0; i < n; i++)
        {
            e[i] = input[i] -'0';
        }

        cout << solve() <<endl;
    }
}
