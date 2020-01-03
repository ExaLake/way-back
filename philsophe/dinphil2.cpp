// dinphil2.cpp

#include <windows.h>
#include <stdlib.h>
#include <iostream.h>

const INT numPhilosophers=20;
HANDLE chopsticks[numPhilosophers];
CHAR csStat[numPhilosophers+1];
CHAR pStat[numPhilosophers+1];

void PhilosopherThread(INT id)
{
  HANDLE cs[2];
  while (1)
  {
    //thinking
    Sleep(GetTickCount() % 50);

    // hungry, so picks up chopsticks
    cs[0] = chopsticks[id];
    cs[1] = chopsticks[(id+1)%numPhilosophers];
    WaitForMultipleObjects(2, cs, TRUE, INFINITE);
    csStat[id]='1';
    csStat[(id+1)%numPhilosophers]='1';
    pStat[id]='1';

    // eating
    cout << csStat << "  " << pStat << endl;
    Sleep(GetTickCount() % 50);

    pStat[id]='0';
    // done eating
    ReleaseMutex(chopsticks[id]);
    csStat[id]='0';
    ReleaseMutex(
      chopsticks[(id+1)%numPhilosophers]);
    csStat[(id+1)%numPhilosophers]='0';
  }
}

void main(void)
{
  HANDLE handles[numPhilosophers];
  DWORD threadID;
  INT i;

  csStat[numPhilosophers]='\0';
  pStat[numPhilosophers]='\0';

  // Create the chopstick mutexes
  for (i=0; i<numPhilosophers; i++)
    chopsticks[i] = CreateMutex(0, FALSE, 0);

  // Create the philosopher threads
  for (i=0; i<numPhilosophers; i++)
  {
    // create the philosopher threads
    handles[i]=CreateThread(0, 0,
      (LPTHREAD_START_ROUTINE) PhilosopherThread, 
      (VOID *) i, 0, &threadID);
  }

  // wait for all threads to finish execution
  WaitForMultipleObjects(numPhilosophers, handles, 
    TRUE, INFINITE);  

  for (i=0; i<numPhilosophers; i++)
    CloseHandle(chopsticks[i]);

  cout << "Done" << endl;
}
