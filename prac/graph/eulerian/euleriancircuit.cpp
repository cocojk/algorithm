
// 오일러 서킷 : 그래프의 모든 간선을 정확히 한 번씩 지나서 시작점으로 돌아오는 경로를 찾는 문제 
// 오일러 트레일 : 그래프의 모든 간선을 정확히 한 번씩 지나지만, 시작점과 끝점이 다른 경로 
// 헤밀토니안 경로(Hamiltonian path) : 그래프의 모든 정점을 정확히 한 번씩 지나는 경로 
// 경로 - 대게 한 점을 한 번만 지나는 단순 경로 
// 트레일 - 한 점을 두 번이상 지나는 경로
// 깊이 우선 탐색을 이용한 오일러 서킷 찾기 
// 그래프의 인접 행렬 표현 adj[i][j]= i와 j 사이의 간선의 수 
vector<vector<int> > adj;
// 무향 그래프의 인접 행렬 adj가 주어질 때 오일러 서킷을 계산한다.
// 결과로 얻어지는 circuit을 뒤집으면 오일러 서킷이 된다.
void getEulerCircuit(int here, vector<int>& circuit)
{
	for(int there=0; there < adj.size(); there++)
	{
		while(adj[here][there]>0)
		{
			// 양쪽 간선을 모두 지운다.
			adj[here][there]--;
			adj[there][here]--;
			getEulerCircuit(there,circuit);
		}

		circuit.push_back(here);
	}
}
