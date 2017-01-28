/*
   문제

   judge-attachments/c32422238dae9e7dcb7c3d878c5f1c15/arctic.png

   남극에는 N 개의 탐사 기지가 있습니다. 남극의 겨울은 혹독하기 때문에, 남극의 겨울이 찾아오면 탐사 기지들간의 왕래가 중단됩니다. 겨울에도 서로 통신하며 연구를 지속하기 위해, N 개의 무전기를 구입해 각 탐사 기지에 배치하려 합니다. 이 때, 두 탐사 기지 사이의 거리가 D 라고 하면, 무전기의 출력이 D 이상이어야만 통신이 가능합니다. 모든 탐사 기지에는 똑같은 무전기가 지급됩니다. 탐사 본부가 다른 모든 기지에 연락을 할 수 있기 위해 필요한 무전기의 최소 출력은 얼마일까요?

   탐사 본부는 다른 기지를 통해 간접적으로 연락할 수 있다고 가정합니다.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (<= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 기지의 수 N (<= 100)이 주어지고, 그 다음 줄에 2개씩의 실수로 각 기지의 좌표 (x,y) 가 주어집니다. 기지의 위치는 0 이상 1000 이하의 실수입니다. 이 때 첫 번째 주어지는 기지가 탐사 본부라고 가정합니다.

   출력

   각 테스트 케이스마다, 탐사 본부가 다른 모든 기지에 연락을 할 수 있기 위해 필요한 최소 무전기의 출력을 소숫점 밑 셋째 자리에서 반올림해 출력합니다.

   예제 입력

   2
   5
   0 0
   1 0
   1 1
   1 2
   0 2
   6
   1.0 1.0
   30.91 8
   4.0 7.64
   21.12 6.0
   11.39 3.0
   5.31 11.0
   예제 출력

   1.00
   10.18
   노트
*/
   
#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;

int n;
const int MAXN = 100;
double x[MAXN];
double y[MAXN];
int parent[MAXN];
int ranks[MAXN];
int num[MAXN];

int find (int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
}

void merge (int u, int v) {
    u = find(u);
    v = find(v);

    // u와 v가 이미 같은 집합에 속하는 경우를 걸러낸다.
    if (u == v)
        return ;
    if (ranks[u] > ranks[v])
        swap(u,v);

    num[find(v)] += num[find(u)];
    parent[u] = v;
    if (ranks[u] == ranks[v]) ranks[v]++;
}

void preCalc(void)
{
    for (int i = 0; i < n; i++)
    { 
        parent[i] = i;
        ranks[i] = 1;
        num[i] = 1;
    }
}
    
int isConnected (int i, int j, double d)
{
    return ((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) <= d*d);
}


// d 이하의 경우가 존재하는지 ?
int decision (double d)
{
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            if (isConnected(i,j,d))
            {
                merge(i,j);
            }
        }

    return (num[find(0)] == n);
}
            
double optimization (void)
{
    double lo = 0, hi = 1416;

    for (int it = 0; it < 100; it++) {
        double mid = (lo+hi)/2.0;
        preCalc();
        if (decision(mid))
            hi = mid;
        else 
            lo = mid;
    }

    return lo;
}

int main (void)
{
    int testcase;
    cin >> testcase;

    while (testcase--)
    {
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cin >> x[i] >> y[i];
        }

        printf("%.2lf\n",optimization());
    }
}

      




