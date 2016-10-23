
/*
   문제

   After suffering from the deficit in summer camp, Ainu7 decided to supply lunch boxes instead of eating outside for Algospot.com winter camp.

   He contacted the famous packed lunch company "Doosot" to prepare N lunch boxes for N participants. Due to the massive amount of order, Doosot was not able to prepare the same menu. Instead, they provided different N lunch boxes. Ainu7 put all the lunch boxes to a refrigerator.

   The lunch time has come, and suddenly Ainu7 noticed that there is only one microwave available. As all lunch boxes are not the same, they need a different amount of time to microwave and eat. Specifically, i-th lunch box needs Mi seconds to microwave and Ei seconds to eat.

   Ainu7 needs to schedule microwave usage order to minimize lunch time. Lunch time is defined as the duration from the beginning of microwaving of any lunch box to the end of eating for all participants. Write a computer program that finds minimum lunch time to help Ainu7. Note that substituting lunch while microwave is turned on is totally unnecessary, because the lunch will be cooled down.

   입력

   The first line of the input contains one integer T, the number of test cases.

   Each test case consists of three lines. The first line of each test case contains N(1≤N≤10000), the number of the participants.

   N integers will follow on the second line. They represent M1, M2, ⋯, MN.
   Similarly, N integers will follow on the third line, representing E1, E2, ⋯, EN.

   출력

   For each test case, print the minimized lunch time in one line. It is guaranteed that the answer is always strictly less than 231.

   예제 입력

   2
   3
   2 2 2
   2 2 2
   3
   1 2 3
   1 2 1
   예제 출력

   8
   7
*/

// 도시락 데우기 문제를 해결하는 탐욕적 알고리즘 
#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>

#define MAX_N 10000

using namespace std;
int n, e[MAX_N], m[MAX_N];
int heat() {
    // 어느 순서로 데워야 할지를 정한다.
    vector<pair<int,int> > order;

    for(int i = 0 ; i < n; i ++)
        order.push_back(make_pair(-e[i],i));
    sort(order.begin(),order.end());

    // 해당 순서대로 데워먹는 과정을 시뮬레이션 한다.
    int ret = 0, beginEat = 0;

    for(int i = 0; i < n; i++) {
        int box = order[i].second;
        beginEat += m[box];
        ret = max(ret, beginEat + e[box]);
    }

    return ret;
}

int main()
{
    int testcase;

    scanf("%d",&testcase);
    
    while(testcase--)
    {
       scanf("%d",&n);
       for(int i = 0; i < n; i++)
           scanf("%d",&m[i]);
       for(int i = 0; i < n; i++)
           scanf("%d",&e[i]);

       printf("%d\n",heat());
    }
}

        
