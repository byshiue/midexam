#include <stdio.h>
int main()
{
	int i, N, m, n, p;
	double *x, *y, *t;
	printf("Input N:");
	scanf("%d", &N);
	x = (double *) malloc(N*sizeof(double));
	y = (double *) malloc(N*sizeof(double));
	for(i=0;i<N;++i)
	{
		x[i] = i;
	}
	for(i=0;i<N;++i)
		printf("%f\n", x[i]);
	n = N;
	while(n>1)
	{
		m = 0;
		while(m < N)
		{
			if(n%2 == 0)
			{
				p = 2;
			}
			else if (n%3 == 0)
			{
				p = 3;
			}
			Group_p(x+m,y+m,n,p);
			m = m + n;
		}
		t = x; x = y; y = t;
		n = n / p;
	}
	for(i=0;i<N;++i)
		printf("%f\n", x[i]);	
}
int Group_2(double *x, double *y, int N)
{
	int i;
	// Group by (2n) (2n+1)
	for(i=0;i<N/2;++i)
	{
		//y[i] = x[2*i];
		//y[i+N/2] = x[2*i+1];
	}
	// other way!
	for(i=0;i<N;++i)
	{
		y[(i/2) + (N/2)*(i%2)] = x[i];
	}
	return 0;
}
int Group_3(double *x, double *y, int N)
{
	int i;
	// Group by (2n) (2n+1)
	for(i=0;i<N/2;++i)
	{
		y[i] = x[3*i];
		y[i+N/3] = x[3*i+1];
		y[i+2*N/3] = x[3*i+2];
	}
	// other way!
	for(i=0;i<N;++i)
	{
		y[(i/3) + (N/3)*(i%3)] = x[i];
	}	
	return 0;
}
int Group_p(double *x, double *y, int N, int p)
{
	int i;
	for(i=0;i<N;++i)
	{
		y[(i/p) + (N/p)*(i%p)] = x[i];
	}	
	return 0;
}

