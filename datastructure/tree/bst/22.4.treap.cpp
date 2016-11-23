
// balanced bst : treap
// 표준 라이브러리는 X보다 작은 원소의 수를 계산하거나 k번째 원소를 찾는 연산을 지원하지 않는다.
// 따라서 이런 연산이 꼭 필요할 때는 결국 bst를 직접 구현해야 한다.
// AVL 트리, 레드 브랙 트리는 구현이 까다롭기 때문에 프로그래밍 대회에서 부적합 -> 비교적 구현 쉬운 treap 이용!

// define 
// 입력이 특정 순서로 주어질 때 그 성능이 떨어진다는 이진 검색 트리의 단점을 해결하기 위해 고안된 일종의 랜덤화된 bst
// 트리의 형태가 원소들의 추가 순서에 따라 결정되지 않고 난수에 의해 임의대로 결정된다. 
// 이와 같은 속성을 유지하기 위해 트립은 새 노드가 추가될 때마다 해당 노드에 priority를 부여
// 이 우선순위는 원소의 대소 관계나 입력된 순서와 아무런 상관없이 난수를 통해 생성 


// 조건 
// 1. bst 조건 : 모든 노드에 대해 왼쪽 서브트리에 있는 노드들의 원소는 해당 노드의 원소보다 작고 오른쪽 서브트리에 있는 노드들의 원소는 해당 노드의 원소보다 크다. 
// 2. heap 조건 : 모든 노드의 우선순위는 각자의 자식 노드보다 크거나 같다. 
// 우선순위가 높을수록 위에 간다는 제약을 추가하면 결과적으로 우선순위 순서대로 노드를 추가한 이진 검색 트리가 된다.
//                      5 (65)
//          2(49)                   7(25)
// 1(37)            4(31)       6(14)
//              3(13)

// 트리의 높이 
// 이와 같은 랜덤화가 의미가 있을려면 트리의 높이의 기대치가 O(N)보다 작아야한다.
// prove: 노드 수의 기대치가 O(lgN) -> 한 단계 내려갈 때마다 후보가 되는 원소의 수가 선형으로 줄어드는 것이 아니라 지수적으로 줄어든다는 것을 보이면 된다.
// 루트가 갖는 원소가 N개의 원소 중에서 r번째로 작은 원소라고 하면, 왼쪽 서브트리에는 r-1개, 오른쪽 서브트리에는 N-r개의 노드가 존재 
// 각 원소가 우리가 원하는 원소일 확률은 동일하다고 가정하면, 왼쪽 서브트리에 있을 확률 r-1/N,루트일 확률은 1/N, 오른쪽 서브트리에 있을 확률은 N-r/N
// 다음 단계 후보의 기대치 : (r-1)*(r-1/N) + 1*(1/N) + (N-r)*(N-r/N)
// 모든 r에 대해서 평균치를 내면 : ~ 2/3*N 
// 따라서, 지수적으로 감소한다는 것을 알 수 있다. 

// implementation

// 코드 22.3 트립의 노드를 표현하는 객체의 구현 

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

   
