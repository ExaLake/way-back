#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

DWORD tlsIndex;

typedef struct
{
  DWORD frequency;
  DWORD duration;
} honkParams;

void ParamsAlloc()
{
  honkParams *params;

  params=(honkParams *) GlobalAlloc(GPTR,
    sizeof(honkParams));

  // generate a randomish value for the frequency
  params->frequency=GetTickCount() & 0x00000FFF;
  cout << "Using frequency: " 
    << params->frequency << endl;
  params->duration=100;

  // save the pointer value relevant 
  // for the calling thread
  TlsSetValue(tlsIndex, params);
}

void ParamsFree()
{
  honkParams *params;

  // retrieve the pointer value relevant
  // for the calling thread
  params=(honkParams *) TlsGetValue(tlsIndex);

  GlobalFree(params);
}

void Honk(void)
{
  honkParams *params;

  // retrieve the pointer value relevant 
  // for the calling thread
  params=(honkParams *) TlsGetValue(tlsIndex);

  Beep(params->frequency, params->duration);
}

void HonkThread()
{
  DWORD i;

  // use a general purpose "params" 
  // allocation function
  ParamsAlloc();

  for (i=0; i<8; i++)
  {
    Honk();
    Sleep(1000);
  }

  // use a general purpose "params" free function
  ParamsFree();
}

void main(void)
{
  HANDLE honkHandles[3];
  DWORD threadID;
  DWORD count;

  // allocate a thread local storage index
  tlsIndex=TlsAlloc();

  for (count=0; count<3; count++)
  {
    // create a thread which beeps
    honkHandles[count]=CreateThread(NULL, 0,
      (LPTHREAD_START_ROUTINE) HonkThread, 0, 0,
      &threadID);
    Sleep(1500);
  }

  WaitForMultipleObjects(3, honkHandles, TRUE,
    INFINITE);  

  // free the thread local storage index
  TlsFree(tlsIndex);
}
