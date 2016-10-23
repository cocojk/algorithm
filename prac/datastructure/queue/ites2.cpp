#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;
unsigned int num;

unsigned int getNext()
{
	unsigned int ret = num;
	num = num*214013+2531011;
	ret = ret%10000+1;
	return (ret);
}
	
int main(void)
{
	int testcase;
	int k,n,i,sum;
	unsigned int current;
	int answer;
	scanf("%d",&testcase);
	
	while(testcase--)
	{
		num = 1983;
		sum = 0;
		answer = 0;
		scanf("%d %d",&k,&n);
		queue<int> q;
		for(i=0;i<n;i++)
		{
			current = getNext();
			sum += current;
			q.push(current);

			while(sum>k)
			{
				sum -= q.front();
				q.pop();
			}

			if(sum==k)
				answer++;
		}

		printf("%d\n",answer);
	}
}
