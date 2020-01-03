#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

void HonkThread(int iter)
{
  for (int i = 0; i < iter; i++) {
    Beep(200, 50);
    Sleep(1000);
  }
}

void main(void)
{
  char iterStr[80];
  cout << "Enter the number of beeps to produce: ";
  cin.getline(iterStr, 80);

  DWORD iterations;

  iterations=atoi(iterStr);

  DWORD threadID;
 
  HANDLE honkHandle=CreateThread(0, 0,
    (LPTHREAD_START_ROUTINE) HonkThread,
    (VOID *) iterations, 0, &threadID);

  int count = 0;
  while (WaitForSingleObject(honkHandle, 0) == WAIT_TIMEOUT)
    cout << "Waiting for the thread to finish "
      << count++ << endl;
}
