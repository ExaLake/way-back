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

  GlobalFree(params);
}

void main(void)
{
  HANDLE honkHandles[3];
  DWORD threadID;
  honkParams *params;
  DWORD count;
  CHAR freqStr[100];
  CHAR durStr[100];
  CHAR iterStr[100];

  for (count=0; count<3; count++)
  {
    params=(honkParams *) GlobalAlloc(GPTR, 
      sizeof(honkParams));

    cout << "Enter the beep frequency: ";
    cin.getline(freqStr, 100);
    params->frequency=atoi(freqStr);

    cout << "Enter the beep duration: ";
    cin.getline(durStr, 100);
    params->duration=atoi(durStr);

    cout << "Enter the number of beeps: ";
    cin.getline(iterStr, 100);
    params->iterations=atoi(iterStr);

    honkHandles[count]=CreateThread(0, 0,
      (LPTHREAD_START_ROUTINE) HonkThread, 
      params, 0, &threadID);
  }

  WaitForMultipleObjects(3, honkHandles, 
    TRUE, INFINITE);  
}
