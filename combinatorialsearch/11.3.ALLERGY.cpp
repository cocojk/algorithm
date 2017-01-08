#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
int m;
int n;
int best;
long food [50];
long cumulSum [50];
const int INF = 987654321;

int isPossible (int index, long set)
{
    if ((cumulSum[index] | set) == ((1l<<n) -1))
        return 1;

    return 0;
}

int isNotInclude (int index, long set)
{
    if ((set | food[index]) == set)
        return 0;

    return 1;
}

void getMin (int index, int value, long set)
{
    if (set == ((1l<<n) -1))
    {
        best = min (best,value);
        return;
    }

    if (index >= m)
    {
        return ;
    }


    if (!isPossible (index, set))
        return ;

    // select 
    if (isNotInclude(index,set))
        getMin (index+1,value+1,(set|food[index]));

    // don't select 
    getMin (index+1,value,set);
}

void preCalc (void)
{
    cumulSum[m-1] = food[m-1];

    for (int i =m-2 ; i >= 0; i --)
        cumulSum[i] = cumulSum[i+1] | food[i];
}

int main (void)
{
    int testcase;
    cin >> testcase;

    while (testcase--)
    {
        cin >> n >> m;
        best = INF;
        map<string,int> names;

        for (int i = 0; i < m; i++)
        {  
            food[i] = 0;

        }

        for (int i = 0; i < n; i++)
        {
            string name;
            cin >> name;
            names[name] = i;
        }

        for (int foodind = 0 ; foodind < m; foodind++)
        {
            int sz;
            cin >> sz;
            for (int j = 0; j < sz; j ++)
            {
                string name;
                cin >> name;
                int nameindex = names[name];
                food[foodind] |= (1l<<nameindex);
            }
        }


        preCalc();
        getMin(0,0,0);
        cout << best << endl;
    }
}

