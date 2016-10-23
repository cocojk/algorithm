
// 점점 깊어지는 탐색 (Iteratively Deeping Search, IDS)
// 프로그램의 메모리가 부족한 경우 사용하는 방법 
// 깊이 우선 탐색은 너비 우선 탐색과 달리 큐를 사용하지 않는다. 또, 각 정점의 방문 여부를 기록하지 않으면 메모리를 거의 사용하지 않고 탐색을 할 수 있다.
// 점점 깊어지느 탐색은 임의의 깊이 제한 l을 정한 후 이 제한보다 짧은 경로가 존재하는 지를 깊이 우선 탐색으로 확인한다. 
// 답을 찾으면 성공이니 반환하고, 답을 찾지 못하면 l을 늘려서 다시 시도한다. 

// 추가적인 최적화 
// 점점 깊어지는 탐색은 조합 탐색과 관계가 깊다. 지금까지 찾은 최적해를 전역 변수에 저장하고, 현재 탐색의 깊이가 이보다 깊어질 경우 종료하는 것은 가지치기 기법이다.
// 많은 경우 조합 탐색에 사용하는 여러 최적화 기법들을 점점 깊어지는 탐색에 적용할 수 있다. 
// 예를 들어, 15-퍼즐에서 목표 저엄까지 도달하기 위한 필요한 움직임 수의 하한을 계산한 뒤, 이것이 지금까지 찾은 최단 거리나 깊이 제한 이상이라면 탐색을 곧바로 포기한다. 
// if(steps + here.estimate() >= best) return; 

// 효율성 평가 
// 메모리 사용 : 탐색의 깊이에 비례하는 메모리만 사용 O(d) 메모리 
// 방문 갯수 : O(b^d) 너비 우선 탐색하고 동일, 하지만 자료구조 유지가 없고, 휴리스틱을 적용하면 더 빨라진다.

// 15-퍼즐 문제를 해결하는 점점 깊어지는 탐색 알고리즘 
// 15 퍼즐 문제의 상태를 표현하는 클래스
class State {
	// 인접한 상태들의 목록을 반환한다.
	vector<State> getAdjacent() const;
	// map에 State를 넣기 위한 비교 연산자
	bool operator < (const State& rhs) const;
	// 종료 상태와 비교하기 위한 연산자 
	bool operator == (const State& rhs) const;
};
int best;

// 깊이 우선 탐색 
void dfs (State here, const State& finish, int steps) {
	
	// 지금까지 구한 최적해봐도 더 좋을 가능성이 없으면 버린다.
	if(steps >= best) return;
	// * 추가적인 하한 휴리스틱 적용시 * //
	// if(steps + here.estimate() >= best) return; 으로 변경된다.
	// estimate()는 현재 state에서 finish까지의 하한 값을 의미 
	// 현재 문제에서는 모든 타일에 대한 현재 위치와 목표 위치 사이의 맨히튼 거리를 의미

	// 목표 상태에 도달한 경우 
	if(here == finish)
	{
		best = steps;
		return;
	}
	
	// 인접 상태들을 깊이 우선 탐색으로 
	vector<State> adjacent = here.getAdjacent();
	for(int i=0; i < adjacent.size(); i++)
		dfs(adjacent[i], finish, steps+1);
}

// 점점 깊어지는 탐색 
int ids (State start, State finish, int growthStep) {
	for(int limit =4 ;  ; limit += growthStep) {
		best = limit+1;
		dfs(start,finish,0);
		if(bets <= limit) 
			return best;
	}

	return -1;
}


