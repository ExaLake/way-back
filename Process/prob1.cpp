#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

volatile INT count;

void CountThread(INT iterations)
{
  INT i;
  INT x;

  for (i=0; i<iterations; i++)
  {
    x=count;
    x++;
    count=x;
  }
}

const INT numThreads=4;

void main(void)
{
  HANDLE handles[numThreads];
  DWORD threadID;
  INT i;

  for (i=0; i<numThreads; i++)
  {
    // create the threads
    handles[i]=CreateThread(0, 0,
      (LPTHREAD_START_ROUTINE) CountThread, 
      (VOID *) 250000, 0, &threadID);
  }

  // wait for all threads to finish execution
  WaitForMultipleObjects(numThreads, handles, 
    TRUE, INFINITE);  

  cout << "Global count = " << count << endl;
}
