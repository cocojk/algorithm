
// 문자열 검색 문제 : 문자열 H가 문자열 N을 부분 문자열로 포함하는지 확인하고, 포함한다면 N과 일치하는 부분 문자열의 시작 위치를 찾는 문제 

// 20.1 단순한 문자열 검색 알고리즘의 구현 

// H의 부분 문자열로 N 이 출현하는 시작 위치들을 모두 반환한다.
vector<int> naive Search(const string& H, const string& N) {
    vector<int> ret;
    // 모든 시작 위치를 다 시도해 본다.
    for (int begin = 0; begin + N.size() <= H.size(); ++begin) {
        bool matched = true;
        for (int i = 0 i < N.size(); i++)
            if(H[begin+i] != N[i]) {
                matched = false;
                break;
            }
        if (matched) ret.push_back(begin);
    }

    retrn ret;
}

// 대부분의 경우 첫 번쨰나, 두번째 위치에서 불일치로 넘어 갈 수 있지만,
// worst case의 경우 모든 경우에 match 되므로 running time = O(H*N)이 된다.
// 하지만, 이런 경우는 흔치 않기 때문에, 표준 라이브러리에 20.1 알고리즘이 사용된다. 
// C의 strstr, c++ string::find(), java indexOf()

// KMP 알고리즘  (Knuth-morris-pratt)
// 검색 과정에서 얻는 정보를 버리지않고 잘 활용하면 많은 시간을 절약할 수 있다.
// N,begin=i                    a a b a a b a c
// H                     ? .. ? a a b a a b a ? ..
// N,begin=i+1                    a a b a a b a c
// N,begin=i+2                      a a b a a b a c
// N,begin=i+3                        a a b a a b a c
// N,begin=i+4                          a a b a a b a c
// N,begin=i+5                            a a b a a b a c
// N,begin=i+6                              a a b a a b a c

// 맨 처음 H와 N을 비교하면 7번째 글자까지 동일하다는 사실을 알 수 있고, 이 정보를 이용해서 시작 위치 중 일부는 답이 도리 수 없을을 보지도 않고도 알 수 있다.
// 즉, i+1, i+2 ,i+4, i+5의 경우 답이 될 수 없음을 알 수 있고,
// 일치한 글자 수는 항상 0에서 |N| 사이의 정수이기 때문에, 전처리 과정에서 이 정보들을 미리 계산해 저장해두면 최적화가 가능하다.

// 다음 시작 위치 찾기 
// 불일치가 일어났을 떄 지금까지 일치한 글자의 수를 이용해 다음으로시도해야 할 시작위치를 빠르게 찾아내야 한다.
// 시작 위치 i+k에서 답을 찾을 수 있기 위해서는 N[...matched-1]의 길이 matched-k인 접두사와 접미사가 같아야 한다.
// 그러므로 답이 될 수 있는 바로 다음 위치를 찾기 위해서는 N의 각 접두사에 대해 접두사도 되고 점미사도 되는 문자열의 최대 길이를 계산해 두면 된다.
// 전처리 과정에서 다음과 같이 정의되는 배열 pi[]를 계산한다.
// pi[i] = N[...i]의 접두사도 되고 접미사도 되는 문자열의 최대 길이  
// pi[]는 N이 어디까지 일치했는지가 주어질 때 다음 시작 위치를 어디로 해야할지를 말해주기 때문에, 흔히 부분일치 테이블 (partial match table) or 실패 함수(failure function)이라고 한다.

// "aabaabac"의 partial match table 
// i    N[...i]         접두사이면서 접미사인 최대 문자열       p[i]
// 0    a               x                                       0
// 1    aa              a                                       1
// 2    aab             x                                       0
// 3    aaba            a                                       1
// 4    aabaa           aa                                      2
// 5    aabaab          aab                                     3
// 6    aabaaba         aaba                                    4
// 7    aabaabac        x                                       0

// 실제 문자열 검색의 구현
// KMP 알고리즘은 단순한 알고리즘처럼 시작 위치 0에서부터 시작해서 H와 N의 글자를 비교한다. 만약 matched 글자가 일치한 후 불일치가 발생했다고 하면, 
// 시작 위치를 matched-pi[matched-1]으로 증가시키고, matched를 pi[matched-1]으로 변경하고 비교를 계속한다. 
// 답을 찾은 경우도, 현재 시작 위치를 답의 목록에 추가해야 하는 것 빼고는 불일치가 발생한 경우와 똑같다. 

// 코드 20.2 KMP 문자열 검색 알고리즘의 구현 

// H의 부분 문자열로 N이 출현하는 시작 위치들을 모두 반환한다.
vector<int> kmpSearch(const string& H, const string& N) {
    int n = H.size(), m=N.size();
    vector<int> ret;
    // pi[i]=N[...i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이 
    vector<int> pi = getParitalMatch(N);
    // begin = matched = 0에서 부터 시작하자.
    int begin = 0, matched = 0;
    while(begin <= n-m)
    {
        // 만약 H의 해당 글자가  N의 해당 글자와 같다면 
        if ( (matched < m) && (H[begin+matched] == N[matched]) ) {
            
            matched++;
            // 결과적으로 m 글자가 모두 일치했다면 답에 추가한다. 
            if (matched == m)
                ret.push_back(begin);
        }
        else {
            
            // 예외: matched가 0인 경우에는 다음 칸에서부터 계속 
            if (matched == 0)
            {
                begin++;
            }
            else 
            {

                begin += matched - pi[matched-1];
                // begin을 옮겼다고 처음부터 다시 비교라 필요가 없다.
                // 옮긴 후에도 pi[matched-1]만큼은 항상 일치하기 때문이다. 
                matched = pi[matched-1];
            }
        }
    }

    return ret;
}

// running time : while : O(H) - 각각의 if문에 대해서 최대 O(H)만큼 수행 가능 .

// 부분일치 테이블 생성하기 
// KMP 검색 과정을 응용해 이 함수를 빠르게 구현할 수 있다.
// 1. 가장 간단한 방법 
// N의 각 접두사에 대해 가능한 답을 하나씩 모두 시도해 보는 것.
// 길이가 p인 접수다 N[...p-1]이 주어졌을 때 길이 p-1인 접두사, 길이 p-2인 접두사, 길이 p-3인 접두사들을 순회하며 
// 이들이 N[...p-1]의 접미사가 되는지 확인한다. 
// running time : O(N^3) : 길이가 총 N에 대해서 각각의 수행 시간이 N^2 (1+2+...+N)
// 대개 |N|은 |H|에 비해 훨씬 작기 때문에 이것만으로도 충분한 경우도 많다.
// N = aaba 
// 1. a a       =  1
//      a
// 2. a a b     =  1 + 2
//      a a
//        a  
// 3. a a b a   =  1 + 2 + 3 
//      a a b 
//        a a 
//          a

// 2. 최적화 1. 각 접두사에 대해 pi[]의 값을 따로 계산하는 것이 아니라 모든 접두사에 대해 한꺼번에 계산한다. 
// 두 글자 N[i]와 N[begind + i]가 일치할 때마다 pi[begin+i]를 갱신해준다.
// running time : O(N^2)
// N = aaba 
// 1. a a b a   =  1 + 2 + 3 
//      a a b 
//        a a 
//          a
// 이 것의 첫 3글자만 따면 1번의 2와 동일하다. 

// 단순한 문자열 알고리즘을 이용해 부분 일치 테이블 계산하기 

// N에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해 
// pi[]를 계산한다.
// pi[i]=N[...i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이 
vector<int> getParitalMatch(const string& N) {
    int m = N.size();
    vector<int> pi(m,0);
    // 단순한 문자열 검색 알고리즘을 구현한다.
    for (int begin = 1; begin < n; begin++) {
        for (int i = 0; i + begin < n; i++) {
            if (N[begin+i] != N[i]) break;
            // i+1 글자가 서로 대응되었다.
            pi[begin + i] = max (pi[begin+i],i+1);
        }
    }

    return pi;
}

// 3. KMP 알고리즘 응용 
// KMP는 begin + matched가 항상 증가한다. 
// 따라서, 항상 pi의 index값이 증가한다. 
// begin 값의 증가는 match되는 최대 증가 길이의 감소를 의미하므로, 
// 따라서, 최초 찾아지는 값이 pi의 값이 된다.
// running time : O(N)
// 두 과정의 시간 복잡도 : O(N+H)

// 현재 matched 글자가 일치했다면, pi[matched-1]는 항상 계산됨 뒤이다. pi의 index값은 항상 증가하므로, 
// pi[]의 각 원소는 최대 한번만 변경된다. (begin+matched가 항상 증가)

// KMP 알고리즘을 이용해 부분 일치 테이블을 생성하기 

// N에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해 pi[]를 계산한다. 
// pi[i]=N[...i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이 
vector<int> getParitalMatch(const string& N) {
    int m = N.size();
    vector<int> pi(m,0);
    // KMP로 자기 자신을 찾는다.
    // N을 N에서 찾는다. begin = 0이면 자기 자신을 찾아버리니깐 안됨.!
    int begin = 1, matched = 0;  
    while (begind + matched < m) {
        if (N[begin+matched] == N[matched])
        {
            matched++;
            pi[begin+matched-1] = matched;
        }
        else 
        {
            if (matched == 0)
                begin++;
            else 
            {
                begin += matched - pi[matched-1];
                matched = pi[matched-1];
            }
        }
    }

    return pi;
}

// 예제: NAMING
/*
문제

아주대에 사는 외수는 작명에 능하기로 유명해서 많은 부부들이 아주대로 몰려와서 태어나는 아이들의 이름을 지어달라고 한다. 부부들은 이름은 잘 짓는게 출세에 영향을 미친다고 생각을 하고 있으며, 따라서 좋은 이름을 지어 출세하기를 기원한다. 허나 게으른 외수에게 작명은 지루한 작업이다. 효율적으로 일을 하고자 궁리하던 차에 쉽지만 기가 막힌 알고리즘을 고안하게 되었다.

외수가 개발한 작명 알고리즘은 다음과 같다.

아버지의 이름 뒤에 어머니의 이름을 덧붙여서 하나의 새로운 문자열 S로 만든다.
이 문자열 S의 접두사(prefix)도 되고 접미사(suffix)도 되는 문자열을 찾는다.
예를 들어 아버지의 이름이 'ala'고 어머니의 이름이 'la' 일 경우 S = 'ala' + 'la' = alala다. 그리고 이 문자열의 접두사이기도 하고 접미사이기도 한 문자열은 다음 세가지다.

a
ala
alala
아버지와 어머니의 이름이 주어질 때, 외수의 규칙을 이용해 지어줄 수 있는 이름들을 모두 찾는 프로그램을 작성하라. 문제에서는 편의상 모든 문자열 대신, 가능한 모든 문자열의 길이를 찾는다.

입력

빈칸이 없는 영문 알파벳 소문자로 이뤄진 문자열이 입력이 두 줄 입력된다.
첫 번째 줄은 아버지의 이름이고, 두 번째 줄은 어머니의 이름이다.
두 문자열의 길이를 합쳐서 400,000 자가 넘어가는 입력은 들어오지 않는다.

출력

외수가 주어질 수 있는 이름들의 길이들을 한 줄에 출력한다.
출력되는 숫자 사이에는 정확히 공백이 하나 포함되어야 하며, 길이는 오름차순으로 출력되어야 한다.

예제 입력

ababcabababa
bcabab
예제 출력

2 4 9 18


*/
#include <string>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

vector<int> getPartialMatch (const string& N) {
    
    int n = N.size();
    vector<int> pi(n,0);
    int begin = 1,matched = 0;
    while ( begin + matched < n)
    {
        if ( N[begin+matched] == N[matched])
        {
            matched++;
            pi[begin+matched-1] = matched;
        }
        else 
        {
            if(matched == 0)
                begin++;
            else 
            {
                begin += matched - pi[matched-1];
                matched = pi[matched-1];
            }
        }
    }

    return pi;
}

int getPrefixSuffix(const string& N) {
    int n = N.size();
    vector<int> ret, pi = getPartialMatch(N);

    while (n != 0)
    {
        ret.push_back(n);
        n = pi[n-1];
    }

    sort(ret.begin(),ret.end());

    for (int i = 0; i < ret.size(); i++)
        printf("%d ",ret[i]);
}


int main(void)
{
    string temp1,temp2;
    getline(cin,temp1);
    getline(cin,temp2);
    temp1.append(temp2);
    getPrefixSuffix(temp1);
}


// 예제: PALINDROMIZE
/*
문제

앞에서부터 읽었을 때와 뒤로부터 읽었을 때 똑같은 문자열을 팰린드롬(palindrome)이라고 합니다. 예를 들면 “noon”이나 “stats” 같은 단어들이 팰린드롬입니다. 주어진 문자열 S 뒤에 적절히 문자열을 붙여서 S 를 팰린드롬으로 만들려고 합니다. 예를 들어 S = “anon”이면 뒤에 “ona”를 붙여서 “anonona”를 만들 수도 있고, “a”를 붙여서 “anona”를 만들 수도 있지요. 물론 S를 뒤집은 문자열을 S 뒤에 붙이면 항상 팰린드롬이 되므로, 결과 팰린드롬이 가능한 한 짧았으면 합니다.

S가 주어질 때 S에서 만들 수 있는 가장 짧은 팰린드롬의 길이를 출력하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C(<=50)가 주어집니다. 그 후 각 테스트 케이스마다 문자열 S가 주어집니다. 주어지는 문자열의 길이는 1 이상 10만 이하이며, 알파벳 소문자로만 구성됩니다.

출력

각 테스트 케이스마다 한 줄에 S를 이용해 만들 수 있는 가장 짧은 팰린드롬의 길이를 출력합니다.

예제 입력

3
there
amanaplanacanal
xyz
예제 출력

7
21
5
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<int> getPartialMatch (const string& N)
{
    int n = N.size();
    vector<int> pi (n,0);

    int begin = 1, match = 0;

    while (begin+match < n)
    {
        if (N[begin+match] == N[match])
        {
            match++;
            pi[begin+match-1] = match;
        }
        else 
        {
            if(match == 0)
            {  
                begin++;
            }
            else 
            {
                begin += match - pi[match-1];
                match =  pi[match-1];
            }
        }
    }

    return pi;
}

void maxOverlap (const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<int> pi = getPartialMatch(b);
}

void getPalindrome (const string& N,const string& M)
{
    int n = N.size();
    vector<int> pi = getPartialMatch(M);
    int begin = 0, match = 0;

    while (begin + match < n)
    {
        if (N[begin+match] == M[match])
        {
            match++;

            if (begin + match == n)
            {
                cout<< n+begin << endl;
                return;
            }

        }
        else 
        {
            if (match == 0)
            {
                begin++;
            }
            else 
            {
                begin += match - pi[match-1];
                match = pi[match-1];
            }
        }
    }
    
}

int main (void)
{
    int testcase;

    string input,input2;
    cin >> testcase;
    getline(cin,input);
    while(testcase--)
    {
        getline(cin,input);
        input2 = input;
        reverse(input2.begin(),input2.end());
        getPalindrome(input,input2);
    }
}

// KMP 알고리즘의 다른 구현 
vector<int> kmpSearch2 (const string& H, const string& N) {
    int n = H.size(), m = N.size();
    vector<int> ret;
    vector<int> pi = getParitalMatch(N);
    // 현재 대응된 글자의 수 
    int matched = 0;
    for (int i = 0; i < n; i++) {
        // matched번 글자와 짚더미의 해당 글자가 불일치할 경우,
        // 현재 대응된 글자의 수를 pi[matched-1]로 줄인다.
        while (matched >0 && H[i] != N[matched])
            matched = pi[matched-1];
        // 글자가 대응될 경우 
        if (H[i] == N[matched]) {
            matched++;
            if (matched == m) {
                ret.push_back(i-m+1);
                matched = pi[matched-1];
            }
        }
    }

    return ret;
}

