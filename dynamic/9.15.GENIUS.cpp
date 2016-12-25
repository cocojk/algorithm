
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int k,n;
int m;
int L[50];
double T [50][50];
int Q[50];
double probs [50][5];


vector<vector<int> >  init (int size)
{
    vector<vector<int> > ret;

    for (int i = 0; i< size; i++)
    {
        vector<int> temp;
        for (int i =0; i < size; i++)
            temp.push_back(0);
        ret.push_back(temp);
    }
    
    return ret;
}

vector<vector<int> > mult (const vector<vector<int> >& a,const vector<vector<int> >& b)
{
    vector<vector<int> > ret;
    for (int i = 0; i < a.size(); i ++)
    {
        vector<int> temp;
        for (int j = 0; j < a.size(); j++)
        {
            int val = 0;
            for (int k = 0; k < a.size(); k++)
            {
                val += a[i][k] * b[k][j];
            }

            temp.push_back(val);
        }

        ret.push_back(temp);
    }

    return ret;
}

vector<vector<int> > identity (int size)
{
    vector<vector<int> > ret;
    for (int i = 0; i < size; i++)
    {
        vector<int> temp;
        for (int j = 0; j < size; j ++)
        {
            if (i == j )
                temp.push_back(1);
            else
                temp.push_back(0);
        }
        ret.push_back(temp);
    }

    return ret;
}

vector<vector<int> > pow (const vector<vector<int> >& A,int k)
{

    if (k == 0)
        return identity(A.size());
    if (k%2 > 0)
        return mult(pow(A,k-1),A);
    vector<vector<int> > ret = pow(A,k/2);
    return mult(ret,ret);
}

// 코드 9.31 지니어스 문제를 해결하는 행렬의 거듭제곱 동적 계획법 

// k분 30초 후에 각 곡이 재생되고 있을 확률을 반환한다.
void solver() {
    vector<vector<int> >W = init(4*n);

    // 자기 자신을 그대로 가져온다.
    // 첫 3*n개의 원소는 그대로 복사해온다.
    for (int i = 0; i < 3*n; i++)
        W[i][i+n] = 1.0;

    // start(time,song) = 시그마 (start(time-L[prev],prev) * T[prev][song])
    // 마지막 n개의 원소는 이전 원소들의 선형 결합으로 이루어진다.
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            W[3*n+i][(4-L[j])*n+j] = T[i][j];

    vector<vector<int> > Wk = pow(W,k);
    // song번 노래가 재생되고 있을 확률을 계산한다.
    for (int song = 0; song < n; song++)
    {
        double ret = 0;
        // song번 노래가 시작했을 시간을 모두 찾아 더한다.
        for (int start = 0; start < L[song]; start++)
            ret += Wk[(3-start)*n+song][3*n];

        cout << ret << endl;
    }
}

        

int main (void)
{
    int testcase;

    cin >> testcase;

    while (testcase--)
    {
        cin >> n >> k >> m;

        for (int i = 0; i < n; i++)
            cin >> L[i];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> T[i][j];

        solver();
    }
}






