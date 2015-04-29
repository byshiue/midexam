#include <stdio.h>

int main()
{
	int k, n, N=1 << 5;
	printf("Please input a number:");
	scanf("%d", &n);
	k = 0;
	while(n>0)
	{
		N = N/2;
		printf("%d(%d)", n % 2, N);
		k += (n % 2) * N;
		n = (n - n % 2) / 2;
	}
	printf("\n%d\n",k);
	return 0;
}
