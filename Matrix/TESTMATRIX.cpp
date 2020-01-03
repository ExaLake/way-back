// TESTMatrix.cpp : Defines the entry point for the console application.
//


#include <iostream.h>
#include "matrix.h"
#include <windows.h>
#include <winbase.h>
#include <typeinfo>



void OuputMatToScreen(Matrix<double> m)
{
	for ( register size_t i = 0 ; i < m.GetNumColumn() ; i++)
	{
		for ( register size_t j = 0 ; j < m.GetNumRow() ; j++)
			cout << m[i][j] << " ";

		cout << endl;
	}
}


int main(int argc, char* argv[])
{
	int i,j;

	if ( argc < 3 )
	{
		cout << "usage: testmatrix i j " << endl;
		cout << "i: " ;
		cin >> i;
		cout << "j: ";
		cin >> j;

	}
	else
	{
		i = atoi(argv[1]);
		j = atoi(argv[2]);
	}

	

	

	
	Matrix<double> m1(i, j,1);
	Matrix<double> m2(i, j,1);
	Matrix<double> m3(i, j,0);

	
	m1[0][0] = 1;
	m1[0][1] = 2;
	m1[1][0] = 3;
	m1[1][1] = 4;

	m2[0][0] = 5;
	m2[0][1] = 6;
	m2[1][0] = 7;
	m2[1][1] = 8;
	

	//OuputMatToScreen( m1);
	//cout << endl;
	//OuputMatToScreen( m2);
	//cout << endl;

	SYSTEMTIME *timeBefore = new SYSTEMTIME;
	SYSTEMTIME *timeAfter  = new SYSTEMTIME;

	GetLocalTime(timeBefore);

    
	cout << "Computing ..." << endl;

		m3 = m1*m2;
	cout << "Done." << endl;
	GetLocalTime(timeAfter);


	int milliseconds; 
	int seconds; 
	int minutes	;

	if ( (timeAfter->wMilliseconds - timeBefore->wMilliseconds) >= 0 )
		milliseconds = (int)(timeAfter->wMilliseconds - timeBefore->wMilliseconds);
	else
		milliseconds = (int)(timeBefore->wMilliseconds - timeAfter->wMilliseconds);

	 if ( (timeAfter->wSecond - timeBefore->wSecond) >= 0 )
		 seconds = (int)(timeAfter->wSecond - timeBefore->wSecond);
	 else
		 seconds = (int)(timeBefore->wSecond - timeAfter->wSecond);

	 if ( (timeAfter->wMinute - timeBefore->wMinute) >= 0 )
		 minutes = (int)(timeAfter->wMinute - timeBefore->wMinute);
	 else
		 minutes = (int)(timeBefore->wMinute - timeAfter->wMinute);
	
	cout << "Elapsed time : " << minutes << " min. "
		 << seconds << " sec. " 
		 << milliseconds << " microsec. " << endl;

	//OuputMatToScreen( m3);
	cout << "hit to return" << endl;
	int dymmy;
	cin >> dymmy;








	
	
	


	//cout << typeid(m).name() << endl;
	return 0;
}
