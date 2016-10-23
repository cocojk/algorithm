
// 3. 무향 그래프에서 절단점을 찾는 알고리즘
// cut vertec(절단점) : 이 점과 인접한 간선들을 모두 지웠을 때 해당 컴포넌트가 두 개 이상으로 나뉘어지는 정점
// 무향 그래프에서 절단점을 포함하지 않는 그래프를 이중 결합 컴포넌트(biconnected component)라고 부른다.
// 즉, 임의의 한 정점을 그래프에서 지우더라도 정점 간의 연결 관계가 유지된다.
// 그래프의 인접 리스트 표현 
vector<vector<int> > adj;
// 각 정점의 발견 순서, -1로 초기화 한다. 
vector<int> discovered;
// 각 정점이 절단점인지 여부를 저장한다. false로 초기화한다.
vector<bool> isCurVertex;
int counter =0;
// here를 루트로 하는 서브트리에 있는 절단점들을 찾는다.
// 반환 값은 해당 서브트리에서 역방향 간선으로 갈 수 있는 정점 중 
// 가장 일찍 발견된 정점의 발견 시점. 처음 호출 할 때는 isRoot=true로 둔다 
int findCutVertex(int here,bool isRoot)
{
	// 발견 순서를 기록한다. 
	discovered[here] = counter++;
	int ret = discovered[here];
	// 루트인 경우의 절단점 판정을 위해 자손 서브트리의 개수를 센다. 
	int children = 0;
	for(int i=0;i<adj[here].size();i++)
	{
		int there = adj[here][i];
		if(discovered[there] == -1)
		{
			children++;
			// 이 서브트리에서 갈 수 있는 가장 높은 정점의 번호 
			int subtree = findCutVertex(there,false);
			// 그 노드가 자기 자신 이하에 있다면 현재 위치는 절단점!
			if(!isRoot&&subtree>=discovered[here])
				isCurVertex[here] = true;
			ret = min(ret,subtree);
		}
		else 
			ret = min(ret,discovered[there]);
	}

	// 루트인 경우 절단점 판정은 서브트리의 개수로 한다. 
	if(isRoot) 
		isCurVertex[here] = (children>=2);
	return ret;
}
