#include <windows.h>
#include <iostream.h>

void main()
{
  HANDLE fileHandle = CreateFile("c:\\fichtest.txt",
    GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE,
    0, OPEN_EXISTING, 0, 0);
  if (fileHandle == INVALID_HANDLE_VALUE)	{
    cerr << "Error on CreateFile: " << GetLastError() << endl;
    return;
  }

  HANDLE mapFileHandle = CreateFileMapping(
    fileHandle, 0, PAGE_READWRITE, 0, 0, "fichmapp");
  if (!mapFileHandle)	{
    cerr << "Error on CreateFileMapping: " << GetLastError() << endl;
    return;
  }

  char *mapView = (char *) MapViewOfFile(mapFileHandle, 
    FILE_MAP_READ, 0, 0, 0);
  if (!mapView) {
    cerr << "Error on MapViewOfFile: " << GetLastError() << endl;
    return;
  }

  for (int i = 1; i < 60; i++) {
    cout << i << ": " << mapView << endl;
    Sleep(1000);
  }

  if (!UnmapViewOfFile(mapView))
    cerr << "Error on UpmapViewOfFile: " << endl;

  CloseHandle(mapFileHandle);
  CloseHandle(fileHandle);  
}
