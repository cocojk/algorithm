#include <stdio.h>

int main(void)
{
	int casenum;
	int number[8];
	char temp[10];
	int i;
	scanf("%d",&casenum);

	while(casenum--)
	{
		scanf("%s",temp+1);
		for(i=1;i<8;i++)
		{
			number[i] = temp[i]-'0';
		}

		if((number[1]^number[3]^number[5]^number[7])==0)
		{
			if((number[2]^number[3]^number[6]^number[7])==1)
			{
				if((number[4]^number[5]^number[6]^number[7])==1)
				{
					printf("%d%d%d%d\n",number[3],number[5],1^number[6],number[7]);
					continue;

				}
			}

		}
		else 
		{
			if((number[2]^number[3]^number[6]^number[7])==1)
			{
				if((number[4]^number[5]^number[6]^number[7])==1)
				{
					printf("%d%d%d%d\n",number[3],number[5],number[6],1^number[7]);
				}
				else 
				{
					printf("%d%d%d%d\n",1^number[3],number[5],number[6],number[7]);
				}
				continue;
			}
			else 
			{
				if((number[4]^number[5]^number[6]^number[7])==1)
				{
					printf("%d%d%d%d\n",number[3],1^number[5],number[6],number[7]);
					continue;
				}
				

			}


		}

		printf("%d%d%d%d\n",number[3],number[5],number[6],number[7]);

	}	

	return 0;
}










