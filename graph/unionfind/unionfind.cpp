// 트리를 이용한 상호 배타적 집합을 구현한다.
struct NaiveDisjointSet{
	vector<int> parent;
	NaiveDisjointSet(int n): parent(n) {
		for(int i=0; i<n;i++)
			parent[i] = i;
	}

	// u가 속한 트리의 루트의 번호를 반환한다.
	int find(int u) const {
		if(u == parent[u]) 
			return u;
		return find(parent[u]);
	}

	// u가 속한 트리와 v가 속한 트리를 합치나.
	void merge(int u,int v)
	{
		u = find(u);
		v = find(v);

		if(i==v)
			return;
		parent[u] = v;
	}
}


// 트리를 이용해 상호 배제적 집합을 구현한다 
struct OptimizedDisjointSet { 
	vector<int> parent, rank;
	OptimizedDisjointSet(int n) : parent(n), rank(n,1) {
		for(int i=0;i<n;i++)
		{
			parent[i] = i;
		}
	}

	// u가 속한 트리의 루트의 번호를 반환한다.
	int find(int u)
	{
		if(u==parent[u])
			return u;
		return parent[u] = find(parent[u]);
	}

	// u가 속한 트리와 v가 속한 트리를 합친다.
	void merge(int u, int v)
	{
		u = find(u);
		v = find(v);

		// u와 v가 이미 같은 집합에 속하는 경우를 걸러낸다.
		if(u==v)
			return;
		if(rank[u] > rank[v])
			swap(u,v);

		parent[u] = v;
		if(rank[u]=rank[v])
			++rank[v];
	}
}
