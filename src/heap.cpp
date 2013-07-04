
// heap.cpp
// Rosen
// 2013-6-8

#include "heap.h"
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

bool HeapAdjust(vector<int> &heapVect, int src, int max);

void MakeHeap(vector<int> &heapVect );

int main(void)
{

	int 	numarray[] = {12, 23, 87,34,22,66,92,10,5};
	vector <int> ivect(numarray, numarray + sizeof(numarray)/sizeof(int));  

	for(vector<int>::iterator iter = ivect.begin(); iter != ivect.end(); iter++)
	{
   		std::cout << *iter << "  "; 
	}

	MakeHeap(ivect);

	cout << endl << "heap sorted: " << endl;
	copy(ivect.begin(), ivect.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;	
}

bool HeapAdjust(vector<int> &heapVect, int src, int max)
{
	bool retVal = false;

	int rc = heapVect[src];
	int j;

	if(0 == max ) return retVal;

	for(j = 2*src; j <= max; j = j * 2)
	{
		if (j < max && heapVect[j] > heapVect[j+1]) ++j; // get the less one
		if (rc < heapVect[j]) break; // the rc less than its children
		heapVect[src] = heapVect[j]; // the children is less, so move to its parent 
		src = j; // step on next level
	}

	heapVect[src] = rc; // get the original value rc right place 

	return retVal;
}

void MakeHeap(vector<int> &heapVect )
{
	int hsize = heapVect.size();
	cout << "heap size: " << hsize << endl;

	// make the little-top heap
	for(int index = (hsize-1)/2; index >= 0; index --) 
	{
		HeapAdjust(heapVect, index , hsize);	
	}

	cout << endl ;
	copy(heapVect.begin(), heapVect.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	for(int pos = hsize -1; pos >=0; pos-- )
	{
		swap(heapVect[0], heapVect[pos]);
		HeapAdjust(heapVect, 0, pos-1); // rebuild [0...pos] as new little-top heap
	}
}
