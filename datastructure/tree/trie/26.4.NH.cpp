/*
   문제

   음지에서 살아가는 보안 초전문가 슈퍼코더 K 는 이번에 새로운 은행의 전산망을 해킹하려고 합니다. 그에게는 원래 은행의 전산망을 해킹하는 것은 손바닥 뒤집는 것보다 쉬운 일인데, 2011년에 추가된 침입 감지 시스템(Intrusion Detection System, IDS) 때문에 골치를 앓고 있습니다. 이 침입 감지 시스템은 네트워크의 모든 트래픽을 감시하면서 그 중 특정 문자열을 발견하는 경우 곧장 해킹 시도가 있었음을 관리자에게 알려줍니다. 따라서 서버로 보내는 데이터에는 이 문자열이 포함되어 있으면 안 됩니다. 다행히 이 침입 감지 시스템이 인식하는 패턴들을 모두 이미 확보했습니다.

   이 전산망의 루트 비밀번호는 알파벳 소문자로 구성된 길이 n 의 문자열인데, 앞에서 이야기한 IDS 의 존재 때문에 해킹 시도로 인식되는 패턴들을 포함하는 비밀번호는 입력할 수 없습니다. 길이 n 인 소문자 문자열 중 IDS 에 인식되지 않는 문자열의 개수를 계산하는 프로그램을 작성하세요.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 만들 문자열의 길이 N (1 <= N <= 100) 과 IDS 가 인식하는 패턴의 수 M (1 <= M <= 100) 이 주어집니다. 그 후 M 줄에 하나씩 문자열은 길이 10 이하의 알파벳 소문자 문자열로 IDS 가 인식하는 패턴이 주어집니다.

   출력

   각 테스트 케이스마다 IDS 에 인식되지 않는 문자열의 수를 출력합니다. 문자열의 수가 클 경우 10007 로 나눈 나머지를 출력합니다.

   예제 입력

   3
   2 2
   rm 
   dd
   4 4
   a
   b
   c
   d
   100 4
   aa
   ba
   ab
   cd
   예제 출력

   674 
   4095
   5293 
*/


#include <string.h>
#include <vector>
#include <queue>
#include <stdio.h>
#include <iostream>

using namespace std;

const int MOD = 10007;
const int ALPHABETS = 26;
int memoization[101][1001];
int nodecount;



struct TrieNode {
    int terminal;
    int nodenum;
    TrieNode* children[ALPHABETS];
    TrieNode* fail;
    vector<int> output;
    TrieNode() {
        terminal = -1;
        nodenum = nodecount++;
        memset(children,0,sizeof(children));
        fail = 0;
    }
};

void insert (const char* key,TrieNode* node,int stringnum);
int dynamic (int n, TrieNode* root);
void computeFailFunc (TrieNode* root);
int toNumber (char ch) ;

void insert (const char* key,TrieNode* node,int stringnum) {
    if (*key == 0)
        node->terminal = stringnum;
    else 
    {
        int next = toNumber(*key);
        if (node->children[next] == NULL)
            node->children[next] = new TrieNode();
        insert (key+1,node->children[next],stringnum);
    }
}

int toNumber (char ch) 
{
    return ch-'a';
}


void computeFailFunc (TrieNode* root) {
    queue<TrieNode*> q;
    root->fail = root;
    q.push(root);

    while(!q.empty()) {
        TrieNode* here = q.front();
        q.pop();

        for (int edge = 0; edge <ALPHABETS; edge++)
        {
            TrieNode* child = here->children[edge];
            if(!child)
                continue;

            if (here == root)
                child->fail = root;
            else 
            {
                TrieNode* t = here->fail; 
                while (t != root && t->children[edge] == NULL)
                {
                    t = t->fail;
                }

                if (t->children[edge])
                    t= t->children[edge];
                child->fail = t;
            }
            
            child->output = child->fail->output;
            if (child->terminal != -1)
                child->output.push_back(child->terminal);
            q.push(child);
        }
    }
}


int solver (int n, TrieNode* root)
{
    int ret = 0;
    for (int i = 0; i < ALPHABETS; i++)
    {
        if (root->children[i] != NULL)
        {
            ret = (ret + dynamic(n,root->children[i])) % MOD;
        }
    }

    return ret;
}


int dynamic (int n, TrieNode* root)
{
    if ((root->output).size())
        return 0;
    if (n == 0)
        return 1;


    int* ret = &memoization[n][root->nodenum];

    if(*ret != -1)
        return *ret;

    *ret = 0;

    for (int i = 0; i < ALPHABETS; i++)
    {
        if (root->children[i] != NULL)
        {
            *ret = (*ret + dynamic(n-1,root->children[i]))%MOD;
        }
        else 
        {
            TrieNode* state = root->fail;

            while (state != state->fail && state->children[i] == NULL)
                state = state->fail;

            if (state->children[i])
            {
                *ret = (*ret + dynamic(n-1,state->children[i]))%MOD;
            }
            else 
            {
                *ret = (*ret + dynamic(n-1,state))%MOD;
            }
        }
    }

    return *ret;
}

int main (void)
{
    int testcase,n,m;
    char input[11];
    cin >> testcase;
    while (testcase--)
    {
       nodecount = 0;
       memset(memoization,-1,sizeof(memoization));
        cin >> n >> m;
        TrieNode* root = new TrieNode();
        while (m--)
        {
            scanf("%s",input);
            insert(input,root,m);
        }
        computeFailFunc(root);

        printf("%d\n",dynamic(n,root));
    }
}









