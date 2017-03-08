/*
   문제

   재훈이는 한 번 담배를 끊겠다고 다짐할 때마다 이메일 계정 비밀번호를 바꾸는 습관이 있습니다. 재훈이는 비밀번호를 항상 "no-smok**X**" 와 같이 정하는데, 여기서 X는 1자리 이상의 자연수입니다. 재훈이에게는 k번째로 금연을 다짐할 때는 항상 정확히 k개의 약수를 갖는 숫자로 X를 선택하는 습관이 있습니다. 예를 들어 재훈이가 12번째로 금연을 다짐했을 때 쓴 비밀번호는 no-smok486 이었습니다. 486 에는 1, 2, 3, 6, 9, .., 243, 486으로 모두 12개의 약수가 있으니까요.

   재훈이는 금연을 다짐하고 비밀번호를 바꾼 뒤 잠들었는데, 아침에 일어나서는 비밀번호가 기억나지 않는다는 사실을 깨달았습니다. 재훈이가 어렴풋이 기억하는 것은 비밀번호가 n개의 약수를 가진다는 사실과, 비밀번호가 아마도 [lo,hi] 범위 내에 있을 거라는 것 뿐입니다 (범위는 양 끝의 수를 포함합니다).

   재훈이가 예상한 범위 내에 비밀번호가 될 수 있는 수가 몇 개나 되는지 계산하는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 c(c <= 50)가 주어집니다. 그 후 c줄에 각 3개의 정수로 n (n < 400), lo , hi(1 <= lo <= hi <= 10,000,000)이 주어집니다. hi-lo 는 항상 1백만 이하입니다.

   출력

   각 테스트 케이스마다, 해당 범위 내에 비밀번호가 될 수 있는 숫자가 몇 개인지 출력합니다.

   예제 입력

   3
   2 2 10
   12 486 486
   200 1000000 2000000 
   예제 출력

   4
   1
   19
*/

// 코드 14.5 1천만 이하의 모든 수의 약수의 수를 계산하는 알고리즘 

// ten milion 
const int TM = 1000*1000*10;
// minFactor[i] = i의 가장 작은 소인 수 (i가 소수인 경우 자기 자신)
int minFactor[TM+1];
// minFactorPower[i] = i의 소인수 분해에는 minFactor[i]의 몇 승이 포함되어 있는가?
int minFactorPower [TM+1];
// factors[i] = i가 가진 약수의 수 
int factors [TM+1];
void getFactorSmart () {
    factors[1] = 1;
    for (int n = 2; n <= TM; n++) {
        // 소수인 경우 약수가 두 개 밖에 없다.
        if (minFactor[n] ==n) {
            minFactorPower[n] = 1;
            factors[n] = 2;
        }
        // 소수가 아닌 경우, 가장 작은 소인수로 나눈 수 (m)의 
        // 약수의 수를 응용해 n의 약수의 수를 찾는다.
        else {
            int p = minFactor[n];
            int m = n/p;
            // m이 p로 더이상 나누어지지 않는 경우 
            if (p != minFactor[m])
                minFactorPower[n] = 1;
            else 
                minFactorPower[n] = minFactorPower[m] + 1;
            int a = minFactorPower[n];
            factors[n] = (factors[m] / a) * (a+1);
        }
    }
}



#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;

const int MAXN = 10000001;
int minFactor [MAXN];

void eratosthenes2 (int n) {
    minFactor[0] = minFactor[1] = -1;

    for (int i = 2; i <= n; i++)
        minFactor[i] = i;

    int sqrtn = int(sqrt(n));
    for (int i = 2; i <= sqrtn; i++)
    {
        if (minFactor[i] == i)
        {
            for (int j = i*i; j <= n; j += i)
            {
                if (minFactor[j] == j)
                    minFactor[j] = i;
            }
        }
    }

}

int solver (int lo, int hi,int n)
{
    int ret = 0;
    int current;
    vector<int> prime;
    int beforePrime;
    int tempCounter;
    vector<int> counter;
    for (int i = lo; i <= hi; i++)
    {
        beforePrime = minFactor[i];
        tempCounter = 1;
        counter.clear();
        current = i / minFactor[i];

        while (current > 1)
        {
            if (beforePrime == minFactor[current])
            {
                tempCounter ++;
            }
            else 
            {
                beforePrime = minFactor[current];
                counter.push_back(tempCounter+1);
                tempCounter = 1;
            }

            current /= minFactor[current];
        }

        counter.push_back(tempCounter+1);

        int total = 1;
        for (int i = 0; i < counter.size(); i++)
            total *= counter[i];

        if (total == n)
            ret++;
    }

    return ret;
}

int main (void)
{
    int testcase;
    cin >> testcase;
    eratosthenes2(MAXN);

    while (testcase--)
    {
        int n, lo, hi;
        cin >> n >> lo >> hi;

        cout << solver(lo,hi,n) <<endl;
    }
}




