
// 동적 계획법이나 분할 정복 등의 디자인 패러다임은 모든 문제에 적용될 수 없다.
// 분할 정복의 경우 적절한 분할 방법이 없는 경우 
// 동적 계획법의 경우 부분 문제가 전혀 중복 되지 않거나 메모리를 너무 많이 사용하는 경우 
// 이럴 경우 완전 탐색으로 돌아와야 한다.

// 부분 답과 완성된 답의 집합을 탐색 공간 (search space) 라고 한다.
// 예를 들어 TSP에서 탐색 공간의 한 원소는 지금까지 방문한 정점의 목록과 현재 위치로 구성된다.

// 완전 탐색은 모든 답을 다 만들어 보면서 문제를 해결하므로, 완전 탐색의 수행 시간은 탐색 공간에 직접적으로 비례한다.
// 하지만 대부분의 문제는 exponential하게 증가하므로 완전탐색은 부적절하다.

// combinatorial search 
// 완전 탐색을 포함해, 유한한 크기의 탐색 공간을 뒤지면서 답을 찾아내는 알고리즘 
// 최적화 방법 : 기본적으로 모두 최적해가 될 가능성이 없는 답들을 탐색하는 것을 방지하여 만들어 봐야 할 답의 수를 줄이는 것을 목표로 한다.

// 유명한 방법들 
// 1. pruning 가지치기 
// 최적해로 연결될 가능성이 없는 부분들을 잘라낸다. 예를들어 현재 상태에서 답의 나머지를 완성했을 때 얻을 수 있는 가장 좋은 답이 
// 지금까지 우리가 알고 있는 최적해보다 나쁘다면 탐색을 중지한다. 
// 여기서 더 최적화하면 현재 상태에서 얻을 수 있는 가장 좋은 답의 상한을 이용하여 pruning을 하는 것 
// 2. 탐색 순서를 바꾸거나 탐색 시작전 탐욕법을 이용해 적당히 좋은 답을 우선 찾아내기
// pruning과 같이 사용할 경우 더 좋은 답을 알고 있으면 좀 더 일찍 탐색을 중단할 수 있다.


