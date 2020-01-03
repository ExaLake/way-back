#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

volatile int count;
void CountThread()
{
  while (1) {
	  count ++;
	  cout << count << endl;
  }

 
}

void main(void)
{
  HANDLE contHandles[4];
  DWORD threadID;
  
  DWORD count;
  

  for (count=0; count <4; count++)
  {
	countHandles[count]=CreateThread(0, 0,
      (LPTHREAD_START_ROUTINE) CountThread, 
      0, 0, &threadID);
  }

  WaitForMultipleObjects(4, countHandles, 
    TRUE, INFINITE);  
}
