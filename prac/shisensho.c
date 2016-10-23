#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int H,W;
int count;
char tiles[51][51];

void sameLow(int y1,int x1,int y2,int x2);
void searchPartner(int h,int w,char input);
void allDiff1(int x1,int y1,int x2,int y2);
void allDiff2(int x1,int y1,int x2,int y2);
void sameColumn(int y1,int x1,int y2,int x2 );
void allDiff(int y1,int x1,int y2,int x2);
int sumHorizon(int x1,int x2,int y);
void match(void);
int sumVirticle(int y1,int y2,int x);

void sameLow(int y1,int x1,int y2,int x2)
{
	int i;
	for(i=0;i<H;i++)
	{
		if((sumHorizon(x1,x2,i)==0)&&(sumVirticle(i,y1,x1)==0)&&(sumVirticle(i,y2,x2)==0))
		{
			printf("correct\n");
			count++;
			return;
		}
	}	
}

void sameColumn(int y1,int x1,int y2,int x2 )
{
	int i;
	for(i=0;i<W;i++)
	{
		if((sumVirticle(y1,y2,i)==0)&&(sumHorizon(x1,i,y1)==0)&&(sumHorizon(x2,i,y2)==0))
		{
			printf("correct\n");
			count++;
			return;
		}
	}
}


void allDiff(int y1,int x1,int y2,int x2)
{
	if((x1<x2)&&(y1<y2))
	{
		allDiff1(x1,y1,x2,y2);
	}
	else if((x1>x2)&&(y1>y2))
	{
		allDiff1(x2,y2,x1,y2);
	}
	else if((x1>x2)&&(y1<y2))
	{
		allDiff2(x1,y1,x2,y2);
	}
	else 
	{
		allDiff2(x2,y2,x1,y1);
	}
}

//  x1,y1 
//         x2,y2 
void allDiff1(int x1,int y1,int x2,int y2)
{
	printf("allDiff1 [%d %d]\n             [%d %d]\n",y1,x1,y2,x2);

	int i;

	// case1
	for(i=x1;i<=x2;i++)
	{
		if((sumHorizon(x1,i,y1)==0)&&(sumHorizon(i,x2,y2)==0)&&(sumVirticle(y1,y2,i)==0))
		{
			printf("case 1 correct\n");
			count++;
			return;
		}
	}

	// case 2
	for(i=y1;i<=y2;i++)
	{
		if((sumHorizon(x1,x2,i)==0)&&(sumVirticle(i,y1,x1)==0)&&(sumVirticle(i,y2,x2)==0))
		{
			printf("case 2 correct\n");
			count++;
			return;
		}
	}

	// case 3
	if(sumVirticle(y1,y2,x2)==0)
	{
		for(i=0;i<y1;i++)
		{
			if((sumVirticle(i,y1,x2)==0)&&(sumHorizon(x1,x2,i)==0)&&(sumVirticle(i,y1,x1)==0))
			{
				printf("case 3 correct\n");
				count++;
				return;
			}
		}
	}

	// case 5
	if(sumVirticle(y1,y2,x1)==0)
	{
		for(i=y2+1;i<H;i++)
		{
			if((sumVirticle(i,y2,x2)==0)&&(sumHorizon(x1,x2,i)==0)&&(sumVirticle(i,y1,x1)==0))
			{
				printf("case 5 correct\n");
				count++;
				return;
			}
		}
	}

	// case 4
	if(sumHorizon(x1,x2,y1)==0)
	{
		for(i=x2+1;i<W;i++)
		{	
			if((sumHorizon(x2,i,y1)==0)&&(sumVirticle(y1,y2,i)==0)&&(sumHorizon(i,x2,y1)==0))
			{
				printf("case 4 correct\n");
				count++;
				return;
			}
		}
	}

	// case 6
	if(sumHorizon(x1,x2,y2)==0)
	{
		for(i=0;i<x1;i++)
		{
			if((sumHorizon(i,x1,y1)==0)&&(sumVirticle(y1,y2,i)==0)&&(sumHorizon(i,x2,y2)==0))
			{
				printf("case 6 correct\n");
				count++;
				return;
			}
		}
	}
}


// 			 x1,y1 
// x2,y2 
void allDiff2(int x1,int y1,int x2,int y2)
{

	printf("allDiff2     [%d %d]\n[%d %d]\n",y1,x1,y2,x2);
	int i;

	// case1
	for(i=x2;i<=x1;i++)
	{
		if((sumHorizon(x1,i,y1)==0)&&(sumHorizon(i,x2,y2)==0)&&(sumVirticle(y1,y2,i)==0))
		{
			printf("case 1correct\n");
			count++;
			return;
		}
	}

	// case 2
	for(i=y1;i<=y2;i++)
	{
		if((sumHorizon(x1,x2,i)==0)&&(sumVirticle(i,y1,x1)==0)&&(sumVirticle(i,y2,x2)==0))
		{
			printf("case 2 correct\n");
			count++;
			return;
		}
	}

	// case 3
	if(sumVirticle(y1,y2,x2)==0)
	{
		for(i=0;i<y1;i++)
		{
			if((sumVirticle(i,y1,x2)==0)&&(sumHorizon(x1,x2,i)==0)&&(sumVirticle(i,y1,x1)==0))
			{
				printf("case 3 correct\n");
				count++;
				return;
			}
		}
	}

	// case 5
	if(sumVirticle(y1,y2,x1)==0)
	{
		for(i=y2+1;i<H;i++)
		{
			if((sumVirticle(i,y2,x2)==0)&&(sumHorizon(x1,x2,i)==0)&&(sumVirticle(i,y2,x1)==0))
			{
				printf("case 5 correct\n");
				count++;
				return;
			}
		}
	}

	// case 4
	if(sumHorizon(x1,x2,y2)==0)
	{
		for(i=x1+1;i<W;i++)
		{	
			if((sumHorizon(x1,i,y1)==0)&&(sumVirticle(y1,y2,i)==0)&&(sumHorizon(i,x1,y2)==0))
			{
				printf("case 4 correct\n");
				count++;
				return;
			}
		}
	}

	// case 6
	if(sumHorizon(x1,x2,y1)==0)
	{
		for(i=0;i<x1;i++)
		{
			if((sumHorizon(i,x2,y1)==0)&&(sumVirticle(y1,y2,i)==0)&&(sumHorizon(i,x2,y2)==0))
			{
				printf("case 6 correct\n");
				count++;
				return;
			}
		}
	}
}






int sumHorizon(int x1,int x2,int y)
{
	int sum=0;
	int low,high;
	int i;	
	if(x1==x2)
	{
		return 0;
	}

	if(x1>x2)
	{
		low = x2;
		high = x1;
	}
	else 
	{
		low = x1;
		high = x2;
	}

	for(i=(low);i<=high;i++)
	{
		sum+= tiles[y][i];
	}

	return sum;

}

int sumVirticle(int y1,int y2,int x)
{
	int sum=0;
	int i;
	int low,high;
	if(y1==y2)
	{
		return 0;
	}

	if(y1>y2)
	{
		low = y2;
		high = y1;
	}
	else 
	{
		low = y1;
		high = y2;
	}

	for(i=(low);i<=high;i++)
	{
		sum+= tiles[i][x];
	}

	return sum;
}

void match(void)
{
	int i,j,k;
	int offset;
	char save;
	offset=0;
	for(i=0;i<H;i++)
	{
		for(j=0;j<W;j++)
		{
			if(tiles[i][j]!='\0')
			{
				searchPartner(i,j,tiles[i][j]);

			}
		}
	}
}

void searchPartner(int h,int w,char input)
{
	int i,j;

	tiles[h][w]=0;

	for(i=h;i<H;i++)
	{
		for(j=0;j<W;j++)
		{
			if((i==h)&&(j<=w))
			{
				continue;
			}

			if(tiles[i][j]==input)
			{
				if(i==h)
				{
					tiles[i][j]=0;
					printf("========= %c ============\n",input);
					printf("same low [%d %d] [%d %d]\n",i,j,h,w);
					sameLow(h,w,i,j);
					printf("\n\n");
					tiles[i][j]=input;
				}
				else if(j==w)
				{
					tiles[i][j]=0;
					printf("========= %c ============\n",input);
					printf("same column [%d %d] [%d %d]\n",i,j,h,w);
					sameColumn(h,w,i,j);
					printf("\n\n");
					tiles[i][j]=input;
				}
				else 
				{
					tiles[i][j]=0;
					printf("========= %c ============\n",input);
				//	printf("all Diff [%d %d] [%d %d]\n",i,j,h,w);
					allDiff(h,w,i,j);
					printf("\n\n");
					tiles[i][j]=input;
				}
			}
		}
	}

	tiles[h][w]=input;
}



int main(void)
{
	int testcase;
	int i,j;
	freopen("shisenshotest.txt","r",stdin);
	scanf("%d",&testcase);

	while(testcase--)
	{
		scanf("%d %d",&H,&W);
		memset(tiles,0,sizeof(char)*50*50);
		count=0;
		for(i=0;i<H;i++)
		{
			scanf("%s",tiles[i]);
			for(j=0;j<W;j++)
			{
				if(tiles[i][j]=='.')
				{
					tiles[i][j]='\0';
				}
			}
		}





		match();

		printf("%d\n",count);
		printf("\n\n");
	}
}


