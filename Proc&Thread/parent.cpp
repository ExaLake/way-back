#include <windows.h>
#include <iostream.h>
#include <stdlib.h>

HANDLE sample;

void main(void)
{
  STARTUPINFO startUpInfo;
  PROCESS_INFORMATION procInfo;
  BOOL success;
  char s[100];
  SECURITY_ATTRIBUTES sa;

  // Set up security attributes to allow 
  // inheritance of the file handle
  sa.nLength = sizeof(SECURITY_ATTRIBUTES);
  sa.lpSecurityDescriptor = 0;
  sa.bInheritHandle=TRUE;

  // Create a file handle
  sample = CreateFile("parent.cpp", GENERIC_READ,
    FILE_SHARE_READ, &sa, OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL, 0);
  if (sample==INVALID_HANDLE_VALUE)
    cout << "In CreateFile" << GetLastError() 
      << endl;

  // Init a startup structure
  GetStartupInfo(&startUpInfo);

  // convert the sample handle to a string
  _itoa((DWORD)sample, s, 10);

  // Create the child process, specifying 
  // inherited handles. Pass the value of the 
  // handle as a command line parameter
  success=CreateProcess("child.exe", s, 0, 0, TRUE, 
    CREATE_NEW_CONSOLE,
    0, 0, &startUpInfo, &procInfo);
  if (!success)
    cout << "Error creating process: " 
      << GetLastError() << endl;

  // wait for the child to return (this
  // is not a requirement since the child
  // is its own independent process)
  WaitForSingleObject(procInfo.hProcess, INFINITE);
}
