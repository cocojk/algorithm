
// n개의 원소 중 m개를 고르는 모든 조합을 찾는 알고리즘 
// 1. for문 사용 골라야할 원소의 수가 입력에 따라 달라질 경우 사용할 수 없다.
for(int i = 0; i < n; i++)
    for(int j = i+1; j < n; j++)
        for(int k = j+1 ; k < n; k++)
            for(int l = k+1; l < n; l++)
                cout << i << " " << j << " " << k << " " << l << endl;


// 2. recursion
// n : 전체 원소의 수 
// picked : 지금까지 고른 원소들의 번호 
// toPick : 더 고를 원소의 수 
// 일 떄, 앞으로  topick개의 원소를 고르는 모든 방법을 출력한다.
void pick(int n, vector<int>& picked, int toPick) {
    // base case 
    if (toPick==0)
    {
        printPicked(picked);
        return;
    }
    // 고를 수 있는 가장 작은 번호를 계산한다.
    int smallest = picked.empty() ? 0 : picked.back() + 1;
    // 이 단계에서 원소 하나를 고른다 . 
    for(int next = smallest; next < n; next++) {
        picked.push_back(next);
        pick(n,picked,toPick-1);
        picked.pop_back();
    }
}

