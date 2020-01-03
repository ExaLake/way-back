#include <windows.h>
#include <iostream.h>

void main(void)
{
  CHAR cmdStr[100];
  STARTUPINFO startUpInfo;
  PROCESS_INFORMATION procInfo;
  BOOL success;

  // Get the name of the child process to run
  cout << "Enter the command to execute: ";
  cin.getline(cmdStr, 100);

  // Retrieve the STARTUPINFOR structure for
  // the current process
  GetStartupInfo(&startUpInfo);

  // Create the child process
  success=CreateProcess(
    0, cmdStr, 0, 0, FALSE, 
    CREATE_NEW_CONSOLE,
    0, 0, &startUpInfo, &procInfo);
  if (!success)
    cout << "Error creating process: " 
      << GetLastError() << endl;

  // Wait for the child process to complete
  WaitForSingleObject(procInfo.hProcess, 
    INFINITE);
}
