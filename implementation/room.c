#include <stdio.h>

int base[200000];
int curX,curY,nextX,nextY;
int n,k,i;
long sum;

int getBaseX(int x,int y)
{
	if(x+y<=n-1)
	{
		return 0;
	}
	else 
	{
		return x+y-(n-1);
	}
}



int getNum()
{
	if((nextX+nextY)%2==0)
	{
		
		printf("base %d offset %d sum %d\n",base[nextX+nextY],nextX-getBaseX(nextX,nextY),base[nextX+nextY]+(nextX-getBaseX(nextX,nextY)));
		return base[nextX+nextY]+(nextX-getBaseX(nextX,nextY));
	}
	else 
	{
		printf("base %d offset %d sum %d\n",base[nextX+nextY],-(nextX-getBaseX(nextX,nextY)),base[nextX+nextY]-(nextX-getBaseX(nextX,nextY)));
		return base[nextX+nextY]-(nextX-getBaseX(nextX,nextY));

	}
}

int main(void) {
	/* 아래 freopen 함수는 input.txt를 read only 형식으로 열고, 표준입력(키보드) 대신 input.txt 로 부터 읽어오겠다는 의미의 코드입니다.
	   만약 본인 PC 에서 테스트 할 때는, 입력값을 input.txt에 저장한 후 freopen 함수를 사용하면
	   그 아래에서 scanf 함수를 사용하여 표준입력 대신 input.txt 파일로 부터 입력값을 읽어 올 수 있습니다.
	   또한, 본인 PC에서 freopen 함수를 사용하지 않고 표준입력을 사용하여 테스트하셔도 무방합니다.
	   단, Codeground 시스템에서 "제출하기" 할 때에는 반드시 freopen 함수를 지우거나 주석(//) 처리 하셔야만 합니다. */
	freopen("input.txt", "r", stdin);

	setbuf(stdout, NULL);

	int TC;
	int test_case;
	char buff[300001];

	scanf("%d", &TC);
	for(test_case = 1; test_case <= TC; test_case++) {
		// 이 부분에서 알고리즘 프로그램을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하셔도 됩니다.
		
		scanf("%d %d",&n,&k);

		// base init
		base[0]=1;
		for(i=1;i<n;i++)
		{
			// even
			if(i%2==0)
			{
				base[i] = base[i-1]+1;
			}
			else // odd
			{
			
				base[i] = base[i-1]+4*(i/2)+2;
			}
		}

		base[2*n-2]=n*n;
		for(i=1;i<n-1;i++)
		{
			// even
			if(i%2==0)
			{
				base[2*n-2-i]=base[2*n-1-i]-4*(i/2);
			}
			else 
			{
				base[2*n-2-i]=base[2*n-1-i]-1;
			}
		}

		for(i=0;i<(2*n-1);i++)
		{
		//	printf("%d\n",base[i]);
		}

		// point init
		curX = 0;
		curY = 0;
		sum = 1;

		scanf("%s",buff);



		for(i=0;i<k;i++)
		{
			switch(buff[i])
			{
				case 'U':
					nextX = curX;
					nextY = curY-1;
					sum += getNum();
					curX = nextX;
					curY = nextY;
					break;

				case 'D':
					nextX = curX;
					nextY = curY+1;
					sum += getNum();					
					curX = nextX;
					curY = nextY;
					break;

				case 'R':
					nextX = curX+1;
					nextY = curY;
					sum += getNum();
					curX = nextX;
					curY = nextY;
					break;

				case 'L':
					nextX = curX-1;
					nextY = curY;
					sum += getNum();
					curX = nextX;
					curY = nextY;
					break;

				default:
					printf("bug\n");
					break;
			}
		}

		// 이 부분에서 정답을 출력하십시오.
		printf("Case #%d\n", test_case);
		printf("%ld\n",sum);
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}
