
// traversal - 포함되어 있는 자료를 전부 순회하는 것 

// 코드 21.2 트리를 순회하며 모든 노드에 포함된 값을 출력하기 
// running time : O(N)
// 주어진 트리의 각 노드에 저장된 값을 모두 출력한다.
void printLabels (TreeNode* root) {
    // 루트에 저장된 값을 출력한다.
    cout << root->label << endl;
    // 각 자손들을 루트로 하는 서브트리에 포함된 값들을 재귀적으로 출력한다.
    for (int i = 0; i < root->children.size(); i++)
        printLabels(root->children[i]);
}

// 코드 21.3 순회를 이용해 트리의 높이를 계산하기 
// running time : O(N)
// root를 루트로 하는 트리의 높이를 구한다.
int height (TreeNode* root) {
    int h = 0;
    for (int i = 0; i < root->children.size(); i++)
        h = max(h,1+height(root->children[i]));
    return h;
}


