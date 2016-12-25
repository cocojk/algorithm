
// kth

// k번째 답 계산하기 레시피 
// 1. 답들을 사전 순서대로 만들며 경우의 수를 세는 완전 탐색 알고리즘을 설계하고, 메모이제이션을 적용해 경우의 수를 세는 동적 계획법 알고리즘으로 바꾼다. 
// 2. 모든 답들을 사전순으로 생성하며 skip개를 건너뛰고 첫 번째 답을 반환하는 재귀 호출 함수를 구현. 재귀 함수는 각 조각들에 들어갈 수 있는 값을 하나씩 고려하면서 
// 이 값을 선택했을 때 답의 수 M과 건너 뛰어야할 답의 수 skip을 비교한다.
// a) M <= skip : M개의 답은 모두 우리가 원하는 답보다 위에 있으므로, 이들을 건너뛴다. 대신 skip을 M만큼 줄인다. 
// b) M > skip : M개의 답 중에 우리가 원하는 답이 있으므로, 이 값을 선택한다. M개의 답 중에 skip개를 건너뛴 것이 우리가 원하는 답이다. 이 값을 답에 추가하고 재귀호출로 
// 답의 나머지 부분을 만든다. 

/*
   문제

   모스 부호(Morse code)는 전화가 없던 시절 무선 전신에 주로 사용하던 코드로, 짧은 신호(단점, o)와 긴 신호(장점, -)를 섞어 글자를 표현하는 표현방식입니다. 예를 들어 알파벳 J는 모스 부호 o---로 표현되고, M은 --로 표현됩니다.

   n개의 장점과 m개의 단점으로 구성된 모든 신호들을 담고 있는 사전이 있다고 합시다. 예를 들어 n = m = 2라면 다음과 같은 신호들이 포함되어 있는 것이죠.

   --oo
   -o-o
   -oo-
   o--o
   o-o-
   oo--
   이 신호들은 사전순서대로 정렬되어 있습니다. -의 아스키 코드는 45이고, o의 아스키 코드는 111이기 때문에 -가 먼저 오게 되죠. n과 m이 주어질 때 이 사전의 k번째 신호를 출력하는 프로그램을 작성해 봅시다. 예를 들어 위 사전에서 네 번째 신호는 o--o입니다.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C(≤50)가 주어집니다. 각 테스트 케이스는 세 개의 정수 n, m(1≤n, m≤100), k(1≤k≤1,000,000,000)로 주어집니다. 사전에는 항상 k개 이상의 신호가 있다고 가정해도 좋습니다.

   출력

   각 테스트 케이스마다 한 줄에 해당 신호를 출력합니다.

   예제 입력

   3
   2 2 4
   4 8 13
   6 4 1
   예제 출력

   o--o
   --o-ooo-oooo
   ------oooo
*/

// 코드 9.6 모든 모드 신호를 만드는 완전 탐색 알고리즘 

// s : 지금까지 만든 신호 
// n : 더 필요한 -의 개수 
// m : 더 필요한 o의 개수 
void generate (int n, int m, string s) {
    // base case 
    if (n == 0 && m == 0) {
        cout << s << endl;
        return;
    }

    if (n > 0) generate(n-1,m,s+"-");
    if (m > 0) generate(n,m-1,s+"o");
}

// 코드 9.7 k-1개 건너뛰고 첫 번째 신호를 출력하는 알고리즘 

int skip;
// skip개를 건너뛰고 출력한다. 
void generate2 (int n, int m, string s) {
    // base case 
    if (skip < 0) return;
    // base case 
    if (n == 0 && m == 0) {
        // 더 건너뛸 신호가 없는 경우 
        if (skip == 0)
            cout << s << endl;
        --skip;
        return;
    }

    if (n > 0) generate2(n-1,m,s+"-");
    if (m > 0) generate2(n,m-1,s+"o");
}

// 코드 9.8 k-1개를 건너뛰고 첫 번째 신호를 출력하는 알고리즘 

// k의 최대값 + 100 , 오버플로를 막기 위해 이보다 큰 값은 구하지 않는다. 
const int M = 1000000000 + 100;
int bino[201][201];

// 필요한 모든 이항 계수를 미리 계산해 둔다.
// running time : O(nm)
void calcBino() {
    memset (bino,0,sizeof(bino));
    for (int i = 0; i <= 200; i++) {
        bino[i][0] = bino[i][i] = 1;
        for (int j = 1; j < i; j++)
            bino[i][j] = min(M,bino[i-1][j-1]+bino[i-1][j]);
    }
}

// skip개를 건너뛰고 출력한다.
// running time : O(n+m)
void generate3 (int n, int m, string s) {
    // base case 
    if (skip < 0 )
        return;
    // base case 
    if (n == 0 && m == 0) {
        if (skip == 0)
            cout << s < endl;
        --skip;
        return ;
    }

    // 현재 상태의 모든 경우의 수 계산 (bino[n+m][n]) 후, skip과 비교하여 
    // 현재 상태 안에 답이 존재하는지 확인 
    if (bino[n+m][n] <= skip) {
        skip -= bino[n+m][n];
        return;
    }
    if (n > 0) generate3(n-1,m,s+"-");
    if (m > 0) generate3(n,m-1,s+"o");
}

// 코드 9.9 k번째 신호를 계산하는 알고리즘 (간결한 코드)

// n개의 -,m개의 o로 구성된 신호 중 skip개를 건너뛰고 만들어지는 신호를 반환한다. 
string kth (int n, int m, int skip) {
    // n == 0인 경우 나머지 부분은 전부 o일 수 밖에 없다.
    if (n == 0)
        return string(m,'o');

    // -를 하나 선택한 경우 그 안에 답이 존재할 경우 
    if ( skip < bino[n+m-1][n-1])
        return "-" + kth(n-1,m,skip);

    return "o" + kth(n,m-1,skip-bino[n+m-1][n-1]);
}




