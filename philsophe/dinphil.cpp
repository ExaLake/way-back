#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

const int numPhil = 5;
const int MIN = 100;  // min # of millisec to think and eat
HANDLE cs[numPhil];
char csStat[numPhil + 1];
char pStat[numPhil + 1];

void PhilosopherThread(int id)
{
  int id2 = (id + 1) % numPhil;
  while (1)
  {
    //thinking
    Sleep(GetTickCount() % 50 + MIN);

    // hungry, so picks up chopsticks
    WaitForSingleObject(cs[id], INFINITE);
    csStat[id] = '1';
    WaitForSingleObject(cs[id2], INFINITE);
    csStat[id2] = '1';
    pStat[id] = '1';
    cout << csStat << "  " << pStat << endl;

    // eating
    Sleep(GetTickCount() % 50 + MIN);

    // done eating
    pStat[id] = '0';
    ReleaseMutex(cs[id]);
    csStat[id] = '0';
    ReleaseMutex(cs[id2]);
    csStat[id2] = '0';
  }
}

void main(void)
{ 
  int i;

  // Init output
  for (i = 0; i < numPhil; i++) {
    csStat[i] = '0';
    pStat[i] = '0';
  }
  csStat[numPhil] = '\0';
  pStat[numPhil] = '\0';

  cout << "chops  phils" << endl;
  cout << "busy   eating" << endl;
  cout << "-----  -----" << endl;

  // Create chopstick mutexes
  for (i = 0; i < numPhil; i++)
    cs[i] = CreateMutex(0, FALSE, 0);

  HANDLE handles[numPhil];
  DWORD threadID;
  // Create philosopher threads
  for (i = 0; i < numPhil; i++)
  {
    // Create philosopher threads
    handles[i] = CreateThread(0, 0,
      (LPTHREAD_START_ROUTINE) PhilosopherThread, 
      (VOID *) i, 0, &threadID);
  }

  // Wait for all threads to finish execution
  WaitForMultipleObjects(numPhil, handles, 
    TRUE, INFINITE);  

  for (i = 0; i < numPhil; i++)
    CloseHandle(cs[i]);

  cout << "Done" << endl;
}