#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

volatile INT count;
HANDLE event;

void CountThread(INT iterations)
{
  INT i;
  INT x;

  for (i=0; i<iterations; i++)
  {
    WaitForSingleObject(event, INFINITE);
    x=count;
    x++;
    count=x;
    SetEvent(event);
  }
}

const INT numThreads=4;

void main(void)
{
  HANDLE handles[numThreads];
  DWORD threadID;
  INT i;

  event = CreateEvent(0, FALSE, TRUE, 0);

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

  CloseHandle(event);

  cout << "Global count = " << count << endl;
}
