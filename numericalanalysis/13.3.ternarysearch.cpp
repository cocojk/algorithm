
// ternary search (삼분 검색)
// 조건 
// 1. local maximum(양쪽 점보다 높이 있는 점) 1개 존재 => 하나의 극대(mode)가 있어서 유니 모달 함수(unimodal function) 
// 2. 최대점 왼쪽에서 x에 따라 항상 순증가 (strictly increasing) (수평 부분 허용 X >)
// <=> 단조 증가 (monotonically increasing) (수평 부분 허용 >=)
// 3. 최대점 오른쪽에서 x에 따라 항상 순감소 (strictly decreasing) 
// 미분 할 수 있는 경우 도함수 값이 0이 되는 점이고, local search같은 알고리즘을 통해서도 답을 구할 수 있다. 
// local search : 임의의 답을 하나 만들어 놓고 이 값을 조금씩 갱신하면서 답이 더 좋아지는 쪽으로 움직이는 알고리즘. 
// ternary search는 미분할 수 없는 함수에도 사용할 수 있으며, local search에 비해 훨씬 빠르게 동작하고 수렴 판정이 용이하다.


// 최대치를 포함하는 후보 구간이 [lo,hi]라고 하면, 삼등분의 위치는 (2*lo + hi)/3 , (lo + 2*hi)/3이 된다. 
// 1. f((2*lo + hi)/3) < f((lo + 2*hi)/3) 
// 왼쪽 구간 [lo,(2*lo + hi)/3]에는 최대치 존재할 수 없다.
// 2. f((2*lo + hi)/3) > f((lo + 2*hi)/3)
// 오른쪽 구간 [(lo + 2*hi)/3,hi]에는 최대치 존재할 수 없다. 
// 이와 같이 한 번 반복할 때마다 후보 구간의 크기를 2/3로 줄여나간다. 

// 코드 13.6 삼분 검색의 구현 

// 우리가 최대치를 찾고 싶어하는 함수 
double f (double x);
// [lo,hi] 구간에서 f(x)가 최대치를 갖는 x를 반환한다. 
double ternary (double lo, double hi) {
    for (int iter = 0; iter < 100; iter++) {
        double a = (2*lo + hi)/3.0;
        double b = (lo + 2*hi)/3.0;
        if (f(a) > f(b))
            hi = b;
        else 
            lo = a;
    }
    
    return (lo + hi) / 2.0;
}

// 예제 : 철인 2종 경기 
/*
   달리기와 자전거로 총 t 킬로미터를 달리는 철인 2종 경기를 개최합니다. 0번부터 n-1번 까지 모두 n명의 참가자가 등록했으며, 각 참가자의 달리기 속도와 자전거 속도가 주어진다. 그런데 n-1번 참가자가 주최측에 뇌물을 건네며 자신이 승리할 수 있도록 달리기와 자전거 경주의 길이를 조정해달라고 요청했습니다. 이 참가자가 2등과 가장 큰 차이로 우승하려면 달리기 경주의 길이 r과 자전거 경주의 길이 t-r을 어떻게 정해야 할까요? 
*/

// concave function & convex function 
// 아래에서 볼때 '오목하게' 생긴 함수들은 오목함수 (concave function) 
// 아래로 '볼록하게' 생긴 함수 볼록 함수 (convex function) 
// concave function & convex function 은 ternary search의 요구 조건을 '거의' 만족한다.
// why? 이들 함수에는 수평선이 존재할 수 있다. (strictly inc/dec X)  하지만, 이런 수평선이 있을 수 있느느 곳은 최소,최대점 뿐이다.
// ternary search의 후보 범이구ㅏ 수평선 내에 들어오더라도 이미 모든 후보가 최소,최대치를 포함한다면 상관없이 항상 정답을 구할 수 있다. 
// 따라서, concave & convex function의 최대, 최소를 찾는 문제는 항상 ternary search 이용가능. 

// concave & concave function property 
// 1. f(x) concave (convex) <=> -f(x) convex(concave)
// 2. concave(convex) + concave(convex) = concave(convex) 두 함수 합  
// 3. c * concave(convex) = concave(convex) 상수 곱

// linear = concave 이기도 하고 convex 이기도 하다. 
// 따라서, linear + concave(convex) = concave(convex)

// 코드 13.7 철인 2종 경기 문제를 해결하는 삼분 검색 알고리즘 

double t;
vector<double> runSpeed, cycleSpeed;
// 달리기 구간의 길이가 run일 때, i번 선수가 걸리는 시간 
double time (int i , double run) {
    double cycle = t - run;
    return run / runSpeed[i] + cycle /cycleSpeed[i];
}

// 달리기 구간 길이가 r일 때, others(r) - cheater(r)를 반환한다. 
double diff (double r) {
    int n = runSpeed.size();
    double cheater = time (n-1, r);
    double others = time (0,r);
    for (int i = 1; i < n-1; i++)
        others = min(others,time(i,r));
    return others - cheater;
}

// diff() 함수의 최대치의 위치를 삼분 검색으로 계산한다.
double maxDifference() {
    double lo = 0, hi = t;
    for (int it = 0; it < 100; it++) {
        double aab = (2*lo + hi)/3;
        double abb = (lo + 2*hi)/3;
        if (diff(aab) > diff(abb))
            hi = abb;
        else 
            lo = aab;
    }

    return (lo + hi)/2;
}

