
// 양방향 탐색 (bidirectional search) 
// 시작 정점에서 시작하는 정방향 탐색과 목표 정점에서 시작해 거꾸로 올라가는 역방향 탐색을 동시에 하면서 이 둘이 가운데서 만나면 종료하는 것.
// 유의 사항 
// 1. 정방향 간선을 찾아내기는 쉽지만 역방향 간선을 찾아내기 어려운 문제 
// 2. 역방향 간선이 아주 많아서 역방향 탐색의 분기 수가 지나치게 큰 경우 
// 너비 우선 탐색보다 훨씬 적은 정점만을 방문하고도 최단 경로를 찾을 수 있다. 
// 15-퍼즐 문제를 해결하는 양방향 탐색 알고리즘 
// 15-퍼즐 문제의 상태를 표현하는 클래스
class State {
	// 인접한 상태들의 목록을 반환한다.
	vector<State> getAdjacent() const;
	// map에 State를 넣기 위한 비교 연산자
	bool operator < (const State& rhs) const;
	// 종료 상태와 비교하기 위한 연산자 
	bool operator == (const State& rhs) const;
};

// x의 부호를 반환한다.
int sgn(int x) { if(!x) return 0; return x>0 ? 1 : -1; }

// x의 절대값을 1 증가시킨다.
int incr(int x) { if(x<0) return x - 1; return x + 1; }

// start에서 finish까지 가는 최단 경로의 길이를 반환한다.
int bidirectional(State start, State finish)
{
	// 각 정점까지의 최단 경로의 길이를 저장한다.
	map<State, int> c;
	// 앞으로 방문할 정점들을 저장한다.
	queue<State> q;
	// 시작 상태와 목표 상태가 같은 경우는 예외로 처리해야 한다.
	if(start == finish)
		return 0;
	q.push(start);
	c[start] = 1;
	q.push(finish);
	c[finish] = -1;

	// 너비 우선 탐색 
	while(!q.empty())
	{
		State here = q.front();
		q.pop();
		// 인접한 상태들을 검사한다.
		vector<State> adjacent = here.getAdjacent();
		for(int i=0;i<adjacent.size;i++)
		{
			map<State, int>::iterator it = c.find(adjacent[i]);
			if( it == c.end())
			{
				c[adjacent[i]] = incr(c[here]);
				q.push(adjacent[i]);
			}
			// 가운데서 만난 경우 
			else if(sgn(it->second) != sgn(c[here]))
				return abs(it->second) + abs(c[here]) -1;
		}
	}

	// 답을 찾지 못한 경우 
	return -1;
}


