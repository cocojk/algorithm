
// suffix array (접미사 배열) 
// 어떤 문자열 S의 모든 접미사를 사전순으로 정렬해 둔 것. 
// 물론, 이 말 곧이 곧대로 접미사들을 문자열 배열에 저장하면 문자열 길이의 제곱에 비례하는 메모리가 필요하기 때문에,
// 대게 접미사 배열은 각 접미사의 시작 위치를 담는 정수 배열로 구현된다. 

// "alohomora"의 접미사 배열 
// i    A[i]    S[A[i]...]
// 0    8       a
// 1    0       alohomora
// 2    3       homora
// 3    1       lohomora
// 4    5       mora
// 5    2       ohmora
// 6    4       omora 
// 7    6       ora
// 8    7       ra 

// 예제: 접미사 배열을 이용한 검색 
// 문자열 검색이 가능 : 짚더미 H가 바늘 N을 포함한다면 항상 N은 H의 어떤 접미사의 접두사라는 점을 이용한다.
// 예를 들어, "alohomora"에서 "homo"를 찾는다고 하면 "homo"는 S의 접미사인 "homora"의 접두사가 된다. 
// 이 속성을 이용하여 H의 접미사 배열을 이진 탐색해서 각 문자열이 출현하는 위치를 찾을 수 있다. O(NlgH) 

// 접미사 배열의 생성 

// 코드 20.8 접미사 배열을 계산하는 단순한 알고리즘 
// running time : sort : O(NlgN) , 각 compare time : O(N) -> O(n^2lgN)
// 실제로는 모든 글자를 다 비교할 것 없이 첫 몇 글자만 비교해도 어느쪽이 큰지 판단할 수 있다. 
// 두 접미사의 시작 위치 i,j가 주어질 때 두 접미사 중 어느 쪽이 앞에 와야 할지 비교한다.
struct SuffixComparator {
    const string& s;
    SuffixComparator (const string& s) : s(s) {}
    bool operator () (int i, int j) {
        // s.substr() 대신에 strcmp()를 쓰면 임시 객체를 만드는 비용이 절약된다
        return strcmp(s.c_str() + i, s.c_str() +j) < 0;
    }
};

// s의 접미사 배열을 계산한다.
vector<int> getSuffixArrayNaive (const string& s) {
    // 접미사 시작 위치를 담은 배열을 만든다.
    vector<int> perm;
    for (int i =0; i < s.size(); i++)
        perm.push_back(i);
    // 접미사를 비교하는 비교자를 이용해 정렬하면 완성!
    sort(perm.begin(),perm.end(),SuffixComparator(s));
    return perm;
}

// 접미사 배열을 만드는 맨버-마이어스의 알고리즘 
// 접미사 배열을 만드는 알고리즘 중 가장 빠른 것은 O(n)이지만, 구현이 복잡.
// 따라서 구현이 어느정도 간단하고, running time이 빠른것이 맨버-마이어스 알고리즘 
// 접미사들의 목록을 여러번 정렬하는데, 매번 그 기준을 바꾼다. 처음에는 접미사의 한 글자만을 기준으로 정렬하고 ,
// 다음에는 접미사의 첫 두 글자를 기준으로 정렬하고, 다음에는 접미사의 첫 네글자를 기준으로 정렬한다.
// 이렇게 lgN번 정렬을 하고 나면 우리가 원하는 접미사 배열을 얻게 된다. 
// running time : O(NlgN^2)
// 첫 한 글자 기준    첫  글자 기준    첫 네 글자 기준    첫 여덟 글자 기준 
// ississipi          i                i                  i
// issipi             ipi              ipi                ipi
// ipi                ississipi        ississipi          issipi
// i                  issipi           issipi             ississipi
// mississipi         mississipi       mississipi         mississipi
// pi                 pi               pi                 pi
// ssissipi           ssissipi         sipi               sipi
// sissipi            sipi             sissipi            sissipi
// ssipi              ssissipi         ssipi              ssipi
// sipi               ssipi            ssissipi           ssissipi

// 코드 20.9 첫 t글자로 묶인 그룹 정보를 이용해 첫 2t글자를 비교하는 비교자의 구현 

// 각 접미사들의 첫 t글자를 기준으로 한 그룹 번호가 주어질 때,
// 주어진 두 접미사르 첫 2*t 글자를 기준으로 비교한다.
// group[]은 길이가 0인 접미사도 포함한다.
struct Comparator {
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& _group, int _t)
    {
        group = _group;
        t = _t;
    }

    bool operator () (int a,int b) {
        // 첫 글자가 t글자가 다르면 이들을 이용해 비교한다.
        if (group[a] != group[b])
            return group[a] < group[b];
        
        // 아니라면 S[a+t..]와 S[b+t..]의 첫 t글자를 비교한다.
        // 이 부분을 참조하는 경우, 이미 t 글자가 동일한 경우이다. 따라서 a+t,b+t는 최대 n을 가진다.
        return group[a+t] < group[b+t];
    }
};

// 코드 20.10 접미사 배열을 계산하는 맨버와 마이어스의 알고리즘 

// s의 접미사 배열을 계산한다.
vector<int> getSuffixArray (const string& s) {
    int n = s.size();


    // group[i] = 접미사들을 첫 t 글자를 기준으로 정렬했을 떄, S[i..]가 들어가는 그룹 번호 
    // t =1 일 떄는 정렬할 것 없이 S[i..]의 첫 글자로 그룹 번호를 정해줘도 같은 효과가 있다.

    int t = 1;
    vector<int> group(n+1);
    for (int i = 0; i < n; i++)
        group[i] = s[i];
    group[n] = -1;
    vector<int> perm(n);
    for (int i =0; i < n; i++)
        perm[i] = i;

    while (t < n) {
        // group[]은 첫 t글자를 기준으로 계산해 뒀다.
        // 첫 2t 글자를 기준으로 perm을 다시 정렬한다.
        Comparator compareUsing2T(group,t);
        sort(perm.begin(),perm.end(),compareUsing2T);
        // 2t 글자가 n을 넘는다면 이제 접미사 배열 완성!
        t *= 2;
        if (t >= n)
            break;

        // 2t글자를 기준으로 한 그룹 정보를 만든다.
        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for (int i = 1; i < n; i++)
            if(compareUsing2T(perm[i-1],perm[i]))
                newGroup[perm[i]] = newGroup[perm[i-1]] +1;
            else 
                newGroup[perm[i]] = newGroup[perm[i-1]];
        group = newGroup;
    }

    return perm;
}

// 예제: 원형 문자열 
// 길이 n(n<40000)인 문자열을 그림 20.8과 같이 끝과 끝이 연결된 원형으로 써봅시다.
// 이 문자열은 항상 시계 방향으로 읽는데, 시작 위치가 어디인지는 정해져 있지 않으므로 n가지 방법으로 읽을 수 있다.
// 이 중 사전순으로 가장 앞에 오는 문자열은 무엇일까?

// 코드 20.11 접미사 배열을 사용해 원형 문자열 문제를 해결하는 알고리즘의 구현 

// 사전순으로 가장 앞에 오는 s의 회전 결과를 구한다. 
string minShift(const string& s) {
    string s2 = s+s;
    vector<int> a = getSuffixArray(s2);
    for (int i = 0;  i < a.size(); i++)
        // 접미사 길이가 n 이상이어야 답이된다.
        if(a[i] <= s.size())
            return s2.substr(a[i],s.size());
    // 여기로 올 일은 없어야 한다.
    return ""__oops__";
}

// 예제: 서로 다른 부분 문자열의 수 
// 길이 n(n<=4000)인 문자열은 최대 (n+1)*n/2개의 부분 문자열을 가질 수 있습니다만, 서로 모두 다른 것은 아니다.
// 예를 들어 문자열 "banana"는 "ana"를 두 번, "n"을 두 번 포함한다. 문자열이 주어질 떄 이들의 서로 다른 부분 문자열의 
// 수를 세는 문제를 풀어보자. 

// 접미사 배열을 만든 후, 만약, 부분 문자열 중 중복이 없다면 각 접미사의 길이를 모두 더하면 부분 문자열의 총 수를 얻을 수 있다.
// 한 부분 문자열이 두 번 이상 출현할 경우 이를 접두사로 갖는 접미사들은 접미사 배열 상에서 항상 인접해 있다. 

// 코드 20.12 접미사 배열을 이용해 다른 부분 문자열의 수를 세는 알고리즘 

// s[i...]와 s[j...]의 공통 접두사의 최대 길이를 계산한다. 
int commonPrefix (const string& s, int i, int j) {
    int k = 0;
    while (i < s.size() && j < s.size() && s[i] == s[j]) {
        ++i; ++j; ++k;
    }
    return k;
}

// s의 서로 다른 부분 문자열의 수를 센다.
int countSubstrings (const string& s) {
    vector<int> a = getSuffixArray(s);
    int ret = 0;
    int n = s.size();
    for (int i = 0; i < a.size(); i++) {
        int cp =0;
        if(i > 0)
            cp = commonPrefix(s,a[i-1],a[i]);
        // a[i]의 (n-a[i])개의 접두사들 중에서 cp개는 중복이다.
        ret += s.size() - a[i] - cp;
    }

    return ret;
}


