#include <stdio.h>
#include <string.h>

/*
   문제

   와일드카드는 다양한 운영체제에서 파일 이름의 일부만으로 파일 이름을 지정하는 방법이다. 와일드카드 문자열은 일반적인 파일명과 같지만, * 나 ? 와 같은 특수 문자를 포함한다.

   와일드카드 문자열을 앞에서 한 글자씩 파일명과 비교해서, 모든 글자가 일치했을 때 해당 와일드카드 문자열이 파일명과 매치된다고 하자. 단, 와일드카드 문자열에 포함된 ? 는 어떤 글자와 비교해도 일치한다고 가정하며, * 는 0 글자 이상의 어떤 문자열에도 일치한다고 본다.

   예를 들어 와일드 카드 he?p 는 파일명 help 에도, heap 에도 매치되지만, helpp 에는 매치되지 않는다. 와일드 카드 *p* 는 파일명 help 에도, papa 에도 매치되지만, hello 에는 매치되지 않는다.

   와일드카드 문자열과 함께 파일명의 집합이 주어질 때, 그 중 매치되는 파일명들을 찾아내는 프로그램을 작성하시오.

   입력

   입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 10) 가 주어진다. 각 테스트 케이스의 첫 줄에는 와일드카드 문자열 W 가 주어지며, 그 다음 줄에는 파일명의 수 N (1 <= N <= 50) 이 주어진다. 그 후 N 줄에 하나씩 각 파일명이 주어진다. 파일명은 공백 없이 알파벳 대소문자와 숫자만으로 이루어져 있으며, 와일드카드는 그 외에 * 와 ? 를 가질 수 있다. 모든 문자열의 길이는 1 이상 100 이하이다.

   출력

   각 테스트 케이스마다 주어진 와일드카드에 매치되는 파일들의 이름을 한 줄에 하나씩 아스키 코드 순서(숫자, 대문자, 소문자 순)대로 출력한다.

   예제 입력

   2
   he?p
   3
   help
   heap
   helpp
   *p*
   3
   help
   papa
   hello
   예제 출력

   heap
   help
   help
   papa
*/

/* 해법 : dynamic programming
 * 접근 방식 : 각각의 경우에 대한 완벽한 처리 
 * 결정적 사항 : 경우의 수 대비 
 * 오답 원인 : 경우의 수 프로그램 실패 
 */

int memoization[10001][10001];
char W[10001];
char S[10001];
char solution[50][10001];
int N;
void sort();
int num;
int high(int i,int j);
int match(int w,int s);
int match(int w,int s)
{
    num++;
	int* ret = &memoization[w][s];
	if(*ret!=-1)
		return *ret;

	// *를 만나거나, W,S 중 하나가 끝부분에 도달하거나, W,S가 일치하지 않는 경우까지 전진 
	while((W[w]!='\0')&&(S[s]!='\0')&&(W[w]=='?'||W[w]==S[s]))
	{
	    return *ret = match(w+1,s+1);
    }

	// W가 끝 부분일 경우 S도 끝일 경우에만 참 아닐 경우 거짓 
	if(W[w]=='\0')
		return *ret = (S[s]=='\0');

	// W가 *인 경우 
	if(W[w]=='*')
	{
		if(match(w+1,s)||(S[s]!='\0'&&match(w,s+1)))
			return *ret =1;
	}

	// 나머지 경우 
	return 0;
}

int high(int i,int j)
{
	int k;
	for(k=0;solution[i][k]!='\0'&&solution[j][k]!='\0';k++)
	{
		if(solution[i][k]>solution[j][k])
		{
			return 1;
		}
		else if(solution[i][k]<solution[j][k])
		{
			return 0;
		}
	}
}

void sort()
{
	int i,j;
	char temp[101];

	for(i=0;i<N;i++)
	{
		for(j=0;j<(N-i-1);j++)
			if(high(j,j+1))
			{
				memcpy(temp,solution[j],strlen(solution[j])+1);
				memcpy(solution[j],solution[j+1],strlen(solution[j+1])+1);
				memcpy(solution[j+1],temp,strlen(temp)+1);
			}

	}

}


int main(void)
{ 
	int testcase;
	int i;
	

	scanf("%d",&testcase);


	while(testcase--)
	{
		scanf("%s",W);
		scanf("%d",&i);
		N=0;
		while(i--)
		{
			scanf("%s",S);
			memset(memoization,-1,sizeof(memoization));
			
			if(match(0,0))
				memcpy(solution[N++],S,strlen(S)+1);
		}

		sort();
		
		for(i=0;i<N;i++)
		{
			puts(solution[i]);
		}

        printf("%d\n",num);
		
	}

}

