/*
문제

이번 학기에 욕심을 부려 학점 초과신청을 한 백준이는 중간고사 성적을 보고 한숨을 토할 수밖에 없었습니다. 다음 학기 장학금을 받을 만큼 성적이 잘 나오지 않았기 때문입니다. 이제 백준이에게 남은 희망은 다음 주의 수강 철회 기간 뿐입니다.

백준이네 학교에서는 장학금을 학생의 중간고사 등수와 기말고사 등수에 따라 배정합니다. 어떤 학생이 듣는 i번째 과목의 수강생 수가 ci라고 합시다. 그리고 이 학생의 i번째 과목 중간 고사 등수가 ri라고 하면, 이 학생의 중간 고사 누적 등수 cumulativeRank 는 다음과 같이 정의됩니다.

cumulativeRank = sum(ri) / sum(ci)

예를 들어 백준이가 수강생이 각각 150, 200, 15명인 3개의 과목을 듣는데, 각각 100, 10, 5등을 했다면 백준이의 누적 등수를 다음과 같이 계산할 수 있지요.

(100 + 10 + 5) / (150 + 200 + 15) = 115 / 365 = 0.315..

수강 철회를 하면 철회한 과목은 중간 고사의 누적 등수 계산에 들어가지 않게 됩니다. 다행히 백준이네 학교에서는 수강 철회를 해도 남은 과목이 k 개 이상이라면 장학금을 받을 수 있습니다. 백준이가 적절히 과목을 철회했을 때 얻을 수 있는 최소 누적 등수를 계산하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 T (T <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 백준이가 수강하는 과목의 수 n(1 <= n <= 1,000)과 남겨둬야 할 과목의 수 k(1 <= k <= n)가 주어집니다. 다음 줄에는 n 개의 정수 쌍 (ri,ci) 이 순서대로 주어집니다. (1 <= ri <= ci <= 1,000)

출력

각 줄마다 백준이가 얻을 수 있는 최소의 누적 등수를 출력합니다. 정답과 10-7 이하의 오차가 있는 답은 정답으로 인정됩니다.

예제 입력

3
3 2
1 4 6 10 10 17
4 2
4 8 9 12 3 10 2 5
10 5
70 180 192 192 1 20 10 200 6 102 60 1000 4 9 1 12 8 127 100 700 
예제 출력

0.5000000000 
0.3333333333 
0.0563991323
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 1000;
int n,k;
int r [MAXN];
int c [MAXN];
int isRemove [MAXN];
int saveIdx [MAXN];
int sumC = 0;
int sumR = 0;

// [start, end)
int remove (int count)
{
    vector <pair<double,int> > comp;

    for (int i = 0; i < count ; i++)
    {
        comp.push_back( make_pair(((double)sumR-r[saveIdx[i]])/(sumC-c[saveIdx[i]]),saveIdx[i]) );
    }

    sort(comp.begin(),comp.end());
    return comp[0].second;

}


double greedy (void)
{
    int current = n;
    int temp;

    sumR = 0;
    sumC = 0;

    for (int i = 0; i < n; i++)
    {
        sumR += r[i];
        sumC += c[i];
        isRemove[i] = 0;
    }

    while( current > k)
    {
        int counter = 0;
        
        for (int i = 0; i < n; i++)
        {
            if (!isRemove[i] && ( r[i]*sumC > c[i]*sumR ))
            {
                saveIdx[counter++] = i;
            }
              
        }
        
        if (counter)
        {   
            temp = remove(counter);
            isRemove[temp] = 1;
            current--;
            sumR -= r[temp];
            sumC -= c[temp];
        }
        else
        {
            break;
        }
    }


   return ((double)sumR/sumC);
}


void read (void)
{
    cin >> n >> k;
    
    for (int i = 0; i < n; i++)
    {
        cin >> r[i] >> c[i];
    }
}


int main (void)
{
    int testcase;

    cin >> testcase;

    while (testcase--)
    {
        read();
        printf("%.10f\n",greedy());
    }
}
      

