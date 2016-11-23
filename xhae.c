#include <stdio.h>
#include <string.h>

main(void)
{
	char* number[11] = {"zero","one","two","three","four","five","six","seven","eight","nine","ten"};
	int check[11] = {210,30,30,1470,210,210,30,810,1890,84,30};
	int prime[5] = {2,3,5,7,9};
	int myAnswer;
	int i,j;
	int checksum;
	int count;
	char temp[11];


	scanf("%d",&count);


	while(--count>=0)
	{

		checksum=1;

		scanf("%s",temp);

		for(i=0;i<11;i++)
		{
			if(strcmp(temp,number[i])==0)
			{
				myAnswer=i;
				break;
			}
		}

		scanf("%s",temp);

		if(strcmp(temp,"+")==0)
		{

			scanf("%s",temp);
			for(i=0;i<11;i++)
			{
				if(strcmp(temp,number[i])==0)
				{
					myAnswer+=i;
				}
			}

		}
		else if(strcmp(temp,"-")==0)
		{

			scanf("%s",temp);
			for(i=0;i<11;i++)
			{
				if(strcmp(temp,number[i])==0)
				{
					myAnswer-=i;
				}
			}
		}
		else 
		{

			scanf("%s",temp);
			for(i=0;i<11;i++)
			{
				if(strcmp(temp,number[i])==0)
				{
					myAnswer*=i;
				}
			}

		}

		scanf("%s",temp);

		scanf("%s",temp);

		if(myAnswer>10||myAnswer<0)
		{
			printf("No\n");
			continue;
		}

		if(strlen(temp)!=strlen(number[myAnswer]))
		{
			printf("No\n");
			continue;
		}

		for(i=0;i<strlen(temp);i++)
		{
			for(j=0;j<strlen(number[myAnswer]);j++)
			{
				if(temp[i]==number[myAnswer][j])
				{
					checksum *= prime[j];
					break;
				}
			}
		}

		if(checksum!=check[myAnswer])
		{
			printf("No\n");
			continue;
		}
		else 
		{
			printf("Yes\n");
		}
	}	
}

