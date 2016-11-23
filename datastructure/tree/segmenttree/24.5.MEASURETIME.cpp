#include <vector>
#include <iostream>

using namespace std;

struct FenwickTree {
    vector <int> tree;
    FenwickTree(int n) : tree(n+1) {}
    // A[0..pos]의 부분합을 구한다. 
    int sum (int pos) {
        // 인덱스가 1부터 시작한다고 생각하자.
        ++pos;
        int ret = 0;
        while (pos >0) {
            ret += tree[pos];
            // 다음 구간을 찾기 위해 최종 비트를 지운다.
            pos &= (pos-1);
        }

        return ret;
    }

    // A[pos]에 val을 더한다.
    void add (int pos, int val) {
        ++pos;
        while (pos < tree.size()) {
            tree[pos] += val;
            pos += (pos&-pos);
        }
    }
};

// 1. 펜윅 트리를 이용해 풀기 
int solve (void)
{
    int n,temp;
    cin >> n;
    FenwickTree tree(1000000);
    long long int ret = 0;
    for (int i =0; i <n; i++)
    {
        cin >>temp;
        ret += tree.sum(999999) -tree.sum(temp);
        tree.add(temp,1);
    }
    return ret;
}

// 2. 구간 트리를 이용해 풀기 
// 펜윅트리로 풀리기 때문에 가능. 

// 3. 이진 검색 트리를 이용해 풀기 
// 트리에 포함된 주어진 키 X보다 작은 키가 몇개나 있는지 파악하는 연산은 O(lgN) 시간에 할 수 있다.
// 따라서 running time : O(NlgN)

// 코드 24.9 삽입 정렬 시간 재기 문제를 트립으로 해결하기 

// 만들었던 트리를 지운다.
void deleteTree (Node* node) {
    if (node == NULL)
        return;
    deleteTree (node->left);
    deleteTree (node->right);
    delete node;
}

// 트립을 이용해 문제를 해결한다.
long long countMoves2 (const vector<int>& A) {
    Node* root = NULL;
    long long ret = 0;
    for (int i = 0; i < A.size(); i++) {
        ret += i - countLessThan(root,A[i]+1);
        root = insert(root,new Node(A[i]));
    }
    deleteTree(root);
    return ret;
}

// 4. 병합 정렬을 이용해 풀기 
// 주어진 수열의 반전(inversion)의 수를 세는 것 inversion이란 더 큰 수가 앞에 있고 작은 수가 뒤에 있는 쌍을 나타낸다.
// 삽입 정렬 과정에서 숫자를 한 번 옮길 때마다 반전이 정확히 하나씩 줄어든다.
// 반전의 수를 세는 좋은 방법 - 병합 정렬 

// 코드 24.10 삽입 정렬 시간 재기 문제를 병합 정렬을 이용해 풀기 

// A[left..right]를 재귀적으로 병합 정렬하고,
// 해당 범위 내의 inversion의 수를 반환한다.
long long conutMoves3 (vector<int>& A, int left, int right) {
    // base case : 구간의 길이가 1인 경우 
    if (left == right) 
        return 0;
    // 반으로 나눠서 부분 정복 
    int mid = (left+right)/2;
    long long ret = countMoves3(A,left,mid) + countMoves3(A,mid+1,right);
    
    // 임시 배열에 정렬된 두 부분 배열을 합친다.
    vector<int> tmp (right-left+1);
    int tmpIndex = 0, leftIndex = left, rightIndex =mid+1;
    while (leftIndex <= mid || rightIndex <= right) {
        if (leftIndex <= mid (rightIndex > right || A[leftIndex] <= A[rightIndex])) {
            temp[tmpIndex++] = A[leftIndex++];
        }
        else {
            // A[rightIndex]는 왼쪽 부분 배열에 남아 있는 모든 수보다 작다.
            // 이 수들만큼 inversion을 더해준다.
            ret += mid - leftIndex + 1;
            temp[tmpIndex++] = A[rightIndex++];
        }
    }

    // tmp에 합친 결과를 A로 다시 복사한다.
    for (int i = 0; i < tmp.size(); i++)
        A[left+1] = tmp[i];
    return ret;
}


int main (void)
{
    ios::sync_with_stdio(false);
    int testcase;
    cin >> testcase;

    while (testcase--)
    {
        cout << solve()<<'\n';
    }
}
