/*
   문제

   n개의 정수를 일렬로 늘어놓은 게임판을 가지고 현우와 서하가 게임을 합니다. 게임은 현우부터 시작해서 번갈아가며 진행하며, 각 참가자는 자기 차례마다 두 가지 일 중 하나를 할 수 있습니다.

   게임판의 왼쪽 끝에 있는 숫자나 오른쪽 끝에 있는 숫자 중 하나를 택해 가져갑니다. 가져간 숫자는 게임판에서 지워집니다.
   게임판에 두 개 이상의 숫자가 있을 경우, 왼쪽 끝에서 2개, 혹은 오른쪽 끝에서 2개를 지웁니다.
   게임은 모든 숫자가 다 없어졌을 때 끝나며, 각 사람의 점수는 자신이 가져간 숫자들의 합입니다. 현우와 서하는 점수가 더 낮은 쪽이 점수 높은 쪽에 한 점 차이마다 백 원씩 주기로 내기를 했습니다. 두 사람 모두 최선을 다할 때, 두 사람의 최종 점수 차이는 얼마일까요?

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 이 주어집니다. 각 테스트 케이스의 첫 줄에는 게임판의 길이 n (1 <= n <= 50) 이 주어지며, 그 다음 줄에 n 개의 정수로 게임판의 숫자들이 순서대로 주어집니다. 각 숫자는 -1,000 에서 1,000 사이의 정수입니다.

   출력

   각 테스트 케이스마다 한 줄로, 두 사람이 최선을 다했을 때 현우가 서하보다 몇 점 더 얻을 수 있는지를 출력합니다.

   예제 입력

   3 
   5 
   -1000 -1000 -3 -1000 -1000 
   6 
   100 -1000 -1000 100 -1000 -1000 
   10 
   7 -5 8 5 1 -4 -8 6 7 9 
   예제 출력

   -1000
   1100
   7
*/

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

#define NON 987654321
int cache [51][51];
int n;
vector<int> number;

// [start,end)
int getDiff (int start,int end)
{
    int size = end-start;

    if (size == 0)
        return 0;

    int* ret = &cache[start][end];

    if (*ret != NON)
        return *ret;

    *ret = -NON;

    if (size >= 2)
    {
        *ret = max (*ret, -getDiff(start+2,end));

        *ret = max (*ret, -getDiff(start,end-2));
    }


    *ret = max(*ret,number[start] -getDiff(start+1,end));
    *ret = max(*ret,number[end-1]-getDiff(start,end-1));

    return *ret;
}

void showAnswer (int start,int end)
{
    if (end-start == 0)
        return;

    int ret = cache[start][end];

    if (end-start >= 2)
    {
        if (ret == -getDiff(start+2,end))
        {
            printf("erase %d %d\n",number[start],number[start+1]);
            showAnswer(start+2,end);
            return;
        }
        
        if (ret == -getDiff(start,end-2))
        {
            printf("erase %d %d\n",number[end-2],number[end-1]);
            showAnswer(start,end-2);
            return;
        }

        
    }
        if (ret == number[start] -getDiff(start+1,end))
        {
            printf("take %d \n",number[start]);
            showAnswer(start+1,end);
            return;
        }
        
        if (ret == number[end-1]-getDiff(start,end-1))
        {
            printf("take %d \n",number[end-1]);
            showAnswer(start,end-1);
            return;
        }

}

int main (void)
{
    int temp;
    int testcase;

    cin >> testcase;

    while(testcase--)
    {
        number.clear();
        cin >> n;

        for (int i = 0 ; i < 51; i++)
            for (int j = 0; j < 51; j ++)
                cache[i][j] = NON;

        for (int i = 0; i < n; i++)
        {
            cin >> temp;
            number.push_back(temp);
        }

        cout << getDiff(0,n)<<endl;
//        showAnswer(0,n);
    }
}



