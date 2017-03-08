/*
문제

봄마다 비염 환자들을 괴롭히는 꽃가루는 종종 과거의 기후 변화를 추적하는 데 유용하게 사용됩니다. 퇴적층에서 발견되는 꽃가루 화석을 통해 각 지방의 기후가 어땠는지 확인할 수 있기 때문입니다. 아마추어 고생물학자인 후연이는 서로 다른 환경에서 자라는 두 종류의 꽃 A 와 B 에 대해 각각의 꽃가루가 발견된 위치들을 지도상에 다음 그림과 같이 표시해 보았습니다.

hulls-cv.png

이 지도에서는 y 좌표가 증가하는 방향이 북쪽, x 좌표가 증가하는 방향이 동쪽입니다. 후연이는 각 꽃의 서식지를 예측하기 위해, 해당 화석이 발견된 위치들을 감싸는 최소의 볼록 다각형을 위 그림에 표시된 것과 같이 구했습니다. 이 다각형들을 볼록 껍질(convex hull) 이라고 부릅니다.

후연이는 이 두 개의 볼록 껍질이 서로 겹치는 부분은 과거에 온도 변화가 심했을 것이라는 가설을 세웠습니다. 이 부분이 얼마나 넓은지 확인하기 위해 이 겹치는 부분 중 남북 방향 폭이 가장 넓은 위치를 찾고자 합니다. 예를 들어 위 그림에서는 점선으로 표현된 곳에서 남북 방향의 폭이 가장 넓습니다.

두 개의 볼록 껍질이 주어질 때 겹치는 부분의 남북 최대 폭을 계산하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 c (c <= 50) 가 주어집니다. 각 테스트 케이스는 세 줄로 주어집니다. 첫 줄에는 두 볼록 껍질에 포함된 점의 수 n 과 m (1 <= n,m <= 100) 이 주어집니다. 다음 줄에는 2n 개의 실수로 첫 번째 볼록 껍질에 포함된 점의 좌표 (x,y) 가 시계 반대 방향 순서대로 주어집니다. 그 다음 줄에는 2m 개의 실수로 두 번째 볼록 껍질에 포함된 점의 좌표 (x,y) 가 시계 반대 방향 순서대로 주어집니다. 각 좌표는 [0,100] 범위의 실수로, 소수점 밑 최대 2자리까지만 주어집니다.

한 테스트 케이스에는 같은 점이 두 번 들어오지 않으며, 한 직선 위에 있는 세 점이 주어지는 일도 없습니다. 주어진 두 다각형의 모든 내각은 180도 미만입니다.

출력

각 테스트 케이스마다 한 줄에, 두 볼록 껍질이 겹치는 부분의 남북 최대 폭을 출력합니다. 만약 두 볼록 껍질이 겹치지 않을 경우 0 을 출력합니다. 정답과 10-7 이하의 절대/상대 오차를 갖는 답은 정답으로 인정됩니다.

예제 입력

2
5 5
35.74 35.85 69.64 50.00 73.52 82.55 43.50 92.22 17.67 76.18
16.47 8.02 60.98 14.62 66.80 37.74 45.89 67.22 13.04 55.19
4 3
73.84 11.41 71.61 32.72 39.87 38.84 22.41 17.87
75.13 51.64 47.72 87.34 15.97 64.56
예제 출력

27.6529680365
0.000000
*/

#include <cmath>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct point {
    double y, x;
};

// 입력에 주어진 볼록 다각형 
vector<point> hull1, hull2;

// 위 껍질에 속하는 선분들과 아래 껍질에 속하는 선분들 
vector<pair<point,point> > upper, lower;

// hull이 반시계 방향으로 주어지므로, 인접한 두 점에 대해 x가 
// 증가하는 방향이면 아래쪽 껍질, x가 감소하는 방향이면 위쪽 껍질이다. 
void decompose (const vector<point>& hull) {
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        if (hull[i].x < hull[(i+1)%n].x)
            lower.push_back (make_pair(hull[i],hull[(i+1)%n]));
        else if (hull[i].x > hull[(i+1)%n].x)
            upper.push_back (make_pair(hull[i],hull[(i+1)%n]));
    }
}

// hull의 점 중 최소의 x 좌표를 반환한다.
double minX (const vector <point>& hull) {
    double ret = 1e20;
    for (int i = 0; i < hull.size(); i++)
        ret = min (ret,hull[i].x);
    return ret;
}

// hull의 점 중 최대의 x 좌표를 반환한다. 
double maxX (const vector<point>& hull) {
    double ret = -1e20;
    for (int i = 0; i < hull.size(); i++)
        ret = max (ret,hull[i].x);
    return ret;
}

// [a.x, b.x] 구간 안에 x가 포함되나 확인한다.
bool between (const point& a, const point& b, double x) {
    return (a.x <= x && x <= b.x) || (b.x <= x && x <= a.x);
}
 
// (a,b) 선분과 주어진 위치이ㅡ 수직선이 교차하는 위치를 반환한다.
double at (const point& a, const point& b, double x) {
    double dy = b.y - a.y, dx = b.x - a.x;
    // 선분 (a,b)가 수직인 경우를 따로 처리한다.
    if (fabs(dx) < 1e-9) 
        return a.y;
    return a.y + dy * (x - a.x) / dx;
}

// 두 다각형의 교집합을 수직선으로 잘랐을 때 단면의 길이를 반환한다.
double vertical (double x) {
    double minUp = 1e20, maxLow = -1e20;

    // 위 껍질의 선분을 순회하며 최소 y 좌표를 찾는다. 
    for (int i = 0; i < upper.size(); i++)
        if (between(upper[i].first, upper[i].second, x))
            minUp = min(minUp,at(upper[i].first,upper[i].second,x));

    // 아래 껍질의 선분을 순회하며 최대 x 좌표를 찾는다. 
    for (int i =0; i < lower.size(); i++)
        if (between(lower[i].first, lower[i].second, x))
            maxLow = max(maxLow,at(lower[i].first ,lower[i].second,x));

    return minUp - maxLow;
}

double solve() {
    
    // 수직선이 두 다각형을 모두 만나는 x 좌표의 범위를 구한다 
    double lo = max (minX(hull1), minX(hull2));
    double hi = min (maxX(hull1), maxX(hull2));

	// 예외 처리: 두 다각형이 아예 겹치지 않는 경우
	if(hi < lo) return 0;

	// 삼분 검색
	for(int iter = 0; iter < 100; ++iter) {
		double aab = (lo*2 + hi) / 3.0;
		double abb = (lo + hi*2) / 3.0;
		if(vertical(aab) < vertical(abb))
			lo = aab;
		else
			hi = abb;
	}
	return max(0.0, vertical(hi));
}

int main() {
    int cases;
    cin >> cases;
    for(int cc = 0; cc < cases; ++cc) {
    	int n, m;
    	cin >> n >> m;
    	hull1.resize(n);
    	hull2.resize(m);
    	for(int i = 0; i < n; i++) cin >> hull1[i].x >> hull1[i].y;
    	for(int i = 0; i < m; i++) cin >> hull2[i].x >> hull2[i].y;
    	upper.clear();
    	lower.clear();
    	decompose(hull1);
    	decompose(hull2);
    	printf("%.10lf\n", max(0.0, solve()));
    }
}


