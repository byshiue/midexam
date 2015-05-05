#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int Initial(double *x, double *y, int N);
int SFT(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int FFT(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int Generate_N(int p, int q, int r);
double Compare_Complex_Vector(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int Print_Complex_Vector(double *y_r, double *y_i, int N);
int Bit_Increase(int *D, int b, int N);
int Bit_Reverse(int *D, int b, int N);
int Bit_Reverse2(int *D, int b, int N);

int Bit_Reverse_Integer(int p);
int FFTv2(double *x_r, double *x_i, double *y_r, double *y_i, int N);
int main()
{
	// y_k = sum(x_n * w^{-kn}, n=0..N-1)
	// w = cos(2*pi/N) + i sin(2*pi/N)
	int N, p, q, r;
	double *y_r, *y_i, *x_r, *x_i, *z_r, *z_i;
	clock_t t1, t2;
	// Input N
	printf("Please input p q r=");
	scanf("%d %d %d", &p, &q, &r);
	N = Generate_N(p, q, r);
	printf("N=2^%d 3^%d 5^%d = %d\n",p,q,r,N);
	// Create Memory for x and y
	x_r = (double *) malloc(N*sizeof(double));
	x_i = (double *) malloc(N*sizeof(double));
	y_r = (double *) malloc(N*sizeof(double));
	y_i = (double *) malloc(N*sizeof(double));
	z_r = (double *) malloc(N*sizeof(double));
	z_i = (double *) malloc(N*sizeof(double));
	// Initial Setup
	Initial(x_r, x_i, N);
	
	// Slow Fourier Transform
	t1 = clock();
	SFT(x_r, x_i, y_r, y_i, N);
	t2 = clock();
	printf("Slow FT: %f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);
	Print_Complex_Vector(y_r, y_i, N);
	
	Initial(x_r, x_i, N);
	t1 = clock();
	FFTv2(x_r, x_i, z_r, z_i, N);
	t2 = clock();
	printf("Fast FT: %f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);	
	Print_Complex_Vector(z_r, z_i, N);
	printf("Error: %e\n", Compare_Complex_Vector(y_r, y_i, z_r, z_i, N));
	return 0;
	
}
int Generate_N(int p, int q, int r)
{
	int N = 1;
	for(;p>0;p--) N*=2;
	for(;q>0;q--) N*=3;
	for(;r>0;r--) N*=5;
	return N;
}
int Initial(double *x, double *y, int N)
{
	int n;
	for(n=0;n<N;++n)
	{
		x[n] = n;
		y[n] = 0.0;
	}
}
int SFT(double *x_r, double *x_i, double *y_r, double *y_i, int N)
{
	int k, n;
	double w_r, w_i;
	// y_k = sum(x_n * w^{-kn}, n=0..N-1)
	// w = cos(2*pi/N) + i sin(2*pi/N)
	for(k=0;k<N;++k)
	{
		y_r[k] = 0.0;
		y_i[k] = 0.0;
		for(n=0;n<N;n++)
		{
			// w^{-kn} = cos(-kn*2*pi/N)+ i sin(-kn*2*pi/N)
			w_r = cos(-k*n*2*M_PI/N);
			w_i = sin(-k*n*2*M_PI/N);
			y_r[k] = y_r[k] + x_r[n]*w_r - x_i[n]*w_i; 
			y_i[k] = y_i[k] + x_r[n]*w_i + x_i[n]*w_r;
		}
	}
	return 1;
}
int Print_Complex_Vector(double *y_r, double *y_i, int N)
{
	int n;
	for(n=0;n<N;++n)
	{
		if (y_i[n] >=0) printf("%d : %f +%f i\n", n, y_r[n], y_i[n]);
		else printf("%d : %f %f i\n", n, y_r[n], y_i[n]);
	}
	return 0;
}
int FFT(double *x_r, double *x_i, double *y_r, double *y_i, int N)
{
	if(N==1)
	{
		y_r[0] = x_r[0];
		y_i[0] = x_i[0];
		return 0; 
	}
	// input : x = x_r + i * x_i
	// output: y = y_r + i * y_i
	int k, n;
	//double *u_r, *u_i, *v_r, *v_i, w_r, w_i;
	double *even_r, *even_i, *odd_r, *odd_i, w_r, w_i;
	double *even_FT_r, *even_FT_i, *odd_FT_r, *odd_FT_i;
	
	even_r = (double *) malloc(N*sizeof(double));
	even_i = (double *) malloc(N*sizeof(double));
	odd_r  = even_r + N/2;//(double *) malloc(N/2*sizeof(double));
	odd_i  = even_i + N/2;//(double *) malloc(N/2*sizeof(double));
	even_FT_r = (double *) malloc(N*sizeof(double));
	even_FT_i = (double *) malloc(N*sizeof(double));
	odd_FT_r = even_FT_r+N/2;//(double *) malloc(N/2*sizeof(double));
	odd_FT_i = even_FT_i+N/2;//(double *) malloc(N/2*sizeof(double));
	for(n=0;n<N/2;n++)
	{
		even_r[n] = x_r[2*n];
		even_i[n] = x_i[2*n];
		odd_r[n] = x_r[2*n+1];
		odd_i[n] = x_i[2*n+1];
	}
	FFT(even_r,even_i,even_FT_r,even_FT_i,N/2);
	FFT(odd_r,odd_i,odd_FT_r,odd_FT_i,N/2);
	for(k=0;k<N/2;++k)
	{
		// w^{-k} 
		w_r = cos(-k*2*M_PI/N);
		w_i = sin(-k*2*M_PI/N);
		//printf("N=%d, w_r = %f, w_i = %f\n", N, w_r, w_i);
		y_r[k] = even_FT_r[k] + (w_r*odd_FT_r[k] - w_i*odd_FT_i[k]);
		y_i[k] = even_FT_i[k] + (w_r*odd_FT_i[k] + w_i*odd_FT_r[k]);
		y_r[k+N/2] = even_FT_r[k] - (w_r*odd_FT_r[k] - w_i*odd_FT_i[k]);
		y_i[k+N/2] = even_FT_i[k] - (w_r*odd_FT_i[k] + w_i*odd_FT_r[k]);
	}
	
	free(even_r);
	free(even_i);
	free(even_FT_r);
	free(even_FT_i);
	/*
	for(k=N/2;k<N-1;++k)
	{
		// w^{-k} 
		w_r = cos(-k*2*M_PI/N);
		w_i = sin(-k*2*M_PI/N);
		y_r[k] = even_r[k-N/2] + w_r*odd_r[k-N/2] - w_i*odd_i[k-N/2];
		y_i[k] = even_i[k-N/2] + w_r*odd_i[k-N/2] + w_i*odd_r[k-N/2];
	}
	*/
	/* 
	u_r = (double *) malloc(N*sizeof(double));
	u_i = (double *) malloc(N*sizeof(double));
	v_r = (double *) malloc(N*sizeof(double));
	v_i = (double *) malloc(N*sizeof(double));
	for(n=0;n<N/2;n++)
	{
		u_r[n] = x_r[2*n];
		u_i[n] = x_i[2*n];
		u_r[n+N/2] = x_r[2*n+1];
		u_i[n+N/2] = x_i[2*n+1];
	}
	FFT(u_r, u_i, v_r, v_i, N/2);
	FFT(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2);
	*/
	return 0;
}
double Compare_Complex_Vector(double *x_r, double *x_i, double *y_r, double *y_i, int N)
{
	int n;
	double dx, dy, err, max_err=0.0;
	for(n=0;n<N;++n)
	{
		dx = x_r[n]-y_r[n];
		dy = x_i[n]-y_i[n];
		err = sqrt(dx*dx+dy*dy);
		if(err > max_err) max_err = err;
	}
	return max_err;
}

int Bit_Increase(int *D, int b, int N)
{
	int i;
	for(i=0;i<N;++i) D[i] = 0;
	while(D[N-1] < b)
	{
		for(i=N-1;i>=0;i--)
		{
			printf("%d",D[i]);
		}
		printf("\n");

		D[0]++;
		i = 0;
		while(D[i] >= b & i<N-1)
		{
			D[i] = 0;
			i++;
			D[i]++;
		}
		system("pause");
	}
	return 0;
}
int Bit_Reverse(int *D, int b, int N)
{
	int i;
	for(i=0;i<N;++i) D[i] = 0;
	while(D[0] < b)
	{
		for(i=N-1;i>=0;i--)
		{
			printf("%d",D[i]);
		}
		printf("\n");

		D[N-1]++;
		i = N-1;
		while(D[i] >= b & i>0)
		{
			D[i] = 0;
			i--;
			D[i]++;
		}
		system("pause");
	}
	return 0;	
}
int Bit_Reverse2(int *D, int b, int N)
{
	int i;
	for(i=0;i<N;++i) D[i] = 0;
	while(D[0] < b)
	{
		for(i=N-1;i>=0;i--)
		{
			printf("%d",D[i]);
		}
		printf("\n");

		i = N-1;
		while(D[i] == b-1 & i>0)
		{
			D[i] = 0;
			i--;
		}
		D[i]++;
		system("pause");
	}
	return 0;	
}
int Bit_Reverse_Integer(int p)
{
	int i, j, N = 1 << p, m = 1 << (p-1), k;
	i = j = 0;
	while(i<N)
	{
		printf("%d <-> %d\n",i,j);
		i++;
		k = m;
		while(j>=k & k>0)
		{
			j-=k;
			k >>= 1;
		}
		j += k;
	}
	
	return 0;	
}
int FFTv2(double *x_r, double *x_i, double *y_r, double *y_i, int N)
{
	int k, n;
	for(n=0;n<N;++n)
	{
		y_r[n] = x_r[n];
		y_i[n] = x_i[n];
	}
	// Do Bit Reverse
	int p, q, m = N/2;
	double t_r, t_i;	// temp 
	// j: Bit Reverse version
	q = m; 
	for(p=1;p<N-1;++p)
	{
		printf("%d <-> %d\n", p,q);

		if(p < q)
		{
			t_r = y_r[p]; 
			t_i = y_i[p];
			y_r[p] = y_r[q];
			y_i[p] = y_i[q];
			y_r[q] = t_r;
			y_i[q] = t_i;
		}
		// next q
		k = m;
		while(q >= k & k > 0)
		{
			q -= k;
			k >>= 1;
		}
		q += k;
	}
	// Butterfly structure
	double theta, w_r, w_i;
	n = 2;
	while(n <= N)
	{
		for(k=0;k<n/2;k++)
		{
			theta = -2.0*k*M_PI/n;
			w_r = cos(theta);
			w_i = sin(theta);
			for(p=k;p<N;p+=n)
			{
				q = p+n/2;
				t_r = w_r*y_r[q]-w_i*y_i[q];
				t_i = w_r*y_i[q]+w_i*y_r[q];
				y_r[q] = y_r[p] - t_r;
				y_i[q] = y_i[p] - t_i;
				y_r[p] += t_r;
				y_i[p] += t_i;
			}
		}
		n <<= 1;
	}
	
}
