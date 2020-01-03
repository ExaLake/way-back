#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

volatile INT count;
CRITICAL_SECTION critSec;

const int NUM_PHILO = 5;


static const int NUM_BOUCHEE = 10;

HANDLE hMutexPoles[NUM_PHILO];


void Philisophe(INT id)
{
	for ( int i = 0 ; i < NUM_BOUCHEE ; i++)
		cout << "My Philisophe ID is : " << id << endl; 
	
	EnterCriticalSection(&critSec);

	LeaveCriticalSection(&critSec);
}


void main(void)
{
  HANDLE hPhilisophe[NUM_PHILO];
  DWORD threadID;
  INT i;

  InitializeCriticalSection(&critSec);
	
  for ( int h = 0 ; h < NUM_PHILO ; h++)
  {
	  hMutexPoles[h] = CreateMutex(0, FALSE, 0);
  }


  for (i=0; i< NUM_PHILO; i++)
  {
    // create a thread and pass it the pointer 
    // to its "params" stru
    hPhilisophe[i]=CreateThread(0, 0,
      (LPTHREAD_START_ROUTINE) Philisophe, 
       (VOID *) i, 0, &threadID);
  }

  
  // wait for all threads to finish execution
  WaitForMultipleObjects(NUM_PHILO, hPhilisophe, TRUE, INFINITE);  

  DeleteCriticalSection(&critSec);

  cout << "Dinner done..." << endl;
}
