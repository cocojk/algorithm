
// 이 문제의 목표는 다음 세 가지 조건을 만족하는 최소의 자연수 c를 찾는 것이다.
// 1. n + m 이상이어야 한다. (욕심쟁이가 아닌 애들에게 하나씩, 욕심쟁이들에게 두 개씩 주려면 최소 n+m개의 장난감이 필요하다)
// 2. n 으로 나눈 나머지가 m이어야 한다.
// 3. d에 포함된 숫자들로만 구성되어 있어야 한다. 
// 이렇게 여러 조건을 동시에 만족하는 답을 찾는 문제를 풀 때 쓸 수 있는 한 가지 전략은, 일부 조건을 없앤 더 단순한 문제를 푼 후 조건을 하나하나 추가해 가는 것입니다. 
// 예를 들어 3번 조건을 무시하고 1번과 2번 조건을 만족하는 답을 찾는 경우
// 이 문제의 답은 m+an(a>=1) 이다. 반면 여기에 3번 조건을 추가하는 것은 수 하나하나 만들어 보며 이들이 3번 조건을 만족시키는지 확인해야 하며, impossible을 판단할 수 없다.

// 1번 조건을 무시하고, 2번과 3번 조건을 만족하는 답을 찾는 경우 
// step1. c를 앞에서부터 한 자리씩 만들어 갈 때, 지금까지 만든 c의 뒤에 숫자 x를 붙인 결과인 c*10 + x를 n으로 나눈 나머지는 실제 c를 모르더라도 알 수 있다. 다음과 같은 성질이 성립하기 때문입니다.
// ((c mod n)*10 + x)mod n = (c*10 + x)mod n <나머지 연산의 분배 법칙>
// 그래프 모델링 
// step2. c를 n으로 나눈 나머지를 정점으로 표현한 방향 그래프를 만들어 본다. 따라서 그래프에는 0부터 n-1까지의 나머지를 표현하는 n개의 정점이 있게 된다. 정점 a는 현재까지 만든 c를 n으로 나눈 나머지가 a인 상태를 나타낸다.
// 이러한 그래프를 기준으로 간선들의 번호가 사전순으로 가장 작은 최단 경로를 찾아야 한다. 
// step3. 마지막 조건 추가하기 
// 첫 번째 예제의 경우, m = 0 이기 때문에 우리는 0에서 0으로 가는 최단 경로를 찾게된다. 물론 이런 최단 경로의 길이는 0 이지만, 1번 조건을 만족시키기 위해서 그래프를 한 바퀴 돌아야 한다. 
// 1번 조건을 고려했을 때, 시작점이 0과 그래프를 한 바퀴 돌아서 다시 도착한 0은 같은 정점일 수 없다. 한쪽은 현재 가진 값이 n 미만이고, 다른 한쪽은 n 이상이기 때문이다. 따라서 n으로 나눈 나머지마다 두 개의 정점을 만든다.
// running time : 2n개의 vertex, 2n*d개의 edge =  O(2n*d)

// 그래프 모델링을 통해 어린이날 문제를 해결하는 알고리즘 
// 현재 정점 번호가 here이라면, 간선 번호 edge를 따라 갔을 때 나오는 정점의 번호는?
int append(int here, int edge, int mod) {
    int there = here*10 + edge;
    if(there>=mod) 
        return mod + there%mod; 
    return there % mod;
}

// digits에 속한 숫자들만으로 구성되고 C mod n == m인 최소의 C를 찾는다. 
string gifts(string digits, int n, int m) {
    // 간선의 번호를 오름차순으로 정렬해 두면 사전순으로 가장 앞에 있는 경로를 찾을 수 있다. 
    sort(digits.begin(),digits.end());
    
    // 흰색 정점 i는 0 ~ n-1, 회색 정점 i는 n ~ 2n -1로 표현한다.
    // parent[i] = BFS 스패닝 트리에서 정점 i의 부모 
    // choice[i] = parent[i]에서 i로 연결된 간선의 번호 
    vector<int> parent(2*n,-1), choice(2*n,-1);
    queue<int> q;
    
    // 흰색 0번을 큐에 추가 
    parent[0] = 0;
    q.push(0);

    while(!q.empty()) {
        int here = q.front();
        q.pop();
        for(int i = 0; i < digits.size(); i++) {
            // 간선 digits[i] - '0'을 따라가 본다.
            int there = append(here,digits[i] - '0',n);
            if(parent[there] == -1) {
                parent[there] = here;
                choice[there] = digits[i] - '0';
                q.push(there);
            }
        }
    }

    // 회색 m 번에 도달하지 못했으면 실패!
    if(parent[n+m] == -1)
        return "IMPOSSIBLE";

    // 부모로 가는 연결을 따라가면서 C를 계산한다.
    string ret;
    int here = n + m;
    while(parent[here] != here) {
        ret += char('0' + choice[here]);
        here = parent[here];
    }

    reverse(ret.begin(),ret.end());
    return ret;
}
