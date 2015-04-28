#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int i, j, k, N = 1 << 3;
	double *a_r, *a_i, *b_r, *b_i;
	a_r = (double *) malloc(N*sizeof(double));
	a_i = (double *) malloc(N*sizeof(double));
	b_r = (double *) malloc(N*sizeof(double));
	b_i = (double *) malloc(N*sizeof(double));
	printf("%d\n",N);
	for(i=0;i<N;++i) 
	{
		a_r[i] = i;
		a_i[i] = 0;	
	}
	FFT(a_r,a_i,b_r,b_i,N);
	print_complex(b_r, b_i, N);
	free(a_r);
	free(a_i);
	free(b_r);
	free(b_i);
	return 0;
}
int FT(double *a_r, double *a_i, double *b_r, double *b_i, int N)
{
	int k, n;
	double w_r, w_i, t, theta = 2*M_PI/N;
	for(k=0;k<N;++k)
	{
		b_r[k] = b_i[k] = 0;
		for(n=0;n<N;++n)
		{
			t = -k*n*theta;
			w_r = cos(t);
			w_i = sin(t);
			b_r[k] += w_r*a_r[n]-w_i*a_i[n];
			b_i[k] += w_r*a_i[n]+w_i*a_r[n];
		}
	}
	return;
}
int print_complex(double *r, double *i, int N)
{
	int n;
	for(n=0;n<N;++n)
	{
		if(i[n]>=0.0)
			printf("%f +%f i\n",r[n],i[n]);
		else
			printf("%f %f i\n",r[n],i[n]);
	}
	return;
}
int FFT(double *a_r, double *a_i, double *b_r, double *b_i, int N)
{
	if(N == 2)
	{
		b_r[0] = a_r[0] + a_r[1];
		b_i[0] = a_i[0] + a_i[1];
		b_r[1] = a_r[0] - a_r[1];
		b_i[1] = a_i[0] - a_i[1]; 
	}
	else
	{
		int k, n;
		double *c_r, *c_i, *d_r, *d_i, theta = 2*M_PI/N, w_r, w_i;
		c_r = (double *) malloc(N*sizeof(double));
		c_i = (double *) malloc(N*sizeof(double));
		d_r = (double *) malloc(N*sizeof(double));
		d_i = (double *) malloc(N*sizeof(double));
		for(n=0;n<N/2;++n)
		{
			c_r[n] = a_r[2*n];
			c_i[n] = a_i[2*n];
			c_r[n+N/2] = a_r[2*n+1];
			c_i[n+N/2] = a_i[2*n+1];
		}
		FFT(c_r,c_i,d_r,d_i,N/2);
		FFT(c_r+N/2,c_i+N/2,d_r+N/2,d_i+N/2,N/2);
		for(k=0;k<N/2;++k)
		{
			w_r = cos(-k*theta);
			w_i = sin(-k*theta);
			b_r[k] = d_r[k] + w_r*d_r[k+N/2] - w_i*d_i[k+N/2];
			b_i[k] = d_i[k] + w_r*d_i[k+N/2] + w_i*d_r[k+N/2];
			b_r[k+N/2] = d_r[k] - (w_r*d_r[k+N/2] - w_i*d_i[k+N/2]);
			b_i[k+N/2] = d_i[k] - (w_r*d_i[k+N/2] + w_i*d_r[k+N/2]);
		}
		free(c_r);
		free(c_i);
		free(d_r);
		free(d_i);
	}
	return 0;
}
