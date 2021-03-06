/*

   문제

   싸비는 윈도우XP 운영체제에 포함되어 있는 스파이더 카드게임을 매우 좋아한다. 처음에는 지는 경우가 있었는데, 점점 연습을 함에 따라 필승법을 발견하였고 매번 승리를 하게 되었다.

   스파이더 게임을 하면 플레이어에 대한 정보가 다음과 같이 주어지는데 싸비는 이것을 보다 표시되고 있는 승률을 1%이상 올리기 위해선 최소한 몇 번의 연승이 필요한지 의구심이 들었다.

   플레이 횟수 : N
   승리 횟수 : M(Z %)

   여기서 Z%의 경우 소수점을 제외한 부분의 승률이다. 즉, 승률이 88.68% 일 경우 Z = 88% 이다.

   N, M이 주어졌을 때, Z를 올리기 위한 최소한의 연승횟수가 필요한지 구하는 프로그램을 작성하라. 여기서 답이 되는 연승횟수는 2,000,000,000 이하라고 가정한다.

   입력

   입력의 첫번째 줄에는 테스트 케이스의 개수 T가 입력되고, 다음 줄 부터 한줄에 하나씩 T개의 테스트 케이스가 입력된다.
   테스트케이스는 두 개의 숫자로 이루어진다. 처음에 들어오는 숫자는 스파이더를 플레이를 한 횟수N(1<=N<=1,000,000,000)를 의미하며, 나중에 들어온 숫자는 승리한 횟수M(0<=M<=N)를 의미한다.

   출력

   각 테스트 케이스에 대해서 한줄에 승률을 올릴 수 있을 경우 이를 위한 최소한의 연승 수를 출력하며, 불가능할 경우 -1을 출력한다.

   예제 입력

   5
   10 8
   100 80
   47 47
   99000 0
   1000000000 470000000
   예제 출력

   1
   6
   -1
   1000
   19230770
*/
#include <iostream>

using namespace std;

long long N,M;

int bisection (void)
{
    long long lo = M;
    long long hi = M+2000000000;
    long long loRate = (M*100)/N;
    long long hiRate = (hi*100)/(N+hi-M);

    // 반복문 불변식 : loRate == N/M , hiRate > N/M
    while (lo+1 < hi)
    {
        long long mid = (lo+hi)/2;
        long long midRate = (mid*100)/(mid-M+N);

        if (midRate == loRate)
        {  
            lo = mid;
        }
        else 
        {
            hi = mid;
        }
    }
    
    return (hi>2000000000)?-1:hi-M;
}

int main (void)
{
    int testcase;
    cin >> testcase;

    while (testcase--)
    {
        cin >> N >> M;
        cout << bisection() << endl;
    }
}



