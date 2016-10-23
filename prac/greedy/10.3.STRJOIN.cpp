
// 허프만 코드 (huffman code)
// 가변 길이 인코딩 (variable-length encoding) 테이블을 만드는 방법으로 여러 압축 알고리즘에 사용된다.
// 원문의 각 글자를 서로 길이가 다를 수 있는 비트 패턴으로 바꿈으로써 원문의 길이를 줄이는 방법 
// 즉, 글자들의 출현 빈도가 주어질 떄 예상 길이를 최소화하는 비트 패턴을 만드는 알고리즘 
// ex) L = 0.6 , H = 0.2 , O = 0.1 , E = 0.1 
//                     0.6 + 0.2 + 0.1 + 0.1
//          0.1 + 0.1 + 0.2               L
//   0.1 + 0.1           H
//    O     E
// 탐욕 알고리즘 : 빈도 목록을 유지하는 상태에서, 빈도가 가장 짧은 것들 두개를 뽑은 후 트리를 만든 후, 그 빈도의 합을 다시 빈도 목록에 넣는다. 

/*
   문제

   프로그래밍 언어 C 의 큰 문제점 중 하나는 언어 차원에서 문자열 변수형을 지원하지 않는다는 것입니다. C 에서는 문자 배열로 문자열을 표현하되 \0 (NULL) 로 문자열의 끝을 지정하는데, 이래서는 문자열의 길이를 쉽게 알 수 있는 방법이 없기 때문에 여러 가지 문제가 발생하게 됩니다.

   void strcat(char* dest, const char* src) {
    // dest 의 마지막 위치를 찾는다
     while(*dest) ++dest;
      // src 를 한 글자씩 dest 에 옮겨 붙인다
       while(*src) *(dest++) = *(src++);
        // 문자열의 끝을 알리는 \0 을 추가한다
         *dest = 0;
         }
         이런 문제 중 하나로 문자열을 조작하는 함수들의 동작 시간이 불필요하게 커진다는 것이 있습니다. 앞에 주어진 함수 strcat() 은 문자열 dest 뒤에 src 를 붙이는 함수인데, 실행 과정에서 반복문을 두 문자열의 길이를 합한 만큼 수행해야 합니다. 이 함수를 사용해 두 개의 문자열을 합치는 비용은 두 문자열의 길이의 합이라고 합시다.

         이 함수를 이용해 n 개의 문자열을 순서와 상관없이 합쳐서 한 개의 문자열로 만들고 싶습니다. 순서가 상관 없다는 말은 {al,go,spot} 을 spotalgo 로 합치든 alspotgo 로 합치든 상관 없다는 의미입니다. 그러나 문자열을 합치는 순서에 따라 전체 비용이 달라질 수 있습니다. 예를 들어 먼저 al 과 go 를 합치고 (2+2=4), 이것을 spot 과 합치면 (4+4=8) 총 12 의 비용이 들지만 al 과 spot 을 합치고 (2+4=6) 이것을 다시 go 에 합치면 (6+2=8) 총 14 의 비용이 필요합니다.

         n 개의 문자열들의 길이가 주어질 때 필요한 최소 비용을 찾는 프로그램을 작성하세요.

         입력

         입력의 첫 줄에는 테스트 케이스의 수 c (c <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 문자열의 수 n (1 <= n <= 100) 이 주어지며, 다음 줄에는 n 개의 정수로 각 문자열의 길이가 주어집니다. 각 문자열의 길이는 1,000 이하의 자연수입니다.

         출력

         각 테스트 케이스마다 한 줄에 모든 문자열을 합칠 때 필요한 최소 비용을 출력합니다.

         예제 입력

         3
         3
         2 2 4
         5
         3 1 3 4 1
         8
         1 1 1 1 1 1 1 2
         예제 출력

         12
         26
         27
*/

// 문자열 합치기 문제를 해결하는 탐욕적 알고리즘 
// running time : O(nlgn)

// 문자열들의 길이가 주어질 때 하나로 합치는 최소 비용을 반환한다.
int concat(const vector<int>& lengths) {
    // 최소 큐를 선언한다. 
    priority_queue<int, vector<int>, greater<int> > pq;
    for(int i = 0; i < lengths.size(); i++)
        pq.push(lengths[i]);
    int ret = 0;
    // 원소가 하나 이상 남은 동안 반복한다.
    while(pq.size() > 1) {
        // 가장 짧은 문자열 두 개를 찾아서 합치고 큐에 넣는다.
        int min1 = pq.top();
        pq.pop();
        int min2 = pq.top();
        pq.pop();
        pq.push(min1+min2);
        ret += min1 + min2;
    }
    return ret;
}
