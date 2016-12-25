
// 분할 정복 (divide & conquer) 
// 가장 유명한 알고리즘 디자인 패러다임으로 각개 격파라는 말
// 주어진 문제를 둘 이상의 부분 문제로 나눈 뒤 각 문제에 대한 답을 재귀호출을 이용해 계산하고, 각 부분 문제의 답으로부터 전체 문제의 답을 계산해낸다.

// *일반적인 재귀 호출과 다른점*
// 재귀호출 : 한조각과 나머지 전체 / 분할 정복 : 거의 같은 크기의 부분 문제 

// 구성 요소 
// 1) divide : 문제를 더 작은 문제로 분할하는 과정 
// 2) merge : 각 문제에 대해 구한 답을 원래 문제에 대한 답으로 병합하는 과정 
// 3) base case : 더 이상 답을 분할하지 않고 곧장 풀 수 있는 매우 작은 문제 

// 필요한 특성 
// 1) 문제를 둘 이상의 부분 문제로 나누는 자연스러운 방법이 존재해야 한다.
// 2) merge에 대해 효과적인 방법이 있어야 한다.

// 장점 
// 많은 경우 같은 작업을 더 빠르게 처리해 준다. 

// 1부터 n까지의 합을 구하는 분할 정복 알고리즘 
// 필수 조건 : n은 자연수
// 1+2+...+n을 반환한다.
// running time : 기존 O(n) ->  O(lgn)
int fastSum(int n) {
    // base case
    if (n==1)
        return 1;
    if (n%2 == 1)
        return fastSum(n-1) + n;
    return 2*fastSum(n/2) + (n/2)*(n/2);
}

// 행렬의 거듭제곱을 구하는 분할 정복 알고리즘
// n : matrix size , m : power
// running time : 기존 O(n^3 * m) -> O(n^3 * lgm)
// 정방 행렬을 표현하는 SquareMatrix 클래스가 있다고 가정하자.
class SquareMatrix;
// n*n 크기의 항등 행렬(identity matrix)을 반환하는 함수 
SquareMatrix identity (int n);
// A^m을 반환한다.
SquareMatrix pow (const SquareMatrix& A, int m) {
    // base case: A^0 = I
    if (m == 0)
        return identity(A.size());
    if (m % 2 > 0)
        return pow(A,m-1)*A;
    SquareMatrix half = pow(A,m/2);
    // A^m = (A^(m/2) * (A^(m/2))
    return half * half;
}

// 홀수 일때도 절반 가량으로 안나누는 이유는 overlapping subproblem때문이다. (dynamic 처리시 앞의 방법과 동일한 running time)
