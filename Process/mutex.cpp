#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

volatile INT count;
HANDLE mutex;

void CountThread(INT iterations)
{
  INT i;
  INT x;

  for (i=0; i<iterations; i++)
  {
    WaitForSingleObject(mutex, INFINITE);
    x=count;
    x++;
    count=x;
    ReleaseMutex(mutex);
  }
}

const INT numThreads=4;

void main(void)
{
  HANDLE handles[numThreads];
  DWORD threadID;
  INT i;

  mutex = CreateMutex(0, FALSE, 0);

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

  CloseHandle(mutex);

  cout << "Global count = " << count << endl;
} 
