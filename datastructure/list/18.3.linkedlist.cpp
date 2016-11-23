
// linked list = 특정 위치에서의 삽입과 삭제를 상수 시간에 할 수 있게 해준다. 
// 원소들이 메모리 여기저기 흩어져 있고, 각 원소들이 이전과 다음 원소를 가리키는 포인터를 가지고 있다.
// 표준 라이브러리 
// C++      list
// Java     Linkedlist

// 연결 리스트 응용 연산들 
// 1. splice (잘라붙이기)
// 다른 리스트를 통째로 삽입하는 것 또한 상수 시간안에 가능 
// 해당 연산 후에 리스트의 크기를 상수 시간안에 파악 불가능 따라서 언어마다 지원하는 방식이 다르다.
// Java     splice 지원 x , 리스트 크기 지원 O
// C++      splice 지원 O , 리스트 크기 지원 X

// 2. undo (삭제했던 원소 돌려놓기)
// 원소 삭제시 해당 노드의 정보는 변경되지 않고, 이전/이후의 노드들의 정보만 변경된다.
// 따라서 삭제된 노드의 정보를 이용해서 undo가 가능하다. 
// 항상 삭제된 순서의 반대로 복구를 해야한다.

// 연결리스트에서 노드를 삭제하고 다시 추가하기
// node 이전/이후 노드의 포인터를 바꿔서 node를 리스트에서 삭제한다.
void deleteNode(ListNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

// node 이전/이후 노드의 포인터를 바꿔서 자기자신을 다시 리스트에 삽입한다.
void recoverNode(ListNode* node) {
    node->prev->next = node;
    node->next->prev = node;
}


