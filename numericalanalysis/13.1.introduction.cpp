
// 수치 해석(numerical analysis)은 직접 풀기 힘든 수학 문제를 근사적을 푸는 알고리즘과 이들의 수치적 안정성, 오차의 범위 
// 등을 연구하는 분야. 

// bisection method 
// 주어진 범위 [lo,hi] 내에서 어떤 함수 f(x)의 값이 0이 되는 지점을 수치적으로 찾아내는 기법 
// 조건 : 연속 함수 -> 중간값 정리에 의해 성립된다.

// 코드 13.1 이분법의 예제 구현 

double f (double x);
// 이분법의 예제 구현 
double bisection (double lo, double hi)  {
    // 반복문 불변식을 강제한다.
    if (f(lo) > 0)
        swap (lo,hi);

    // 반복문 불변식 : f(lo) <= 0 < f(hi)

    while (fabs(hi-lo) > 2e-7) {
        double mid = (lo + hi) / 2;
        double fmid = f(mid);
        if (fmid <= 0)
            lo = mid;
        else 
            hi = mid;
    }

    // 가운데 값을 반환한다. (최대 오차 최소화)
    return (lo + hi) / 2;
}

// 종료 판정 
// 1. 절대 오차를 이용한 종료 판정 : 만약 정답과 10-7 이하의 차이가 나는 답들 또한 정답으로 인정한다 하면. |lo - hi| <= 2*10-7인 상황에서 
// 반복문을 종료하고 두 값의 평균을 반환하면 최대 오차는 |lo-hi|/2 <= 10-7이 된다. 
// 2. 상대 오차를 이용한 종료 판정 : 절대 오차를 다루는 방법은 값의 크기가 작을 때는 훌륭하게 동작하지만 값의 크기가 커지면 문제가 생길 수 있다. 
// 컴퓨터에서 소수는 가수부 (mantisa)와 지수부 (exponent)로 구성되기 때문에 표현할 수 있는 수의 집합이 제한되어 있다. 
// 따라서 숫자의 절대 값이 커지면 커질수록 표현할 수 있는 수들이 듬성듬성해지게 된다. 
// 정답 A에 대해 [A*(1-10-7),A*(1+10-7)] 범위에 포함되는 답을 정답으로 인정한다.
// 현재의 근사 값 (lo+hi)/2이 [lo,hi] 범위 안의 어떤 정답에 대해서도 정답으로 인정 되기위해서는 다음 조건이 참이어야 한다.
// (1-10-7) * hi < (lo+hi)/2 < (1+10-7) * lo
// 3. 정해진 횟수 만큼 반복하기 : 반복문을 100번 수행되도록 작성하면 우리가 반환하는 답의 절대 오차는 최대 |lo-hi|/20^101이 된다. 
// 큰 숫자를 다루는 경우에도 충분히 답을 구할 수 있고, 절대로 무한 루프에 빠지지 않으며, 프로그램의 최대 수행 시간을 예상하기도 쉽다.

// 코드 13.2 영원히 종료하지 않는 이분법의 예 

// lo = 123456123456.12346 , hi = 123456123456.12347로 double로 표현되기 때문에 두 수 사이에 double로 표현될 수 있는 수가 존재하지 않고,
// 두 수의 차이가 2e-7이상이기 때문에 영원히 종료되지 않는 코드이다.
// 종료되지 않는다.
void infiniteBisection() {
    double lo = 123456123456.1234588623046875;
    double hi = 123456123456.1234741210937500;
    while (fabs(hi-lo) > 2e-7)
        hi = (lo+hi) /2.0;
    printf("finished!\n");
}

// 예제: 단변수 다항 방정식의 수치적 해법 (ROOTS)

/*
   문제

   실수 근만을 갖는 ax2 + bx + c = 0과 같은 형태의 단변수 다항 방정식이 주어질 때, 이들의 근을 계산하는 프로그램을 작성하세요.

   다항식의 모든 해의 절대값은 10 이하라고 가정해도 좋습니다.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C(C<=50)가 주어집니다. 각 테스트 케이스의 첫 줄에는 방정식의 차수 n(2 <= n <= 5)이 주어지고, 그 다음 줄에 n+1개의 실수로 방정식의 차수가 고차항부터 주어집니다.

   출력

   각 테스트 케이스마다 n개의 실수로 오름차순으로 정렬된 방정식의 해를 출력합니다. 방정식의 해는 모두 다르다고 가정해도 좋습니다. 10-8 이하의 상대/절대 오차가 있는 답은 정답으로 처리됩니다.

   예제 입력

   2
   3
   1.00 -6.00 11.00 -6.00
   2
   1.00 -12.50 31.50
   예제 출력

   1.000000000000 2.000000000000 3.000000000000 
   3.500000000000 9.000000000000
*/

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

// 코드 13.3 단변수 다항 방정식의 해를 이분법으로 찾기 

// 단일 변수 다항식 p의 계수가 주어질 때 미분한 결과 p`의 계수를 반환한다.
vector<double> differentiate (const vector<double>& poly)
{
    vector<double> ret;
    int n = poly.size() -1;
    for (int i = 0; i < n; i++)
    {
        ret.push_back(poly[i]*(n-i));
    }

    return ret;
}

// 1차 혹은 2차 방정식을 푼다.
vector<double> solveNaive (const vector<double>& poly)
{
    vector<double> ret;
    int n = poly.size() -1;
    if (n == 1)
    {
        ret.push_back((-poly[1])/poly[0]);
    }
    else 
    {
        double a = poly[0];
        double b = poly[1];
        double c = poly[2];

        ret.push_back((-b-sqrt(b*b-4*a*c))/(2*a));
        ret.push_back((-b+sqrt(b*b-4*a*c))/(2*a));
    }

    return ret;
}

// 다항식 f(x)의 계수 poly가 주어질 때, f(x0)를 반환한다.
double evaluate (const vector<double>& poly, double x0)
{
    int n = poly.size();
    double ret = 0;
    for (int i = 0; i < n;i++)
    {
        ret += poly[i]*pow(x0,n-i-1);
    }

    return ret;
}

// 방정식의 해의 절대 값은 L이하여야 한다. 
const double L = 10;

// 방정식 sum(poly[i]*x^i) = 0의 근을 반환한다.
vector<double> solve (const vector<double>& poly) {
    int n = poly.size() - 1;
    // base case : 2차 이하의 방정식들은 풀 수 있다. 
    if (n <= 2) return solveNaive(poly);
    // 방정식을 미분해서 n-1차 방정식을 얻는다.
    vector<double> derivative = differentiate(poly);
    vector<double> sols = solve (derivative);
    // 이 극점들 사이를 하나하나 검사하며 근이 있나 확인한다.
    sols.insert(sols.begin(),-L-1);
    sols.insert(sols.end(),L+1);
    vector<double> ret;
    for (int i = 0; i+1 < sols.size(); i++) {
        double x1 = sols[i], x2 = sols[i+1];
        double y1 = evaluate(poly,x1), y2 = evaluate(poly,x2);
        // f(x1)과 f(x2)의 부호가 같은 경우 답은 없다.
        if (y1*y2 > 0)
            continue;
        // 불변 조건 : f(x1) <= 0 < f(x2) 
        if (y1 > y2) {
            swap(y1,y2);
            swap(x1,x2);
        }

        // 이분법을 사용하자.
        for (int iter = 0; iter < 100; iter++) {
            double mx = (x1+x2)/2;
            double my = evaluate(poly,mx);
            if (my <= 0) {
                y1 = my;
                x1 = mx;
            }
            else {
                y2 = my;
                x2 = mx;
            }
        }

        ret.push_back((x1+x2)/2);
    }

    sort (ret.begin(),ret.end());
    return ret;
}

void read (vector<double>& c)
{
    int n;
    double temp;
    cin >> n;
    n++;
    while (n--)
    {
        cin >> temp;
        c.push_back(temp);
    }
}

int main (void)
{
    int testcase;
    cin >> testcase;

    while (testcase--)
    {
        vector<double> c;
        vector<double> answer;
        read(c);
        answer = solve(c);      
        for (int i = 0; i <answer.size(); i++)
        {
            printf("%.12lf ",answer[i]); 
        }
        puts("");
    }

}

// 예제 : 전세금 균등상환 (LOAN)
/*
   문제

   집을 떠나 혼자 살게 된 재훈이는 회사 근처의 전세집을 알아보고 있습니다. 전세금은 N원인데, 재훈이는 이것을 연이율 P%로 대출받을 수 있습니다. 재훈이는 M개월 동안 매달 일정액 C원씩을 갚으려고 합니다.

   대출의 잔금은 대출 기간 동안 다음과 같이 변화합니다.

   ᆞ대출의 잔금은 대출 금액 N원에서 시작합니다.
   ᆞ한 달이 지날 때마다 대출 잔금이 월 이자 (P/12)% 만큼 불어납니다.
   ᆞ이자가 추가된 다음 월 상환액 C를 대출 잔금에서 제합니다.
   M개월 걸려 모든 대출 금액을 갚기 위해서는 한 달에 최소 얼마씩을 갚아야 할까요?

   입력

   입력의 첫 줄에는 테스트 케이스의 수 T(<= 50)가 주어집니다. 각 테스트 케이스는 3개의 수 N, M, P(1 <= N <= 100,000,000, 1 <= M <= 120, 0 < P <= 50)으로 주어집니다. N과 P는 실수이며, M은 정수입니다.

   출력

   각 테스트 케이스마다 한 줄에 한 달마다 상환할 금액 C를 출력합니다. 10-7 이하의 절대/상대 오차가 있는 답은 정답으로 인정됩니다.

   예제 입력

   4
   20000000 12 6.8
   35000000 120 1.1
   40000000 36 0.5
   100 120 0.1
   예제 출력

   1728691.4686372071
   308135.8967737053
   1119696.7387703573
   0.8375416659
*/


 
#include <iostream>
#include <stdio.h>

using namespace std;

// 코드 13.4 전세금 균등상환 문제를 해결하는 이분법의구현 

// amount원을 연 이율 rates 퍼센트로 duration월 간 한달에 monthlyPayment로 
// 갚았을 때 대출 잔금은?
double balance (double amount, int duration, double rates, double monthlyPayment) {
    double balance = amount;
    for (int i =0; i < duration; i++) {
        // 이자가 붙는다.
        balance *= (1.0 + (rates/12.0)/100.0);
        // 상환액을 잔금에서 제한다.
        balance -= monthlyPayment;
    }

    return balance;
}

// amount원을 연 이율 rates 퍼센트로 duration월 간 갚으려면 한 달에 얼마씩 갚아야 하나?
double payment (double amount, int duration, double rates) {
    // 1. lo원씩 갚으면 duration개월 안에 갚을 수 없다.
    // 2. hi원씩 갚으면 duration개월 안에 갚을 수 있다.
    double lo = 0;
    double hi = amount*(1.0 + (rates/12.0)/100.0);
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi)/2.0;
        if (balance(amount,duration,rates,mid) <= 0)
            hi = mid;
        else 
            lo = mid; 
    }

    return hi;
}

int main (void)
{
    int testcase;
    double amount,rates;
    int duration;
    cin >> testcase;

    while (testcase--)
    {
        cin >> amount >> duration >> rates;
        printf("%.10lf\n",payment(amount,duration,rates));
    }
}





