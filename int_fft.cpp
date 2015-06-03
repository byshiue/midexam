#include<iostream>
#include<math.h>
using namespace std;
int ISPRIME(int p) ;
int FINDPRIME(int N, int start) ;
int FINDBASIS(int p, int t);

int main()
{

	int N=1, p, s ,M ,t=1  ; 
	cin >>  s; 
	for ( int i = 0 ; i< s ;i++) N = N*2 ; 
	M = 2 * (int(log10(N))+1) ; // length of the number * 2 
	while ( t < M)	{	t *= 2; } // t is the length of power of 2 such that t > M 
	
	int W = 0 ; 
	while ( W == 0 )
	{
		p = FINDPRIME(N, 1 ) ; 
		W = FINDBASIS(p, t) ; // basis element 
	}
//	p = FINDPRIME(N, 1 ) ; 
//	int b = FINDBASIS(p, t) ; 
//	
//	for ( int i = 0 ; i< t; i ++) 
//	{
//		cout << b << endl ;
//		b*= b ;
//		b = b% p ;  
//	}
//	cout << t << endl ;
	cout << p << endl ;
	cout << W << endl ;
	for ( int i = 0 ; i < t ; i++)
	{
			int r = 1 ; 
			for ( int j = 0 ; j <t ; j++)
			{
				for ( int l = 0 ; l < i*j ; l++) r = r*W % p; 
				cout << r << " " ; 
			}
			
		
		cout << endl ;
	}
	

	int o = 1 ; 
for ( int i = 0 ; i< 10 ; i++) 
{
	
	cout << o << endl ;
	o = o * W % p ; 
}
}

int ISPRIME(int p)
{
	int i = 2 ; 
	while ( (p%i)!= 0 && i < sqrt(p) )	
	{	i ++ ; 	}
	if ( (p%i) != 0  ) return 1 ; // if p is prime, cout 1. else cout 0.
	else	return 0 ; 	
	
}

int FINDPRIME(int N , int start )
{	
	int p = start ; 
	int r = 0 ; 
	int M = int(log10(N) ) +1 ;  // number of digits 
	while(r == 0 )
	{
		if ( p > 81*(M) && ISPRIME(p) == 1 ) 	r = 1 ;
		else 	p += 8 ; 
	}
	return p ; 
}

int FINDBASIS(int p, int t)
{
	int i = 1 ;
	while( i <  p  )
	{
		
		int m = 1 ; 
		for ( int k = 0 ; k< t ; k ++)
		{
			m *= i ; 
			m = m % p ; 
		}
		
		if ( m == 1 )
		{
			m = 1 ; 
			for ( int j = 0 ; j < t-1 ; j ++) 
			{	
				m *= i ; 
				m = m % p ; 
				if ( m == 1 ) break ; 
			}
			if ( m!= 1 ) return i ; 	
		}
		i++ ; 
	}
	return 0 ; 
}
