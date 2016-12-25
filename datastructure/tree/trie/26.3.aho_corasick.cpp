
// aho-corasic 
// 트라이를 이용한 다중 문자열 검색 
// 트라이에 포함된 문자열들이 접두사를 공유할 경우, 이 접두사들은 같은 노드에 대응된다는 점을 이용해 탐색 공간을 줄이는 알고리즘을 설계할 수 있다. -> 다중 문자열 검색에서 이용됨 

// 20장에서 다룬 문자열 검색 문제와 다를 것이 없지만, 바늘 문자열이 여러개이다. 
// 예를 들어 짚더미 H="CACACHEFCACHY"이고 네 개의 바늘 "CACHE", "HE", "CHEF", "ACHY"이 있다고 하면 각 바늘 문자열들의 출현 위치를 모두 계산하는 문제 
// KMP를 여러번 사용가능 -> 바늘의 갯수가 만큼 수행해야한다. -> 비효율적 

// KMP의 failure function (부분 매치 테이블)을 중첩시켜서 트라이를 만들자!  => 모든 바늘 문자열을 한꺼번에 짚더미에서 찾을 수 있다.
// failure function (s) = s의 접미사이면서 트라이에 포함된 가장 긴 문자열까지 가는 화살표 

// failure function 계산 
// 각 노드마다 다음과 같은 정보를 추가적으로 가지고 있어야 한다.
// 1. 실패 연결 (failure link)
// 이 노드에서의 실패 함수 값으로, 이 노드에서 다음 글자가 대응하는 데 실패했을 때 다음으로 가서 시도해야할 노드의 포인터 
// 2. 출력 문자열 목록 
// 각 노드에 도달했을 때 어떤 바늘 문자열들을 발견하게 되는지를 저장. 
// 한 바늘 문자열이 다른 바늘 문자열의 부분 문자열인 경우 해당 바늘 문자열이 종료되는 노드 외의 장소에서도 문자열을 발견할 수 있기 때문에 
// 예를 들어, 바늘 문자열 ABC,B,BC가 있다면 상태 AB에 도달했을 때는 바늘 문자열 B를, 상태 ABC에 도달했을 때는 바늘 문자열 ABC와 BC를 발견할 수 있다. 

// 코드 26.5 야호-코라식 알고리즘을 위해 트라이의 각 노드에 추가적으로 계산해야 할 정보 

// 트라이의 한 노드를 나타내는 객체 
struct TrieNode {
    // 현 위치에서 끝나는 문자열의 번호 
    int terminal;
    // 실패 연결 : 이 노드에서 매칭이 실패했을 때 이 곳으로 가서 계속한다.
    // 이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열 
    TrieNode* fail;
    // 출력 문자열 목록 : 이 노드가 방문되었을 때 등장하는 바늘 문자열들의 번호 
    vector<int> output;

    TrieNode* children[ALPHABETS];
};

// naive algorithm : 모든 접미사들을 하나하나 시도하면서 이 중 트라이에 포함되어 있는 첫 번째 문자열을 찾는 것 

// improved algorithm 
// 부모 노드의 실패 연결을 이용해 자식 노드의 실패 연결을 쉽게 알 수 있다 !!
// def 1 :한 노드의 실패 연결을 계속 따라가면, 그 노드에 해당하는 트라이에 포함된 문자열들을 길이가 긴 순서대로 얻을 수 있다.
// 부모 (문자열 A)와 자식 (문자열 Ax)가 존재한다고 하면, 자식의 failure function이 가질 수 있는 가장 긴 문자열은 
// 부모의 failure function + 1 이다.
// 따라서, 부모 (A)의  failure function을 따라간 후, x가 존재하면 그 노드가 Ax의 failure function이고, 존재하지않으면,
// 해당 노드의 failure function을 다시 따라 간후, x를 찾는다. (def 1에 의해)
// dependency solve 
// 실패 연결을 계산하기 위해서는 그 부모 노드에서 실패 연결을 따라가 만날 수 있는 모든 노드들에 대해 실패 연결을 먼저 계산해야 한다. 
// failure function을 통해 만나는 문자열은 원래 노드의 문자열보다 항상 짧다. (why? failure function def때문에)
// 따라서, 깊이가 낮은 노드들부터 순서대로 실패 연결을 계산하면 된다. (bfs)

// 출력 문자열 계산 
// 현재 노드에 대응되는 문자열의 접미사가 트라이에 포함된 어떤 문자열과 같다면, 이 노드에서 실패 연결을 따라가다 보면 이 문자열을 반드시 찾을 수 있다. 

// 코드 26.6 야호-코라식 알고리즘에서 실패 함수의 계산 

// 트라이가 주어질 때 각 노드에 대해 실패 연결과 출력 문자열 목록을 계산한다.
void computeFailFunc (TrieNode* root) {
    // 루트에서부터 시작해 한 단계식 아래로 내려가며 각 노드의 실패 연결을 계산한다.
    queue<TrieNode*> q;
    // 루트의 실패 연결을 자기 자신 
    root->fail = root;
    q.push(root);
    while(!q.empty()) {
        TrieNode* here = q.front();
        q.pop();
        // here의 모든 자손에 대해 실패 연결을 계산하고 이들을 큐에 넣는다.
        for (int edge = 0; edge < ALPHABETS; edge++) {
            TrieNode* child = here->children[edge];
            if(!child) continue;

            // 1 레벨 노드의 실패 연결은 항상 루트 
            if (here == root)
                child->fail = root;
            else {
                // 아닌 경우 보므의 실패 연결을 따라가면서 실패 연결을 찾는다.
                TrieNode* t = here->fail;
                while (t != root && t->children[edge] == NULL)
                    t = t->fail;
                if (t->children[edge])
                    t = t->children[edge];
                child->fail = t;
            }

            // 출력 문자열 목록 : 실패 연결을 따라간 노드에서 복사해온 뒤,
            // 이 위치에서 끝나는 바늘 문자열이 있으면 추가한다.
            child->output = child->fail->output;
            if (child->terminal != -1)
                child->output.push_back(child->terminal);
            q.push(child);
        }
    }
}

// 코드 26.7 아호-코라식 알고리즘의 실제 탐색 과정 

// trie에 포함된 패턴들을 s에 찾는다.
// s 내에서 패턴이 출현할 때마다 (마지막 글자, 패턴 번호)의 쌍을 지정한다. 
vector<pair<int,int> > ahoCorasick(const string& s, TrieNode* root) {
    vector<pair<int,int> > ret;
    TrieNode* state = root;
    // 실제 반복문 내는 KMP와 별로 다를 것이 없다.
    for (int i = 0; i < s.size(); i++) {
        int chr = toNumber(s[i]);
        while (state != root && state->children[chr] == NULL)
        {
            state = state->fail;
        }
        
        if (state->children[chr])
            state = state->children[chr];

        for (int j = 0; j <state->output.size(); j++)
            ret.push_back(make_pair(i,state->output[j]));
    }
    
    return ret;
}

// running time  : O(N+O+M)
// match : O(N+P) 짚더미의 길이 N, 바늘의 출현 횟수 P
// 1. 출력 문자열 목록을 순회하는 for문 - 짚더미에 바늘이 출현하는 횟수만큼 
// 2. while문 : while문 실행 안될 경우 대응되는 문자열의 길이가 1 증가하며, while문의 조건이 맞아 실행되더라도 최악의 경우 현재 대응되는 문자열의 길이만큼 수행된다. (failure function이 모두 한 글자씩 감소하며, 모두 대응되지 않는 경우)  따라서 최대 짚더미의 길이 N만큼 수행가능하다. 


// failure function : O(M) 바늘 문자열 길이의 합 M
// 1. while 문 : while문 실행이 안될 경우 부모 보다 1 증가한 문자열 길이를 가진다. while문의 조건이 맞아 실행되더라도 최악의 경우 현재 노드의 부모의 failure function의 문자열 길이만큼 수행된다. 이 경우, 현재 노드의 failure 문자열 길이는 1로 초기화 된다. 따라서 최대 바늘 문자열 길이의 합 M에 비례한다.


