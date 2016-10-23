#include <stdio.h>
#define MAXN 102

int lower_bound(int *trace, int n, int value) {
	if(n <= 1) {
		return 0;
	}

	for(int i = 0; i < n; ++i) {
		if (trace[i] >= value) {
			return i;
		}
	}

	return n;
}

int lis(int* arr, int n, int* trace) {
	int current;

	// initialize.
	current = 1;
	trace[0] = arr[0];
	for(int i = 1;i < n ; ++i) {
		if (trace[current - 1] < arr[i]) {
			trace[current] = arr[i];
			++current;
			continue;
		}

		int start = lower_bound(trace, current, arr[i]);
		trace[start] = arr[i];
	}

	return current;
}

int merge(int *a, int numA, int *b, int numB) {
	int *smaller = (numA > numB) ? b : a;
	int *bigger = (numA > numB) ? a : b;
	int smallNum = (numA > numB) ? numB : numA;
	int bigNum = (numA > numB) ? numA : numB;

	int mergeNum = numA + numB;

	for(int i = 0, j = 0; i < smallNum; ++i) {
		while (smaller[i] > bigger[j]) {
			++j;
			if (j >= bigNum) {
				return mergeNum;
			}
		}

		if (smaller[i] == bigger[j]) {
			--mergeNum;
		}
	}

	return mergeNum;
}

int main() {
	int c, n, m, i;

	scanf("%d", &c);
	while(--c >= 0) {
		int a[MAXN], b[MAXN], maxA[MAXN], maxB[MAXN], lisA, lisB, ans;
		// input
		scanf("%d %d", &n, &m);

		for(i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
		}

		for(i = 0; i < m; ++i) {
			scanf("%d", &b[i]);
		}

		// get lis from A
		lisA = lis(a, n, maxA);
		// get lis from B
		lisB = lis(b, m, maxB);

		// output
		ans = merge(maxA, lisA, maxB, lisB);


		printf("%d\n", ans);
	}

	return 0;
}
