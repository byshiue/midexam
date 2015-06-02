#include<math.h>
#include<iostream>
using namespace std;


int * poly ( int value)
{
	int N = 1+ int( log10(value) ), M = 2*N-1;
	int *pv ; 
	pv = new int[M] ; 
	for ( int i = 0 ; i< M; i++) pv[i] = 0 ; 
	int k = N-1 ; 
	while ( value > 0 )
	{
		pv[M-1-k] = int ( value/ (int(pow(10,k)) )) ; 
		value -= pv[M-1-k]*pow(10,k) ; 
		k-- ;
	}
	return pv ; 
}

int main()
{
	int * p ; 
	int n ; 
	cin >> n ; 
	p = poly(n)  ; 
	for ( int i = 0 ; i< 1+2*int(log10(n) );i++ ) cout << p[i] << " " ;
	cout << endl ;
}
