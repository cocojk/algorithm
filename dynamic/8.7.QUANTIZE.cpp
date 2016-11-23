
/*
   문제

   Quantization (양자화) 과정은, 더 넓은 범위를 갖는 값들을 작은 범위를 갖는 값들로 근사해 표현함으로써 자료를 손실 압축하는 과정을 말한다. 예를 들어 16비트 JPG 파일을 4컬러 GIF 파일로 변환하는 것은 RGB 색 공간의 색들을 4컬러 중의 하나로 양자화하는 것이고, 키가 161, 164, 170, 178 인 학생 넷을 '160대 둘, 170대 둘' 이라고 축약해 표현하는 것 또한 양자화라고 할 수 있다.

   1000 이하의 자연수들로 구성된 수열을 최대 S종류 의 값만을 사용하도록 양자화하고 싶다. 이 때 양자화된 숫자는 원래 수열에 없는 숫자일 수도 있다. 양자화를 하는 방법은 여러 가지가 있다. 수열 1 2 3 4 5 6 7 8 9 10 을 2개의 숫자만을 써서 표현하려면, 3 3 3 3 3 7 7 7 7 7 과 같이 할 수도 있고, 1 1 1 1 1 10 10 10 10 10 으로 할 수도 있다. 우리는 이 중, 각 숫자별 오차 제곱의 합을 최소화하는 양자화 결과를 알고 싶다.

   예를 들어, 수열 1 2 3 4 5 를 1 1 3 3 3 으로 양자화하면 오차 제곱의 합은 0+1+0+1+4=6 이 되고, 2 2 2 4 4 로 양자화하면 오차 제곱의 합은 1+0+1+0+1=3 이 된다.

   수열과 S 가 주어질 때, 가능한 오차 제곱의 합의 최소값을 구하는 프로그램을 작성하시오.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어진다. 각 테스트 케이스의 첫 줄에는 수열의 길이 N (1 <= N <= 100), 사용할 숫자의 수 S (1 <= S <= 10) 이 주어진다. 그 다음 줄에 N개의 정수로 수열의 숫자들이 주어진다. 수열의 모든 수는 1000 이하의 자연수이다.

   출력

   각 테스트 케이스마다, 주어진 수열을 최대 S 개의 수로 양자화할 때 오차 제곱의 합의 최소값을 출력한다.

   예제 입력

   2
   10 3
   3 3 3 1 2  3 2 2 2 1
   9 3
   1 744 755 4 897 902 890 6 777

   예제 출력

   0
   651
*/

// Quantization 문제의 구현 

const int INF = 987654321;
// A[] : 양자화해야 할 수열, 정렬한 상태 
// pSum[] : A[]의 부분합을 저장한다. pSum[i]는 A[0]..A[i]의 합 
// pSqSum[] : A[] 제곱의 부분합을 저장한다. pSqSum[i]는 A[0]^2 .. A[i]^2의 합 
int n;
int A[101], pSum[101], pSqSum[101];
// A를 정렬하고 각 부분합을 계산한다. 
void precalc() {
    sort(A,A+n);
    pSum[0] = A[0];
    pSqSum[0] = A[0] * A[0];
    for( int i = 1; i < n; i++) {
        pSum[i] = pSum[i-1] + A[i];
        pSqSum[i] = pSqSum[i-1] + A[i] * A[i];
    }
}

// A[lo]..A[hi] 구간을 하나의 숫자로 표현할 때 최소 오차 합을 계산한다.
int minError(int lo, int hi) {
    // 부분합을 이용해 A[lo] ~ A[hi]까지의 합을 구한다. 
    int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo-1]);
    int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo-1]);
    // 평균을 반올림한 값으로 이 수들을 표현한다. 
    int m = int(0.5 + (double)sum/(hi-lo+1));
    // sum (A[i]-m)^2를 전개한 결과를 부분 합으로 표현 
    int ret = sqSum - 2 * m * sum + m * m * (hi-lo+1);
    return ret;
}

int cache[101][11];
int quantize(int from, int parts) {
    // base case : 모든 숫자를 다 양자화했을 때 
    if (from == n ) return 0;
    // base case : 숫자는 아직 남았는데 더 묶을 수 없을 때 아주 큰 값을 반환한다. 
    int (parts == 0) return INF;
    int* ret = &cache[from][parts];
    if (*ret != -1) return *ret;
    *ret = INF;
    // 조각의 길이를 변화시켜 가며 최소치를 찾는다. 
    for (int partSize = 1; from+partSize <= n; partSize++)
        *ret = min(*ret,minError(from,from+partSize-1) + quantize(from+partSize,parts-1));

    return *ret;
}

