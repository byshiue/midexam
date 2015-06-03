#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
using namespace std; 

int INITIAL(double *x_r, double*x_i, int N)  ; 
void FFT(double *x_r, double *x_i, double *y_r, double *y_i,int p)  ;
void iFFT(double *x_r, double *x_i, double *y_r, double *y_i,int p)  ;
int main()
{
	double *x_r, *x_i, *y_r, *y_i ,*z_r, *z_i ; 
	int p, N=1 ; 
	srand(0) ; 
	cout << "Please input the p: " ;
	cin >> p ;
	for ( int i = 0 ; i<p ;i ++) N = N*2 ; 
	
	cout << "N = 2^" << p << " = " << N << endl ;
	
	x_r = (double*) malloc( N*sizeof(double)) ; 
	x_i = (double*) malloc( N*sizeof(double)) ; 
	y_r = (double*) malloc( N*sizeof(double)) ; 
	y_i = (double*) malloc( N*sizeof(double)) ; 
	z_r = (double*) malloc( N*sizeof(double)) ; 
	z_i = (double*) malloc( N*sizeof(double)) ; 
	
	INITIAL(x_r, x_i, N) ; 
	for ( int  i = 0 ; i< N ;i ++) cout << x_r[i] << " "  ;
	cout << endl ;
	FFT(x_r,x_i,y_r,y_i,p) ;
	
	iFFT(y_r,y_i,z_r,z_i,p) ; 
	
	 
}

int INITIAL(double *x_r, double*x_i, int N)  
{
	for ( int i = 0 ; i< N ; i++)
	{
		x_r[i] = i ;
		x_i[i] = 0.0 ; 
	}
}

void FFT(double *x_r, double *x_i, double *y_r, double *y_i, int p) 
{
	int N = 1 ; 
	for ( int i = 0 ; i<p ;i ++) N = N*2 ; 
	
//	for ( int i = 0 ; i<N ; i++)
//	{
//		y_r[i] = x_r[i] ; 
//		y_i[i] = x_i[i] ; 
//	}

	int i = 0 , j = 0, M ;
	/*
	while ( i < N)
	{
		y_r[i] = j ; 
	
		 M = N/2 ; 
		int k = M  ; 
		int r = (N/M)-1 ; 
		while  ( j >= r * k  && k > 0  ) 
		{
			
			j -= r *k ; 
			k = k/2, r=1 ;
		}
		
		j += k ; 
		i++ ; 
	
	}
	*/
	double * z ;
	z =  (double*) malloc( N*sizeof(double)) ; 
	
	for ( int i = 0 ; i< N ;i ++) z[i] = i ; 
	
	while ( i < N)
	{
		z[i] = j ; 
	
		 M = N/2 ; 
		int k = M  ; 
		int r = (N/M)-1 ; 
		while  ( j >= r * k  && k > 0  ) 
		{
			
			j -= r *k ; 
			k = k/2, r=1 ;
		}
		
		j += k ; 
		i++ ; 
	}
	for ( int i = 0 ; i< N ; i++) 
	{
		int t = z[i] ;
		y_r[i] = x_r[t] ; 	
		y_i[i] = x_i[t] ; 
	}
	
	int l = 1 ; 
	while (l<=p)
	{
		double n = pow(2,l) ; 
		for ( int i = 0 ; i< n/2 ; i++)
		{
				double theta = -2.0*i*M_PI/n ; 
				double w_r = cos(theta);
				double w_i = sin(theta);
				
			for ( int j = i ; j < N ; j += n )
			{
				int k = j + n/2 ;
				
				double t_r = y_r[k]*w_r-w_i*y_i[k];
				double t_i = y_i[k]*w_r+w_i*y_r[k];
								
				y_r[k] = y_r[j]-t_r;
				y_i[k] = y_i[j]-t_i ; 
				y_r[j] += t_r ;
				y_i[j] += t_i ; 
				
			}
		
		}
		l++ ;
	}


	
	for ( int i = 0 ; i < N ; i++) cout << y_r[i] << "   i * " << y_i[i] << endl ;
	
}


void iFFT(double *x_r, double *x_i, double *y_r, double *y_i, int p) 
{
	int N = 1 ; 
	for ( int i = 0 ; i<p ;i ++) N = N*2 ; 
	
//	for ( int i = 0 ; i<N ; i++)
//	{
//		y_r[i] = x_r[i] ; 
//		y_i[i] = x_i[i] ; 
//	}

	int i = 0 , j = 0, M ;
	/*
	while ( i < N)
	{
		y_r[i] = j ; 
	
		 M = N/2 ; 
		int k = M  ; 
		int r = (N/M)-1 ; 
		while  ( j >= r * k  && k > 0  ) 
		{
			
			j -= r *k ; 
			k = k/2, r=1 ;
		}
		
		j += k ; 
		i++ ; 
	
	}
	*/
	double * z ;
	z =  (double*) malloc( N*sizeof(double)) ; 
	
	for ( int i = 0 ; i< N ;i ++) z[i] = i ; 
	
	while ( i < N)
	{
		z[i] = j ; 
	
		 M = N/2 ; 
		int k = M  ; 
		int r = (N/M)-1 ; 
		while  ( j >= r * k  && k > 0  ) 
		{
			
			j -= r *k ; 
			k = k/2, r=1 ;
		}
		
		j += k ; 
		i++ ; 
	}
	for ( int i = 0 ; i< N ; i++) 
	{
		int t = z[i] ;
		y_r[i] = x_r[t] ; 	
		y_i[i] = x_i[t] ; 
	}
	
	int l = 1 ; 
	while (l<=p)
	{
		double n = pow(2,l) ; 
		for ( int i = 0 ; i< n/2 ; i++)
		{
				double theta = 2.0*i*M_PI/n ; 
				double w_r = cos(theta);
				double w_i = sin(theta);
				
			for ( int j = i ; j < N ; j += n )
			{
				int k = j + n/2 ;
				
				double t_r = y_r[k]*w_r-w_i*y_i[k];
				double t_i = y_i[k]*w_r+w_i*y_r[k];
								
				y_r[k] = y_r[j]-t_r;
				y_i[k] = y_i[j]-t_i ; 
				y_r[j] += t_r ;
				y_i[j] += t_i ; 
				
			}
		
		}
		l++ ;
	}

	for ( int i = 0 ; i<N ;i++) y_r[i] = y_r[i] / N ; 
	for ( int i = 0 ; i<N ;i++) y_i[i] = y_i[i] / N ; 
	
	for ( int i = 0 ; i < N ; i++) cout << y_r[i] << "   i * " << y_i[i] << endl ;
	
}
	
	
	










