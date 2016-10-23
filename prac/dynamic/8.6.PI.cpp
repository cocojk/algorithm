
/*
   문제

   (주의: 이 문제는 TopCoder 의 번역 문제입니다.)

   가끔 TV 에 보면 원주율을 몇만 자리까지 줄줄 외우는 신동들이 등장하곤 합니다. 이들이 이 수를 외우기 위해 사용하는 방법 중 하나로, 숫자를 몇 자리 이상 끊어 외우는 것이 있습니다. 이들은 숫자를 세 자리에서 다섯 자리까지로 끊어서 외우는데, 가능하면 55555 나 123 같이 외우기 쉬운 조각들이 많이 등장하는 방법을 택하곤 합니다.

   이 때, 각 조각들의 난이도는 다음과 같이 정해집니다:

   모든 숫자가 같을 때 (예: 333, 5555) 난이도: 1
   숫자가 1씩 단조 증가하거나 단조 감소할 때 (예: 23456, 3210) 난이도: 2
   두 개의 숫자가 번갈아 가며 출현할 때 (예: 323, 54545) 난이도: 4
   숫자가 등차 수열을 이룰 때 (예: 147, 8642) 난이도: 5
   그 외의 경우 난이도: 10
   원주율의 일부가 입력으로 주어질 때, 난이도의 합을 최소화하도록 숫자들을 3자리에서 5자리까지 끊어 읽고 싶습니다. 최소의 난이도를 계산하는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (<= 50) 가 주어집니다. 각 테스트 케이스는 8글자 이상 10000글자 이하의 숫자로 주어집니다.

   출력

   각 테스트 케이스마다 한 줄에 최소의 난이도를 출력합니다.

   예제 입력

   5 
   12341234 
   11111222 
   12122222 
   22222222 
   12673939 
   예제 출력

   4
   2
   5
   2
   14 
*/

// 원주율 외우기 문제를 해결하는 동적 계획법 알고리즘 
const int INF = 987654321;
string N;
// N[a..b] 구간의 난이도를 반환한다.
int classify(int a, int b) {
    // 숫자 조각을 가져온다.
    string M = N.substr(a,b-a+1);
    // 첫 글자만으로 이루어진 문자열과 같으면 난이도는 1 
    if (M == string(M.size(),M[0]))
        return 1;
    // 등차수열인지 검사한다.
    bool progressive = true;
    for(int i = 0; i < M.size() - 1; i++)
        if(M[i+1] - M[i] != M[1] - M[0])
            progressive = false;
    // 등차수열이고 공차가 1 혹은 -1이면 난이도는 2 
    if(progressive && abs(M[1] - M[0]) ==1)
        return 2;
    // 두 수가 번갈아 등장하는지 확인한다.
    bool alternating = true;
    for (int i = 0; i < M.size(); i++)
        if(M[i] != M[i%2])
            alternating = false;
    // 두 수가 번갈아 등장하면 난이도는 4 
    if(alternating) return 4;
    // 공차가 1 아닌 등차수열의 난이도는 5 
    if(progressive) return 5; 
    // 이 외는 모두 난이도 10 
    return 10;
}

int cache[10002];
// 수열 N[begin..]를 외우는 방법 중 난이도의 최소 합을 출력한다.
int memorize(int begin) {
    // base case : 수열의 끝에 도달했을 경우 
    if(begin == N.size())
        return 0;
    // memoization
    int* ret = &cache[begin];
    if(*ret != -1)
        return *ret;
    *ret = INF;
    for(int L = 3; L <=5; L++)
        if(begin + L <= N.size())
            *ret = min(*ret,memorize(begin+L) + classify(begin,begin+L-1));
    return *ret;
}

