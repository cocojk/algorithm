/*
문제

유명한 정렬 알고리즘인 삽입 정렬은 정렬된 부분 배열을 유지하며 이 배열에 새 원소를 삽입해 나가는 식으로 동작합니다. 주어진 정수 배열 A를 정렬하는 삽입 정렬의 구현은 다음과 같습니다.

void insertionSort(vector<int>& A) {
  for(int i = 0; i < A.size(); ++i) {
    // A[0..i-1] 에 A[i] 를 끼워넣는다
    int j = i;
    while(j > 0 && A[j-1] > A[j]) {
      // 불변식 a: A[j+1..i] 의 모든 원소는 A[j] 보다 크다.
      // 불변식 b: A[0..i] 구간은 A[j] 를 제외하면 정렬되어 있다.
      swap(A[j-1], A[j]);
      --j;
    }
  }
}
삽입 정렬은 A[0..i-1] 이 정렬된 배열일 때, A[i] 를 적절한 위치를 만날 때까지 왼쪽으로 한칸씩 움직입니다. 예를 들어 A={5,1,4,3,2} 의 삽입 정렬은 다음과 같이 이루어집니다.

A	비고
5 1 4 3 2	초기 상태
1 5 4 3 2	1을 왼쪽으로 1칸 옮김
1 4 5 3 2	4를 왼쪽으로 1칸 옮김
1 3 4 5 2	3을 왼쪽으로 2칸 옮김
1 2 3 4 5	2를 왼쪽으로 3칸 옮김
1부터 N까지의 자연수가 한 번씩 포함된 길이 N 인 수열 A[] 를 삽입 정렬했습니다. 원래 수열은 알 수 없지만, 그 과정에서 각 원소가 왼쪽으로 몇 칸이나 이동했는지를 알고 있습니다. 예를 들어, 위 예제에서 각 위치에 있는 값들이 움직인 칸수를 표현하면 {0,1,1,2,3} 이 됩니다. 이 때 원래 수열을 찾아내는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 원 배열의 길이 N (1 <= N <= 50000) 이 주어집니다. 그 다음 줄에 N 개의 정수로 A의 각 위치에 있던 값들이 움직인 칸수가 주어집니다. A 는 1부터 N 까지의 정수를 한 번씩 포함합니다.

입력의 양이 많으므로 가능한 빠른 입력 함수를 사용하는 것이 좋습니다.

출력

각 테스트 케이스마다 재구성한 A[] 를 한 줄에 출력합니다.

예제 입력

2
5
0 1 1 2 3
4
0 1 2 3
예제 출력

5 1 4 3 2
4 3 2 1
*/

/* 해법 : 
 * 접근 방식 : 
 * 결정적 사항 : treap 활용 
 * 오답 원인 : 
 */


#include <stdio.h>
#include <stdlib.h>
#include <utility>

using namespace std;

struct Node
{
	int key;
	int priority;
	int size;
	Node* left,*right;
	Node(const int key) : key(key),priority(rand()),size(1),left(NULL),right(NULL)
	{
	}

	void setLeft(Node* newLeft)
	{
		left = newLeft;
		calcSize();
	}

	void setRight(Node* newRight)
	{
		right = newRight;
		calcSize();
	}

	void calcSize()
	{
		size=1;
		if(left)
			size += left->size;
		if(right)
			size += right->size;
	}
};

typedef pair<Node*,Node*> NodePair;
int array[50000];
int A[50000];
int N;
NodePair split(Node* root,int key);
Node* insert(Node* root,Node* node);
Node* merge(Node* a,Node* b);
Node* erase(Node* root,int key);
int countLessThan(Node* root,int key);
void solve();
Node* kth(Node* root,int k);
// NodePair (key보다 낮은값,key보다 높은값)
NodePair split(Node* root,int key)
{
	if(root==NULL)
		return NodePair(NULL,NULL);
	if(root->key>key)
	{
		NodePair temp = split(root->left,key);
		root->setLeft(temp.second);
		return NodePair(temp.first,root);
	}

	NodePair temp = split(root->right,key);
	root->setRight(temp.first);
	return NodePair(root,temp.second);
}

Node* insert(Node* root,Node* node)
{
	if(root==NULL)
		return node;
	if(node->priority>root->priority)
	{
		NodePair temp = split(root,node->key);
		node->setRight(temp.second);
		node->setLeft(temp.first);
		return node;
	}
	else if(node->key<root->key)
		root->setLeft(insert(root->left,node));
	else 
		root->setRight(insert(root->right,node));
	return root;
}

Node* merge(Node* a,Node* b)
{
	if(a==NULL)
		return b;
	if(b==NULL)
		return a;
	
	if(a->priority>b->priority)
	{
		a->setRight(merge(a->right,b));
		return a;
	}

	b->setLeft(merge(a,b->left));
	return b;
}

Node* erase(Node* root,int key)
{
	if(root==NULL)
		return NULL;
	if(root->key==key)
	{
		Node* temp = merge(root->left,root->right);
		delete root;
		return temp;
	}

	if(key<root->key)
		root->setLeft(erase(root->left,key));
	else 
		root->setRight(erase(root->right,key));
	return root;
}

Node* kth(Node* root,int k)
{
	int leftSize=0;
	if(root->left!=NULL)
		leftSize = root->left->size;
	if(k<=leftSize)
		return kth(root->left,k);
	if(k==leftSize+1)
		return root;
	return kth(root->right,k-leftSize-1);
}

int countLessThan(Node* root,int key)
{
	if(root==NULL)
		return 0;
	if(root->key>=key)
		return countLessThan(root->left,key);
	int ls = (root->left? root->left->size:0);
	return ls + 1 + countLessThan(root->right,key);
}


void solve()
{
	int offset,i,tempvalue;
	Node* root =NULL;
	Node* temp;
	for(i=0;i<N;i++)
		root = insert(root,new Node(i+1));
	for(i=N-1;i>=0;i--)
	{
		temp = kth(root,i-array[i]+1);
		A[i]=temp->key;
		root = erase(root,temp->key);
	}

	for(i=0;i<N;i++)
		printf("%d ",A[i]);
	puts("");
}

int main(void)
{
	int testcase;
	int i;
	scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d",&N);
		for(i=0;i<N;i++)
		{
			scanf("%d",&array[i]);
		}

		solve();
	}
}