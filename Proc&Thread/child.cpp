#include <windows.h>
#include <iostream.h>
#include <stdlib.h>

HANDLE sample;

void main(int argc, char *argv[])
{
  char str[200];
  DWORD numRead;
  BOOL success;

  // Get the handle value off of the command line
  sample = (HANDLE) atoi(argv[0]);

  // Now use it like a normal file handle to
  // read the file
  success = ReadFile(sample, str, 100,
    &numRead, 0);
  if (!success)
    cout << "In ReadFile: " << GetLastError() 
      << endl;

  // Output the string read from the file
  str[numRead] = '\0';
  cout << str << endl;

  Sleep(2000);
}
