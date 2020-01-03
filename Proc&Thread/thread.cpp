#include <windows.h>
#include <iostream.h>

volatile int count;

void CountThread()
{
  while (1) {
    count++;
    Sleep(100);
  }
}

void main(void)
{
  count=0;

  DWORD threadID;
  HANDLE countHandle=CreateThread(0, 0,
    (LPTHREAD_START_ROUTINE) CountThread,
    0, 0, &threadID);
  if (countHandle == 0)
    cout << "Cannot create thread: " << GetLastError() << endl;  

  char retStr[80];
  while (1)
  {
    cout << "Press <Enter> to display the count... ";
    cin.getline(retStr, 80);
    cout << "count: " << count << endl << endl;
  }
}
