
// 부분합의 계산의 경우 최대 O(N)이 걸린다. 만약 부분합의 계산이 많이 일어나는 경우 더 최적화 할 수 없을까?
// partial sum을 이용하면 된다.
// partial sum - 배열의 각 위치에 대해 배열의 시작부터 현재 위치까지의 원소의 합을 구해 둔 배열이다.
// partial sum을 이용하면 부분합을 O(1)에 구할 수 있다.

// 부분합을 계산하는 함수와 이를 이용해 구간합을 계산하는 함수의 구현 
// 주어진 벡터 a의 부분합을 계산한다. O(N) 
vector<int> partialSum(const vector<int>& a) {
    vector<int> ret(a.size());
    ret[0] = a[0];
    for(int i = 1; i < a.size(); i++)
        ret[i] = ret[i-1] + a[i];
    return ret;
}

// 어떤 벡터의 부분합 psum[]이 주어질때, 원래 벡터의 a부터 b까지의 합을 구한다. O(1)
int rangeSum(const vector<int>& psum, int a, int b) {
    if (a == 0) return psum[b];
    return psum[b] - psum[a-1];
}

// 배열의 부분합과 제곱의 부분합을 입력받고 특정 구간의 분산을 계산하는 함수의 구현 
// A[]의 제곱의 부분합 벡터 sqpsum, A[]의 부분 합 벡터 psum이 주어질 때
// A[a..b]의 분산을 반환한다.
double variance (const vector<int>& sqpsum, const vector<int>& psum, int a, int b) {
    // 우선 해당 구간의 평균을 계산한다.
    double mean = rangeSum(psum, a, b) / double(b-a+1);
    double ret = rangeSum(sqpsum, a, b) - 2 * mean * rangeSum(psum, a, b) n+ (b-a+1)*mean*mean;
    return ret / (b-a+1);
}

// 2차원으로의 확장 
// 부분합을 이용해 2차원 배열의 구간 합을 구하는 함수의 구현 
// 어떤 2차원 배열 A[][]의 부분합 psum[][]이 주어질 때, ((0,0)을 왼쪽 위칸, (y,x)를 오른쪽 아래칸)
// A[y1,x1]과 A[y2,x2]를 양 끝으로 갖는 부분 배열의 합을 반환한다.
int gridSum (const vector<vector<int> > & pSum, int y1, int x1, int y2, int x2) { 
    int ret = psum[y2][x2];
    if(y1 > 0) ret -= psum[y1-1][x2];
    if(x1 > 0) ret -= psum[y2][x1-1];
    if(y1 > 0 && x1 > 0) ret += psum[y1-1][x1-1];
    return ret;
}

// 합이 0에 가장 가까운 구간 
// 양수와 음수가 모두 포함된 배열 A[]가 있을 때, 그 합이 0에 가장 가까운 구간을 찾는 문제 
// 부분 합이 0에 가장 가깝다는 것은 partialSum의 두 값의 차이가 가장 적은 것을 골라내는 것이다.
// 1. partialSum을 모두 구한다. O(N)
// 2. sorting 후, adjacent한 것들의 차이가 가장 적은 것을 찾아낸다. sorting - O(NlgN)  find - O(N)
// 그래서 총 O(NlgN)




