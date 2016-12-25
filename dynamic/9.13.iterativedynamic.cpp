
// iterative dynamic programming
// 부분 문제 간의 의존성을 파악하기 쉬울 경우에는 재귀 함수가 아니라 반복문을 이용해서 동적 계획법을 구현할 수 있다. 

// 예제 : 삼각형 위의 최대 경로 
// path2(y,x) = triangle[y,x] + max (path2(y+1,x) , path2(y+1,x+1))

// 코드 9.23 삼각형 위의 최대 경로 문제를 해결하는 반복적 동적 계획법 알고리즘 
int n, triangle[100][100];
int C[100][100];
int iterative () {
    // base case 
    for (int x = 0; x < n; x++)
        C[n-1][x] = triangle[n-1][x];

    // 다른 부분을 계산한다.
    for (int y = n-2; y >= 0; y--)
        for (int x = 0; x < y+1; x++)
            C[y][x] = max (C[y+1][x], C[y+1][x+1]) + triangle[y][x];
    return C[0][0];
}

// sliding window (슬라이딩 윈도)를 이용한 공간 복잡도 줄이기 
// 사용하는 데이터 전체를 메모리에 유지하는 것이 아니라 필요한 부분만을 저장하는 기법을 가리킨다.
// 새 값을 계산할 때 과거에 계산한 결과가 전부 필요한 것이 아니라 일부분만이 필요할 때 사용 가능 
// 삼각형 위의 최대 경로 문제는 space complexity = O(n^2) 이다.
// 하지만, 위의 예제는 C[i]를 계산하기 위해서 C[i+1]만 필요하기 때문에 적용 가능하다. 

// 코드 9.24 슬라이딩 윈도를 이용한 삼각형 위의 최대 경로 알고리즘 

int C2[2][10000];
int iterative2 () {
    // base case 
    for (int x = 0; x < n; x++)
        C[(n-1)%2][x] = triangle[n-1][x];

    /// 다른 부분을 계산한다.
    for (int y = n-2; y >=0; y--)
        for (int x = 0; x < y+1; x++)
            C2[y%2][x] = max(C2[(y+1)%2][x],C2[(y+1)%2][x+1]) + triangle[y][x];

    return C2[0][0];
}

// 행렬 거듭 제곱을 이용한 동적 계획법 
// 굉장히 한정된 경우에만 쓸 수 있지만, linear transform 형태의 점화식을 행렬을 이용해 빠르게 푸는 기법 
// 예를 들어 fibonacci sequence의 특정 항을 구하는 문제를 예로 들어보면 
// fib(n) = fib(n-1) + fib(n-2)
// 기존 방법 running time : O(n)
// 행렬 거듭 제곱 이용 running time : O(m^2 lgn)

// 코드 9.25 피보나치 수열의 특정 항을 구하는 동적 계획법 알고리즘 

int fib (int n) {
    if (n <= 1) return n;
    int seq[3];
    seq[0] = 0;
    seq[1] = 1;
    for (int i = 2; i <=n; i++)
        seq[i%3] = (seq[(i-1)%3] + seq[(i-2)%3]) % 100000;
    return seq[n % 3];
}

// 행렬 Ci를 다음과 같이 정의하면 
// Ci = |fib(i-1) | 
//      |fib(i)   |
// Ci+1 = | fib(i)  |  = | fib(i)            | = | Ci,1        |  = | 0 1 | Ci
//        | fib(i+1)|  = | fib(i-1) + fib(i) | = | Ci,0 + Ci,1 |  = | 1 1 |
// 행렬을 W로 표현하면 다음과 같이 나타낼 수 있다. Cn = W * Cn-1 = W^n-1 * C1

// 코드 9.26 피보나치 수열의 특정항을 구하는 빠른 행렬 제곱 알고리즘 


// A^n을 구한다. 이 때 각 계산은 모두 100,000에 대한 나머지로 한다.
SquareMatrix pow (const SquareMatrix& A, int n);
int fib3 (int n) {
    if (n == 0) return 0;
    SquareMatrix W (2);
    W[0][0] = 0;
    W[0][1] = W[1][0] = W[1][1] = 1;
    return pow(W,n-1)[1][1];
}

// 반복적 동적 계획법과 재귀적 동적 계획법의 비교 

// 1. 재귀적 동적 계획법의 장단점 
// 장점 : 좀 더 직관적인 코드를 짤 수 있다.
//        부분 문제 간의 의존 관계나 계산 순서에 대해 고민할 필요가 없다.
//        전체 부분 문제 중 일부의 답만을 필요한 경우 더 빠르게 동작한다.
// 단점 : 슬라이딩 윈도 기법을 쓸 수 없다. 
//        스택 오버플로를 조심해야 한다.

// 2. 반복적 동적 계획법의 장단점 
// 장점 : 구현이 대개 더 짧다.
//        재귀 호출에 필요한 부하가 없기 때문에 조금 더 빠르게 동작한다.
//        슬라이딩 윈도 기법을 쓸 수 있다.
// 단점 : 구현이 좀더 비직관적이다.
//        부분 문제 간의 의존 관계를 고려해 계산된느 순서를 고민해야 한다. 

     


