/*
   문제

   문자 입력이 불편한 핸드폰이나 타블렛 같은 기계에서는 빠른 타이핑을 위해 강력한 자동 완성 기능을 제공합니다. 시리우스 사이버네틱스 주식회사에서 이번에 출시한 돌고래용 타블렛의 자동 완성 알고리즘은 사전에 저장된 N개의 단어들을 이용해 자동완성을 수행합니다. 돌고래가 새 단어를 타이핑하기 시작하면, 자동 완성 시스템은 지금까지 타이핑한 부분으로 시작하는 사전 내 단어 중 가장 출현 빈도가 높은 것을 자동으로 추천합니다. 만약 출현 빈도가 가장 높은 것이 여러 개 있다면 사전순으로(돌고래의 사전 역시 알파벳 순을 따릅니다) 가장 앞에 오는 단어가 추천되지요. 돌고래가 탭 키를 누르면 지금 추천된 단어가 자동으로 입력됩니다.

   예를 들어 사전에 다음 7개의 단어가 들어 있다고 합시다.

   단어    ALL AND FISH    FOR SO  THANKS  THE
   출현 빈도   4   3   8   6   4   9   9
   이 때 문자열 "SO LONG AND THANKS FOR ALL THE FISH"를 타이핑한다고 하지요. 돌고래가 S를 누르면 자동완성 시스템은 자동으로 SO 를 추천하고, 여기서 탭 키를 누르면 SO가 입력됩니다. 이와 같은 방식으로 나머지 단어를 입력하는 데는 각 4번(LONG 은 사전에 없으므로 추천되지 않습니다), 3번(AN 과 탭), 2번 (T 와 탭), 3번(FO 와 탭), 2번 (A 와 탭), 3번(THE 모두 입력해야 합니다), 2번 (F 와 탭) 의 키 입력이 필요하지요. 여기에 7번의 공백 문자까지 입력하면 전체 28번 키를 눌러야 합니다.

   단 이 타블렛에는 이미 입력한 단어를 편집하는 기능이 없기 때문에, THANKS를 입력하고 "S"를 지워서 "THANK"를 만들거나 "THE"를 입력하고 "RE"를 덧붙여서 "THERE"를 입력하는 것은 불가능합니다.

   돌고래들의 지느러미는 타블렛의 입력에 적합하지 않으므로, 가능한 적은 타이핑 수로 모든 문장을 입력하고 싶습니다. 타블렛의 자동완성 알고리즘이 사용하는 단어들과 각 단어들의 출현 빈도가 주어질 때, 주어지는 긴 문자열을 입력하기 위해 필요한 최소 타이핑 수를 계산하는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C(1 <= C <= 10)가 주어집니다. 각 테스트 케이스의 첫 줄에는 사전에 포함된 단어의 수 N (1 <= N <= 10000)과 입력할 단어의 수 M (1 <= M <= 20000)이 주어집니다. 그 후 N 줄에는 한 줄에 하나의 문자열과 정수로 사전에 포함된 단어와 해당 단어의 출현 빈도가 사전 순서와 무관하게 주어집니다. 같은 단어가 두번 이상 주어지는 일은 없으며, 출현 빈도는 1 과 10만 사이의 정수입니다. 그 다음 줄에 M개의 단어로 입력할 문자열이 주어집니다. 모든 단어는 알파벳 대문자이며, 길이는 최대 10입니다.

   입력의 양이 많으므로 가능한 빠른 입력 함수를 이용하는 것이 좋습니다.

   출력

   각 테스트 케이스마다 한 줄에 모든 단어들을 입력하기 위해 필요한 최소 타자 수를 출력합니다

   예제 입력

   2
   7 8
   ALL 4
   AND 3
   FISH 8
   FOR 6
   SO 4
   THANKS 9
   THE 9
   SO LONG AND THANKS FOR ALL THE FISH
   7 8
   ALL 4
   AND 5
   FISH 3
   FOR 6
   SO 8
   THANKS 1
   THE 2
   SO LONG AND THANKS FOR ALL THE FISH
   예제 출력

   28
   29
 */
#include <vector>
#include <stdio.h>
#include <utility>
#include <algorithm>
#include <string.h>
#include <iostream>

using namespace std;


const int ALPHABETS = 26;
const int MAX = 21;

int toNumber (char ch) {return ch - 'A';}
struct Node {
    Node* child[ALPHABETS];
    // 이 노드에서 종료하는 문자열의 번호. 없으면 -1
    int terminal;
    // 이 노드를 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호. -1로 초기화 
    int first;

    Node() : terminal(-1),first(-1) {
        memset(child,0,sizeof(child));
    }

    // 이 노드를 루트로 하는 트라이에 번호 id인 문자열 key를 추가한다.
    void insert (const char* key,int id) {
        // first를 우선 갱신 
        if (first == -1)
            first = id;

        // 문자열이 끝났다면 terminal만 바꾸고 종료 
        if(*key == 0)
            terminal = id;
        else {
            int next = toNumber(*key);
            // 해당 자식 노드가 없다면 생성한다.
            if(child[next] == NULL)
                child[next] = new Node();
            // 해당 자식 노드로 재귀 호출 
            child[next]->insert(key+1,id);
        }
    }

    Node* find (const char* key) {
        if (*key == 0)
            return this;
        int next = toNumber(*key);
        if (child[next] == NULL)
            return NULL;
        return child[next]->find(key+1);
    }

    // 이 노드까지 타이핑해 왔을 때, 번호 id인 key를 타이핑하기 위해
    // 최소 몇번의 키를 더 눌러야 하나?
    int type (const char* key, int id) {
        // 문자열 종료시 
        if (*key == 0)
            return 0;
        // 이 노드에서 추천되는 문자열이 이 문자열이면 탭 누르고 종료 
        if (first == id) 
            return 1;
        // 아니면 다음 문자를 타이핑한다.
        int next = toNumber(*key);
        return 1 + child[next]->type(key+1,id);
    }
};
// 사전을 나타내는 트라이가 주어질 때, 단어 word를 타이핑하는 데 
// 몇 번이나 키를 눌ㄹ러야 하는지 계산한다.
int countKeys (Node* trie, const char* word) {
    // 이 문자열이 사전에 있는지 확인하고, 있다면 번호를 구한다.
    Node* node = trie->find(word);
    // 사전에 없으면 직접 타이핑할 수 밖에 없다.
    if (node == NULL || node->terminal == -1)
        return strlen(word);
    // 탐색하면서 타이핑할 방법을 찾는다.
    return trie->type(word,node->terminal);
}

// 입력에 주어지는 단어들을 정렬해서 트라이오 변환한다.
Node* readInput (int words) {
    // 단어들을 출현 빈도의 내림차순, 단어의 오름차순으로 정렬한다.
    vector<pair<int,string> > input;
    for (int i = 0; i < words; i++) {
        char buf[11];
        int freq;
        scanf("%s %d",buf,&freq);
        input.push_back(make_pair(-freq,buf));
    }
    sort(input.begin(),input.end());
    // 이때 앞에 있는 단어일수록 우선순위가 높다.
    // 배열의 인덱스를 각 단어의 번호로 쓰자.
    Node* trie = new Node();
    for(int i = 0; i < input.size(); i++)
        trie->insert(input[i].second.c_str(),i);
    trie->first = -1;
    return trie;
}

int main (void)
{
    int testcase,n,m,freq;
    char input[MAX];
    int answer;

    cin >> testcase;

    while(testcase--)
    {
        answer = 0;
        cin >> n >> m;
        Node* root = readInput(n);

        answer += m-1;
        while (m--)
        {
            cin >> input;
            answer += countKeys(root,input);
            //cout << countKeys(root,input) << '\n';
        }

        cout <<answer<<'\n';
    }
}



#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;


const int ALPHABET = 26;
const int MAX = 11;

int toNumber (char ch) {return ch - 'A';}
struct Node {
    Node* child[ALPHABET];
    char mostString[MAX];
    int mostFreq;

    Node() : mostFreq(0) {
        memset(child,0,sizeof(child));
        memset(mostString,0,sizeof(mostString));
    }

    void rootInsert (const char* key, int freq) {
        int next = toNumber(*key);
        if (child[next] == NULL)
            child[next] = new Node();
        child[next]->insert(key+1,freq);
    }

    void insert (const char* key,int freq) {
        if(*key == 0)
        {

            if ((freq==mostFreq ) ||freq > mostFreq)
            {
                mostFreq = freq;
                mostString[0] = 0;
            }
            return ;
        }
        else 
        {
            char temp [MAX];
            int next = toNumber(*key);
            if (child[next]==NULL)
                child[next] = new Node();

            strcpy(temp,(key));

            if ((freq==mostFreq && strcmp(mostString,temp) > 0) ||freq > mostFreq)
            {
                mostFreq = freq;
                strcpy(mostString,temp);
            }

            child[next]->insert (key+1,freq);

        }
    }

    int find (const char* key)
    {
        if (*key == 0)
            return 0;
        int next = toNumber(*key);
        if (child[next]==NULL)
            return strlen(key);

        if (strcmp(mostString,(key))==0)
            return 1;

        return 1 + child[next]->find(key+1);
    }
};

int main (void)
{
    int testcase,n,m,freq;
    char input[MAX];
    int answer;

    cin >> testcase;

    while(testcase--)
    {
        answer = 0;
        Node* root = new Node();
        cin >> n >> m;
        while (n--)
        {
            scanf("%s %d",input,&freq);
            root->rootInsert(input,freq);
        }

        answer += m-1;
        while (m--)
        {
            cin >> input;
            answer += root->find(input);

        }

        cout <<answer<<'\n';
    }
}


