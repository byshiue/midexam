#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
using namespace std ; 

int EASYQUICK(int A[], int start, int end ) ; // first int is dclare an array, 
							   //second int declare the start position, 
								//The third int declare the end position. 

int main()
{
	// quicksort
	srand(time(0)) ; // random seed 
	const int m = 10 ;
	int Array[m] = {} ; 
	for ( int i = 0 ; i<m ; i++) Array[i] = rand()/10 ; // build up a random array
	
	cout << "The original array is :" << endl ;
	cout << setw(6) ;
	for ( int i = 0 ; i<m ; i++) cout << Array[i] << " " ; 
	cout << endl ;
	EASYQUICK( Array , 0 , m-1 )  ; 
	
	cout << "The sorted array is :" << endl ;
	cout << setw(6)  ;
	for ( int i = 0 ; i<m ; i++) cout << Array[i] << " " ; 
	cout << endl ;
	
	return 0 ;
}

int EASYQUICK(int A[], int start, int end )
{
	if ( end - start > 0 ) 
	{
		int pivot = A[end] ; 
		int B [end-start+1] ; 
		for ( int i = start ; i <= end ; i++) B[i] = 0 ; 
		
		int head=start, tail=end ; 
		for ( int i = start ; i< end ; i++)
		{
			if ( A[i] < pivot )
			{
				B[head] = A[i] ; 
				head ++ ; 
			}
			else 
			{
				B[tail] = A[i] ; 
				tail -- ; 
			}
		}
		int median = head  ; 
		B[median] = pivot ;
			
		for ( int i = start ; i<= end ; i++ ) A[i] = B[i] ; 
		if ( head >start) EASYQUICK(A,start,median-1) ; 
		if ( tail <end) EASYQUICK(A,median+1,end) ; 
		
	}
	
} 
