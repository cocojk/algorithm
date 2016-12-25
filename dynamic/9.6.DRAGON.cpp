/*
문제

dragon10b.png
드래곤 커브(Dragon curve)는 간단한 수학 규칙으로 그릴 수 있는 그림으로, 위 그림같은 형태를 지닙니다. 드래곤 커브는 선분 하나에서 시작해서 간단한 규칙으로 이 선분을 변형해서 만들어지며, 변형이 한 번 이루어져 세대가 변할 때마다 더욱 복잡한 모양으로 진화합니다. 이 도형같이 일부를 확대했을 때 전체와 비슷한 형태로 구성된 도형들을 프랙탈(fractal) 이라고 하지요.

드래곤 커브를 그리는 방법을 드래곤 커브 문자열이라고 부릅시다. 드래곤 커브 문자열은 X, Y, F, +, -로 구성된 문자열인데, 우리는 한 점에서 시작해 다음과 같이 커브를 그리면 됩니다.

F: 앞으로 한 칸 전진하며 선을 긋습니다.
+: 왼쪽으로 90도 회전합니다.
-: 오른쪽으로 90도 회전합니다.
X, Y: 무시합니다.
0세대 드래곤 커브를 그리는 문자열은 선분 하나인 FX 입니다. 그리고 그 이후의 다음 세대는 이전 세대 문자열의 각 글자를 다음과 같이 치환해서 만들어집니다.

X => X+YF
Y => FX-Y
따라서 1, 2세대 드래곤 커브 문자열은 다음과 같습니다.

1세대: FX+YF
2세대: FX+YF+FX-YF
n세대 드래곤 커브 문자열을 구하고 싶습니다. 이 때 문자열 전체를 구하면 너무 기니, 문자열 중 p번째 글자부터 l글자만을 계산하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 c (c <=50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 세 개의 정수로 드래곤 커브의 세대 n (0 <= n <= 50) , 그리고 p 와 l (1 <= p <= 1,000,000,000 , 1 <= l <= 50) 이 주어집니다. n세대의 드래곤 커브 문자열의 길이는 항상 p+l 이상이라고 가정해도 좋습니다.

출력

각 테스트케이스마다 한 줄에 n세대 드래곤 커브 문자열의 p번째 글자부터 l글자를 출력합니다.

예제 입력

4
0 1 2
1 1 5
2 6 5
42 764853475 30 
예제 출력

FX 
FX+YF 
+FX-Y 
FX-YF-FX+YF+FX-YF-FX+YF-FX-YF-
*/
#include <math.h>
#include <iostream>
#include <string.h>
#include <string>

#define count(n) (2 + 3 * ((int)pow(2,(n)) -1))

const int MAX = 1000000000;
using namespace std;
void reconstructG (int n, int k);
void reconstructF (int n, int k);
int getGCount (int n);
int getFCount (int n);
int cacheG [51];

int getFCount (int n)
{
    if (n >=29)
        return MAX;

    return count(n);
}

int getGCount (int n)
{
    if (n == 1)
        return 2;

    int * ret = &cacheG[n];

    if (*ret != -1)
        return *ret;

    return *ret = getGCount(n-1)  + getFCount(n-2) + 1;
}


void reconstructF (int n,int k)
{
    if ( n== 1 || n == 0)
    {
        string temp = "FX+YF";
        cout << temp[k];
        return;
    }

    if ( getFCount (n-1) <= k )
    {
        k -= getFCount (n-1);
    }
    else 
    {
        reconstructF (n-1,k);
        return;
    }

    if (k == 0)
    { 
        cout << "+";
        return;
    }

    k--;

    if ( getFCount (n-2) <= k )
    {
        k -= getFCount (n-2);
    }
    else 
    {
        reconstructF (n-2,k);
        return;
    }

    if (k == 0)
    {

        cout << "-";
        return;
    }
    k--;

    reconstructG (n-1,k);
    return;

}

void reconstructG (int n,int k)
{
    if ( n== 1 )
    {
        string temp = "YF";
        cout << temp[k];
        return;
    }

    if ( getFCount (n-2) <= k )
    {
        k -= getFCount (n-2);
    }
    else 
    {
        reconstructF (n-2,k);
        return;
    }

    if (k == 0)
    { 
        cout << "-";
        return;
    }
    k--;

    reconstructG (n-1,k);  
    return;
}

int main (void)
{
    int testcase;
    int n,k,l;
    cin >> testcase;

    while (testcase --)
    {
        cin >> n >> k >> l;
        memset(cacheG,-1,sizeof(cacheG));
        for (int i = 0; i < l ; i ++)
        {
            reconstructF (n,k-1+i);
        }

        cout << endl;
    }
}





