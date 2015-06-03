#include<iostream>
using namespace std;
int Group_2(double *x, double *y, int N)  ;
int main()
{
	double *x, *y;
	int p,N=1 ; 
	cin >> p ; 
	for ( int i = 0 ; i<p ; i++) N=N*2 ; 
	x = new double [N] ; 
	y = new double [N] ; 
	for ( int i = 0 ; i < N; i++) x[i] = i ; 
//	Group_2(x,y,N) ;
	
	
	int n = N , m ; 
	while(n>1)
	{
		m = 0 ; 
		while(m<N)
		{
			Group_2(x+m,y+m,n);
			m = m + n ;
			
		}
		n = n / 2 ;
		swap(x,y) ;
	}
	
	for ( int i = 0 ; i< N; i++) cout << y[i] << endl ;
}

int Group_2(double *x, double *y, int N)  
 {
	 int i;  
	 	// other way!  
	 for(i=0;i<N;++i)  
	 {  
	 		y[(i/2) + (N/2)*(i%2)] = x[i];  
	 }
	 	return 0;  
 }  

