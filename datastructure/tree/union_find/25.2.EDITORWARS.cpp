#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>

using namespace std;

int ranks [10000];
int parent [10000];
int enemy [10000];
int size [10000];

void init (int n)
{
    for (int i = 0; i < n; i++)
    {
        ranks[i] = 1;
        parent[i] = i;
        enemy[i] = -1;
        size[i] = 1;
    }
}

int find (int u)
{
    if (u == -1)
        return -1;

    if (u == parent[u])
        return u;
    
    return parent[u] = find(parent[u]);
}

int merge (int u, int v)
{
    // u나 v가 공집합인 경우 나머지 하나를 반환한다.
    if (u == -1 || v == -1)
        return max (u,v);

    u = find(u);
    v = find(v);

    // already same set 
    if (u == v)
        return u;

    if (ranks[u] > ranks[v])
        swap(u,v);

    size[v] += size[u];
    parent[u] = v;
    
    if (ranks[u] == ranks[v])
        ranks[v]++;

    return v;
}

// u와 v가 서로 적대하는 집합에 속한다.
int setDis (int u, int v)
{
    // 우선 루트를 찾는다.
    u = find(u);
    v = find(v);

    // 같은 집합에 속해 있으면 모순!
    if (u == v)
        return 0;
    
    // 적의 적은 나의 동지 
    int a = merge (u,enemy[v]), b = merge(v,enemy[u]);
    enemy[a] = b;
    enemy[b] = a;
    return 1;
}

// u와 v가 같은 집합에 속한다.
int setAck (int u, int v)
{
    // 우선 루트를 찾는다.
    u = find(u);
    v = find(v);

    // 두 집합이 서로 적대 관계라면 모순 
    if(enemy[u] == v)
        return 0;

    // 동지의 적은 나의 적 
    int a = merge(u,v), b = merge(enemy[u],enemy[v]);
    enemy[a] = b;
    // 두 집합 다 적대하는 집합이 없으면 b는 -1일 수도 있다.
    if(b != -1)
        enemy[b] = a;
    return 1;
}

int answer (int n)
{
    int ret = 0;
    for (int node = 0; node < n; node++)
    {
        if(parent[node] == node) {
            int enemy = buf.enemy[node];
            // 같은 모임 쌍을 두번 세지 않기 위해 enemy < node인 경우만 센다.
            // enemy == -1 인 경우도 정확히 한 번씩 세게 된다.
            if (enemy  > node)
                continue;
            int mySize = size[node];
            int enemySize = (enemy == -1 ? 0 : size[enemy]);
            // 두 집합 중 큰 집합을 더한다.
            ret += max(mySize,enemySize);
        }

    }

    return ret;
}




         




int main (void)
{
    int testcase,n,state,u,v,checker;
    string input;
    cin >> testcase;

    while (testcase--)
    {
        checker = 0;
        cin >>n>>state;
        init(n);
        for (int i = 0; i < state; i++)
        {
            cin>>input>>u>>v;
            if (input == "ACK")
            {
                if(!setAck(u,v))
                {
                    checker = 1;
                    printf("CONTRADICTION AT %d\n",i+1);
                    for (int j = i+1; j <state; j++)
                        cin >>input>>u>>v;
                    break;
                }
            }
            else 
            {
                if(!setDis(u,v))
                {
                    checker = 1;
                    printf("CONTRADICTION AT %d\n",i+1);
                    for (int j = i+1; j <state; j++)
                        cin >>input>>u>>v;
                    break;
                }
            }
         }
        
         if (!checker)
            printf("MAX PARTY SIZE IS %d\n",answer(n));
    }
}




        




