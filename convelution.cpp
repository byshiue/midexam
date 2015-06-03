#include<math.h>
#include<iostream>
using namespace std;


int * poly ( int value, int & len)
{
	int N = 1+ int( log10(value) ), M = 2*N-1;
	int size = 1 ; 
	while ( size < M) size *= 2  ;
	int *pv ; 
	pv = new int[size] ; 
	for ( int i = 0 ; i< size; i++) pv[i] = 0 ; 
	int k = N-1 ; 
	while ( value > 0 )
	{
		pv[size-1-k] = int ( value/ (int(pow(10,k)) )) ; 
		value -= pv[size-1-k]*pow(10,k) ; 
		k-- ;
	}
	len = size;
	return pv ; 
}

int main()
{
	int * p ; 
	int n,len ; 
	cin >> n ; 
	p = poly(n,len)  ; 
	for ( int i = 0 ; i< len;i++ ) cout << p[i] << " " ;
	cout << endl ;
}
