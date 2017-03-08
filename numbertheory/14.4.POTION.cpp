/*
   문제

   마법의 약 수업 시간에 교수님의 설명을 안 듣고 졸던 헤리는 실수로 냄비에 몇 가지 재료의 양을 잘못 넣고 말았습니다. 약의 색깔이 심상치 않게 변하는 것을 눈치챈 해르미온느가 재빨리 레시피의 정확한 양을 알려주어서 약을 전부 망치는 것은 면했습니다. 지금 얼른 재료를 더 넣어서 약을 완성해야 합니다.

   이번 시간에 만드는 마법의 약은 n 종류의 재료를 각 ri 숟가락씩 넣어서 만들어야 합니다. 모든 재료를 정확히 넣었을 경우 만들어진 마법의 약은 정확히 한 병 분량이 됩니다. 헤리가 이미 냄비에 넣은 각 재료들의 양은 pi 로 주어집니다. 헤리는 적절히 냄비에 재료를 최소한으로 더 넣어 각 재료의 비율을 정확히 맞추고 싶습니다. 이를 위해 한 병보다 많은 약을 만들어도 상관 없지만, 최소한 한 병은 만들어야 합니다. 헤리는 항상 숟가락 단위로만 재료를 넣을 수 있기 때문에, 반 숟가락의 재료를 더 넣는다거나 하는 일은 불가능합니다.

   넣어야 할 각 재료의 최소량을 계산하는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 c (c <= 50) 가 주어집니다. 각 테스트 케이스는 세 줄로 구성됩니다. 첫 줄에는 재료의 수 n (1 <= n <= 200) 이 주어지고, 다음 줄에는 n 개의 정수로 약에 들어가야 하는 각 재료의 양 ri (1 <= ri <= 1000), 그 다음 줄에는 n 개의 정수로 이미 냄비에 넣은 재료의 양 pi (0 <= pi <= 1000) 가 주어집니다.

   출력

   각 테스트 케이스마다 한 줄에 n 개의 정수로 각 재료마다 더 넣어야 하는 양을 출력합니다.

   예제 입력

   3
   4
   4 6 2 4
   6 4 2 4
   4 
   4 6 2 4
   7 4 2 4
   3
   4 5 6 
   1 2 3 
   예제 출력

   0 5 1 2
   1 8 2 4
   3 3 3
*/

// 코드 14.8 마법의 약 문제를 해결하는 단순한 알고리즘 

// 마법의 약 레서피와 이미 넣은 재료의 양이 주어질 때, 더 넣을 재료의 양을 구한다.
vector<int> solveSimulation (const vector<int> recipe, vector<int> put) {
    int n = recipe.size();
    vector<int> ret(n);

    // 각 재료를 최소한 recipe에 적힌 만큼은 넣어야 한다.
    for (int i = 0; i < n; i++) {
        ret[i] = max(recipe[i] - put[i], 0);
        put[i] += ret[i];
    }

    // 비율이 전부 맞을 때까지 재료를 계속 추가하자.
    int iter = 0;
    
    while (true) {
        iter++; 

        // 냄비에 재료를 더 넣지 않아도 될 때까지 반복한다.
        bool ok = true;
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) {
                // i번째 재료에 의하면 모든 재료는 put[i] /recipe[i] = X배 이상은 넣어야 한다. 
                // 따라서 put[j] 는 recipe[j] * X 이상의 정수가 되어야 한다. 
                int required = (put[i] * recipe[j] + recipe[i] -1 ) / recipe[i];
                // 더 넣어야 하는가?
                if (required > put[j]) {
                    ret[j] += required - put[j];
                    put[j] = required;
                    ok = false;
                }
            }
        if (ok) break;
    }

    return ret;
}

// 코드 14.9 마법의 약 문제를 해결하는 O(n) 알고리즘 

int gcd (int a, int b) {
    return b == 0 ? a : gcd (b,a%b);
}

// 분수 a/b보다 같거나 큰 최소의 자연수를 반환한다.
int ceil (int a, int b) {
    return (a + b -1) / b;
}

// 마법의 약 레서피와 이미 넣은 재료의 양이 주어질 때, 더 넣을 재료의 양을 구한다.
vector<int> solve (const vector<int>& recipe, const vector<int>& put) {
    int n = recipe.size();
    // 모든 recipe[]의 최대 공약수를 구한다. 
    int b = recipe[0];
    
    for (int i = 1; i < n; i++)
        b = gcd (b,recipe[i]);

    
    // 최소한 b/b = 1배는 만들어야 하므로, a의 초기값을 b로 둔다.
    int a = b;


    // X를 직접 구하는 대신 ceil(put[i]*b, recipe[i])의 최대값을 구한다.
    for (int i = 0; i < n; i++)
        a = max (a,ceil(put[i]*b,recipe[i]));

    // a/b배 분량을 만들면 된다.
    vector<int> ret(n);
    for (int i =0; i < n; i++)
        ret[i] = ((recipe[i] * a) / b) -put[i];

    return ret;
}

#include <iostream>
#include <algorithm>


using namespace std;
int r [200];
int smaller [200];
int p [200];

int gcd (int p, int q) {
    if (q == 0)
        return p;
    return gcd (q,p%q);
}

// [start , end]
int getCommonDivider (int start,int end)
{
    if (start == end)
        return r[start];

    if (end == start + 1)
        return gcd (r[start],r[end]);

    int mid = (start+end)/2;

    return gcd (getCommonDivider(start,mid),getCommonDivider(mid+1,end));
}

int calculate (int n)
{
    int commondivider = getCommonDivider (0,n);
    
    for (int i = 0; i < n; i++)
        smaller[i] = r[i] / commondivider;

    return commondivider;
}

void solver (int n)
{
    int minN = -1;
    int commondivider;
    
    commondivider = calculate (n);

    for (int i = 0; i < n; i++)
    {
        if (p[i] % smaller[i] == 0)
            minN = max (minN,p[i]/smaller[i]);
        else 
            minN = max (minN,(p[i]/smaller[i] + 1));
    }

    if (minN < commondivider)
        minN = commondivider;

    for (int i = 0; i < n; i++)
        cout << (minN*smaller[i] - p[i]) << " ";

    cout << endl;
}

int main (void)
{
    int testcase;

    cin>> testcase; 

    while (testcase--)
    {
        int n;
        cin >> n;

        for (int i = 0; i < n; i++)
            cin >> r[i];

        for (int i = 0; i < n; i++)
            cin >> p[i];

        solver(n);
    }
}

