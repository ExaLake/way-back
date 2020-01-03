#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

typedef struct
{
  DWORD frequency;
  DWORD duration;
  DWORD iterations;
} honkParams;

void HonkThread(honkParams *params)
{
  DWORD i;

  for (i=0; i<params->iterations; i++)
  {
    Beep(params->frequency, params->duration);
    Sleep(1000);
  }
}

void main(void)
{
  HANDLE honkHandle;
  DWORD threadID;
  honkParams params;
  CHAR freqStr[100];
  CHAR durStr[100];
  CHAR iterStr[100];

  cout << "Enter the beep frequency to produce: ";
  cin.getline(freqStr, 100);
  params.frequency=atoi(freqStr);

  cout << "Enter the beep duration to produce: ";
  cin.getline(durStr, 100);
  params.duration=atoi(durStr);

  cout << "Enter the number of beeps to produce: ";
  cin.getline(iterStr, 100);
  params.iterations=atoi(iterStr);

  // create a thread and pass it the address of
  //the "params" structure
  honkHandle=CreateThread(0, 0,
    (LPTHREAD_START_ROUTINE) HonkThread,
    &params, 0, &threadID);

  WaitForSingleObject(honkHandle, INFINITE);  
}
