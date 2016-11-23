/*  
문제

아마추어 고고학자인 일리노이 존스는 시카고 근교에서 고대 문명의 흔적을 찾아냈습니다. 그 흔적 중에는 이 언어의 사전도 포함되어 있었는데, 이 사전에 포함된 단어들은 모두 영어의 소문자 알파벳으로 구성되어 있었지만 사전에 포함된 단어의 순서들이 영어와 서로 달랐습니다. 발굴팀은 단어들이 사전 순이 아닌 다른 순서대로 정렬되어 있는지, 아니면 알파벳들의 순서가 영어와 서로 다른 것인지를 알고 싶어합니다.

일리노이 존스는 이 언어에서는 알파벳들의 순서가 영어와 서로 다를 뿐, 사전의 단어들은 사전 순서대로 배치되어 있다는 가설을 세웠습니다. 이 가설이 사실이라고 가정하고, 단어의 목록으로부터 알파벳의 순서를 찾아내려고 합니다.

예를 들어 다섯 개의 단어 gg, kia, lotte, lg, hanhwa 가 사전에 순서대로 적혀 있다고 합시다. gg가 kia보다 앞에 오려면 이 언어에서는 g가 k보다 앞에 와야 합니다. 같은 원리로 k는 l앞에, l은 h앞에 와야 한다는 것을 알 수 있지요. lotte 가 lg 보다 앞에 오려면 o가 g 보다 앞에 와야 한다는 것도 알 수 있습니다. 이들을 종합하면 다섯 개의 알파벳 o, g, k, l, h 의 상대적 순서를 알게 됩니다.

사전에 포함된 단어들의 목록이 순서대로 주어질 때 이 언어에서 알파벳의 순서를 계산하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 사전에 포함된 단어의 수 N (1 <= N <= 1000) 이 주어집니다. 그 후 N 줄에 하나씩 사전에 포함된 단어가 순서대로 주어집니다. 각 단어는 알파벳 소문자로 구성되어 있으며, 길이는 1 이상 20 이하입니다. 중복으로 출현하는 단어는 없습니다.

출력

각 테스트 케이스마다 한 줄을 출력합니다. 만약 알파벳들의 순서에 모순이 있다면 "INVALID HYPOTHESIS"를 출력하고, 모순이 없다면 26개의 소문자로 알파벳들의 순서를 출력합니다. 만약 가능한 순서가 여러 개 있다면 아무 것이나 출력해도 좋습니다.

예제 입력

3
3
ba
aa
ab
5
gg
kia
lotte
lg
hanhwa
6
dictionary
english
is
ordered
ordinary
this
예제 출력

INVALID HYPOTHESIS
ogklhabcdefijmnpqrstuvwxyz
abcdefghijklmnopqrstuvwxyz 
 */

/* 해법 : dfs을 이용한 topological sort
 * 접근 방식 : dfs을 이용하면 topological sort가 가능하다는 사실 
 * 결정적 사항 : adj = vector<vector<int> >(26,vector<int>(0));		
		visited = vector<int>(26,0); 을 이용한 초기화 방법 숙지 
 * 오답 원인 :  
 */

#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;
vector < vector<int> > adj;
vector<int> visited;
vector<char> answer;

int dfs(int here);
void compare(char* before,char* current);
#define NOT	0
#define ING	1
#define END	2

int dfs(int here)
{
	visited[here]=ING;
	int i;
	for(i=0;i<adj[here].size();i++)
	{
		if(visited[adj[here][i]]==ING)
			return 0;
		else if(visited[adj[here][i]]==NOT)
		{	
			if(dfs(adj[here][i])==0)
				return 0;
		}
	}

	answer.push_back((here+'a'));
	visited[here]=END;
	return 1;
}

void compare(char* before,char* current)
{
	int i;
	int len = min(strlen(before),strlen(current));
	for(i=0;i<len;i++)
	{
		if(before[i]!=current[i])
		{
			adj[(before[i]-'a')].push_back((current[i]-'a'));
			return;
		}
	}
}


int main(void)
{
	int testcase;
	int n,i,check;
	char before[21];
	char current[21];

	scanf("%d",&testcase);


	while(testcase--)
	{
		scanf("%d",&n);
		*before=0;
		check=0;
		adj = vector<vector<int> >(26,vector<int>(0));		
		visited = vector<int>(26,0);
		
		for(i=0;i<n;i++)
		{
			scanf("%s",current);
			compare(before,current);
			strcpy(before,current);
		}
		
		for(i=0;i<26;i++)
		{
			if(visited[i]==NOT)
			{	
				if(dfs(i)==0)
				{	printf("INVALID HYPOTHESIS\n");
					check=1;
					break;
				}
			}
		}

		if(check==0)
		{
			for(i=25;i>=0;i--)
			{
				putc(answer[i],stdout);
			}
			puts("");
		}

		adj.clear();
		visited.clear();
		answer.clear();
	}

	return 0;
}

