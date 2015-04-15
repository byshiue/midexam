#include<iostream>
#include<stdlib.h> //  srand 
#include<time.h>
using namespace std ; 

int main()
{
	int i,*vec; 
	const int N = 10 ; 
	time_t T = 1 ;  	// time( time_t *time) 
	srand(time(&T))  ;  // random seed 
	
	// Create N random integers 
	vec = (int *) malloc ( N* sizeof ( int )) ; 
	for ( i = 0 ;  i<N; i++)
	{
		vec[i] = rand() % 100 ; 
		cout << vec[i] << ", " ; 
	}
	cout << endl ;
	
	// Bubble sort 
	// compare two number each time , 
	// compare vec[i], vec[j] 
	// if vec[i] > vec[j] , then vec[i] <-> vec[j] 
	
	for ( int j = 1 ; j < N ; j++)
	{
		for ( i= 0 ; i<N-j ; i++)     // only need to compare N-1 numbers
		{
			if ( vec[i] > vec[i+1] )  //compare (vec[0],vec[1]) ,..., (vec[8],vec[9])
			{
//				int key = vec[i] ; 
//				vec[i] = vec[i+1] , vec[i+1] = key; 
			swap(vec[i],vec[i+1]) ; 
			}
		}
	}	
	
	
//	for ( i = 0 ; i < N ; i ++)
//	{
//		for ( int j = 0 ; j<i ; j++)
//		{
//			if ( vec[i] < vec[j] ) 
//			{
//				int key = vec[i] ; 
//				vec[i] = vec[j] , vec[j] = key; 
//			}
//		}
//	}
	
	for ( i = 0 ; i < N; i++) cout << vec[i] << ", " ; 
	cout << endl ;
	
	return 0 ; 
}
