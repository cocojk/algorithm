#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
vector<int> fixed;


void solve(const vector<int>& perm);
int main(void)
{
	char buffer [9] ;
	vector<int> v;
	while(1)
	{
	    gets(buffer);
		v.push_back(atoi(&buffer[0]));
		v.push_back(atoi(&buffer[2]));
		v.push_back(atoi(&buffer[4]));
		v.push_back(atoi(&buffer[6]));
		
		solve(v);

		for(int i=0;i<4;i++)
			printf("%d ",fixed[i]);
		puts("");

		v.clear();
	}

}


void solve(const vector<int>& perm) {
	int n= perm.size();
	fixed = vector<int>(n);
	for(int i=0;i<n;i++) {
		int smaller = 0;
		for(int j=0;j<n;j++)
			if(perm[j]<perm[i])
				++smaller;
		fixed[i] = smaller;
	}
}
