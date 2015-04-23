// QUICK_MEDIAN
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
using namespace std ; 
const int N = 15 ; // the size of the array
int QUICK_MEDIAN( int * , int , int, int  );
int main()
{
	int *pa = new int [N] ; 
	int median = (N+1)/2 ; 
	srand(time(0)) ; // random seed
	for ( int i = 0  ; i< N ; i++) pa[i] = rand() % 10000 , cout<< setw(4) << pa[i] << " " ; 
	cout << endl ;
	QUICK_MEDIAN(pa, 0 , N-1, median) ;
}

int QUICK_MEDIAN( int * pv, int start, int end, int me )
{
	if ( (end-start) > 0)
	{
		int count = end ;
		int pivot = pv[end] ; 
		for ( int i = start  ; i<=end-1 ; i++) 
		{
			while ( pv[i] >= pivot && count > i )
			{
				count -- ; 
				swap(pv[i],pv[count]) ; 
			}
		}
		swap(pv[end],pv[count]) ; 
		if ( count+1 < me ) QUICK_MEDIAN( pv, count+1 , end , me);
		else if ( count+1 > me ) QUICK_MEDIAN(pv, start, count-1 ,me );
		else  cout << "THe answer is : " << pv[count] << endl ;
	
		
	}
	else 	cout << "The answer is : " << pv[end] << endl;
		
}
	

