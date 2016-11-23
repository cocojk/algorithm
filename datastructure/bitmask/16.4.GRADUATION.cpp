
/*
   문제

   1학년은 노는 게 남는 거란 선배의 말을 철석같이 믿고, 전공 과목은 다 수강철회하고 교양 과목은 다 F 받는 방탕한 1학년을 보냈던 태우는 이제 와서 자신의 행동을 후회하고 있습니다. 졸업 전에 채워야 할 학점이 너무 많기 때문입니다. 졸업 필수 학점을 채우려면 전공 과목 N 개 중 K 개 이상을 수강해야 합니다. 그런데 각 과목은 해당 과목의 선수과목을 미리 수강했어야만 수강할 수 있으며, 각 학기마다 모든 과목이 개설되는 것이 아니기 때문에 문제가 복잡해졌습니다. 어떻게 해야 최소 학기에 졸업을 할 수 있을까요?

   각 과목의 정보와 앞으로 M 학기 동안 개설될 과목의 목록이 주어질 때, 태우가 최소 몇 학기를 다녀야 졸업할 수 있는지 계산하는 프로그램을 작성하세요. 한 과목도 수강하지 않는 학기는 휴학한 것으로 하며, 다닌 학기 수에 포함되지 않습니다.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 전공 과목의 수 N (1 <= N <= 12), 들어야 할 과목의 수 K (0 <= K <= N), 학기의 수 M (1 <= M <= 10) 과 태우가 한 학기에 최대로 들을 수 있는 과목의 수 L (1 <= L <= 10)이 주어집니다. 각 과목에는 0부터 N-1 까지의 번호가 매겨져 있습니다.

   그 후 N 줄에 0번 과목부터 순서대로 각 과목의 정보가 주어집니다. 이 줄에는 해당 과목의 선수 과목의 수 Ri (0 <= Ri <= N-1) 가 처음 주어지고, 그 후 Ri 개의 정수로 선수 과목의 번호가 주어집니다.

   그 후 M 줄에는 이번 학기부터 순서대로 각 학기의 정보가 주어집니다. 각 줄에는 해당 학기에 개설되는 과목의 숫자 Ci (1 <= Ci <= 10) 가 주어지고, 그 후 Ci 개의 정수로 개설되는 과목의 번호들이 주어집니다.

   출력

   각 테스트 케이스마다 한 줄에 태우가 다녀야 할 최소 학기 수를 출력합니다. M 학기 내에 졸업할 수 없는 경우 IMPOSSIBLE을 출력합니다.

   예제 입력

   2
   4 4 4 4
   0
   1 0
   3 0 1 3
   0
   4 0 1 2 3 
   4 0 1 2 3
   3 0 1 3
   4 0 1 2 3
   4 2 2 4
   1 1
   0
   1 3
   1 2
   3 0 2 3
   3 1 2 3
   예제 출력

   3
   IMPOSSIBLE
 */

#include <stdio.h>
#include <algorithm>
#include <string.h>

#define MAXN 12
#define INF 987654321

int N,K,M,L;
// classes[i] = i번째 학기에 개설되는 과목의 집합 
int classes [MAXM];
// prerequisite[i] = i번째 과목의 선수과목의 집합 
int prerequisite [MAXN];
int memoization [MAXM][1<<MAXN];

using namespace std;

// 이번 학기가 semester이고, 지금까지 들은 과목의 집합이 taken일 때
// k개 이상의 과목을 모두 들을려면 몇 학기나 더 있어야 하는가?
// 불가능한 경우 INF를 반환한다.
int dynamic (int taken,int semester)
{
    // basecase : k개 이상의 과목을 이미 들은 경우 
    if (__builtin_popcount(taken) >= K)
        return 0;
    
    // base case : m학기가 전부 지난 경우 
    if (semester == M )
        return INF;

    int* ret = &memoization[semester][taken];

    if(*ret != -1)
        return *ret;

    *ret = INF;

    // 이번 학기에 들을 수 있는 과목 중 아직 듣지 않은 과목들을 찾는다.
    int canTake = classes[semester] & ~taken;

    // 선수 과목을 다 듣지 않은 과목들을 걸러낸다.
    for(int i = 0 ; i < N ; i ++)
    {
        if ( (canTake&(1<<i)) && ( (taken & prerequisite[i]) != prerequisite[i]))
            canTake = canTake & ~(1<<i);
    }

    // 이 집합의 모든 부분집합을 순회한다.
    for(int take = canTake; take > 0; take = ((take-1) & canTake) )
    {
        // 한 학기에 L 과목까지만 들을 수 있다.
        if (__builtin_popcount(take) > L ) continue;
        *ret = min(*ret,dynamic(take|taken,semester+1)+1);
    }

    *ret = min(*ret,dynamic(taken,semester+1));

    return *ret;

}

int main (void)
{
    int testcase;

    scanf("%d",&testcase);

    while(testcase--)
    {
        memset(memoization,-1,sizeof(memoization));
        memset(prerequisite,0,sizeof(prerequisite));
        memset(classes,0,sizeof(classes));
        scanf("%d %d %d %d",&N,&K,&M,&L);
        for(int i = 0; i < N;i++)
        {
            int depennum,temp;
            scanf("%d",&depennum);
            while(depennum--)
            {
                scanf("%d",&temp);
                prerequisite[i] |= (1<<temp);
            }
        }

        for(int i = 0; i < M ; i++)
        {
            int num,temp;
            scanf("%d",&num);
            while(num--)
            {
                scanf("%d",&temp);
                classes[i] |= (1<<temp);
            }
        }

        int ret;
        if( (ret =dynamic(0,0))==INF)
        {
            printf("IMPOSSIBLE\n");
        }
        else 
        {
            printf("%d\n",ret);
        }
    }
}




