
// 조합 탐색 기법들 

// 최적화       소형(n=12)  중형(n=16)   대형(n=20)     초대형(n=24)
// 동적계획법   0.03        0.58         26.45          768.21

// 동적 계획법의 경우 입력의 크기에 따라 메모리의 사용량이 지수적으로 커진다. 초대형의 경우 3GB의 메모리를 필요로 한다.

// 코드 11.1 TSP를 해결하는 완적 탐색의 구현 

const double INF = 1e200;
const int MAX = 30;
// 도시의 수
int n; 
// 두 도시간의 거리를 저장하는 배열 
double dist[MAX][MAX];

double best;

// path : 지금까지 만든 경로 
// visited : 각 도시의 방문 여부
// currentLength : 지금까지 만든 경로의 길이 
// 나머지 도시들을 모두 방문하는 경로들을 만들어보고 가능하면 최적해를 갱신한다.
void search (vector<int>& path, vector<bool>& visited, double currentLength) 
{
    int here = path.back();
    
    // base case 
    if (path.size() == n)
    {
        best = min (best, currentLength + dist[here][0]);
        return;
    }

    for (int next = 0; next < n; next++) {
        if (visited[next]) 
            continue;

        path.push_back(next);
        visited[next] = true;

        search(path,visited,currentLength + dist[here][next]);

        visited[next] = false;
        path.pop_back();
    }
}

double solve() 
{
    best = INF;
    vector<bool> visited(n,false);
    vector<int> path(1,0);
    visited[0] = true;
    search(path,visited,0);
    return best;
}

// 최적화       소형(n=12)  중형(n=16)   대형(n=20)     초대형(n=24)
// 동적계획법   0.03        0.58         26.45          768.21
// 완전 탐색    89.74       시간초과     시간초과       시간초과 

// 1. 최적해보다 나빠지면 그만두기 

void search (vector<int>& path, vector<bool>& visited, double currentLength) 
{
   
    // 간단한 가지치기 : 지금까지 찾은 가장 좋은 답 이상일 경우 중단 
    if (best <= currentLength) return;

    int here = path.back();
    
    // base case 
    if (path.size() == n)
    {
        best = min (best, currentLength + dist[here][0]);
        return;
    }

    for (int next = 0; next < n; next++) {
        if (visited[next]) 
            continue;

        path.push_back(next);
        visited[next] = true;

        search(path,visited,currentLength + dist[here][next]);

        visited[next] = false;
        path.pop_back();
    }
}

// 최적화       소형(n=12)  중형(n=16)   대형(n=20)     초대형(n=24)
// 동적계획법   0.03        0.58         26.45          768.21
// 완전 탐색    89.74       시간초과     시간초과       시간초과
// (1)          2.58        981.53       시간초과       시간초과

// 2. 간단한 휴리스틱을 이용한 가지치기 
// 조합 탐색에서 방문하는 상태의 수는 탐색의 깊이가 깊어질수록 증가하기 때문에 탐색 중 '이 부분에서는 최적해가 나올 수 없다'는 것을 가능한 한 
// 일찍 알아내는 것이 유리하다. 
// 휴리스틱의 값은 항상 남은 최단 경로의 길이보다 작거나 같아야 한다. (하한) (underestimate 휴리스틱, optimistic 휴리스틱)

// 코드 11.2 아직 방문하지 않은 도시들에 대해 인접한 간선 중 가장 짧은 간선의 길이를 더하는 휴리스틱 (최단 경로의 하한이다)

// 각 도시에 인접한 간선 중 가장 짧은 것을 미리 찾아 둔다.
double minEdge [MAX];
// 가장 단순한 형태의 휴리스틱 
double simpleHeuristic (vector<bool>& visited) {
    // 마지막에 시작점으로 돌아갈 때 사용할 간선 
    double ret = minEdge[0];
    for (int i = 0; i < n; i++)
        if(!visited[i])
            ret += minEdge[i];
    return ret;
}

void search (vector<int>& path, vector<bool>& visited, double currentLength) 
{
    // 단순한 휴리스틱을 이용한 가지치기 
    if (best <= currentLength + simpleHeuristic(visited)) return;
    // ... 생략 ...
}

double solve() {
    // simpleHeuristic()을 위한 초기화 
    for (int i =0; i < n; i++) {
        minEdge[i] = INF;
        for (int j = 0; j < n; j++)
            if(i != j)
                minEdge[i] = min (minEdge[i],dist[i][j]);
    }
    // ... 생략 ...
}

// 최적화       소형(n=12)  중형(n=16)   대형(n=20)     초대형(n=24)
// 동적계획법   0.03        0.58         26.45          768.21
// 완전 탐색    89.74       시간초과     시간초과       시간초과
// (1)          2.58        981.53       시간초과       시간초과
// (2)          0.85        84.18        시간초과       시간초과 

// 3. 가까운 도시부터 방문하기 

// 코드 11.3 가까운 정점부터 방문하는 최적화의 구현 

// 각 도시마다 다른 도시들을 가까운 순서대로 정렬해 둔다.
// 탐욕 알고리즘으로 초기해를 구하는 것과 같은 효과가 있다. 맨 처음에 도시에서 가까운 도시들을 방문하기 때문에 
vector<int> nearest[MAX];
void search (vector<int>& path, vector<bool>& visited, double currentLength) {
    // ... 생략 ...
    // 다음 방문할 도시를 전부 시도해 본다. 
    for (int i = 0; i < nearest[here].size(); i++) {
        int next = nearest[here][i];
        // ... 생략 ...
    }
}

double solve() {
    // nearest 초기화 
    for (int i =0; i < n; i++) {
        vector<pair<double,int> > order;
        for (int j = 0; j < n; j++)
            if (i != j)
                order.push_back(make_pair(dist[i][j],j));
        sort(order.begin(),order.end());
        nearest[i].clear();
        for (int j = 0; j < n-1; j++)
           nearest.push_back(order[j].second);
    }
    // ... 생략 ...
}

// 최적화       소형(n=12)  중형(n=16)   대형(n=20)     초대형(n=24)
// 동적계획법   0.03        0.58         26.45          768.21
// 완전 탐색    89.74       시간초과     시간초과       시간초과
// (1)          2.58        981.53       시간초과       시간초과
// (2)          0.85        84.18        시간초과       시간초과
// (3)          0.52        31.03        시간초과       시간초과 

// 4. 지나온 경로를 이용한 가지치기 

// 코드 11.4 지나온 경로를 이용하는 두 가지 가지치기 전략의 구현 

// path의 마지막 네 개의 도시 중 가운데 있는 두 도시의 순서를 바꿧을 때 
// 경로가 더 짧아 지는지 여부를 반환한다.
bool pathSwapPruning (const vector<int>& path) {
    if (path.size() < 4)
        return false;
    int p = path[path.size() - 4];
    int a = path[path.size() - 3];
    int b = path[path.size() - 2];
    int q = path[path.size() - 1];
    return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}

// 시작 도시와 현재 도시를 제외한 path의 부분 경로를 
// 뒤집어 보고 더 짧아지는 지 확인한다.
bool pathReversePruning (const vector<int>& path) {
    if (path.size() < 4)
        return false;
    int b = path[path.size() - 2];
    int q = path[path.size() - 1];
    for (int i = 0; i + 3 < path.size(); i++) {
        int p = path[i];
        int a = path[i+1];
        // [...,p,a,...,b,q]를 [...,p,b,..,a,q]로 바꿔본다.
        if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
            return true;
    }

    return false;
}


// 최적화       소형(n=12)  중형(n=16)   대형(n=20)     초대형(n=24)
// 동적계획법   0.03        0.58         26.45          768.21
// 완전 탐색    89.74       시간초과     시간초과       시간초과
// (1)          2.58        981.53       시간초과       시간초과
// (2)          0.85        84.18        시간초과       시간초과
// (3)          0.52        31.03        시간초과       시간초과 
// (4.1)        0.15        4.64         233.52         시간초과 
// (4.2)        0.07        1.13         33.29          1160.81

// 5. MST 휴리스틱을 이용한 가지치기의 구현 

// 코드 11.5 MST 휴리스틱의 구현 

// 상호 배타적 집합 자료 구조를 구현한다.
struct DisjointSet {
    // n개의 원소로 구성된 집합 자료 구조를 만든다. 
    DisjointSet (int n);
    // here가 포함된 집합의 대표를 반환한다.
    int find (int here);
    // a가 포함된 집합과 b가 포함된 집합을 합친다. 
    bool merge (int a, int b);
};

// 모든 도시 간의 도로를 길이 순으로 정렬해 저장해 둔다. 
vector<pair<double,pair<int,int> > > edges;
// here와 시작점, 아직 방문하지 않은 도시들을 모두 연결하는 MST를 찾는다. 
double mstHeuristic (int here, const vector<bool>& visited) {
    // kruskal's MST 
    DisjointSet sets(n);
    double taken = 0; 
    for (int i = 0; i < edges.size(); i++) 
    {
        int a = edges[i].second.first, b = edges[i].second.second;
        if (a != 0 && a != here && visited[a])
            continue;
        if (b != 0 && b != here & visited[b])
            continue;
        if (sets.merge(a,b))
            taken += edges[i].first;
    }

    return taken;
}

// 최적화       소형(n=12)  중형(n=16)   대형(n=20)     초대형(n=24)
// 동적계획법   0.03        0.58         26.45          768.21
// 완전 탐색    89.74       시간초과     시간초과       시간초과
// (1)          2.58        981.53       시간초과       시간초과
// (2)          0.85        84.18        시간초과       시간초과
// (3)          0.52        31.03        시간초과       시간초과 
// (4.1)        0.15        4.64         233.52         시간초과 
// (4.2)        0.07        1.13         33.29          1160.81
// (5)          0.06        0.37         14.77          836.43 

// 6. 부분적으로 메모이제이션 하기 

// 코드 11.6 부분적으로 메모이제이션을 사용하는 최적화의 구현 

// 남은 도시의 수가 CACHED_DEPTH 이하면 동적 계획법으로 바꾼다.
const int CACHED_DEPTH = 5;
// dp (here,visited) = cached[here][남은 도시의 수][visited]
map<int, double> cache[MAX][CACHED_DEPTH + 1];
// here : 현재 위치 
// visited : 각 도시의 방문 여부 일 때 나머지 도시를 모두 방문하고 시작점으로 돌아가는 최단 경로의 길이를 반환한다. 
double dp (int here, int visited) {
    // base case 
    if (visited == (1<<n) -1)
        return dist[here][0];
    // 메모이제이션 
    int remaining = n - __builtin_popcount(visited);
    double* ret = &cache[here][remaining][visited];
    if (*ret > 0 )
        return *ret;
    *ret = INF;
    // 다음 도시를 하나씩 시도한다. 
    for (int next = 0; next < n; next++)
    {
        if (visited & (1<< next) )
            continue;
        *ret = min (*ret, dp(next,visited + (1<<next)) + dist[here][next]);
    }

    return *ret;
}

void search (vectotr<int>& path, int visited, double currentLength) 
{
    // ... 생략 ...
    // base 
    if (path.size() + CACHED_DEPTH >= n)
        best = min(best,currentLength + dp(path.back(),visited));
    return;
    // ... 생략 ...

}

// 최적화       소형(n=12)  중형(n=16)   대형(n=20)     초대형(n=24)
// 동적계획법   0.03        0.58         26.45          768.21
// 완전 탐색    89.74       시간초과     시간초과       시간초과
// (1)          2.58        981.53       시간초과       시간초과
// (2)          0.85        84.18        시간초과       시간초과
// (3)          0.52        31.03        시간초과       시간초과 
// (4.1)        0.15        4.64         233.52         시간초과 
// (4.2)        0.07        1.13         33.29          1160.81
// (5)          0.06        0.37         14.77          836.43
// (6)          0.06        0.28         2.91           25.24 
