
// bitmask -  정수의 이진수 표현을 자료 구조로 쓰는 기법 
// 장점들 
// 1. 더 빠른 수행 시간 - 대부분 O(1) 
// 2. 더 간결한 코드 - 반복문 없이 한 줄에 쓸 수 있기 때문에 
// 3. 더 작은 메모리 사용량 
// 4. 연관 배열을 배열로 대체 - map <vector<bool>, int> -> 단순한 배열 int[]로 대체 

// 유의할 점 
// 1. 연산자 우선순위  -> 괄호를 잘쓰자
// 2. 64비트 정수를 비트마스크로 쓸때 발생하는 오버플로 
// bool isBitSet(unsigned long long a, int b) {
// return (a & (1<<b)) > 0; }
// c++에서는 1은 부호 있는 32비트 상수로 취급되기 때문에 b가 32이상이 되면 오버플로가 발생한다.
// 따라서 1 뒤에 이 상수가 부호 없는 64비트 정수임을 알려주는 접미사 ull을 부여줘야 한다. 
// 3. 부호 있는 정수의 사용 -> 최상위 비트 음수 일때 1 조심하자 !

