#include <stdio.h>
#include <string.h>

int  top;
char bracket[5000];
inline int push(int data)
{
	bracket[top++] = data;
	return 1;
}

inline int pop(int data)
{
	if (top == 0 )
		return 0;
	if (bracket[--top] != data)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int main(void)
{
	int i,  ret;
	int testcase;
	char    buf[10001];


	freopen("test.txt","r",stdin);
	scanf("%d", &testcase);

	while(testcase--)
	{
		memset(buf, 0, sizeof(buf));
		memset(bracket, 0, sizeof(bracket));
		scanf("%s", buf);

		i = 0;
		top = 0;
		ret =0;
		while (buf[i])
		{
			switch (buf[i]){
				case '(':
					ret = push(1);
					break;
				case ')':
					ret = pop(1);
					break;
				case '{':
					ret = push(2);
					break;
				case '}':
					ret = pop(2);
					break;
				case '[':
					ret = push(3);
					break;
				case ']':
					ret = pop(3);
					break;
			}

			if (!ret)
				break;
			i++;
		}
		if (!ret)
			printf("No\n");
		else
		{
			if (top)
				printf("No\n");
			else
				printf("Yes\n");
		}
	}

	return 0;
}


