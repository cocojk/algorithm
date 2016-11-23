
/* 해법 : euleriancircuit 응용 
 * 접근 방식 : 
 * 결정적 사항 : 해밀토니안 경로 (그래프의 모든 정점을 정확히 한번 씩 지나는 경로)의 경우 n!의 running time이 걸리므로, 오일러 서킷으로 문제를 변형한다. 오일러 서킷의 경우 running time = v*E이므로 제한시간내에 끝날 수 있다. 
 * 오답 원인 :  
*/
/*   
문제

끝말잇기는 참가자들이 원을 그리고 앉은 뒤, 시계 방향으로 돌아가면서 단어를 말하는 게임입니다. 이 때 각 사람이 말하는 단어의 첫 글자는 이전 사람이 말한 단어의 마지막 글자와 같아야 합니다. 단어 제한 끝말잇기는 일반적인 끝말잇기와 달리 사용할 수 있는 단어의 종류가 게임 시작 전에 미리 정해져 있으며, 한 단어를 두 번 사용할 수 없습니다. 단어 제한 끝말잇기에서 사용할 수 있는 단어들의 목록이 주어질 때, 단어들을 전부 사용하고 게임이 끝날 수 있는지, 그럴 수 있다면 어떤 순서로 단어를 사용해야 하는지를 계산하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 게임에서 사용할 수 있는 단어의 수 N (1 <= N <= 100) 이 주어집니다. 그 후 N 줄에 하나씩 게임에서 사용할 수 있는 단어가 주어집니다. 각 단어는 알파벳 소문자로 구성되어 있으며, 길이는 2 이상 10 이하입니다. 중복으로 출현하는 단어는 없습니다.

출력

각 테스트 케이스마다 한 줄을 출력합니다. 만약 모든 단어를 사용하고 게임이 끝나는 방법이 없다면 "IMPOSSIBLE" 을 출력하고 (따옴표 제외), 방법이 있다면 사용할 단어들을 빈 칸 하나씩을 사이에 두고 순서대로 출력합니다. 방법이 여러 개 있다면 그 중 아무 것이나 출력해도 좋습니다.

예제 입력

3
4
dog
god
dragon
need
3
aa
ab
bb
2
ab
cd
예제 출력

need dog god dragon
aa ab bb
IMPOSSIBLE
 */






#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;
vector<vector<int> > adj;
vector<string> graph[26][26];
vector<int> indegree,outdegree;
string solve(const vector<string>& words);
void makeGraph(const vector<string>& words);
void getEulerCircuit(int here,vector<int>& circuit);
vector<int> getEulerTrailOrCircuit();
bool checkEuler();

void makeGraph(const vector<string>& words)
{
	for(int i=0;i<26;i++)
		for(int j=0;j<26;j++)
			graph[i][j].clear();

	adj = vector<vector<int> >(26,vector<int>(26,0));
	indegree = outdegree = vector<int>(26,0);

	for(int i=0;i<words.size();i++)
	{
		int a = words[i][0]-'a';
		int b = words[i][words[i].size()-1] - 'a';
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}

void getEulerCircuit(int here,vector<int>& circuit)
{
	for(int there=0;there<adj.size();there++)
		while(adj[here][there]>0){
			adj[here][there]--;
			getEulerCircuit(there,circuit);
		}

	circuit.push_back(here);
}

// 현재 그래프의 오일러 트레일이나 서킷을 반환한다.
vector<int> getEulerTrailOrCircuit()
{
	vector<int> circuit;

	// 우선 트레일을 찾아본다. 시작점이 존재하는 경우 
	for(int i=0;i<26;i++)
		if(outdegree[i]==indegree[i]+1)
		{
			getEulerCircuit(i,circuit);
			return circuit;
		}

	// 아니면 서킷이니 간선에 인접한 아무 정점에서나 시작한다.
	for(int i=0;i<26;i++)
		if(outdegree[i]){
			getEulerCircuit(i,circuit);
			return circuit;
		}
	
	// 모두 실패한 경우 빈 배열을 반환한다.
	return circuit;
}

// 현재 그래프의 오일러 서킷/트레일 존재 여부를 확인한다.
bool checkEuler(){
	// 예비 시작점과 끝점의 수 
	int plus1=0,minus1=0;
	for(int i=0;i<26;i++)
	{
		int delta = outdegree[i]-indegree[i];
		// 모든 정점의 차수는 -1,1 또는 0 이어야 한다.
		if(delta<-1||1<delta) return false;
		if(delta==1) plus1++;
		if(delta==-1) minus1++;
	}

	// 시작점과 끝점은 각 하나씩 있거나 하나도 없어야 한다.
	return (plus1==1&&minus1==1)||(plus1==0&&minus1==0);
}

string solve(const vector<string>& words){
	makeGraph(words);
	// 차수가 맞지 않으면 실패 
	if(!checkEuler())
		return "IMPOSSIBLE";

	// 오일러 서킷이나 트레일을 찾아낸다.
	vector<int> circuit = getEulerTrailOrCircuit();

	// 모든 간선을 방문하지 못했으면 실패!
	if(circuit.size()!=words.size()+1)
		return "IMPOSSIBLE";

	// 아닌 경우 방문 순서를 뒤집은 뒤 간선들을 모아 문자열로 만들어 반환한다.
	reverse(circuit.begin(),circuit.end());
	string ret;
	for(int i=1;i<circuit.size();i++){
		int a = circuit[i-1],b=circuit[i];
		if(ret.size())
			ret +=" ";
		ret += graph[a][b].back();
		graph[a][b].pop_back();
	}

	return ret;
}

int main(void)
{
	int testcase,n;
	vector<string> words;
	char temp[11];
	scanf("%d",&testcase);
	while(testcase--)
	{
		
		scanf("%d",&n);
		while(n--)
		{
			scanf("%s",temp);
			words.push_back(temp);
		}
		cout<<solve(words)<<endl;
		words.clear();
	}
}
