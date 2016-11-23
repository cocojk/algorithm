/*   
문제

한 수열의 중간값(median)은 이 수열을 정렬했을 때 가운데 오는 값입니다. 예를 들어 {3,1,5,4,2}를 정렬했을 때 가운데 오는 값은 3이지요. 수열의 길이가 짝수일 때는 가운데 있는 두 값 중 보다 작은 것을 수열의 중간값이라고 정의하도록 합시다.

한 수열의 중간값은 수열에 새로운 수가 추가될 때마다 바뀔 수 있습니다. 텅 빈 수열에서 시작해서 각 수가 추가될 때마다 중간값을 계산하는 프로그램을 작성하세요. 예를 들어 3, 1, 5, 4, 2 순서대로 숫자가 추가될 경우 수열의 중간값은 3, 1, 3, 3, 3 순서로 변화합니다.

입력 생성

입력의 크기가 큰 관계로, 이 문제에서는 수열을 입력받는 대신 다음과 같은 식을 통해 프로그램 내에서 직접 생성합니다.

A[0] = 1983
A[i] = (A[i-1] * a + b) % 20090711
a와 b는 입력에 주어지는 상수입니다. 이 문제의 해법은 입력을 생성하는 방식과는 아무 상관이 없습니다.

입력

입력 파일의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 20)가 주어지고, 그 후 C줄에 각 3개의 정수로 수열의 길이 N (1 <= N <= 200,000), 그리고 수열을 생성하는 데 필요한 두 정수 a , b (0 <= a,b <= 10000) 가 주어집니다.

출력

각 테스트 케이스마다 한 줄에 N개의 중간값의 합을 20090711로 나눈 나머지를 출력합니다.

예제 입력

3
10 1 0
10 1 1
10000 1273 4936 
예제 출력

19830 
19850 
2448920
 */

/* 해법 : head 응용
 * 접근 방식 : min heap과 max heap을 나눈후 max heap | min heap 인 경우 min heap의 top이 max heap의 top보다 큰 경우 max heap의 전체 요소는 min heap의 전체 요소보다 작다는 사실을 이용하여 max heap의 top의 median이 되도록 적절하게 heap을 유지시키는 것 !
 * 결정적 사항 : 반 씩 나누고, optimal 증명 방법 귀류법 중요 !
priority_queue <int> maxHeap;
	priority_queue <int,vector<int>,greater<int> > minHeap; 초기화법 !
 * 오답 원인 :  
 */

#include <stdlib.h>
#include <queue>
#include <utility>
#include <stdio.h>
#include <functional>

using namespace std;
struct RNG {
	int seed,a,b;
	RNG(int ina,int inb): a(ina),b(inb),seed(1983){}
	int next()
	{
		int ret = seed;
		seed = ((seed*(long long)a)+b)%20090711;
		return ret;
	}
};

typedef int KeyType;
// 트립의 한 노드를 저장한다. 
struct Node {
    // 노드에 저장된 원소 
    KeyType key;
    // 이 노드의 우선순위 (priority)
    // 이 노드를 루트로 하는 서브트리의 크기 (size)
    int priority, size;
    // 두 자식 노드의 포인터 
    Node* left, * right;
    // 생성자에서 난수 우선순위를 생성하고 size와 left/right를 초기화한다. 
    Node (const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}

    void setLeft (Node* newLeft) { left = newLeft; calcSize(); }
    void setRight (Node* newRight) { right = newRight; calcSize(); }
    // size 멤버를 갱신한다. 
    void calcSize() {
        size = 1;
        if (left) size += left->size;
        if (right) size += right->size;
    }
};

// 코드 22.4 트립에서의 노드 추가와 트립 쪼개기 연산의 구현 

typedef pair<Node*, Node*> NodePair;
// root를 루트로 하는 트립을 key 미만의 값과 이상의 값을 갖는
// 두 개의 트립으로 분리한다.
NodePair split (Node* root, KeyType key) {
    if (root == NULL) return NodePair(NULL,NULL);

    // 루트가 key 미만이면 오른쪽 서브트리를 쪼갠다.
    if ( root->key < key) {
        NodePair temp = split(root->right,key);
        root->setRight(temp.first);
        return NodePair(root,temp.second);
    }

    // 루트가 key 이상이면 왼쪽 서브트리르 쪼갠다.
    NodePair temp = split(root->left,key);
    root->setLeft(temp.second);
    return NodePair(temp.first,root);
}


// root를 루트로 하는 트립에 새 노드 node를 삽입한 뒤 결과 트립의 
// 루트를 반환한다.
Node* insert (Node* root, Node* node) {
    if (root==NULL) return node;

    // node가 루트를 대체해야 한다. 해당 서브트리를 바능로 잘라 
    // 각각 자손으로 한다.
    if (root->priority < node->priority) {
        NodePair temp = split (root,node->key);
        node->setLeft(temp.first);
        node->setRight(temp.second);
        return node;
    }
    else if (node->key < root->key)
        root->setLeft(insert(root->left,node));
    else 
        root->setRight(insert(root->right,node));
    return root;
}

// 새 값 추가 : root = insert(root,new Node(value));

// 코드 22.5 트립에서 노드의 삭제와 합치기 연산의 구현 

// a와 b가 두 개의 트립이고, max(a) < min(b)일 때 이 둘을 합친다. 
Node* merge (Node* a, Node* b) {
    if (a==NULL) return b;
    if (b==NULL) return a;

    if (a->priority < b->priority) {
        b->setLeft(merge(a,b->left));
        return b;
    }
    a->setRight(merge(a->right,b));
    return a;
}

// root를 루트로 하는 트립에서 key를 지우고 결과 트립의 루트를 반환한다.
Node* erase (Node* root, KeyType key) {
    if (root == NULL) return root;
    // root를 지우고 양 서브트리를 합친 뒤 반환한다. 
    if (root->key == key) {
        Node* ret = merge(root->left, root->right);
        delete root;
        return ret;
    }
    if(key < root->key)
        root->setLeft(erase(root->left,key));
    else
        root->setRight(erase(root->right,key));
    return root;
}

// 코드 22.6 트립에서 k번째 원소를 찾는 알고리즘의 구현 

// root를 루트로 하는 트리 중에서 k번째 원소를 반환한다. 
Node* kth (Node* root, int k) {
    // 왼쪽 서브트리의 크기를 우선 계산한다. 
    int leftSize = 0;
    if (root->left != NULL) leftSize = root->left->size;
    if (k <= leftSize) return kth(root->left,k);
    if (k == leftSize+1) return root;
    return kth(root->right,k-leftSize-1);
}

// 코드 22.7 트립에서 X보다 작은 원소의 수를 찾는 알고리즘의 구현 

// key보다 작은 키 값의 수를 반환한다. 
int countLessThan (Node* root, KeyType key) {
    if (root == NULL) return 0;
    if (root-> key >= key)
        return countLessThan(root->left,key);
    int ls = (root->left ? root->left->size : 0);
    return ls + 1 + countLessThan(root->right,key);
}

   
int solve(int n,RNG* rng);
int solve(int n,RNG* rng)
{
	priority_queue <int> maxHeap;
	priority_queue <int,vector<int>,greater<int> > minHeap;
	int ret=0;
	int cnt;

	for(cnt=1;cnt<=n;cnt++)
	{
		if(maxHeap.size()==minHeap.size())
			maxHeap.push(rng->next());
		else 
			minHeap.push(rng->next());

		if((!minHeap.empty())&&(!maxHeap.empty())&&(minHeap.top()<maxHeap.top()))
		{
			int a = maxHeap.top();
			int b = minHeap.top();
			maxHeap.pop();
			minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}

		ret =(ret+maxHeap.top())%20090711;
	}

	return ret;
}

int solve2 (int n, RNG* rng) 
{
    int ret = 0;
    Node* root = NULL;
    for (int i = 0; i < n; i++)
    {
        root = insert(root,new Node(rng->next()));
        ret = (ret + kth(root,i/2+1)->key) % 20090711;
    }

    return ret;
}
        
    

int main(void)
{
	int testcase;
	scanf("%d",&testcase);

	while(testcase--)
	{
		int n,a,b;
		scanf("%d %d %d",&n,&a,&b);
		RNG* temp = new RNG(a,b);
		printf("%d\n",solve2(n,temp));
		delete temp;
	}
}




