
// priority queue
// 순서대로 기다리고 있는 자료들을 저장하는 자료구조 + 우선순위가 가장 높은 자료가 가정 먼저 꺼내진다. 
// 구현 방법 
// 1. 연결 리스트 / 배열 ? - 원소 추가 O(1) / 원소 꺼내기 O(N)
// 2. bst - 원소 추가 O(lgN) / 원소 꺼내기 O(lgN) - 우리가 원하는 작업은 굉장히 단순한 것이라서, 훨씬 간단한 구조로 목적 달성 가능 

// heap
// 가장 큰 원소를 찾는데 최적화된 형태의 이진 트리 
// 원소 추가 / 큰 원소 꺼내기 O(lgN)
// 특정한 규칙을 만족하도록 구성된 이진 트리, 단순히 최대 원소를 가능한 빠르게 찾을 수 잇는 방법으로 설계되었기 때문에 더 단순한 알고리즘으로도 
// 효율적으로 동작가능 
// 규칙 
// 1. 대소 관계 규칙 
// 부모 노드가 가진 원소는 항상 자식 노드가 가진 원소 이상 
// 2. 구조 제약  -> 트리 높이 항상 일정하게 유지가능 
// 1) 마지막 레벨을 제외한 모든 레벨에 노드가 꽉 차 있어야 한다.
// 2) 마지막 레벨에 노드가 있을 때는 항상 가장 왼쪽부터 순서대로 채워져 있어야 한다. 
// 대소 관계 규칙이 bst보다 느슨하기 때문에 쉽게 만족 가능 

// 배열을 이용한 힙의 구현 
// 노드의 개수만 알면 트리의 전체 구조 파악 가능 -> 배열 이용 가능 
// 1) A[i]에 대응되는 노드의 왼쪽 자손은 A[2*i+1]에 대응된다.
// 2) A[i]에 대응되는 노드의 오른쪽 자손은 A[2*i+2]에 대응된다.
// 3) A[i]에 대응되는 노드의 부모는 A[(i-1)/2]에 대응된다. 

// operations

// 1. insert
// running time : O(lgN)

// 코드 23.1 정수 원소를 갖는 최대 힙에 새 원소 삽입하기
// 정수를 담는 최대 힙 heap에 새 원소 newValue를 삽입한다.
void push_heap (vector<int>& heap, int newValue) {
    // 힙의 맨 끝에 newValue를 삽입한다.
    heap.push_back(newValue);
    // 현재 newValue의 위치 
    int idx = heap.size() - 1;
    // 루트에 도달하거나 newValue 이상의 원소를 가진 조상을 만날 때까지
    while (idex > 0 && heap[(idx-1)/2] < heap[idx]) {
        swap(heap[idx],heap[(idx-1)/2]);
        idx = (idx-1)/2;
    }
}

// 2. extract max 
// running time : O(lgN)

// 코드 23.2 정수 원소를 갖는 최대 힙에서 최대 원소 삭제하기 
// 정수를 담는 최대 힙 heap에서 heap[0]를 제거한다.
void pop_heap (vector<int>& heap) {
    // 힙의 맨 끝에서 값을 가져와 루트에 덮어씌운다.
    heap[0] = heap.back();
    heap.pop_back();
    int here = 0;
    while(true) {
        int left = here*2 + 1;
        int right = here*2 + 2;
        // leaf에 도달한 경우 
        if (leaf >= heap.size()) break;
        // heap[here]가 내려갈 위치를 찾는다.
        int next = here;
        if (heap[next] < heap[left])
            next = left;
        if (right < heap.size() && heap[next] < heap[right])
            next = right;
        if (next == here)  break;
        swap (heap[here],heap[next]);
        here = next;
    }
}

// 3. makeHeap
// running time : O(N) 

// 4. heapSort
// 힙에서 원소들을 꺼낼 때 항상 정렬된 순서대로 반환횐다는 점을 이용한다.
// 주어진 배열을 힙으로 만든 뒤 모든 원소들을 꺼내서 반환 순서대로 배열하면 정렬 결과가 된다.
// 이때 힙에서 원소를 하나 꺼내면 힙을 담은 배열의 맨 뒤쪽에 한 칸이 비게 되므로, 최대 원소를 여기에 옮기면 추가 메모리를 사용하지 않고 
// 정렬을 구현할 수 있다. 
// 병합 정렬과는 달리 추가적인 메모리를 요구하지 않고, 최악의 경우에도 O(NlgN)의 시간이 거린다. 

// 5. increase key / decrease key 
// 새 원소를 삽입할 때 처럼 위로 올려주거나/ 아래로 내려준다. 
// 이를 위해 각 원소가 힙의 어디에 위치하는지를 별도의 배열에 유지해야 한다. 

