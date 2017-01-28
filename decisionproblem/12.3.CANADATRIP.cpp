/*
문제

동건이는 여름 방학을 맞아 자동차를 끌고 캐나다 횡단 여행을 떠나기로 했습니다. 캐나다의 1번 고속도로는 세계에서 가장 긴 고속도로 중 하나로, 캐나다의 동쪽 끝에서 서쪽 끝까지 있는 모든 주요 도시를 연결합니다. 동건이는 이 고속도로를 타고 캐나다의 서쪽 끝 빅토리아에서 동쪽 끝 세인트 존까지 8,030km 를 달리기로 마음먹었습니다.

이 고속도로는 굉장히 많은 표지판이 있기로도 유명합니다(이 문장부터는 사실이 아닙니다..). 이 고속도로는 N개의 주요 도시를 지나치는데, 각 도시까지의 남은 거리를 나타내는 표지판이 많기 때문입니다. i번째 도시까지의 거리를 나타내는 표지판은 도시에 도착하기 Mi미터 전부터 시작해서 도시에 도착할 때까지 Gi미터 간격으로 설치되어 있습니다. 예를 들어 M0=500이고 G0=50이라고 하면 여행자는 다음과 같은 11개의 표지판을 순서대로 보게 됩니다.

"0번 도시 500미터 전"
"0번 도시 450미터 전"
...
"0번 도시 50미터 전"
"0번 도시: 환영합니다"
시작점으로부터 각 도시까지의 거리 Li와 Mi, Gi가 주어질 때, 시작점으로부터 여행하면서 동건이가 보게 되는 K번째 표지판의 위치를 계산하는 프로그램을 작성하세요. 한 위치에 표지판이 여러 개 있을 경우에도 각각의 표지판을 따로 세기로 합니다.

입력

입력의 첫 줄에는 테스트 케이스의 수 T (T <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 도시의 수 N (1 <= N <= 5000) 과 K (1 <= K <= 2^31-1) 가 주어집니다. 그 후 N줄에는 각 3개의 정수로 Li, Mi, Gi (1 <= Gi <= Mi <= Li <= 8,030,000) 가 주어집니다. Mi는 항상 Gi의 배수입니다. K는 항상 총 표지판의 수 이하입니다.

입출력 데이터의 양이 많으니 빠른 입출력 방법을 사용하시기 바랍니다.

출력

각 테스트 케이스마다 한 줄에 K번째 표지판의 위치를 출력합니다.

예제 입력

2
3 15
500 100 10
504 16 4
510 60 6
2 1234567
8030000 8030000 1
2 2 1
예제 출력

480
1234563
*/

#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 8030000
int N,K;
int L[MAXN];
int M[MAXN];
int G[MAXN];


// 거리 d에 k개 이상 포함되는 가?
int decision (int d)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if ( (L[i] - M[i]) <= d)
        {
            count += (((min(d,L[i]) - (L[i]-M[i])) / G[i]) + 1);
        }
    }

    return count >= K;
}


int optimize (void)
{
    // 반복문 불변식 : !decision(lo) && decision(hi)
    // hi는 항상 decision(hi)를 만족해야하고, lo는 항상 decision(lo)를 만족하지 않는다.
    // 즉 hi는 정확히 K개 포함할 수도 있지만, lo는 항상 정확히 K개를 포함하지 않는다.
    // 100 99 98 
    // hi     lo 일때 decision (99)가 참일 경우 99가 답이 되고, decision (99)가 거짓일 경우 100이 답이 된다.
    // decision (99)가 참일 경우 hi가 99로 바뀌게 되고, lo는 답이 될 수 없으므로 hi가 답이 되고,
    // decision (99)가 거짓일 경우 lo가 99로 바뀌게 되고, lo는 답이 될 수 없으므로 hi가 답이 된다. 
    // hi는 decision (k)가 참일 때 k로 변경된다. (답 include 가능)
    // lo는 decision (k)가 거짓일 때 k로 변경된다. (답 include 불가능)
    int lo = -1;
    int hi = 8030001;

    while (lo + 1 < hi) {
        
        int mid = (lo + hi) / 2;
        
        if (decision(mid))
            hi = mid;
        else 
            lo = mid;
    }

    return hi;
}

void read (void)
{
    cin >> N >> K;

    for (int i = 0; i < N; i++)
    {
        cin >> L[i] >> M[i] >> G[i];
    }
}

int main (void)
{
    int testcase;
    cin >> testcase;

    while (testcase--)
    {
        read();
        cout << optimize() <<endl;
    }
}




