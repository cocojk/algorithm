
// merge & quick sort
// divide and conquer 기반 알고리즘 

// 1. merge 
// 주어진 수열을 가운데에서 쪼개 비슷한 크기의 수열 두개로 만든 뒤 이들을 재귀호출을 이용해 각각 정렬한다. 그 후, 정렬된 배열을 하나로 merge한다.
// divide - O(1)
// merge - O(n)
// running time - O(nlgn)

// 2. quick
// 배열을 단순하게 가운데에서 쪼개는 대신, 병합 과정이 필요 없도록 한쪽의 배열에 포함된 수가 다른 쪽 배열의 수보다 항상 작도록 배열을 분활한다. 
// divide - O(n)
// merge - O(1)
// running time - O(nlgn) (average) O(n^2) (worst)


