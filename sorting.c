#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i, j, N, *v, temp;
	time_t T = 1;
	
	// Create N random integers
	srand(time(&T));
	N = 10;
	v = (int *) malloc( N * sizeof(int) );
	for(i=0;i<N;++i)
	{
		v[i] = rand() % 100;
		printf("%d,",v[i]);
	}
	printf("\n");
	
	// Bubble Sort
	// compare v[i] and v[j], 
	// if v[i] > v[j] then v[i] <-> v[j]
	// 由左到右，相鄰兩兩比較，較大者往右挪，
	// 最後最大值會出現在陣列右端。
	// 遞迴處理尚未排序的 N-1 個元素。
	for(i=0;i<N-1;++i) // 由左到右  N-1 need your attention
	{
		if(v[i]>v[i+1]) // 相鄰兩兩比較: compare (V[0],V[1]),(V[1],V[2])...(V[8],V[9])
		{					// 較大者往右移
			temp = v[i];	// 不能只寫下面這樣... 
			v[i] = v[i+1];	// V[0] = V[1]
			v[i+1] = temp;  // V[1] = V[0]
		}
	}
	for(i=0;i<N;++i) // 由左到右  N-1 need your attention
	{
		printf("%d,",v[i]);
	}
	printf("\n");

	for(i=0;i<N-2;++i) // 由左到右  N-1 need your attention
	{
		if(v[i]>v[i+1]) // 相鄰兩兩比較: compare (V[0],V[1]),(V[1],V[2])...(V[8],V[9])
		{					// 較大者往右移
			temp = v[i];	// 不能只寫下面這樣... 
			v[i] = v[i+1];	// V[0] = V[1]
			v[i+1] = temp;  // V[1] = V[0]
		}
	}
	
	for(i=0;i<N;++i) // 由左到右  N-1 need your attention
	{
		printf("%d,",v[i]);
	}
	printf("\n");
	// 總不能一直複製貼上貼到死吧…
	for(j=1;j<N;++j)
	{
		for(i=0;i<N-j;++i) // 由左到右  N-1 need your attention
		{
			if(v[i]>v[i+1]) // 相鄰兩兩比較: compare (V[0],V[1]),(V[1],V[2])...(V[8],V[9])
			{					// 較大者往右移
				temp = v[i];	// 不能只寫下面這樣... 
				v[i] = v[i+1];	// V[0] = V[1]
				v[i+1] = temp;  // V[1] = V[0]
			}
		}
		for(i=0;i<N;++i) // 由左到右  N-1 need your attention
		{
			printf("%d,",v[i]);
		}
		printf("\n");
	}
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
