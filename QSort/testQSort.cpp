// testQSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#define SIZE 200000

#define Random() rand

int Partition(int *pArray, int p, int r)
{
	int x = pArray[p];
	int i = p-1;
	int j = r+1;

	while(1)
	{
		do 
		{
			j--;
		}
		while( (pArray[j] > x)  );
		
		do
		{
			i++;
		}
		while ( (pArray[i] < x) );
		

		if ( i < j )
		{
			//Exchange...
			int temp = pArray[i];
			pArray[i] = pArray[j];
			pArray[j] = temp;
		}
		else 
			return j;	
	}
}


void QSort(int *pArray, int p, int r)
{
	int q;

	if ( p < r )
	{
		q = Partition(pArray, p, r);
		QSort(pArray,p,q);
		QSort(pArray,q+1,r);
	}
}


void Execute1()
{
	srand( 90 );

	// Constructing the array
	cout << "Constructing the Array" << endl;
	int pArray[SIZE];
	for ( int i = 0 ; i < SIZE ; i++)
		pArray[i] = rand();

	cout << "Sorting ...";

	DWORD dwBefore = timeGetTime();
	QSort(pArray, 0, SIZE-1);
	cout << "Done." << endl;
	DWORD dwAfter = timeGetTime();

	cout << "Elapsed time for sorting : " << dwAfter - dwBefore << endl;

	//for ( i = 0 ; i < SIZE ; i++)
	//	cout << pArray[i] << endl;
}



int main(int argc, char* argv[])
{	
	Execute1();
	return 0;
}
