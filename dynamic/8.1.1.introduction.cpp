
// dynamic programming 
// 최적화 문제를 연구하는 수학 이론에서 았으며, 전산학 용어랑 상관 X
// overlapping problem을 메모리에 저장하여 중복 계산을 없애느 패러다임 

// 예 : 이항 계수 계산 

// 재귀 호출을 이용한 이항 계수의 계산 
int bino(int n, int r) {
    // base case : n=r (모든 원소를 다 고르는 경우) 혹은 r = 0 (고를 원소가 없는 경우)
    if (r == 0 || n == r) return 1;
    return bino(n-1, r-1) + bino(n-1, r);
}

// 메모이제이션을 이용한 이항 계수의 계산 
// memoization - 한번 계산한 값을 저장해 뒀다 재활용하는 최적화 기법 
// -1로 초기화 해둔다.
int cache[30][30];
int bino2(int n, int r) {
    // base case 
    if (r == 0 || n == r) return 1;
    // -1이 아니라면 한 번 계산했던 값이니 곧장 반환 
    if (cache[n][r] != -1)
        return cache[n][r];
    // 직접 계산한 뒤 배열에 저장 
    return cache[n][r] = bino2(n-1, r-1) + bino2(n-1, r);
}

// 메모이제이션을 적용할 수 있는 경우 
// 함수의 반환 값이 그 입력 값만으로 결정되는지의 여부를 참조적 투명성 (referential transparency)
// 입력이 고정되어 있을떄 그 결과가 항상 같은 함수 : 참조적 투명성 함수 (referential transparency function)

// 메모이제이션 구현 패턴 
// 전부 -1로 초기화해 둔다.
int cache[2500][2500];
// a와 b는 각각 [0,2500) 구간 안의 정수 
// 반환 값은 항상 int형 안에 들어가는 음이 아닌 정수.
int someObscureFunction(int a, int b) {
    // bas case를 처음에 처리한다.
    if (...) return ..;
    // (a,b)에 대한 답을 구한 적이 있으면 곧장 반환
    int* ret = &cache[a][b];
    if (ret != -1)
        return *ret;
    // 여기에서 답을 계산한다.
    
    return *ret;
}

int main() {
    // memset()을 이용해 cache 배열을 초기화한다.
    memset(cache,-1,sizeof(cache));
}

// 메모이제이션의 시간 복잡도 
// 상한 : (존재하는 부분 문제의 수(중복 제거)) * (한 부분 문제를 풀 때 필요한 반목문의 수행 횟수)

