
// segment tree 
// 저장된 자료들을 적절히 전처리해 그들에 대한 질의들을 빠르게 대답할 수 있도록 한다. 
// 흔히 일차원 배열의 특정 구간에 대한 질문을 빠르게 대답하는데 사용한다.
// 예를 들어, 구간의 최소치를 구하는 문제, 어떤 배열 A의 부부 ㄴ구간의 최소치를 구하는 연산을 여러 번 하고 싶다고 한다.
// 예를 들어, A={1,2,1,2,3,1,2,3,4} 라면 [2,4] 구간의 최소치는 1이고 [6,8] 구간의 최소치는 2이다. 
// 이 연산을 구현하는 가장 간단한 알고리즘은 구간이 주어질 때마다 해당 배열을 순회하며 최소치를 찾는 것, 즉 질문 하나에 대답하는데 O(n)의 시간이 걸린다.
// 기본적인 아이디어 : 주어진 배열의 구간들을 표현하는 이진트리를 만드는 것 
// 예제) 배열의 길이가 15인 구간 트리의 각 노드가 표현하는 구간들 
//                                              (0,14)
//                      (0,7)                                           (8,14)
//          (0,3)                   (4,7)                   (8,11)                  (12,14)
//  (0,1)           (2,3)       (4,5)       (6,7)       (8,9)       (10,11)     (12,13)     (14)
//(0)   (1)     (2)     (3)   (4)   (5)  (6)    (7)  (8)    (9)   (10)    (11) (12)   (13)
// 노드마다 해당 구간에 대한 계산 결과를 저장해둔다. 예를 들어 구간의 최소치를 구하는 구간 트리는 해당 구간의 최소치를 각 노드에 저장한다.
// 이런 전처리 과정을 수행해 두면, 어떤 구간 [i,j]가 주어지더라도 이 구간을 구간 트리의 노드에 포함된 구간들의 합집합으로 표현할 수 있다. 
// 예를 들어, 구간 [6,12] 구간은 [6,7] [8,11] [12,12]의 합집합으로 표현가능하다. 

// segment tree의 표현 
// 특정 구간의 최소치를 찾는 문제 (range minimum query, RMQ)
// segment tree는 비교적 '꽉 찬' 이진 트리이다. 따라서 배열로 표현 가능 
// 루트 노드를 배열의 1번 원쏘, 노드 i의 왼쪽 자손과 오른쪽 자손을 각각 2*i와 2*i+1번 원소로 표현 
// 배열의 길이 ?
// 배열의 길이 n이 2의 거듭제곱이라면 이 배열의 길이는 2n이면 충분하다.(정확히 2n-1개 존재, 하지만 루트 index = 1이므로 2n) 다른 경우에는 그렇지 않다.
// 예를 들어 n = 6인 경우 구간 트리를 그려보면 인덱스의 최대 위치가 2n을 초과하는 13이 된다는 사실을 알 수 있다. 
// 1. 배열의 길이를 안전하게 구하려면 가장 가까운 2의 거듭제곱으로 n을 올림한 뒤 2를 곱해야 한다. n=6인 경우 8*2 = 16 
// 2. 4n으로 값을 잡는다. (2n은 가장 가까운 2의 거듭제곱보다 값이 크다.) 

const int INT_MAX = numeric_limits<int>::max();
// 배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현 
struct RMQ {
    
    // 1. init
    // running time : O(n) (각 노드마다 O(1)의 시간이 걸림 배열의 길이는 O(n))

    // 코드 24.1 배열의 구간 최소 쿼리(RMQ) 문제를 해결하는 구간 트리의 초기화 

    // 배열의 길이 
    int n;
    // 각 구간의 최소치 
    vector<int> rangeMin;
    RMQ (const vector<int>& array) {
        n = array.size();
        rangeMin.resize(n*4);
        init(array,0,n-1,1);
    }

    // node 노드가 array[left...right] 배열을 표현할 때
    // node를 루트로 하는 서브트리를 초기화 하고, 이 꾸간의 최소치를 반환한다.
    init init (const vector<int>& array, int left, int right, int node) {
        if (left==right) 
            return rangeMin[node] = array[left];
        int mid = (left+right)/2;
        int leftMin = init(array,left,mid,node*2);
        int rightMin = init(array,mid+1,right,node*2+1);
        return rangeMin[node] = min(leftMin,rightMin);
    }

    // 2. query 
    // query op = 임의의 구간의 최소치를 구하는 연산 
    // query(left,right,node,nodeLeft,nodeRight) = node가 표현하는 범위 [nodeLeft,nodeRight]와 우리가 최소치를 찾기 원하는 구간 [left,right]의 교집합의 최소 원소를 반환한다.
    // 가능한 경우의 수 
    // 1) 교집합이 공집합인 경우 
    // 두 구간은 서로 겹치지 않는다. 따라서 반환 값은 존재하지 않는다. 반환 값이 무시되도록 아주 큰 값을 반환하도록 한다.
    // 2) 교집합이 [nodeLeft,nodeRight]인 경우 
    // [left,right]가 노드가 표현하는 집합을 완전히 포함하는 경우 이 노드에 미리 계산해 둔 최소치를 곧장 반환한다.
    // 3) 이 외의 모든 경우 
    // 두 개의 자손 노드에 대해 query()를 재귀 호출한 뒤, 이 두 값 중 더 작은 값을 택해 반환한다.
    // running time : O(lgN)
    // 대부분의 경우, 자손 노드에 대해 함수 호출 시(3의 경우), 한개는 바로 종료된다. 바로 종료되지 않는 경우는 한 번만 발생한다.
    // 바로 종료 되지 않는 경우는 left nodeLeft mid nodeRight right 인 경우인데, 자식 노드에서는 한쪽 끝은 모두 포함되어 있기 때문이다.
    // 따라서 트리의 바닥까지 최대 두 번만 탐색 가능하므로 running time은 O(lgN)이다.

    // 코드 24.2 RMQ 문제를 푸는 구간 트리에서의 질의 연산의 구현 
    int query (int left, int right, int node, int nodeLeft, int nodeRight) {
        
        // 두 구간이 겹치지 않으면 아주 큰 값을 반환한다. : 무시됨 
        if (right < nodeLeft || nodeRight < left) return INT_MAX;

        // node가 표현하는 범위가 array[left...right]에 완전히 포함되는 경우 
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];

        // 양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
        int mid = (nodeLeft + nodeRight) /2;
        return min (query(left,right,node*2,nodeLeft,mid),query(left,right,node*2+1,nodeRight));
    }

    // query()를 외부에서 호출하기 위한 인터페이스 
    int query (int left, int right) {
        return query(left,right,1,0,n-1);
    }

    // 3. update
    // 전처리를 통해 구간 트리를 생성한 다음에 원래 배열의 값이 바뀐다면?
    // 해당 위치를 포함하는 구간은 트리에 O(lgN)개 존재가능 따라서 이들만 재계산하면 된다. 
    // running time : O(lgN)

    // 코드 24.3 RMQ 문제를 푸는 구간 트리에서 갱신 연산의 구현 
    // array[index] = newValue로 바뀌었을 때 node를 루트로 하는 
    // 구간 트리르 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.
    int update (int index, int newValue, int node, int nodeLeft,int nodeRight) {
        // index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
        if (index < nodeLeft || nodeRight < index)
            return rangeMin[node];

        // 트리의 리프까지 내려온 경우 
        if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
        int mid = (nodeLeft + nodeRight) / 2;
        return rangeMin[node] = min(update(index, newValue, node*2, nodeLeft, mid) , update(index, newValue, node*2+1, mid+1, nodeRight));
    }

    // update()를 외부에서 호출하기 위한 인터페이스 
    int update (int index, int newValue) {
        return update (index, newValue, 1,0,n-1);
    }
};

// 예제 : 특정 구간에서 최소치 두개 찾기 
// 구간이 주어졌을 때 최소치 하나만을 찾는게 아니라 가장 작은 두개의 값을 찾는 문제를 푸는 구간 트리 
// 구간 트리를 사용하려면 두 개의 작은 부분 구간에 대해 계산한 값을 효율적으로 합치는 방법이 있어야 한다.
// 두 개의 자식 구간에 대해 최소치 두 개씩을 찾았다고 하면, 네 개의 값 중에서 가장 작은 두개를 선택하면 된다.
// 구간의 길이가 1밖에 안될 때는 해당 구간에 포함된 숫자와 아주 큰 값을 반환하면 된다. 

// 예제 : 정렬된 수열의 특정 구간에서 최대 출현 빈도 계산 
// 최대 출현 빈도 : 이 수열에서 가장 자주 등장하는 수의 출현 횟수  
// 예를 들어, {1,1,1,2}의 최대 출현 빈도 3 , {1,2,3}의 최대 출현 빈도 1

// 왼쪽 구간의 최대 출현 빈도와 오른쪽 구간의 최대 출현 빈도 중 더 큰 것을 취한다? - NO! 반례 존재 

// 예외
// 1. 두 구간에서 가장 많이 출현하는 수가 같은 경우 
// 왼쪽 부분 구간 {1,2,2,2} , 오른쪽 부분 구간 {2,2,2,3}인 경우 
// 2. 두 구간을 이어보면 가장 많이 출현하는 수가 바뀌는 경우 
// 왼쪽 부분 구간 {1,1,1,2,2} 오른쪽 부분 구간 {2,2,3,3,3}인 경우 양쪽 부분 구간에서 가장 많이 출현하는 수는 각각 1과 3이지만, 
// 두 구간을 합쳐 보면 2가 네 번으로 가장 많이 출현한다. 

// 추가 정보도 계산해서 같이 반환할 필요가 있다.

// 코드 24.4 숫자의 최대 출현 횟수 문제의 두 개의 답을 합치기 

// 부분 구간의 계산 결과 
struct RangeResult {
    // 이 구간의 크기 
    int size;
    // 가장 자주 등장하는 숫자의 출현 횟수 
    int mostFrequent;
    // 왼쪽 끝 숫자와 오른쪽 끝 숫자의 출현 횟수 
    int leftNumber, leftFreq;
    // 오른쪽 끝 숫자와 오른쪽 끝 
    int rightNumber, rightFreq;
};

// 왼쪽 부분 구간의 계산 결과 a, 오른쪽 부분 구간의 계산 결과 b를 합친다.
RangeResult merge(const RangeResult& a, const RangeResult& b) {
    RangeResult ret;
    // 구간의 크기는 쉽게 계산 가능 
    ret.size = a.size + b.size;
    // 왼쪽 숫자는 a.leftNumber로 정해져 있다.
    // 왼쪽 부분 구간이 전부 a.leftNumber인 경우만 별도로 처리 
    // 예: [1,1,1,1]과 [1,2,2,2]를 합칠 때
    ret.leftNumber = a.leftNumber;
    ret.leftFreq = a.leftFreq;
    if (a.size == a.leftFreq && a.leftNumber == b.leftNumber)
        ret.leftFreq += b.leftFreq;
    
    // 오른쪽 끝 숫자도 비슷하게 계산하자
    ret.rightNumber = b.rightNumber;
    ret.rightFreq = b.rightFreq;
    if (b.size == b.rightFreq && a.rightNumber == b.rightNumber)
        ret.rightFreq += a.rightFreq;

    // 기본적으로 가장 많이 출현하는 수의 빈도수는 둘 중 큰쪽으로 
    ret.mostFrequent = max(a.mostFrequent,b.mostFrequent);
    // 왼쪽 구간의 오른쪽 끝 숫자와 오른쪽 구간의 왼쪽 끝 숫자가 합쳐지는 경우 
    // 이 두 수를 합쳤을 때 mostFrequent보다 커지는지 확인한다.
    if (a.rightNumber == b.leftNumber)
        ret.mostFrequent = max(ret.mostFrequent,a.rightFreq+b.leftFreq);
    return ret;
}

