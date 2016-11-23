
// dynamic array = 자료의 개수가 변함에 따라 크기가 변경되는 배열 
// 특징 
// 1. 원소들은 메모리의 연속된 위치에 저장된다.
// 2. 주어진 위치의 원소를 반환하거나 변경하는 동작을 O(1)에 할 수 있다.
// 3. 배열의 크기를 변경하는 resize() 연산이 가능하다. O(N)
// 4. 주어진 원소를 배열의 맨 끝에 추가함으로써 크기를 1 늘리는 append() 연산을 지원한다. O(1)

// append()의 경우 재할당을 기존 배열의 크기 * 2 로 하면 평균적으로 O(1)에 연산 속도를 지원할 수 있다.
// 표준 라이브러리 
// C++      vector
// Java     ArrayList 

// 배열의 최종 크기가 얼마인지 미리 짐작할 수 있다면, 동적 배열의 capacity를 미리 할당하는 것이 좋다. 
// C++      reserve()
// Java     ensureCapacity()
