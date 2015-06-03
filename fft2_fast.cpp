#include<iostream>
#include<math.h>
#include<stdlib.h>
using namespace std; 

int INITIAL(double *x_r, double*x_i, int N)  ; 
int FFT2(double *x_r, double *x_i, double *y_r, double *y_i, int N) ; 
int main()
{
	double *x_r, *x_i, *y_r, *y_i ; 
	int p, q, r, N ; 
	
	cout << "Please enter a number :" ;
	cin >> p ;
	N = pow(2,p) ; 
	cout << "N=" << N << endl ;
	
	x_r = (double*) malloc( N*sizeof(double)) ; 
	x_i = (double*) malloc( N*sizeof(double)) ; 
	y_r = (double*) malloc( N*sizeof(double)) ; 
	y_i = (double*) malloc( N*sizeof(double)) ; 
	INITIAL(x_r, x_i, N) ; 
	
	FFT2(x_r, x_i, y_r, y_i, N) ; 
}

int INITIAL(double *x_r, double*x_i, int N)  
{
	for ( int i = 0 ; i< N ; i++)
	{
		x_r[i] = i ;
		x_i[i] = 0.0 ; 
	}
}

int FFT2(double *x_r, double *x_i, double *y_r, double *y_i, int N) 
{
	for ( int i = 0 ; i<N ; i++)
	{
		y_r[i] = x_r[i] ; 
		y_i[i] = x_i[i] ; 
	}
	
	// bitreverse of version 2 
	int i= 0 , j=0 , M; 
	while ( i < N  )
	{
		if ( i < j ) 
		{
			swap(y_r[i], y_r[j]) ; 
			swap(y_i[i], y_i[j]) ; 
		}
		M = N/2 ; 
		while ( j >= M & M > 0 )
		{
			j -= M ; 
			M /= 2 ; 
		}
		j+= M ; 
		i++ ; 
	}
	
	int n = 1 ;
	while (n<N)
	{
		double w_r=1, w_i= 0, u_r = cos(-1.0*M_PI/n), u_i = sin(-1.0*M_PI/n) ;   
		for ( int i = 0 ; i< n ; i++)
		{
			double temp = w_r ; 
			w_r = w_r*u_r - w_i*u_i ; 
			w_i = temp*u_i + w_i*u_r ; 
			
			for ( int j = i ; j < N ; j += 2*n )
			{
				int k = j + n ;
				double t_r = w_r*y_r[k]-w_i*y_i[k];
				double t_i = w_r*y_i[k]+w_i*y_r[k];
				// jth = jth + w^(-i)*kth = jth +t 
				// kth = kth + w^(-i)*kth = kth -t
				y_r[k] = y_r[j]-t_r ; 
				y_i[k] = y_i[j]-t_i ; 
				y_r[j] += t_r ; 
				y_i[j] += t_i ; 
				
				
			}
			
		}
		n *= 2 ;
	}
	for ( int i = N-1 ; i>= 0   ; i--) cout << y_r[i] << "   i * " << y_i[i] << endl ;
}






















