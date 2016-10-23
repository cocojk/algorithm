#include <stdio.h>
#include <string.h>

#define NEXT ((a0=((a0*214013+2531011)%(1UL<<32)))%10000+1)
int head,tail;
int buff[5000];
int currentSum;

inline void headPop(void)
{
	int temp = head;
	currentSum -=buff[head];
	head = (head+1)%5000;
}

inline void TailPush(int input)
{
	buff[tail]=input;
	tail = (tail+1)%5000;
	currentSum +=input;
}


int main(void)
{
	unsigned long a0=1983;
	int testcase;
	int sum,total,current;
	int counter;
	scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d %d",&sum,&total);
		head=0;
		tail=0;
		current=1;
		counter=0;
		a0 = 1983;
		memset(buff,0,sizeof(buff));
		currentSum = 0;
		TailPush(a0+1);

		while(current<total)
		{
			if(currentSum<sum)
			{
				TailPush(NEXT);
				current++;
			}
			else if(currentSum==sum)
			{
				counter++;
				TailPush(NEXT);
				current++;
				headPop();
			}
			else 
			{
				headPop();
			}
		}

		if(currentSum==sum)
		{
			counter++;
		}
		else if(currentSum>sum)
		{
			headPop();
			if(currentSum==sum)
				counter++;
		}

		printf("%d\n",counter);

	}
}
