
// 1. 지수시간 동적 계획법 
// 배열 대신 정수로 집합을 표현하면 이것을 곧장 배열의 인덱스로 쓸 수 있다.

// 2. 에라토스테네스의 체 
// 에라토스테네스의 체는 굉장히 빠르게 동작하기 때문에, 수행 범위를 늘릴 때 부담이 되는 것은 수행시간 보다는 메모리였다.
// 체를 구현할 때 범위 내의 각 정수가 지워졌는지 여부를 저장해야 하는데, 불린 값 배열 대신 비트마스크를 이용 

// 3. 15퍼즐 상태 표현하기 
// 표현해야 하는 값의 범위가 작을때는 2비트씩, 3비트식 묶어서 배열로 쓸 수 있다. 
// 29.6절에서 예제로 다루는 15퍼즐의 경우 상태는 0부터 15까지의 숫자가 들어 있는 4 * 4 크기의 배열로 표현할 수 있었다.
// 각각의 숫자를 4빝로 표현하고 16개의 숫자가 있기 때문에 비트마스크를 사용하면 이 배열 전체를 64비트 정수 하나로 표현할 수 있다. 

// 코드 16.2 64비트 부호 없는 정수를 [0,15] 범위의 정수 16개를 담는 배열로 사용하기 
typdef unsigned long long uint64;

// mask의 index 위치에 쓰인 값을 반환한다.
int get(uint64 mask, int index) {
    return (mask >> (index << 2)) &15;
}

// mask의 index 위치를 value로 바꾼 결과를 반환한다.
uint64 set(uint64 mask, int index, uint64 value) {
    return mask & ~(15LL << (index <<2)) | (value << (index << 2));
}

// 4. O(1) 우선순위 큐 
// 우선순위 큐 (heap)에 경우 자료 추가/ 삭제 O(lgN)의 시간이 걸린다.
// 만약, 우선순위가 특정 범위로 제한되어 있을 경우 비트 마스크를 이용하면 모든 작업을 O(1)에 할 수 있다.
// 원소의 우선순위가 1이상 140 이하의 정수라고 하면, 140개의 큐를 만들고, 각 큐에 원소가 있는지 여부를 비트 마스크로 표현하면 된다. 

// 5. 극대 안정 집합 
// N(N<=20)개의 화학물질을 운반해야 한다고 한다. 각 화학 물질은 무해하지만, 같이 두었을 때 서로 반응해 폭발하는 물질들이 있다고 한다. 
// 이때 한 상자에 넣어도 폭발하지 않는 물질으 지비합을 안정적이라고 한다. 물질을 하나라도 추가하면 폭발이 일어나는 집합들을 극대 안정 집합(maximal stable set)이라고 할때,
// 극대 안정 집합의 수는 ?

// 7부에서 다루는 그래프의 탐색 알고리즘을 사용해 모든 안정 집합을 만들어나가면 된다.
// 하지만, 이 문제에서는 입력의 크기가 그렇게 크지 않기 때문에 비효율적이라도 짧은 코드를 작성하려고 한다.

// 비트 마스크를 이용해 모든 극대 안정 집합의 수를 세는 함수의 구현 

int n;
// explodes[i]는 i와 같이 두었을 때 폭발하는 물질 집합의 비트 마스크 표현 
int explodes[MAXN];
// 주어진 집합이 안정적인지 확인한다.
bool isStable(int set) {
    for(int i = 0; i < n; i++)
    {
        // 집합에 포함된 i번째 원소와 같이 두었을 때 폭발하는 물질이 set에 있다면 
        if((set & (1<<i) ) && (set & explodes[i]) )
            return false;
    }
    return true;
}

// 모든 극대 안정 집합의 수를 센다.
int countStableSet() {
    int ret = 0;
    // 모든 집합을 만들어 보자 .
    for ( int set = 1; set < (1<<n); set++) {
        // 우선 안정적이 아니라면 셀 필요가 없다.
        if(!isStable(set)) continue;
        // 극대 안정 집합인지 확인하기 위해 넣을 수 있는 다른 물질이 있나 확인한다.
        bool canExtend = false;
        for(int add = 0 ; add < n;add++)
            // add가 집합에 포함되어 있지 않고, set에 add를 넣어도 안정적이라면 
            if((set & (1<<add)) == 0 && (explodes[add] & set) == 0) {
                canExtend = true;
                break;
            }
        if(!canExtend)
            ++ret;
    }
    return ret;
}



