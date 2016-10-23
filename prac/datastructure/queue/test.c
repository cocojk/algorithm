#include <stdio.h>

int next()
{
	static int a=1;
	return a++;
}

int main(void)
{
	printf("%d\n",next());
	printf("%d\n",next());
	printf("%d\n",next());
}
