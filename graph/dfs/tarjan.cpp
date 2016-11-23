
// 강결합 컴포넌트 SCC (strongly connected components) 
// 방향 그래프 상에서 두 정점 u와 v에 대해 양 방향으로 가는 경로가 모두 존재했을때 두 정점은 같은 SCC에 속해 있다고 말한다.
// tarjan 알고리즘 : 각 정점을 SCC 별로 분리하는 알고리즘 

// 그래프의 인접 리스트 표현
vector<vector<int> > adj;
// 각 정점의 컴포넌트 번호, 컴포넌트 번호는 0부터 시작하며,
// 같은 강결합 컴퓨넌트에 속한 정점들의 컴포넌트 번호가 같다.
vector<int> sccId;
// 각 정점의 발견 순서 
vector<int> discovered;
// 정점의 번호를 담는 스택 
stack<int> st;
int sccCounter, vertexCounter;
// here를 루트로하는 서브트리에서 역방향 간선이나 교차 간선을
// 통해 갈 수 있는 정점 중 최소 발견 순서를 반환한다.
// (이미 SCC로 묶인 정점으로 연결된 교차 간선은 무시한다)
int scc(int here) {
	int ret = discovered[here] = vertexCounter++;
	// 스택에 here를 넣는다. here의 후손들은 모두 스택에서 here 후에 들어간다.
	st.push(here);
	for(int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		// (here,there) 가 트리 간선 
		if(discovered[there] == -1)
			ret = min(ret,scc(there));
		// there가 무시해야 하는 교차 간선이 아니라면 
		// scc가 결합된 상태에서는 무시
		// scc가 결합되지 않은 상태에서는 discovered[there]는 there과 그 자식들에서 얻을 수 있는 최소 발견 순서를 의미.
		else if (sccId[there] == -1)
			ret = min(ret,discovered[there]);
	}

	// here에서 부모로 올라가는 간선을 끊어야 할지 확인한다.
	// 자식들에 대해서 dfs 조사후, 나보다 작은 최소 발견 순서가 없기 때문에, 더 이상 graph 확장 불가능  
	if (ret == discovered[here])
	{
		// here를 루트로 하는 서브트리에 남아 있는 정점들을 전부 하나의 컴포넌트로 묶는다.
		while (true) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if (t==here) break;
		}

		++sccCounter;
	}

	return ret;
}

// tarjan의 scc 알고리즘  
vector<int> tarjinSCC() {
	// 배열들을 전부 초기화 
	sccId = discovered = vector<int>(adj.size(),-1);
	// 카운터 초기화 
	sccCounter = vertexCounter = 0;
	// 모든 정점에 대해 scc() 호출 
	for(int i = 0; i < adj.size(); i++)
		if(discovered[i] == -1)
			scc(i);

	return sccId;
}
