// sema.cpp

#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

volatile INT count;
HANDLE semaphore;

void CountThread(INT iterations)
{
  INT i;
  INT x;
  LONG semaCount;

  for (i=0; i<iterations; i++)
  {
    WaitForSingleObject(semaphore, INFINITE);
    x=count;
    x++;
    count=x;
    ReleaseSemaphore(semaphore, 1, &semaCount);
  }
}

const INT numThreads=4;

void main(void)
{
  HANDLE handles[numThreads];
  DWORD threadID;
  INT i;

  semaphore = CreateSemaphore(0, 1, 1, 0);

  for (i=0; i<numThreads; i++)
  {
    // create the threads
    handles[i]=CreateThread(0, 0,
      (LPTHREAD_START_ROUTINE) CountThread, 
      (VOID *) 25000, 0, &threadID);
  }

  // wait for all threads to finish execution
  WaitForMultipleObjects(numThreads, handles, 
    TRUE, INFINITE);  

  CloseHandle(semaphore);

  cout << "Global count = " << count << endl;
}
