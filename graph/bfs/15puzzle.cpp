
// 15-퍼즐을 해결하는 너비 우선 탐색 알고리즘 
// 15-퍼즐에 관련된 부분은 전부 State 내에서 구현함으로써 bfs의 구현이 15-퍼즐과 독립적
// State의 갯수가 너무 많기 때문에 배열로 잡을 수 없다?? 따라서, Map으로 대체.
// 너비 우선 탐색이 방문하는 정점의 개수에 가장 직접적인 영향을 주느 요소
// 1. 시작 정점과 목표 정점까지으 최단 거리 d
// 너비 우선 탐색은 시작 정점에서 가까운 정점들로부터 방문하기 때문에, 목표 정점이 가깝다면 일찍 종료하지만, 멀리 떨어져 있으면 더 오래 걸린다. 
// 2. 탐색 분기 수 (branching factor) b (경로의 길이가 하나 늘어날 때마다 닿을 수 있는 정점의 개수가 몇 배로 늘어나는 지를 나타낸다.)



// 게임판의 상태를 표현한다.
// 상태에 대한 여러 연산을 가능한 효율적으로 구현, 가능한 적은 메모리를 사용해야 한다. (큐,map에서 사용되기 때문에 메모리 사용량은 물론, 객체 생성하거나 복사하는 데 드는 시간도 많다.)
class State {
	// 인접한 상태들의 목록을 반환한다.
	vector<State> getAdjacent() const;
	// map에 State를 넣기 위한 비교 연산자
	bool operator < (const State& rhs) const;
	// 종료 상태와 비교하기 위한 연산자 
	bool operator == (const State& rhs) const;
};

typedef map<State, int> StateMap;
// start에서 finish까지 가는 최단 경로의 길이를 반환한다. 
int bfs(State start,State finish) {
	// 예외 start == finish인 경우
	if(start == finish) 
		return 0;
	// 각 정점까지의 최단 경로의 길이를 저장한다.
	StateMap c;
	// 앞으로 방문할 정점들을 저장한다.
	queue<State> q;
	q.push(start);
	c[start] = 0;
	// 너비 우선 탐색 
	while(!q.empty()) {
		State here = q.front();
		q.pop();
		int cost = c[here];
		// 인접한 정점들의 번호를 얻어낸다.
		vector<State> adjacent = here.getAdjacent();
		for(int i = 0; i<adjacent.size(); i++) 
		{
			if(c.count(adjacent[i]) == 0)
			{
				// 답을 찾았나?
				if(adjacent[i] == finish)
					return cost+1;
				c[adjacent[i]] = cost +1;
				q.push(adjacent[i]);
			}
		}
	}

	// 답을 찾지 못한 경우 
	return -1;
}
