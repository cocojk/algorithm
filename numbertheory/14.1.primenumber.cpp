
// prime number  <-> composite number 
// 양의 약수가 1과 자기 자신 두개뿐인 자연수 

// determine prime number 

// 코드 14.1 O(루트(n)) 시간에 동작하는 소수 판별 알고리즘 
// running time이 숫자의 갯수가 아니라 크기에 관련된다.

// 주어진 자연수 n이 소수인지 확인한다.
bool isPrime (int n) {
    // 예외 처리 : 1과 2는 예외로 처리한다.
    if (n <= 1)
        return false;
    if (n <= 2)
        return true;
    // 2를 제외한 모든 짝수는 소수가 아니다.
    if (n % 2 == 0)
        return false;
    // 2를 제외했으니 3 이상의 모든 홀수로 나누어보자.
    int sqrtn = int(sqrt(n));
    for (int div = 3; div <= sqrtn; div += 2)
        if (n % div == 0)
            return false;

    return true;
}

// 최적화 방법 => 판단해야할 수가 많지 않을 경우 가능 .
// 1. 2와 3을 제외한 모든 소수는 6k+1 , 6k -1의 형태를 띤다. 
// 증명, 
// 6k-1    6k    6k+1    6k+2    6k+3    6k+4 
//      6의 배수        짝수   3의 배수  짝수 
// 6k-1, 6k+1이 가능성 있다.
// 2. 작은 소수들의 목록을 미리 만들어 놨다가 이들로 먼저 나누는 방법 

// prime factorization 


// 코드 14.2 간단한 소인수 분해 알고리즘 

// 만약 div가 합성수라면 이미 n은 div의 소인수들로 최대한 나눠진 뒤이기 때문에 (div의 소인수들은 div보다 작고, div의 소인수는 n의 소인수이기도 하다.)
// n이 div로 나누어 떨어질 일은 없다. 
// 주어진 정수 n을 소인수분해 하는 간단한 알고리즘 
vector<int> factorSimple (int n) {
    vector<int> ret;
    int sqrtn = int(sqrt(n));
    for (int div = 2; div <= sqrtn; div++) 
        while (n % div == 0) {
            n /= div;
            ret.push_back(div);
        }

    if (n > 1)
        ret.push_back(n);
    return ret;
}

// sieve of eratosthenes (에라토스테네스의 체)
// 주어진 수 n 이하의 소수들을 모두 찾아낸다. 
// step 1. 2부터 n까지의 수를 다음과 같이 쭉 쓴다.
// 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 
// step 2. 이 목록에서 지워지지 않은 수들을 순회하며 이 수의 배수를 지운다. 
// step 2-1 2의 배수 지우기 
// 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
//     x   x   x   x     x     x     x     x     x
// step 2-2 3의 배수 지우기 
// 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
//   x x   x   x x       x     x  x  x     x     x
// 정해진 범위 수 끝가지 도달할때까지 반복 결과적으로 남는 수들이 모두 소수가 된다. 
// 소수를 찾을 때마다 그 배수들을 지우는 형태로 동작하기 때문에 훨씬 빠르게 수행된다. 

// 에라토스테네스의 체 최적화 
// 1. 지워지지 않은 수를 찾을 때 n이 아니라 루트(n)까지만 찾는다. 
// -> 최대 가능 수가 n이기 때문에 이 수의 최대 소인수는 루트(n)이고, 루트(n) ~ n-1 까지에 만약 composite number가 있는 경우, 루트(n) 이하의 소인수를 갖는다.
// 2. i의 배수들을 모두 지울 때 2*i에서 시작하는 것이 아니라 i*i에서 시작한다. 
// 2*2      2*3      2*4      2*5      2*6      2*7 
// 3*2      3*3      3*4      3*5      3*6      3*7
// 2의 배수 
// 4*2      4*3      4*4      4*5      4*6      4*7
// 2의 배수 3의 배수 
// 5*2      5*3      5*4      5*5      5*6      5*7 
// 2의 배수 3의 배수 2의 배수 
// 6*2      6*3      6*4      6*5      6*6      6*7 
// 2의 배수 3의 배수 2의 배수 5의 배수 

// 코드 14.3 에라토스테네스의 체 

int n;
bool isPrime[MAX_N+1];
// 가장 단순한 형태의 에라토스테네스의 체의 구현 
// 종료한 뒤 isPrime[i] = i 가 소수인가?
void eratosthenes() {
    memset (isPrime,1,sizeof(isPrime));
    // 1은 항상 예외 처리 !
    isPrime[0] = isPrime[1] = false;
    int sqrtn = int(sqrt(n));
    for (int i = 2; i <= sqrtn; i++)
        // 이 수가 아직 지워지지 않았다면 
        if (isPrime[i])
            // i의 배수 j들에 대해 isPrime[j] = false로 둔다.
            // i*i 미만의 배수는 이미 지워졌으므로 신경 쓰지 않는다.
            for (int j = i*i; j <= n; j+= i) 
                isPrime[j] = false;
}

// running time : 계산하기 까다롭다. 내부 반복문이 얼마나 실행될지는 [1,root(n)] 범위 내에 소수가 어떤 분포로 출현하는 지에 따라 달라지기 때문이다. 
// 소수의 분포를 근사값으로 표현하는 기법을 사용하면 필요한 전체 연산의 수가 O(nloglogn) 임을 증명할 수 있다.
// 실용적인 범위 내에서 수행시간은 거의 O(n)과 비슷하다고 생각해도 좋다. 
// 에라토스테네스의 체를 구현할때 문제가 되는 것은 시간보다는 메모리 사용량이다. ! 짝수를 별도로 처리하든가, 비트마스크를 이용하는 등의 기법을 이용한다. 

// 예제: 에라토스테네스의 체를 이용한 빠른 소인수 분해 .
// 각 숫자가 소수인지 합성수인지만을 기록하는 것이 아니라, 각 숫자의 가장 작은 소인수를 같이 기록한다. 
// 에라토스테네스의 체는 2부터 크기 순서대로 소수들을 찾아 나가므로, 이 정보를 모든 합성수에 대해 쉽게 계산할 수 있다. 

// 코드 14.4 에라토스테네스의 체를 이요한 빠른 소인수 분해 

// minFactor[i] = i의 가장 작은 소인수 (i가 소수인 경우 자기 자신) 
int minFactor [MAX_N];
// 에라토스테네스의 체를 수행하면서 소인수 분해를 위한 정보도 저장한다. 
void eratosthenes2 () {
    // 1은 항상 예외 처리 
    minFactor[0] = minFactor[1] = -1;
    // 모든 숫자를 처음에는 소수로 표시해 둔다.
    for (int i = 2; i <= n; i++)
        minFactor[i] = i;
    // 에라토스테네스의 체를 수행한다.
    int sqrtn = int(sqrt(n));
    for (int i = 2 ; i <= sqrtn; i++) {
        int (minFactor[i] == i) { 
            for (int j = i*i; j <= n ; j += i)
                // 아직 약수를 본 적 없는 숫자인 경우 i를 써 둔다.
                if (minFactor[j] == j)
                    minFactor[j] = i;

        }
    }
}

// 2 이상의 자연수 n을 소인수분해한 결과를 반환한다.
vector<int> factor (int n) {
    vector<int> ret;
    
    // n이 1이 될 때까지 가장 작은 소인수로 나누기를 반복한다.
    while (n > 1) {
        ret.push_back(minFactor[i]);
        n /= minFactor[n];
    }

    return ret;
}




