/* 
  문제

castle.svg.png
중세의 성과 요새들은 보안을 튼튼히 하면서도 더 넓은 영역을 보호하기 위해 여러 개의 성벽을 갖고 있었다고 하지요. 전세계에서 가장 편집증이 심한 영주가 지은 스트로고(Strawgoh) 요새는 이의 극치를 보여줍니다. 이 요새는 그림과 같이 커다란 원형 외벽 내에 여러 개의 원형 성벽이 겹겹이 지어진 형태로 구성되어 있는데, 어떤 성벽에도 문이 없어서 성벽을 지나가려면 사다리를 타고 성벽을 오르내려야 합니다. 요새 내에서도 한 곳에서 다른 곳으로 이동하는 데 시간이 너무 오래 걸린다는 원성이 자자해지자, 영주는 요새 내에서 왕래가 불편한 곳들을 연결하는 터널을 만들기로 했습니다. 계획을 세우기 위해 요새 내에서 서로 왕래하기 위해 가장 성벽을 많이 넘어야 하는 두 지점을 찾으려고 합니다. 예를 들어 위 그림의 경우, 별표로 표시된 두 지점 간을 이동하기 위해서는 다섯 번이나 성벽을 넘어야 하지요.

성벽들의 정보가 주어질 때 가장 성벽을 많이 넘어야 하는 두 지점 간을 이동하기 위해 몇 번이나 성벽을 넘어야 하는지 계산하는 프로그램을 작성하세요.

입력

입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 100) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 성벽의 수 N (1 <= N <= 100) 이 주어집니다. 그 후 N 줄에는 각 3개의 정수로 각 성벽의 위치와 크기에 대한 정보 xi , yi , ri 가 주어집니다. (0 <= xi, yi <= 1000,1 <= ri <= 1000,0 <= i<N) 이 때 i 번 성벽은 (xi, yi) 를 중심으로 하는 반지름 ri 인 원형으로 설치되어 있습니다. 편의상 모든 성벽의 두께는 0이라고 가정하며, 입력에 주어지는 성벽들은 서로 겹치거나 닿지 않습니다. 입력에 주어지는 첫 번째 성벽은 외벽이며, 외벽은 입력에 주어지는 모든 다른 성벽을 포함합니다.

출력

각 테스트 케이스마다 한 줄에 두 지점 간 이동을 위해 최대 몇 번이나 성벽을 넘어야 하는지를 출력하세요.

예제 입력

2
3
5 5 15
5 5 10
5 5 5
8 
21 15 20 
15 15 10 
13 12 5 
12 12 3 
19 19 2 
30 24 5 
32 10 7 
32 9 4 
예제 출력

2
5
 */

/* 해법 : tree
 * 접근 방식 : 
 * 결정적 사항 : 
 * 오답 원인 :  
 */


#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>

#define MAX(i,j) ((i)>(j))?(i):(j)
using namespace std;
typedef struct _tree{
	int height;
	int index;
	vector<_tree*> child;
} TREE;


typedef struct _point{
	int x;
	int y;
	int r;
} POINT;

int getMaxHeight(int index);
int inCircle(POINT* p1,POINT* p2);
int answer();
int makeTree(TREE* root,int index);
POINT point[100];
TREE tree[100];
int longest;

int inCircle(POINT* p1,POINT* p2)
{
	if(abs(p1->r-p2->r)>sqrt(pow((p1->x-p2->x),2)+pow((p1->y-p2->y),2)))
		return 1;
	else 
		return 0;
}

int makeTree(TREE* root,int index)
{
	int i;
	for(i=0;i<root->child.size();i++)
	{
		if(makeTree(root->child[i],index))
			return 1;
	}

	if(inCircle(&point[root->index],&point[index]))
	{	
		tree[index].index = index;
		root->child.push_back(&tree[index]);
		return 1;
	}
	else 
		return 0;
}

int answer()
{
	longest=0;
	int h = getMaxHeight(0);
	return max(longest,h);
}

int getMaxHeight(int index)
{
	int i;
	int ret,temp;
	ret = 0;
	vector<int> heights;
	for(i=0;i<tree[index].child.size();i++)
	{
		heights.push_back(getMaxHeight((tree[index].child[i])->index));
	}

	if(heights.empty())
		return 0;

	sort(heights.begin(),heights.end());

	if(heights.size()>=2)
		longest = max(longest,2+heights[heights.size()-2]+heights[heights.size()-1]);

	return heights.back()+1;
}
int main(void)
{
	int testcase;
	int n,i;
	scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d",&n);
		scanf("%d %d %d",&point[0].x,&point[0].y,&point[0].r);
		tree[0].index=0;
		for(i=1;i<n;i++)
		{
			scanf("%d %d %d",&point[i].x,&point[i].y,&point[i].r);
			makeTree(&tree[0],i);
		}
	
		printf("%d\n",answer());
		for(i=0;i<n;i++)
			tree[i].child.clear();
	}
}





