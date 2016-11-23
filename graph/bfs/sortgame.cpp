
// 최적화 방법 
// 1. 숫자들이 다르더라도 상대적인 크기가 같은 배열들에 대한 답은 항상 같다.
// 예를 들어 두 배열 {30,40,10,20}과 {3,4,1,2}는 숫자들의 상대적 크기가 같기 때문에 필요한 최소 연산 수도 2로 같다.
// 2. 이 문제의 상태 공간은 양방향 그래프이기 때문에 시작 정점에서 목표 정점으로 가는 최단 거리는 목표 정점에서 시작 정점으로 가는 최단 거리와 같다.

/*
   문제

   중복이 없는 정수 수열이 주어진다. 이 때, 우리는 이 수열의 임의의 구간을 선택해서 해당 구간을 뒤집을 수 있다. 이 뒤집기 연산을 통해 전체 수열을 정렬하고 싶다. 그런데, 같은 수열도 두 가지 이상의 방식으로 정렬할 수 있다. 예를 들어 3 4 1 2 는, 3 4 와 1 2 를 각각 뒤집어 4 3 2 1 을 만든 뒤, 전체를 뒤집어 정렬할 수도 있지만, 4 1 2 를 먼저 뒤집고, 3 2 1 을 다시 뒤집으면 두 번만의 연산으로 정렬할 수도 있다.

   정렬을 위해 뒤집기 연산을 최소 몇 번 해야 하는지를 계산하는 프로그램을 작성하라.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (<= 1000) 이 주어진다. 각 테스트 케이스의 첫 줄에는 수열의 길이 N (1 <= N <= 8) 이 주어진다. 다음 줄에 N개의 정수로 각 수열의 원소들이 순서대로 주어진다. 한 수열에 같은 수가 두 번 출현하지 않는다고 가정해도 좋다. 모든 수는 1부터 1백만 사이의 정수이다.

   출력

   각 테스트 케이스마다 입력을 정렬하기 위해 필요한 최소 뒤집기 연산의 수를 출력한다.

   예제 입력

   3
   8
   1 2 3 4 8 7 6 5
   4
   3 4 1 2
   3
   1 2 3
   예제 출력

   1
   2
   0
*/


// sort game 문제를 해결하는 너비 우선 탐색 알고리즘 
// perm을 정렬하기 위해 필요한 최소 뒤집기 연산의 수를 계산한다.
int bfs(const vector<int>& perm) {
	int n = perm.size();
	// 목표 정점을 미리 계산한다.
	vector<int> sorted = perm;
	sort(sorted.begin(),sorted.end());
	// 방문 목록(큐)과 시작점부터 각 정점까지의 거리 
	queue<vector<int> > q;
	map<vector<int>, int> distance;
	// 시작점을 큐에 넣는다.
	distance[perm] = 0;
	q.push(perm);
	while(!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		// 목표 정점을 발견했으면 곧장 종료한다.
		int(here = sorted) return distance[here];
		int cost = distance[here];
		// 가능한 모든 부분 구간을 뒤집어 본다.
		for(int i=0;i<n;i++)
			for(j=i+2;j<=n;j++)
			{
				reverse(here.begin()+i,here.begin()+j);
				if(distance.count(here)==0)
				{
					distance[here] = cost+1;
					q.push(here);
				}
				reverse(here.begin()+i,here.begin()+j);
			}
	}

	// oops 
	return -1;
}

//sort game 문제를 빠르게 해결하느 너비 우선 탐색의 구현 
map<vector<int>, int> toSort;
// [0,...,n-1]의 모든 순열에 대해 toSort[]를 계산해 저장한다.
void precalc(int n) {
	vector<int> perm(n);
	for(int i=0;i<n;i++)
		perm[i] = i;
	queue<vector<int> > q;
	q.push(perm);
	toSort[perm] = 0;
	while(!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		int cost = toSort[here];
		for(int i=0;i<n;i++) {
			for(int j=i+2;j<=n;j++) {
				reverse(here.begin()+i,here.begin()+j);
				if(toSort.count(here) == 0) {
					toSort[here] = cost +1;
					q.push(here);
				}

				reverse(here.begin()+i,here.begin()+j);
			}
		}
	}
}

int solve(const vector<int>& perm) {
	// perm을 [0,...,n-1]의 순열로 변환한다.
	int n = perm.size();
	vector<int> fixed(n);
	for(int i=0;i<n;i++) {
		int smaller = 0;
		for(int j=0;j<n;j++)
			if(perm[j] < perm[i])
				++smaller;
		fixed[i] = smaller;
	}

	return toSort[fixed];
}

