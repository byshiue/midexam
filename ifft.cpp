#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
using namespace std; 

int INITIAL(double *x_r, double*x_i, int N)  ; 
void FFT(double *x_r, double *x_i, double *y_r, double *y_i,int p, int q , int r)  ;
void iFFT(double *x_r, double *x_i, double *y_r, double *y_i,int p, int q , int r)  ;
int main()
{
	double *x_r, *x_i, *y_r, *y_i ; 
	int p, q, r, N=1 ; 
	
	cout << "Please input the p, q, r :" ;
	cin >> p >> q >> r  ;
	for ( int i = 0 ; i<p ;i ++) N = N*2 ; 
	for ( int i = 0 ; i<q ;i ++) N = N*3 ; 
	for ( int i = 0 ; i<r ;i ++) N = N*5 ; 
	cout << "N = 2^" << p << " * 3^" << q << " * 5^" << r << " = " << N << endl ;
	
	x_r = (double*) malloc( N*sizeof(double)) ; 
	x_i = (double*) malloc( N*sizeof(double)) ; 
	y_r = (double*) malloc( N*sizeof(double)) ; 
	y_i = (double*) malloc( N*sizeof(double)) ; 
	INITIAL(x_r, x_i, N) ; 
	
	
	FFT(x_r,x_i,y_r,y_i,p,q,r) ;
	
}

int INITIAL(double *x_r, double*x_i, int N)  
{
	for ( int i = 0 ; i< N ; i++)
	{
		x_r[i] = i ;
		x_i[i] = 0.0 ; 
	}
}

void FFT(double *x_r, double *x_i, double *y_r, double *y_i, int p, int q , int r) 
{
	int N = 1 ; 
	for ( int i = 0 ; i<p ;i ++) N = N*2 ; 
	for ( int i = 0 ; i<q ;i ++) N = N*3 ; 
	for ( int i = 0 ; i<r ;i ++) N = N*5 ; 
	
	for ( int i = 0 ; i<N ; i++)
	{
		y_r[i] = x_r[i] ; 
		y_i[i] = x_i[i] ; 
	}

	int i = 0 , j = 0, M ;
	
	while ( i < N)
	{
		y_r[i] = j ; 
	
		if ( N%5 == 0 ) M = N/5 ; 
		else if ( N%5 != 0 && N % 3 == 0 ) M = N/3 ; 
		else M = N/2 ; 
		int k = M  ; 
		int r = (N/M)-1 ; 
		while  ( j >= r * k  && k > 0  ) 
		{
			
			j -= r *k ; 
			if ( k%5 == 0 ) k = k/5, r = 4 ; 
			else if ( k%5 != 0 && k % 3 == 0 ) k = k/3, r=2 ; 
			else k = k/2, r=1 ;
		}
		
		j += k ; 
		i++ ; 
	
	}
	
	int l = 1 ;
	while (l<=r)
	{
		double n = pow(5,l) ; 
		
		for ( int i = 0 ; i< n/5 ; i++)
		{
				double phi = -2.0*M_PI*i/n ; 
				double theta = -2.0*M_PI/5 ; 
				double w_r = cos(theta);
				double w_i = sin(theta);
				double w2_r = cos(2*theta);
				double w2_i = sin(2*theta);
				
				double v_r = cos(phi) ; 
				double v_i = sin(phi) ; 
				double v2_r = cos(phi*2) ; 
				double v2_i = sin(phi*2) ; 
				double v3_r = cos(phi*3) ; 
				double v3_i = sin(phi*3) ; 
				double v4_r = cos(phi*4) ; 
				double v4_i = sin(phi*4) ; 
								
			for ( int j = i ; j < N ; j += n )
			{
				int j1 = j + n/5 ;
				int j2 = j + 2*n/5 ;
				int j3 = j + 3*n/5 ;  
				int j4 = j + 4*n/5 ; 
				double temp ;
				
				temp = y_r[j1]*v_i + y_i[j1]*v_r ; 
				y_r[j1] = y_r[j1]*v_r - y_i[j1]*v_i ; 
				y_i[j1] = temp ;
				
				temp = y_r[j2]*v2_i + y_i[j2]*v2_r ; 
				y_r[j2] = y_r[j2]*v2_r - y_i[j2]*v2_i ; 
				y_i[j2] = temp ;
				
				temp = y_r[j3]*v3_i + y_i[j3]*v3_r ; 
				y_r[j3] = y_r[j3]*v3_r - y_i[j3]*v3_i ; 
				y_i[j3] = temp ;
				
				temp = y_r[j4]*v4_i + y_i[j4]*v4_r ;  
				y_r[j4] = y_r[j4]*v4_r - y_i[j4]*v4_i ; 
				y_i[j4] = temp ;
				
				double a11_r = y_r[j1]*w_r-w_i*y_i[j1];
				double a11_i = y_i[j1]*w_r+w_i*y_r[j1];
				double a21_r = y_r[j1]*w2_r-w2_i*y_i[j1] ; 
				double a21_i = y_i[j1]*w2_r+w2_i*y_r[j1];
				double a41_r = y_r[j1]*w2_r+w2_i*y_i[j1] ; 
				double a41_i = y_i[j1]*w2_r-w2_i*y_r[j1];
				double a31_r = y_r[j1]*w_r+w_i*y_i[j1];
				double a31_i = y_i[j1]*w_r-w_i*y_r[j1];
								
				double a42_r = y_r[j2]*w_r-w_i*y_i[j2];
				double a42_i = y_i[j2]*w_r+w_i*y_r[j2];
				double a12_r = y_r[j2]*w2_r-w2_i*y_i[j2] ; 
				double a12_i = y_i[j2]*w2_r+w2_i*y_r[j2];
				double a32_r = y_r[j2]*w2_r+w2_i*y_i[j2] ; 
				double a32_i = y_i[j2]*w2_r-w2_i*y_r[j2];
				double a22_r = y_r[j2]*w_r+w_i*y_i[j2];
				double a22_i = y_i[j2]*w_r-w_i*y_r[j2];
				
				double a23_r = y_r[j3]*w_r-w_i*y_i[j3];
				double a23_i = y_i[j3]*w_r+w_i*y_r[j3];
				double a33_r = y_r[j3]*w2_r-w2_i*y_i[j3] ; 
				double a33_i = y_i[j3]*w2_r+w2_i*y_r[j3];
				double a13_r = y_r[j3]*w2_r+w2_i*y_i[j3] ; 
				double a13_i = y_i[j3]*w2_r-w2_i*y_r[j3];
				double a43_r = y_r[j3]*w_r+w_i*y_i[j3];
				double a43_i = y_i[j3]*w_r-w_i*y_r[j3];
				
				double a34_r = y_r[j4]*w_r-w_i*y_i[j4];
				double a34_i = y_i[j4]*w_r+w_i*y_r[j4];
				double a44_r = y_r[j4]*w2_r-w2_i*y_i[j4] ; 
				double a44_i = y_i[j4]*w2_r+w2_i*y_r[j4];
				double a24_r = y_r[j4]*w2_r+w2_i*y_i[j4] ; 
				double a24_i = y_i[j4]*w2_r-w2_i*y_r[j4];
				double a14_r = y_r[j4]*w_r+w_i*y_i[j4];
				double a14_i = y_i[j4]*w_r-w_i*y_r[j4];
				
				double u_r = y_r[j1] + y_r[j2] + y_r[j3] + y_r[j4] ; 
				double u_i = y_i[j1] + y_i[j2] + y_i[j3] + y_i[j4] ;
								
				y_r[j1] = y_r[j]+ a11_r + a12_r + a13_r +a14_r ; 
				y_i[j1] = y_i[j]+ a11_i + a12_i + a13_i +a14_i ; 
				y_r[j2] = y_r[j]+ a21_r + a22_r + a23_r +a24_r ; 
				y_i[j2] = y_i[j]+ a21_i + a22_i + a23_i +a24_i ;
				y_r[j3] = y_r[j]+ a41_r + a42_r + a43_r +a44_r ; 
				y_i[j3] = y_i[j]+ a41_i + a42_i + a43_i +a44_i ;
				y_r[j4] = y_r[j]+ a31_r + a32_r + a33_r +a34_r ; 
				y_i[j4] = y_i[j]+ a31_i + a32_i + a33_i +a34_i ;
				y_r[j] += u_r ;
				y_i[j] += u_i ; 
		
			}
		
		}
		l++ ; 
	}
	
	
	l = 1 ; 
	while (l<=q)
	{
		double n = pow(3,l)*pow(5,r) ;	
		for ( int i = 0 ; i< n/3 ; i++)
		{
				double phi = -2.0*M_PI*i/n ; 
				double theta = -2.0*M_PI/3 ; 
				double w_r = cos(theta);
				double w_i = sin(theta);
				double v_r = cos(phi) ; 
				double v_i = sin(phi) ; 
				double v2_r = cos(phi*2) ; 
				double v2_i = sin(phi*2) ; 
				
			for ( int j = i ; j < N ; j += n )
			{
				int j1 = j + n/3 ;
				int j2 = j + 2*n/3 ; 
				
				double temp = y_r[j1]*v_i + y_i[j1]*v_r ;
				y_r[j1] = y_r[j1]*v_r - y_i[j1]*v_i ; 
				y_i[j1] = temp ;
				
				temp = y_r[j2]*v2_i + y_i[j2]*v2_r ;
				y_r[j2] = y_r[j2]*v2_r - y_i[j2]*v2_i ; 
				y_i[j2] = temp ;
				
				
				double t_r = y_r[j1]*w_r-w_i*y_i[j1];
				double t_i = y_i[j1]*w_r+w_i*y_r[j1];
				double t2_r = y_r[j1] *w_r+w_i*y_i[j1] ; 
				double t2_i = y_i[j1]*w_r-w_i*y_r[j1];
				
				double s_r = y_r[j2]*w_r+y_i[j2]*w_i;
				double s_i = -y_r[j2]*w_i+y_i[j2]*w_r;
				double s2_r = y_r[j2]*w_r-y_i[j2]*w_i;
				double s2_i = y_r[j2]*w_i+y_i[j2]*w_r;
				
				double u_r = y_r[j1] + y_r[j2] ;
				double u_i = y_i[j1] + y_i[j2] ;
								
				y_r[j1] = y_r[j]+t_r+s_r;
				y_i[j1] = y_i[j]+t_i+s_i ; 
				y_r[j2] = y_r[j]+t2_r+s2_r ;
				y_i[j2] = y_i[j]+t2_i+s2_i ; 
				y_r[j] += u_r ;
				y_i[j] += u_i ; 
				
				
			}
		
		}
		l++ ;
	}
	
	l = 1 ; 
	while (l<=p)
	{
		double n = pow(2,l)*pow(3,q)*pow(5,r) ; 
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

void iFFT(double *x_r, double *x_i, double *y_r, double *y_i, int p, int q , int r) 
{
	int N = 1 ; 
	for ( int i = 0 ; i<p ;i ++) N = N*2 ; 
	for ( int i = 0 ; i<q ;i ++) N = N*3 ; 
	for ( int i = 0 ; i<r ;i ++) N = N*5 ; 
	
	for ( int i = 0 ; i<N ; i++)
	{
		y_r[i] = x_r[i] ; 
		y_i[i] = x_i[i] ; 
	}

	int i = 0 , j = 0, M ;
	
	while ( i < N)
	{
		y_r[i] = j ; 
	
		if ( N%5 == 0 ) M = N/5 ; 
		else if ( N%5 != 0 && N % 3 == 0 ) M = N/3 ; 
		else M = N/2 ; 
		int k = M  ; 
		int r = (N/M)-1 ; 
		while  ( j >= r * k  && k > 0  ) 
		{
			
			j -= r *k ; 
			if ( k%5 == 0 ) k = k/5, r = 4 ; 
			else if ( k%5 != 0 && k % 3 == 0 ) k = k/3, r=2 ; 
			else k = k/2, r=1 ;
		}
		
		j += k ; 
		i++ ; 
	
	}
	
	int l = 1 ;
	while (l<=r)
	{
		double n = pow(5,l) ; 
		
		for ( int i = 0 ; i< n/5 ; i++)
		{
				double phi = 2.0*M_PI*i/n ; 
				double theta = 2.0*M_PI/5 ; 
				double w_r = cos(theta);
				double w_i = sin(theta);
				double w2_r = cos(2*theta);
				double w2_i = sin(2*theta);
				
				double v_r = cos(phi) ; 
				double v_i = sin(phi) ; 
				double v2_r = cos(phi*2) ; 
				double v2_i = sin(phi*2) ; 
				double v3_r = cos(phi*3) ; 
				double v3_i = sin(phi*3) ; 
				double v4_r = cos(phi*4) ; 
				double v4_i = sin(phi*4) ; 
								
			for ( int j = i ; j < N ; j += n )
			{
				int j1 = j + n/5 ;
				int j2 = j + 2*n/5 ;
				int j3 = j + 3*n/5 ;  
				int j4 = j + 4*n/5 ; 
				double temp ;
				
				temp = y_r[j1]*v_i + y_i[j1]*v_r ; 
				y_r[j1] = y_r[j1]*v_r - y_i[j1]*v_i ; 
				y_i[j1] = temp ;
				
				temp = y_r[j2]*v2_i + y_i[j2]*v2_r ; 
				y_r[j2] = y_r[j2]*v2_r - y_i[j2]*v2_i ; 
				y_i[j2] = temp ;
				
				temp = y_r[j3]*v3_i + y_i[j3]*v3_r ; 
				y_r[j3] = y_r[j3]*v3_r - y_i[j3]*v3_i ; 
				y_i[j3] = temp ;
				
				temp = y_r[j4]*v4_i + y_i[j4]*v4_r ;  
				y_r[j4] = y_r[j4]*v4_r - y_i[j4]*v4_i ; 
				y_i[j4] = temp ;
				
				double a11_r = y_r[j1]*w_r-w_i*y_i[j1];
				double a11_i = y_i[j1]*w_r+w_i*y_r[j1];
				double a21_r = y_r[j1]*w2_r-w2_i*y_i[j1] ; 
				double a21_i = y_i[j1]*w2_r+w2_i*y_r[j1];
				double a41_r = y_r[j1]*w2_r+w2_i*y_i[j1] ; 
				double a41_i = y_i[j1]*w2_r-w2_i*y_r[j1];
				double a31_r = y_r[j1]*w_r+w_i*y_i[j1];
				double a31_i = y_i[j1]*w_r-w_i*y_r[j1];
								
				double a42_r = y_r[j2]*w_r-w_i*y_i[j2];
				double a42_i = y_i[j2]*w_r+w_i*y_r[j2];
				double a12_r = y_r[j2]*w2_r-w2_i*y_i[j2] ; 
				double a12_i = y_i[j2]*w2_r+w2_i*y_r[j2];
				double a32_r = y_r[j2]*w2_r+w2_i*y_i[j2] ; 
				double a32_i = y_i[j2]*w2_r-w2_i*y_r[j2];
				double a22_r = y_r[j2]*w_r+w_i*y_i[j2];
				double a22_i = y_i[j2]*w_r-w_i*y_r[j2];
				
				double a23_r = y_r[j3]*w_r-w_i*y_i[j3];
				double a23_i = y_i[j3]*w_r+w_i*y_r[j3];
				double a33_r = y_r[j3]*w2_r-w2_i*y_i[j3] ; 
				double a33_i = y_i[j3]*w2_r+w2_i*y_r[j3];
				double a13_r = y_r[j3]*w2_r+w2_i*y_i[j3] ; 
				double a13_i = y_i[j3]*w2_r-w2_i*y_r[j3];
				double a43_r = y_r[j3]*w_r+w_i*y_i[j3];
				double a43_i = y_i[j3]*w_r-w_i*y_r[j3];
				
				double a34_r = y_r[j4]*w_r-w_i*y_i[j4];
				double a34_i = y_i[j4]*w_r+w_i*y_r[j4];
				double a44_r = y_r[j4]*w2_r-w2_i*y_i[j4] ; 
				double a44_i = y_i[j4]*w2_r+w2_i*y_r[j4];
				double a24_r = y_r[j4]*w2_r+w2_i*y_i[j4] ; 
				double a24_i = y_i[j4]*w2_r-w2_i*y_r[j4];
				double a14_r = y_r[j4]*w_r+w_i*y_i[j4];
				double a14_i = y_i[j4]*w_r-w_i*y_r[j4];
				
				double u_r = y_r[j1] + y_r[j2] + y_r[j3] + y_r[j4] ; 
				double u_i = y_i[j1] + y_i[j2] + y_i[j3] + y_i[j4] ;
								
				y_r[j1] = y_r[j]+ a11_r + a12_r + a13_r +a14_r ; 
				y_i[j1] = y_i[j]+ a11_i + a12_i + a13_i +a14_i ; 
				y_r[j2] = y_r[j]+ a21_r + a22_r + a23_r +a24_r ; 
				y_i[j2] = y_i[j]+ a21_i + a22_i + a23_i +a24_i ;
				y_r[j3] = y_r[j]+ a41_r + a42_r + a43_r +a44_r ; 
				y_i[j3] = y_i[j]+ a41_i + a42_i + a43_i +a44_i ;
				y_r[j4] = y_r[j]+ a31_r + a32_r + a33_r +a34_r ; 
				y_i[j4] = y_i[j]+ a31_i + a32_i + a33_i +a34_i ;
				y_r[j] += u_r ;
				y_i[j] += u_i ; 
		
			}
		
		}
		l++ ; 
	}
	
	
	l = 1 ; 
	while (l<=q)
	{
		double n = pow(3,l)*pow(5,r) ;	
		for ( int i = 0 ; i< n/3 ; i++)
		{
				double phi = 2.0*M_PI*i/n ; 
				double theta = 2.0*M_PI/3 ; 
				double w_r = cos(theta);
				double w_i = sin(theta);
				double v_r = cos(phi) ; 
				double v_i = sin(phi) ; 
				double v2_r = cos(phi*2) ; 
				double v2_i = sin(phi*2) ; 
				
			for ( int j = i ; j < N ; j += n )
			{
				int j1 = j + n/3 ;
				int j2 = j + 2*n/3 ; 
				
				double temp = y_r[j1]*v_i + y_i[j1]*v_r ;
				y_r[j1] = y_r[j1]*v_r - y_i[j1]*v_i ; 
				y_i[j1] = temp ;
				
				temp = y_r[j2]*v2_i + y_i[j2]*v2_r ;
				y_r[j2] = y_r[j2]*v2_r - y_i[j2]*v2_i ; 
				y_i[j2] = temp ;
				
				
				double t_r = y_r[j1]*w_r-w_i*y_i[j1];
				double t_i = y_i[j1]*w_r+w_i*y_r[j1];
				double t2_r = y_r[j1] *w_r+w_i*y_i[j1] ; 
				double t2_i = y_i[j1]*w_r-w_i*y_r[j1];
				
				double s_r = y_r[j2]*w_r+y_i[j2]*w_i;
				double s_i = -y_r[j2]*w_i+y_i[j2]*w_r;
				double s2_r = y_r[j2]*w_r-y_i[j2]*w_i;
				double s2_i = y_r[j2]*w_i+y_i[j2]*w_r;
				
				double u_r = y_r[j1] + y_r[j2] ;
				double u_i = y_i[j1] + y_i[j2] ;
								
				y_r[j1] = y_r[j]+t_r+s_r;
				y_i[j1] = y_i[j]+t_i+s_i ; 
				y_r[j2] = y_r[j]+t2_r+s2_r ;
				y_i[j2] = y_i[j]+t2_i+s2_i ; 
				y_r[j] += u_r ;
				y_i[j] += u_i ; 
				
				
			}
		
		}
		l++ ;
	}
	
	l = 1 ; 
	while (l<=p)
	{
		double n = pow(2,l)*pow(3,q)*pow(5,r) ; 
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

	for ( int i = 0 ; i<N ;i++) y_r[i] = y_r[i]  /N ; 
	for ( int i = 0 ; i<N ;i++) y_i[i] = y_i[i] /N ; 
	
	for ( int i = 0 ; i < N ; i++) cout << y_r[i] << "   i * " << y_i[i] << endl ;
	
}

























