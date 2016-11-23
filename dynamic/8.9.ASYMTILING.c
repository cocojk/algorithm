

/*   
     그림과 같이 2 * n 크기의 직사각형을 2 * 1 크기의 타일로 채우려고 합니다. 타일들은 서로 겹쳐서는 안 되고, 90도로 회전해서 쓸 수 있습니다. 단 이 타일링 방법은 좌우 대칭이어서는 안 됩니다. 위 그림은 2 * 5 크기의 직사각형을 채우는 비대칭 타일링 방법 6가지를 보여줍니다. 다음의 2가지는 좌우대칭이기 때문에 세지 않습니다.


     n 이 주어질 때 가능한 비대칭 타일링 방법의 수를 계산하는 프로그램을 작성하세요. 방법의 수는 매우 클 수 있으므로, 1,000,000,007 로 나눈 나머지를 출력합니다.

     입력

     입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다. 그 후 각 줄에 사각형의 너비 n (1 <= n <= 100) 이 주어집니다.

     출력

     각 테스트 케이스마다 한 줄에 비대칭 타일링 방법의 수를 1,000,000,007 로 나눈 나머지를 출력합니다.

     예제 입력

     3
     2
     4
     92
     예제 출력

     0
     2
     913227494

 */

/* 해법 : divide and conquer
 * 접근 방식 : 
 * 결정적 사항 : 반 씩 나누고, optimal 증명 방법 귀류법 중요 !
 * 오답 원인 :  
 */

#include <stdio.h>
#include <string.h>

const int MOD =  1000000007;
int memoization[101];

int tiling(int width) {

    if(width==0)
        return 0;

	if(width<=1)
		return 1;

    if(width==2)
        return 2;
	int* ret = &memoization[width];
	if(*ret!=-1)
		return *ret;

	return *ret = (tiling(width-2)+tiling(width-1))%MOD;
}

int asymmetric(int width) {
	if(width%2==1)
		return (tiling(width)-tiling(width/2)+MOD)%MOD;
	int ret = tiling(width);
	ret = (ret - tiling(width/2) + MOD)%MOD;
	ret = (ret - tiling(width/2-1) + MOD)%MOD;
	return ret;
}

// 직접 비대칭 타일링의 수를 세는 동적 계획법 알고리즘 
int cache2[101];
// 2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
int asymmetric2(int width) {
    // base case : width가 2 이하인 경우 
    if(width <= 2) return 0;
    // memoization 
    int* ret = &cache2[width];
    if(*ret != -1)
        return *ret;
    // 양끝을 | 로 세우기 
    *ret = asymmetric2(width-2) % MOD;
    // 양끝을 = 로 세우기 
    *ret = (*ret + asymmetric2(width-4)) % MOD;
    // 양끝을 |  , = 로 세우기 (해당 연산 후 비대칭이 된다.)
    *ret = (*ret + tiling(width-3)) % MOD;
    // 양끝을 =  , | 로 세우기 (해당 연산 후 비대칭이 된다.)
    *ret = (*ret + tiling(width-3)) % MOD;
    return *ret;
}

int main(void)
{
    int testcase;

    scanf("%d",&testcase);
    memset(memoization,-1,sizeof(memoization));

    while(testcase--)
    {
        int width;
        scanf("%d",&width);
        printf("%d\n",asymmetric(width));
    }

}



