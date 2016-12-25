#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

// 코드 9.18 실험 데이터 복구 문제를 해결하는 동적 계획법 알고리즘 
const int MAX_N = 15;
int k;
string word[MAX_N];
int cache[MAX_N][1<<MAX_N],overlap[MAX_N][MAX_N];


int getOverlap (int a, int b)
{

    for (int start = 0; start < word[a].size(); start++)
    {
        int checker = 1;
        for (int i = 0; start + i < word[a].size() && i < word[b].size(); i++)
        {
            if (word[a][start+i] != word[b][i])
            {    
                checker= 0;
                break;
            }
        }

        if (checker)
            return (word[b].size() > (word[a].size() - start)) ? word[a].size() -start : word[b].size();
    }
}
void precalc (void)
{
    for (int i = 0; i < k; i ++)
    {
        for (int j = 0; j < k; j++)
        {
            overlap[i][j] = getOverlap(i,j);
        }
    }
}
        
// overlap이 가장큰 값이 최적해가 된다.
// 마지막 단어의 index가 last이고, 사용된 단어가 used bitmap일때 overlap의 최대값 
int restore (int last, int used) {
    // base case 
    if (used == (1<<k) -1)
        return 0;
    // memization 
    int* ret = &cache[last][used];
    if (*ret != -1)
        return *ret;
    *ret = 0;
    for (int next = 0; next < k ; next++)
    {
        if( (used & (1<<next)) == 0) {
            int cand = overlap[last][next] + restore(next,used + (1<<next));
            *ret = max(*ret,cand);
        }
    }

    return *ret;
}

// 코드 9.19 실험 데이터 복구 문제의 실제 답을 계산하는 알고리즘 

// 처음 호출 시 last는 restore()가 최댓값을 반환한 시작 단어로 
// used는 1 << lst로 둔다.
string reconstruct (int last, int used) {
    // base case 
    if (used == (1<<k) -1 )
        return "";

    // 다음에 올 문자열 조각을 찾는다.
    for (int next = 0; next < k; next++) {
        // next가 이미 사용되었으면 제외 
        if (used & (1<<next)) continue;
        // next를 사용했을 경우의 답이 최적해와 같다면 next를 사용한다. 
        int ifUsed = restore(next,used+(1<<next)) + overlap[last][next];
        if (restore(last,used) == ifUsed)
            return (word[next].substr(overlap[last][next]) + reconstruct(next,used+(1<<next)));
    }

    // 뭔가 잘못된 경우 
    return "****oops****";
}

int main (void)
{
    int testcase ;
    int maxval,index,temp;
    cin >> testcase;

    while(testcase--)
    {
        cin >> k;
        memset (cache,-1,sizeof(cache));
        for (int i = 0; i < k; i++)
        {
            cin >>word[i];
        }
        precalc();
        maxval = 0;
        for (int i = 0; i < k; i ++)
        {
            temp = restore(i,(1<<i));
            printf("index : %d val %d\n",i,temp);
            if (temp > maxval)
            {
                maxval = temp;
                index = i;
            }
        }

        cout << word[index] + reconstruct(index,(1<<index))<<endl;

    }
}
