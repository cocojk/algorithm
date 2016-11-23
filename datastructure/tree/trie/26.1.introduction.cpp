
// 정수나 실수형 - 크기가 정해져 있어서 비교에 상수 시간이 걸림 
// 문자열 - 최악의 경우 문자열의 길이에 비례하는 시간이 걸림 
// 예를들어, bst에서 정수나 실수형의 경우 find O(lgN)의 시간이 걸리는데, 문자열은 O(MlgN)의 시간이 걸린다. 

// 이를 해결하기 위해 고완된 자료구조 : trie (문자열 특화 자료구조)
// 문자열의 집합을 표현하는 트리구조, 집합 내에서 원하는 원소를 찾는 작업을 O(M) 시간만에 할 수 있다.
// 예제 : S = {"BT", "BET", "BUS", "TEA", "TEN"} 
// 트라이 : 집합에 포함된 문자열의 접두사들에 대응되는 노드들이 서로 연결된 트리.
// 한 접두사의 맨 뒤에 글자를 덧붙여 다른 접두사를 얻을 수 있을 때 두 노드는 부모 자식 관계로 연결된다. 간선은 덧붙인 글자에 대응된다.
//                                  |0|
//                          B                T
//                         |B|              |T|
//              U           E                E
//            |BU|         |BE(o)|          |TE|
//              S           T                A          N
//            |BUS(o)|     |BET(o)|         |TEA(0)|  |TEN(0)|
// (o) 처진 노드들은 종료 노드들로, 이 노드들은 해당 위치에 대응되는 문자열이 트라이가 표현하는 집합에 포함되어 있다는 것을 나타낸다.
// 루트에서 한 노드까지 내려가는 경로에서 만나는 글자들을 모으면 해당 노드에 대응되는 접두사를 얻을 수 있다. 따라서 각 노드에는 대응되는 문자열을 저장할 필요가 없다.
// 객체는 자손들을 가리키는 포인터 목록과, 이 노드가 종료 노드인지를 나타내는 불린 값 변수로 구성된다.
// 자손 노드들을 가리키는 포인터 목록은 동적 배열로 구현 X/ 모든 문자에 대응하는 고정 길이 배열로 구현

// running time : find , insert : O(M) // space : 공간이 너무 크다. 각 노드는 26개의 포인터를 저장해야하기 때문에

// 코드 26.1 트라이의 노드를 표현하는 객체의 선언 

// 알파벳 대문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다.
const int ALPHABETS = 26;
int toNumber (char ch) {return ch - 'A';}
// 트라이의 한 노드를 나타내는 객체 
struct TrieNode {
    TrieNode* children[ALPHABETS];
    // 이 노드가 종료 노드인가?
    bool terminal;
    
    TrieNode() : terminal(false) {
        memset(children,0,sizeof(children));
    }

    ~TrieNode() {
        for (int i = 0; i < ALPHABETS; i++)
            if(children[i])
                delete children[i];
    }

    // 이 노드를 루트로 하는 트라이에 문자열 key를 추가한다.
    void insert (const char* key) {
        // 문자열이 끝나면 terminal만 참으로 바꾸고 종료
        if (*key == 0)
            terminal = true;
        else {
            int next = toNumber(*key);
            // 해당 자식 노드가 없다면 생성한다.
            if (children[next] == NULL)
                children[next] = new TrieNode();
            // 해당 자식 노드로 재귀 호출 
            children[next]->insert(key+1);
        }
    }

    // 이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾는다.
    // 없으면 NULL을 반환한다.
    TrieNode* find (const char* key) {
        if(*key == 0)
            return this;
        int next = toNumber(*key);
        if (children[next] == NULL)
            return NULL;
        return children[next]->find(key+1);
    }
}

// 사전 자료 구조로 쓰기 
// termianl 멤버 변수를 불린 값에서 다른 변수형으로 바꾸면 트라이를 사전 자료 구조로 이용할 수 있다.
// 예를 들어, termianl을 정수형으로 바꾸면 간단하게 문자열을 정수로 대응하는 사전 자료 구조가 되므로, map<string,int>를 대체할 수 있다.

// 접미사 트리 
// 여러 문자열들을 트라이에 집어 넣는 대신 한 문자열 S의 모든 접미사를 트라이에 집어 넣는 것 
// 문자열의 모든 부분 문자열은 결국 어떤 접미사의 접두사. 트라이는 저장된 문자열의 모든 접두사들을 저장 -> 이 문자열의 모든 부분 문자열에 대응되는 노드를 가지고 있다.
// 하지만, 메모리 사용량이 너무 많다.
// 이 문제를 해결하기 위해서 고완 -> 접미사 트리 (suffix tree)
// 많은 부분은 분기 없이 일자로 구성되어 있다는데 착안하여, 각 간선이 문자열의 한 글자가 아니라 여러 글자에 대응되도록 한다. -> 전체 노드 갯수  O(N)으로 줄어든다. 
// 하지만 build하는데 O(N^2)의 시간이 걸리고, 너무 복잡하다. 

    


