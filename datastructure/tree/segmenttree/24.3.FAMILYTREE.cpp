/*
   문제

   촌수는 혈연관계의 멀고 가까움을 의미하는 숫자로, 고려 말에 들어와 조선 시대에 정착된 것으로 알려져 있습니다. 촌수를 세는 계촌법은 부모와 자식간이 1촌이 되는 것을 기본으로 합니다. 두 사람의 촌수는 이 두 사람이 부모 자식 관계를 몇 번이나 따라가야 서로 연결되는가를 나타내지요. 예를 들어 형제자매는 같은 부모를 공유하기 때문에 2촌입니다. 조부모의 자식, 즉 부모의 형제자매는 이와 같은 원리로 3촌이지요.

   어떤 가문의 족보가 시조부터 시작해 쭉 주어질 때, 두 사람의 촌수를 계산하는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다. 각 테스트 케이스는 한 가문의 족보와 촌수를 계산할 사람들의 쌍들로 구성됩니다.

   각 테스트 케이스의 첫 줄에는 족보에 포함된 사람의 수 N (1 <= N <= 100,000) 과 촌수를 계산할 두 사람의 수 Q (1 <= Q <= 10,000) 가 주어집니다. 이 때 족보에 포함된 사람들은 0번부터 N-1 번까지 번호가 매겨져 있으며, 0번은 항상 이 가문의 시조입니다. 테스트 케이스의 두 번째 줄에는 N-1 개의 정수로 1번부터 N-1 번까지 각 사람의 아버지의 번호가 주어집니다. 그 다음 Q 줄에 각 2개의 정수로 두 사람의 번호 a, b 가 주어집니다. (0 <= a,b < N)

   족보에는 시조의 후손이 아닌 사람은 주어지지 않으며, 자기 자신의 조상이 되는 등의 모순된 입력 또한 주어지지 않습니다.

   입력의 크기가 크므로 가능한 빠른 입력 방법을 사용하는 것이 좋습니다.

   출력

   각 사람의 쌍마다 한 줄에 두 사람의 촌수를 출력합니다.

   예제 입력

   1
   13 5
   0 1 1 3 3 0 6 0 8 9 9 8
   2 7
   10 11
   4 11
   7 7
   10 0
   예제 출력

   4
   2
   6
   0
   3
*/

#include <algorithm>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;


const int INF = 987654321;

vector<int> lca;
// index : serial number
vector<int> trip;

int firstIndex [100000];
int depth [100000];

vector<int> child [100000];
int nextSerial;

int no2Serial [100000];

// function prototype
void init (int n);
int query (int u, int v);
void clean (int n);
void makeGraph (int size);
void traverse (int here,int depth);
int segmentTreeInit (int node, int left, int right);
int queryImp (int node, int leftNode,int rightNode,int left, int right);


void init (int n)
{
    nextSerial = 0;
    makeGraph (n);
    trip.reserve (2*n-1);
    traverse (0,0);
    lca.reserve (4*(2*n-1));
    segmentTreeInit (1,0,2*n-1);
}

int query (int n,int u, int v)
{
    int left = no2Serial[u];
    int right = no2Serial[v];

    if (left > right)
        swap(left,right);
    int lcaIndex = queryImp (1,0,2*n-1,firstIndex[left],firstIndex[right]);
    return depth[left] + depth[right] - 2*depth[lcaIndex];
}

// To do
void clean (int n)
{
    trip.clear();
    lca.clear();
    for (int i = 0 ; i < n; i ++)
        child[i].clear();

}

void makeGraph (int size)
{
    int temp;
    for (int i = 1; i < size; i++)
    {
        cin >> temp;
        child[temp].push_back(i);
    }
}
 
void traverse (int here,int d)
{
    depth[nextSerial] = d;
    no2Serial[here] = nextSerial;
    firstIndex[nextSerial] = trip.size();
    trip.push_back(nextSerial);
    
    nextSerial++;

    for (int i =0; i < child[here].size(); i++)
    {
        traverse (child[here][i],d+1);
        trip.push_back(no2Serial[here]);
    }
}
    
int segmentTreeInit (int node, int leftNode, int rightNode)
{
    if (leftNode == rightNode)
        return lca[node] = trip[leftNode];

    int mid = (leftNode+rightNode)/2;
    return lca[node] = min (segmentTreeInit(node*2,leftNode,mid),segmentTreeInit(node*2+1,mid+1,rightNode));
}

int queryImp (int node,int leftNode,int rightNode,int left, int right)
{
    if (right < leftNode ||  rightNode < left)
        return INF;

    if (leftNode == rightNode)
        return lca[node];

    int mid = (leftNode + rightNode)/2;
    return min (queryImp(node*2,leftNode,mid,left,right),queryImp(node*2+1,mid+1,rightNode,left,right));
}


int main (void)
{
std::ios_base::sync_with_stdio(false);
cin.tie(0);
    int testcase,n,calNum,u,v;
    cin >> testcase;
    while (testcase--)
    {
        cin>>n>>calNum;
        init(n);
        while (calNum--)
        {
            cin >> u >> v;
            cout<<query(n,u,v)<<'\n';
        }
       
        clean(n);
    }
}

