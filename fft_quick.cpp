#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iomanip>
#include<time.h>
using namespace std;

int main()
{
	// y_k = sum( x_n * w^{-kn}, n=0..N-1}
	// w = cos(2*pi / N) + i*sin(2*pi/N)
	double *y_r, *y_i, *x_r, *x_i, w_r, w_i, t1, t2 ; 
									// x_r : real part of x 
									// x_i : image part of x 
									// y_r : real part of y
									// y_i : image part of y
	int k, n, N ;  // in put an integer to N 
	cin  >> N ; 
	
	// create memory of x, y 
	x_r = (double*) malloc ( N*sizeof(double)) ; 
	x_i = (double*) malloc ( N*sizeof(double)) ; 
	y_r = (double*) malloc ( N*sizeof(double)) ; 
	y_i = (double*) malloc ( N*sizeof(double)) ; 
	
	for ( int i = 0 ; i < N ; i++) 
	{
		x_r[i] = i ; 
		x_i[i] = 0 ;
	}
	
	FFT( x_r, x_i, y_r, y_i, N ) ; 
	
/*	
	t1 = clock() ; 
	for ( int k = 0 ; k < N ; k++)
	{
		y_r[k] = 0.0 ; 
		y_i[k] = 0.0 ; 
		for ( int j = 0 ; j < N; j++)
		{
			// w^{-kn} 
			// = cos(-kn*2pi / N ) + isin (-kn*2pi / N) 
			w_r = cos(-k*j*2*M_PI/N) ; 
			w_i = sin(-k*j*2*M_PI/N) ; 
			
			y_r[k] += x_r[j] * w_r - x_i[j] * w_i  ;
			y_i[k] += x_r[j] * w_i + x_i[j] * w_r  ;
		}
	}
	t2 = clock() ; 
		
	for ( int i = 0 ; i< N ; i++) 
	{
		cout << setw(6) ; 
		cout << "第" << i << "個y的實部為:" << y_r[i] << " "
			 << "第" << i << "個y的虛部為:" << y_i[i] << " " << endl ;
			 
	}
	cout << (t2-t1)/1000 << endl ;
	
	return 0 ;
*/	
}


// yk = sum ( x(n) * w^(-kn) , n=0..N-1)
// yk = sum ( x(n) 
int FFT( double* x_r, double* x_i, double* y_r, double* y_i, int N ) ; 
{
	int k, n ;
	double *u_r, *u_i, *v_r, *v_i , w_r, w_i ; 
	
	u_r = (double*) malloc(N*sizeof(double)) ; 
	u_i = (double*) malloc(N*sizeof(double)) ; 
	v_r = (double*) malloc(N*sizeof(double)) ; 
	v_i = (double*) malloc(N*sizeof(double)) ; 
	
	for ( n=0 ; n< N/2 ; n++)
	{
		u_r[n] = x_r[2*n] ; // even terms of real part of x puts in first n terms of u_r
		u_i[n] = x_i[2*n] ; // even terms of image part of x puts in first n terms of u_i
		u_r[n+N/2] = x_r[2+n+1] ; // odd terms of real part of x puts in last n terms of u_r
		u_i[n+N/2] = x_i[2+n+1] ; // odd terms of real part of x puts in last n terms of u_r
	}
	FFT(u_r, u_i, v_r, v_i, N/2 ) ; 
	FFT(u_r+N/2, u_i+N/2, v_r+N/2, v_i+N/2, N/2 ) ; 
}

