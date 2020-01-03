#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

volatile INT count;
CRITICAL_SECTION critSec;

void CountThread(INT iterations)
{
  INT i;
  INT x;

  for (i=0; i<iterations; i++)
  {
    EnterCriticalSection(&critSec);
    x=count;
    x++;
    count=x;
    LeaveCriticalSection(&critSec);
  }
}

const INT numThreads=4;

void main(void)
{
  HANDLE handles[numThreads];
  DWORD threadID;
  INT i;

  InitializeCriticalSection(&critSec);

  for (i=0; i<numThreads; i++)
  {
    // create a thread and pass it the pointer 
    // to its "params" struct
    handles[i]=CreateThread(0, 0,
      (LPTHREAD_START_ROUTINE) CountThread, 
      (VOID *) 25000, 0, &threadID);
  }

  // wait for all threads to finish execution
  WaitForMultipleObjects(numThreads, handles, 
						 TRUE, INFINITE);  

  DeleteCriticalSection(&critSec);

  cout << "Global count = " << count << endl;
}
