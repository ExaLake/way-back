#include <windows.h>
#include <iostream.h>

// Don't forget to link winmm.lib

#define TARGET_RESOLUTION 1    // 1-millisecond target resolution

int c = 0;

void CALLBACK CallbackFunction(UINT wTimerID, UINT msg, 
    DWORD dwUser, DWORD dw1, DWORD dw2) 
{ 
   c++;
   if (!(c % 1000))
     cout << c << endl;
} 

void main()
{

  // Establish timer resolution
  TIMECAPS tc;
  UINT wTimerRes;

  if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
    cerr << "Error: timer resolution to low for app" << endl;
    return;
  }

  cout << "Minimum timer resolution: " << tc.wPeriodMin << endl;
  cout << "Maximum timer resolution: " << tc.wPeriodMax << endl;


  wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
  cout << "Setting resolution to " << wTimerRes << endl;
  timeBeginPeriod(wTimerRes); 

  // Set timer
  MMRESULT TimerID;                    // timer ID
  UINT msInterval = TARGET_RESOLUTION; // event interval, in miliseconds
  cout << "Setting interval to " << msInterval << endl;
  
  TimerID = timeSetEvent(
        msInterval,                    // delay
        wTimerRes,                     // resolution
                                       // 0: greatest accuracy, highest overhead
                                       //   set it to highest value possible for app
        CallbackFunction,              // callback function
        NULL,                          // user data
        TIME_PERIODIC);                // single timer event
  if(!TimerID) {
    cerr << "Error in SetTimerCallback: " << GetLastError() << endl;
    return;
  }
  
  while (1);

  // should call timerEndPeriod on unload
 
}