#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

int PARENT( int x) 
{
	return (x-1) / 2 ; 
}

int LEFT(int x)
{
	return (2*x+1) ; 
}

int RIGHT( int x) 
{
	return( 2*x+2) ; 
}

int HEAPIFY( int A[], int posi, int size) // posi :position
{
	int largest = posi ;
	if 	( LEFT(posi) < size )
	{
		if ( A[posi] < A[LEFT(posi)]) largest = LEFT(posi) ; 
		if ( RIGHT(posi) < size && A[RIGHT(posi)] > A[largest]) largest = RIGHT(posi) ; 
	}
	if ( largest != posi ) 
	{
		swap( A[largest], A[posi]);
		posi = largest ; 
		HEAPIFY(A,posi, size) ; 
	}
	
	
}

int main()
{	
	srand(time(0)) ; 
	int const m = 10 ; 
	int array[m] = {} ;
	for ( int i = 0 ; i < m ; i++) array[i] = rand() ; 
	
	cout << "The original array is :" << endl ;
	for ( int i = 0 ; i<m ; i++ ) cout << setw(5) << array[i] << " "  ;
	cout << endl ;
	
	for ( int i = m/2 ; i>= 0 ; i--) HEAPIFY(array,i,m) ; 
		
	int tail = m-1 ; 
	for ( int i = 0 ; i < m ; i++)
	{
		cout << setw(5) << array[0] << " " ; 
		array[0] = 0 ; 
		swap (array[0],array[tail]); 
		tail -- ; 
		HEAPIFY(array,0,tail+1); 
	}
	
}

