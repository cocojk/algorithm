#include <stdio.h>
#include <stdlib.h>

int middle;
int** numbers;

int recur(int stage,int index)
{
	int i;
	int return1,return2;
	return1=0;
	return2=0;

	if(stage<middle)
	{
		return1 = numbers[stage-1][index]+recur(stage+1,index);
		return2 = numbers[stage-1][index]+recur(stage+1,index+1);
		
	}
	else  
	{
		if(index-1>=0)
		{
			return1 = numbers[stage-1][index]+recur(stage+1,index-1);
		}

		if(index!=((middle-1)-(stage-middle)))
		{
			return2 = numbers[stage-1][index]+recur(stage+1,index);
		}
		
		if(stage==(middle*2-1))
		{
			return numbers[stage-1][index];
		}

	}
	
	if(return1>return2)
	{
		return return1;
	}
	else 
	{
		return return2;
	}
}

int main(void)
{
	int step,i,j;

	scanf("%d",&step);

	while(step--)
	{
		scanf("%d",&middle);
		numbers = (int**)malloc(sizeof(int*)*(middle*2-1));
		for(i=0;i<(middle*2-1);i++)
		{
			numbers[i]=(int*)malloc(sizeof(int)*middle);
			if(i<middle)
			{
				for(j=0;j<i+1;j++)
				{
					scanf("%d",&numbers[i][j]);

				}
			}
			else 
			{
				for(j=0;j<(2*middle-(i+1));j++)
				{
					scanf("%d",&numbers[i][j]);
				}
			}
		}

		printf("%d\n",recur(1,0));
	}


	return 0;
}
