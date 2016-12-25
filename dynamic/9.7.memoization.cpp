
// 정수 이외의 입력에 대한 메모이제이션 

// 1. 연관 배열 사용하기 
// 예를 들어, 입력으로 정수배열이 주어진다면,
// STL의 map
// ex) map<vector<int>,int> cache; 
// vector<int>를 키를 갖는 map을 이용할 수 있다. 
// map에 접근할때마다 시간이 걸리고, vector와 같은 컨테이너들은 비교하는 데도 시간이 오래걸린다. 
// 계산량이 아주 작은 문제에만 사용할 수 있다. 

// 2. 일대일 대응 함수 작성하기 (bijection function)
// 입력을 적절하게 정수로 변환해 줄 수 있는 함수를 작성 
// 예를 들어, 주어지는 정수 배열이 항상 [1,n] 범위의 수를 하나씩 가지고 있다면, 입력의 종류는 n!가지가 된다. 
// 이럴 땐 입력 배열이 n!개의 가능한 입력 중 사전순으로 몇 번째인지르 반환하는 함수를 만들면 n! 크기의 배열을 
// 이용해 메모이제이션을 할 수 있다. 

int cache[N_FACTORIAL];
// N!개의 입력 중 key가 몇 번째에 해당하는지 반환한다. 
int mapFunc (const vector<int>& key);
int f (const vector<int>& key) {
    // base case를 처리한다. 
    // 메모이제이션 
    int* ret = &cache[mapFunc(key)];
    if (*ret != -1)
        return *ret;
    // 답을 실제로 계산한다. 
    return *ret;
}

// 일대일 대응이 아니면, 메모리가 낭비되거나 같은 영역을 가르키게 되서 오류를 초래한다. 

// 3. 입력이 불린 값의 배열인 경우 
// 길이 n인 배열을 길이가 n인 이진수로 보는 것
// A[0]은 맨 아래 자리, A[1]은 그 다음 자리, A[n-1]은 가장 윗자리 
// 이때 해당 위치에 참 값이 들어 있다면 그 자리에 1이 있는 것으로 본다.
// 이 이진수는 항상 [0,2^n-1] 구간의 값이고, 주어진 배열과 일대일 대응이 된다. 
// 이와 같은 방식은 원래의 시간 복잡도가 팩토리얼 이거나 2보다 큰 밑을 사용하는 지수 함수인 알고리즘을 메모이제이션하는 데 유용하게 사용된다. 

// 4. 입력이 순열인 경우 
// 이런 문제는 가능한 n!개의 입력들 중 X가 사전순으로 몇 번째 오는지를 계산하는 함수를 만들면 된다. 
// 코드 9.14 순열의 사전순 번호 찾기 
// factorials[i] = i!
int factorials[12];
// X가 [0...n-1]의 순열일 때 사전순 번호를 반환한다. (0에서 시작)
int getIndex (const vector<int>& X) {
    int ret = 0;
    for (int i = 0; i < X.size(); i++) {
        int less = 0;
        // X[i+1...] 중 X[i]보다 작은 수를 센다. 이것이 X 앞에 오는 묶음의 수가 된다. 
        // 이전에 쓰이지 않은 수 중에서 X보다 앞에 있는 수의 갯수 찾는 것 !
        for (int j = i + 1; j < X.size(); j++)
        {
            if (X[j] < X[i]) 
                ++less;
        }
        
        ret += factorials[X.size() - i -1] * less;
    }

    return ret;
}

// 5. 입력의 범위가 좁을 경우 
// 길이 5인 정수 배열의 각 값이 [0,9] 범위에 속한다고 하면, 각 배열은 십진수 하나에 일대일로 대응된다. 
// 일반적으로 말해 배열의 길이가 n이고, 배열의 원소가 [0,k-1] 범위에 들어간다면 이 입력을 n자리의 k진수로 볼 수 있다. 

// 코드 9.15 여행하는 외판원 문제를 해결하는 동적 계획법 알고리즘 

int n, dist[MAX][MAX];
double cache[MAX][1<<MAX];
// here: 현재 위치 
// visited: 각 도시의 방문 여부 
// here에서 시작해 남은 도시들을 방문할 수 있는 최단 경로의 길이를 반환한다.
// 나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다.
// 항상 0번 도시에서 시작한다고 가정한다.
double shortestPath2 (int here, int visited) {
    // base case: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다.
    if (visited == (1<<n) -1)
        return dist[here][0];
    // 메모이제이션 
    double* ret = &cache[here][visited];
    if (*ret >= 0 )
        return *ret;
    *ret = INF;
    // 다음 방문할 도시를 전수 시도해 본다. 
    for (int next = 0; next < n; next++) {
        // 이미 방문한 도시인 경우 
        if (visited & (1<<next))
            continue;
        double cand = dist[here][next] + shortestPath2(next,visited+(1<<next));

        *ret = MIN(*ret,cand);
    }

    return *ret;
}

        


       
            
