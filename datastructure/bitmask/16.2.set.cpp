
// 비트 마스크를 이용한 집합의 구현 
// N 비트 정수 변수는 0부터 N-1까지의 정수 원소를 가질 수 있는 집합이 된다. 
// ex) 피자집 - 고객들이 원하는 토핑을 골라 주문할 수 있는 피자집의 주문 시스템을 만든다고 할때,
// 이 피자집에는 0부터 19까지의 번호를 갖는 스무 가지의 토핑이 있으며, 주문시 토핑을 넣기/넣지 않기를 선택할 수 있다.

// 1. 공집합과 꽉찬 집합 구하기 
// 공집합 - 0 , 꽉찬 집합 int full pizza = (1<<20) - 1;

// 2. 원소 추가 
// toppings |= (1<<p);

// 3. 원소 포함 여부 확인 
// if(toppings & (1<<p) ) cout<< "pepperoni is in" << endl; 
// 결과값 : 0 또는 1<<p

// 4. 원소의 삭제 
// toppings &= ~(1<<p);

// 5. 원소의 토글 
// toppings ^= (1<<p);

// 6. 두 집합에 대해 연산하기 
// int added = (a | b); // a와 b의 합집합 
// int interseciton = (a & b); // a와 b의 교집합
// int removed = (a & ~b); // a에서 b를 뺀 차집합 
// int toggled = (a ^ b); // a와 b 중 하나에만 포함된 원소들의 집합 

// 7. 집합 크기 구하기
// 집합에 포함된 원소의 수를 구하기 
// 1) 구현 
// int bitCount(int x) {
// if(x==0) return 0;
// return x % 2 + bitCount(x/2);
// }
// 2) compiler 내장 명령어 
// 컴파일러 혹은 언어   집합의 크기 구하기 
// gcc/g++              __builtin_popcount(unsigned int toppings)
// Visual C++           __popcnt(toppings)
// Java                 Integer.bitCount(toppings)

// 8. 최소 원소 찾기 
// 1. 집합에 포함된 가장 작은 원소를 찾기 "이 정수의 이진수 표현에서 끝에 붙어 있는 0이 몇개인가?" -> 켜져 있는 최하위 비트의 번호를 반환하게 된다.
// 컴파일러 혹은 언어   최소 원소 찾기 
// gcc/g++              __builtin_ctz(toppings)
// Visual C++           _BitScanForward(&index,toppings)
// Java                 Integer.numberOfTrailingZeros(toppings)
// 2. 최하위 비트 번호대신 해당 비트를 직접 구하기 
// 예를 들어, 40이 주어질 경우 3대신 2^3이 반환 
// int firstTopping = (toppings & -toppings);

// 9. 최소 원소 지우기 
// toppings &= (toppings-1);

// 10. 모든 부분 집합 순회하기 
// 예를들어, {1,2,3} = {1} , {1,2} , {1,2,3} , {2,3} , {1,3} , {2} , {3}
// for(int subset = pizza; subset; subset = ((subset-1) &pizza)) {
// // subset은 pizza의 부분 집합 }

