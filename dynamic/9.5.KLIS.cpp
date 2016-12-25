/*
문제

어떤 정수 수열에서 0개 이상의 숫자를 지우면 이 수열의 부분 수열 (subsequence) 를 얻을 수 있다. 예를 들어 10 7 4 9 의 부분 수열에는 7 4 9, 10 4, 10 9 등이 있다. 단, 10 4 7 은 원래 수열의 순서와 다르므로 10 7 4 9 의 부분 수열이 아니다.

어떤 부분 수열이 _단조 증가_할 때 이 부분 수열을 증가 부분 수열 (increasing subsequence) 라고 하며, 이 중 가장 긴 것을 최대 증가 부분 수열 (LIS, longest increasing subsequence) 라고 한다. 예를 들어, 5 20 21 22 8 9 10 의 최대 증가 부분 수열은 5 8 9 10 이다.

어떤 수열에는 LIS 가 두 개 이상 있을 수 있다. 예를 들어, 4 5 6 1 2 3 의 LIS 는 두 개가 있다.

모든 숫자가 서로 다른 (중복 숫자가 없는) 수열이 주어질 때, 이 수열의 LIS 중 사전 순서대로 맨 앞에서 k번째 있는 LIS 를 출력하는 프로그램을 작성하시오.

입력

입력의 첫 줄에는 테스트 케이스의 수 C (<= 50) 가 주어진다. 각 테스트 케이스의 첫 줄에는 수열에 포함된 원소의 수 N (<= 500) 과 K 가 주어진다. K 는 32비트 부호 있는 정수에 저장할 수 있다. 그 다음 줄에 N개의 정수로 수열이 주어진다. 각 정수는 1 이상 100,000 이하이며, 같은 수는 두 번 등장하지 않는다.

주어진 수열의 LIS 는 최소 K 개 있다고 가정해도 좋다.

출력

각 테스트케이스마다 두 줄을 출력한다. 첫 줄에는 LIS 의 길이 L 을 출력하고, 그 다음 줄에 L 개의 정수로 K번째 LIS 를 출력한다.

예제 입력

3
9 2
1 9 7 4 2 6 3 11 10
8 4
2 1 4 3 6 5 8 7
8 2
5 6 7 8 1 2 3 4
예제 출력

4
1 2 3 11
4
1 3 6 8
4
5 6 7 8
*/
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// 코드 9.10 k번째 LIS 구하기 : LIS의 개수 세기 
const int MAX = 2000000000 + 1;
int n;
int cacheLen[501],cacheCnt[501],S[500];

// S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis3(int start)
{
    int * ret = &cacheLen[start+1];
    if (*ret != -1)
        return *ret;

    *ret = 1;
    for (int next = start +1; next < n; next++)
        if (start == -1 || S[start] < S[next])
            *ret = max(*ret,lis3(next)+1);

    return *ret;
}

// S[start]에서 시작하는 최대 증가 부분 수열의 수를 반환한다.
int count (int start) {
    if (lis3(start) == 1)
        return 1;

    int* ret = &cacheCnt[start+1];
    if (*ret != -1)
        return *ret;
    *ret = 0;

    for (int next = start + 1; next < n; next++) {
        if ( (start == -1 || S[start] < S[next]) && lis3(start) == lis3(next) + 1) 
        {
            *ret = min<long long> (MAX,(long long)*ret + count(next));
        }
    }

    return *ret;
}

// 코드 9.11 K번째 LIS 구하기 : K번째 LIS 계산하기 
// S[start]에서 시작하는 LIS 중 사전순으로 skip개 건너뛴 수열을 lis에 저장한다.
void reconstruct (int start, int skip, vector<int>& lis) {
    // 1. S[start]는 항상 LIS에 포함된ㄷ. 
    if (start != -1)
        lis.push_back(S[start]);

    // 2. 뒤에 올 수 있는 숫자들과 위치의 목록을 만든다. 
    // (숫자,숫자의 위치)의 목록이 된다.
    vector<pair<int,int> > followers;
    for (int next = start + 1; next < n; next++)
    {
        if ( (start == -1 || S[start] < S[next]) && lis3(start) == lis3(next) + 1)
            followers.push_back(make_pair(S[next],next));
    }

    sort(followers.begin(),followers.end());
    
    // 3. k번쨰 LIS의 다음 숫자를 찾는다. 
    for (int i = 0; i < followers.size(); i++) {
        // 이 숫자를 뒤에 이어서 만들 수 있는 LIS의 개수를 본다 .
        int idx = followers[i].second;
        int cnt = count(idx);
        if (cnt <= skip)
            skip -= cnt;
        else {
            // 다음 숫자는 S[idx]임을 알았다.
            // 4. 재귀 호출을 통해 
            reconstruct(idx,skip,lis);
            break;
        }
    }

}

int main (void)
{
    int testcase;
    int k;
    cin >> testcase;

    while(testcase--)
    {
        memset(cacheLen,-1,sizeof(cacheLen));
        memset(cacheCnt,-1,sizeof(cacheCnt));
        cin >> n >> k;
        vector<int> lis;
        for (int i = 0; i < n ; i ++)
        {
            cin >> S[i] ;
        }

        reconstruct (-1,k-1,lis);
        cout << lis.size() <<endl;
        for (int i = 0; i < lis.size(); i++)
        {
            cout << lis[i] << " ";
        }

        cout << endl;
    }
}




