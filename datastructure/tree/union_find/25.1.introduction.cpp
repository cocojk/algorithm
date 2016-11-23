
// union-find 자료구조 : 상호 배타적 집합(disjoint set)을 표현할 때 쓰는 자료구조 
// disjoint set : 공통 원소가 없는 집합 
// operation
// 1. 초기화 : n개의 원소가 각각의 집합에 포함되어 있도록 초기화한다.
// 2. 합치기(union) 연산 : 두 원소 a,b가 주어질 때 이들이 속한 두 집합을 하나로 합친다.
// 3. 찾기(find) 연산 : 어떤 원소 a가 주어질 때 이 원소가 속한 집합을 반환한다. 

// 배열를 이용
// belongsTo[i] = i번 원소가 속하는 집합의 번호 
// find : O(1)
// union : O(n) (집합에 해당하는 원소를 모두 찾아야하기 때문에)

// 트리를 이용 
// 각각의 트리가 집합을 나타내며, 루트를 해당 트리를 나타내는 대표로 표현 

// 코드 25.1 트리를 이용한 (단순한) 상호 배타적 집합 자료 구조의 구현 
// 트리를 이용해 상호 배타적 집합을 구현한다.
struct NaiveDisjointSet {
    vector<int> parent;
    NaiveDisjointSet (int n): parent(n) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // u가 속한 트리의 루트의 번호를 반환한다. 
    int find (int u) const {
        if (u == parent[u]) return u;
        return find(parent[u]);
    }

    // u가 속한 트리와 v가 속한 트리를 합친다. 
    void merge (int u, int v) {
        u = find(u);
        v = find(v);
        // u와 v가 이미 같은 트리에 속하는 경우를 걸러낸다.
        if (u == v)
            return;
        parent[u] = v;
    }
};
// find : O(h) 
// union : find에 의존 

// 최적화
// 1. union 최적화 (union by rank)
// 트리의 표현을 이용하면 합치기 연산을 할때 집합에 포함되는 모든 원소를 변경하는 대신 루트 하나의 정보만 바꾸면 된다. 
// 하지만, 트리가 기울어질 수 있다는 문제를 피해갈 수 없다. -> 발생시 find,union : O(n)
// 최적화 : rank(항상 높이가 더 낮은 트리)를 rank(더 높은 트리) 밑에 집어넣는다. (find 최적화 후에는 rank가 트리에 높이에 해당하지 않는다.)
// 트리의 높이는 두 트리의 높이가 같을 떄만 증가하므로, 높이가 h인 트리가 생기기 위해서는 높이가 h-1인 두 개의 트리가 합쳐져야 한다. 
// 높이가 h-1이기 위해 최소 n개의 노드가 필요하면, 높이가 h가 되기 위해서는 최소 2x개의 노드가 필요하다.
// 따라서 h = O(lgN)

// 2. find 최적화 (path compression)
// 한 노드에 find 여러번 연산시 중복된 계산이 일어난다. 
// find(u)를 통해 u가 속하는 트리의 루트를 찾아냈으면, parent[u]를 찾아낸 루트로 변경한다. 

// 두 최적화 적용후 running time 
// find , union : O(ack(n)) (애커만 함수 우리가 상상할 수 있는 모든 크기의 n에 대해 4이하의 값을 가짐) 거의 상수라고 봐도된다. 

// 코드 25.2 최적화된 상호 배타적 집합의 구현 

// 트리를 이용해 상호 배타적 집합을 구현한다.
struct OptimizedDisjointSet {
    vector<int> parent, rank;
    OptimizedDisjointSet (int n) : parent(n), rank(n,1) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // u가 속한 트리의 루트의 번호를 반환한다.
    int find (int u) {
        if (u == parent[u]) return u;
        return parent[u] = find (parent[u]);
    }

    // u가 속한 트리와 v가 속한 트리를 합친다. 
    void merge (int u, int v) {
        u = find(u);
        v = find(v);
        // u와 v가 이미 같은 집합에 속하는 경우를 걸러낸다.
        if (u == v)
            return;
        if (rank[u] > rank[v])
            swap(u,v);

        // 이제 rank[v]가 항상 rank[u] 이상이므로, u를 v의 자식으로 넣는다.
        parent[u] = v;
        if (rank[u] == rank[v]) rank[v]++;
    }
};

// 예제: 그래프의 연결성 확인하기 
// N개의 도시가 도로망으로 연결되어 있는데, 각 도로는 정확히 두 개의 도시를 연결한다. 그런데 이들이 폭설로 인해 모두 마비되었다. 시간이 지남에 따라 하나하나 도로들이 복구되는데, 도로가 복구될때마다 임의의 두 도시 간에 서로 왕래가 가능한지를 알고 싶다. 

// 예제 : 가장 큰 집합 추적하기 
// 각 집합에 속한 원소의 수를 추적할 수 있다. rank[]처럼 각 트리의 노드의 개수를 담는 배열 size[]를 추가한 뒤 두 집합이 합쳐질 때 마다 이 값을 갱신해 주면 된다. 
// 이것을 이용하면 집합들이 합쳐지는 과정에서 가장 큰 집합의 크기가 어떻게 변하는지 추적한다거나, 과반수가 출현하는 시점을 찾는다거나 하는 작업을 간단하게 구현할 수 있다. 

