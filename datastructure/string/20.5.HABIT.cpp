/*
문제

대중 앞에서 연설이나 강의를 하는 사람들은 말 중간중간에 습관적으로 들어가는 말버릇들을 없애기 위해 많은 노력을 합니다. 강의를 하는 사람이 한 마디 할 때마다 "음~" 혹은 "그래서요~" 같은 말을 반복하면 잘 신뢰가 가지 않기 때문이지요.

다음 학기에 처음으로 학부 강의를 맡게 된 정박사는 자신의 버릇을 고치기 위해 알고스팟 웅변 학원에 찾아왔습니다. 알고스팟 웅변 학원에서는 수강생들이 과거에 한 발표 자료들을 자동화된 프로그램으로 분석해 고쳐야 할 말버릇들을 정확히 짚어냅니다.

정박사가 지금까지 했던 발표들과 강의들에서 했던 말을 모두 음성 인식을 통해 대본으로 만들었습니다. 이 때 대본 중 K 번 이상 등장하는 부분 문자열을 "말버릇" 이라고 합시다. 우선 가장 티가 많이 나는 것부터 고치기 위해 가장 긴 말버릇을 찾으려 합니다.

대본이 주어질 때 가장 긴 말버릇의 길이를 찾는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다. 각 테스트 케이스는 두 줄로 주어지며, 첫 줄에는 K (1 <= K <= 1000) 가, 두 번째 줄에는 정박사의 발표 대본이 주어집니다. 대본은 공백 없이 알파벳 소문자로만 구성된 문자열이며 길이는 1 이상이고 4000 을 넘지 않습니다.

출력

각 테스트 케이스마다 K 번 이상 등장하는 부분 문자열의 최대 길이를 출력합니다. 어떤 부분 문자열도 K 번 이상 등장하지 않는다면 0 을 출력합니다.

예제 입력

4
2 
uhmhellouhmmynameislibe 
3
banana
1 
thatsagoodquestion 
3
hello
예제 출력

3
1
18
0
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

struct Comparator {
    const vector<int>& group;
    int t;
    Comparator (const vector<int>& _group,int _t): group(_group),t(_t) {
    }

    bool operator () (int a, int b) {
        if (group[a] != group[b])
            return group[a] < group[b];

        return group[a+t] < group[b+t];
    }
};

vector<int> getSuffixArray (const string& N)
{
    int n = N.size();
    int t = 1;
    vector<int> group (n+1);

    group[n] = -1;

    for (int i = 0; i < n; i++)
        group[i] = N[i];

    vector<int> perm(n);
    for (int i = 0; i < n; i++)
        perm[i] = i;
    while (t < n)
    {
        Comparator compareUsing2T(group,t);
        sort(perm.begin(),perm.end(),compareUsing2T);

        t *= 2;
        if (t >= n)
            break;

        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if(compareUsing2T(perm[i-1],perm[i]))
                newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
            else 
                newGroup[perm[i]] = newGroup[perm[i-1]];
        }

        group = newGroup;
    }   
       
 return perm;
  
}

int commonPrefix (const string& s, int i, int j) {
    int k = 0;
    while ( i < s.size() && j < s.size() && s[i] == s[j]) {
        ++i; ++j; ++k;
    }

    return k;
}

int longestFrequent (int k, const string& s) {
    vector<int> a = getSuffixArray(s);
    int ret = 0;
    for (int i = 0; i + k <= s.size(); i++) 
        ret = max (ret, commonPrefix(s,a[i],a[i + k -1]));
    return ret;
}

int main (void)
{
    int testcase;
    int k;
    string input;
    cin >> testcase;

    while (testcase--)
    {
        cin >> k >> input;
       
        cout<<longestFrequent(k,input)<<'\n';
    }
}

        
