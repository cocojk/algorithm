    
// 지배  집합 찾기 (dominating set)
// 각 정점이 자기 자신과 모든 인접한 정점들을 지배한다고 할때, 그래프의 모든 정점을 지배하는 정점의 부분 집합을 의미.
// 최소 지배 집합 찾기 문제 = np-complete
// unrooted tree 조건 !
// 1. 정확히 V-1개의 간선이 있습니다.
// 2. 사이클이 존재하지 않습니다.
// 3. 두 정점 사이를 연결하는 단순 경로가 정확히 하나 있습니다.
// 이 조건들은 모두 동치로, 한 조건이라도 성립할 경우 다른 조건들이 모두 성립하게 된다.

/*
   문제

   전세계의 유명한 인물화들을 모아 두는 미술관에 괴도 콩의 도전장이 날아들었습니다. 2022년 2월 2일을 기념하여, 미술관에 전시된 인물화 중 하나의 얼굴을 모 프로게이머의 얼굴로 합성하겠다는 것입니다. 미술관의 관장을 맡고 있는 재하는 이와 같은 사태를 방지하기 위해 감시 카메라를 설치하기로 마음먹었습니다. 미술관은 여러 개의 갤러리와 이들을 연결하는 복도로 구성되어 있으며, 한 갤러리에 감시 카메라를 설치하면 이 갤러리와, 복도로 직접 연결된 갤러리들을 감시할 수 있습니다. 모든 갤러리를 감시하기 위해 필요한 최소 감시 카메라의 수는 몇 개일까요?

   미술관은 한 번 관람한 갤러리를 다시 가기 위해서는 이전에 지나왔던 복도를 반드시 한 번 지나야 하는 구조로 설계되어 있으며, 모든 갤러리가 서로 연결되어 있지 않을 수도 있습니다.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 미술관에 포함된 갤러리의 수 G (1 <= G <= 1000) 와 갤러리들을 연결하는 복도의 수 H (0 <= H < G) 가 주어집니다. 각 갤러리에는 0번부터 G-1 번까지의 고유 번호가 있습니다. 그 후 H 줄에 각 2개의 정수로 각 복도가 연결하는 두 갤러리의 번호가 주어집니다.

   출력

   각 테스트 케이스마다 한 줄에 필요한 카메라의 최소 개수를 출력합니다.

   예제 입력

   3
   6 5
   0 1
   1 2
   1 3
   2 5
   0 4
   4 2
   0 1
   2 3
   1000 1
   0 1
   예제 출력

   3
   2
   999
*/

int V;
vector<int> adj[MAX_V];
vector<bool> visited;
const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;
// 지금까지 설치한 카메라의 총 수 
int installed;	
// here로부터 깊이 우선 탐색을 하고, here의 정보를 반환한다.
int dfs(int here) {
	visited[here] = true;
	int children[3] = { 0,0,0 };
	for(int i = 0; i < adj[here].size() ; i++) {
        int there = adj[here][i];
        if(!visited[here])
            ++children[dfs(there)];
    }

    //  자손 노드 중 감시되지 않는 노드가 있을 경우 카메라를 설치한다.
    if(children[UNWATCHED]) {
        ++installed;
        return INSTALLED;
    }
    // 자손 노드 중 카메라가 설치된 노드가 있을 경우 설치할 필요가 없다.
    if (children[UNWATCHED]) {
        ++installed;
        return INSTALLED;
    }
    // 자손 노드 중 카메라가 설치된 노드가 있을 경우 설치할 필요가 없다. 
    if (children[INSTALLED]) 
        return WATCHED;
    return UNWATCHED;
}

// 그래프를 감시하는 데 필요한 카메라의 최소 수를 반환한다.
int installCamera() {
    installed = 0;
    visited = vector<bool>(V,false);
    for(int u = 0; u < V; u++) 
        if(!visited[u] && dfs(u) == UNWATCHED)
            ++installed;
    return installed;
}

