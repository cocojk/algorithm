
// 유명한 디자인 원칙 중 하나 
// 최적화 문제를 결정 문제(decision problem)로 바꾼 뒤, 이것을 이분법을 이용해 해결하는 방법  
// decision problem = 예 혹은 아니오 형태의 답만이 나오는 문제들 
// Optimization problem = 실수나 정수 형태의 답 
// ex) tsp
// optimize(G) = 그래프 G의 모든 정점을 한 번씩 방문하고 시작점으로 돌아오는 최단 경로의 길이를 반환한다. (최적화 문제)
// decision(G,x) = 그래프 G의 모든 정점을 한 번씩 방문하고 시작점으로 돌아오면서 길이가 x 이하인 경로의 존재 여부를 반환한다. 

// 최적화 문제와 결정 문제의 관계 
// 1. 두 문제의 형태가 똑같이 어려운 경우 
// 2. 최적화 문제가 더 어려운 경우 
// 결정 문제는 최적화 문제보다 더 어려울 수 없다. 왜냐하면 최적화 문제를 푼 경우 결정 문제는 자동으로 풀리기 때문에. 
double optimize (const Graph& g);
bool decision (const Graph& g, double x) {
    return optimize(g) <= x;
}

// 최적화 문제를 결정 문제로 바꾸는 레시피 
// 1. "가장 좋은 답은 무엇인가?"라는 최적화 문제를 "x 혹은 그보다 좋은 답이 있는가?"라는 결정 문제 형태로 바꾼다.
// 2. 결정 문제를 쉽게 풀 수 있는 방법이 있는지 찾아본다.
// 3. 결정 문제를 내부적으로 이용하는 이분법 알고리즘을 작성한다. 

/*
   문제

   DARPA Grand Challenge 는 운전자 없는 차들을 컴퓨터 인공지능으로 조작해 누가 먼저 결승점에 도달하느냐를 가지고 겨루는 인공지능 대회입니다. 2004년 DARPA Grand Challenge 의 과제는 사막을 가로지르는 240km 도로를 완주하는 것이었습니다.

   우리는 이 경기를 N 개의 카메라로 중계하려고 합니다. 이 도로에는 카메라를 설치할 수 있는 곳이 M 군데 있습니다. 여기에 카메라를 배치하여, 가장 가까운 두 카메라 간의 간격을 최대화하고 싶습니다. 이와 같은 배치를 찾아내는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (<= 50) 이 주어집니다. 각 테스트 케이스의 첫 줄에는 카메라의 개수 N (<= 100) 과 설치 가능한 중계소의 수 M (N <= M <= 200) 이 주어집니다. 그 다음 줄에는 M 개의 실수로, 카메라를 설치 가능한 곳의 위치가 오름 차순으로 주어집니다. 각 위치는 시작점에서부터의 거리로, 240 이하의 실수이며 소숫점 둘째 자리까지 주어질 수 있습니다.

   출력

   각 테스트 케이스마다 가장 가까운 두 카메라 간의 최대 간격을 소수점 셋째 자리에서 반올림해 출력합니다.

   예제 입력

   3
   2 4 
   80 100 120 140 
   4 4 
   80 100 120 140.00
   4 7 
   0 70 90 120 200 210 220 
   예제 출력

   60.00
   20.00
   50.00
*/

// 코드 12.1 DARPA의 결정 문제 형태를 해결하는 탐욕적 알고리즘 

// 결정 문제 : 정렬되어 있는 locations 중 cameras를 선택해 모든 카메라 간의 간격이 
// gap 이상이 되는 방법이 있는지를 반환한다.
bool decision (const vector<double>& location, int cameras, double gap) {
    // 카메라를 설치할 수 있을 때마다 설치하는 탐욕적 알고리즘 
    double limit = -1;
    int installed = 0 ;
    for (int i = 0; i < location.size(); i++) {
        if (limit <= location[i]) {
            ++installed;
            // location[i] + gap 이후는 되어야 카메라를 설치할 수 있다.
            limit = location[i] + gap;
        }
    }

    // 결과적으로 cameras대 이상을 설치할 수 있었으면 성공 
    return installed >= cameras;
}

// 최적화 문제 : 정렬되어 있는 locations 중 cameras를 선택해 최소 간격을 최대화한다.
double optimize (const vector<douoble>& location, int cameras) {
    double lo = 0; hi = 241;
    // 반복문 불변식 : decision(lo) && !decision(hi)
    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2.0;
        // 간격이 mid 이상이 되도록 할 수 있으면 답은 [mid,hi]에 있다.
        if (decision(location,cameras,mid))
            lo = mid;
        // 간격이 mid 이상이 되도록 할 수 없으면 답은 [lo,mid]에 있다.
        else 
            hi = mid;
    }

    return lo;
}


