#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <windows.h>
#include <winsock.h>



#include <Process.h>


static int threadNumber = 0;

#define NUMTHREADS 10

bool thStates[NUMTHREADS];

int runningTh = 0;


BOOL WINAPI ClientThread( LPVOID lp )
{

	 DWORD id =  GetCurrentThreadId();


	cout << " My id is :" << id << endl;
	
	double bigTime = 0.0 ;

	for ( int i = 0 ; i < 1000; i++ )
		for ( int j = 0 ; j < 10000 ; j++ )
			bigTime = bigTime*bigTime*bigTime*123123123*0.000123123;
		

	cout << "Done processing in thread " << id << endl;


	thStates[id] = true;
	return true;
}


bool CheckTState()
{
	for ( int i = 0 ; i < NUMTHREADS ; i++)
	{
		if ( thStates[i] == false )
		{
			return false;
		}
	}

	return true;

}



int main( int argc, char *argv[] )
{
	DWORD dwThreadId;	

	int tid = 0;
	int runningTh = 0;

	HANDLE hthread;
	
	for ( int i = 0 ; i < NUMTHREADS ; i ++)
	{
		
		hthread = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,0,
					(LPTHREAD_START_ROUTINE) ClientThread, (LPVOID)&i, 0,
					&dwThreadId );

		cout << "The ID of the create thread is : " << dwThreadId << endl;
	}

	bool threadsDone = false;
	WaitForSingleObject(hthread, INFINITE);

    
 
	return 0;
}