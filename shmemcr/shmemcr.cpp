#include <windows.h>
#include <iostream.h>

void main(void)
{
  HANDLE mapFileHandle = CreateFileMapping(
    (HANDLE) 0xFFFFFFFF, 0, PAGE_READWRITE, 0, 1024, "shmem1");
  if (!mapFileHandle)	{
    cerr << "Error on CreateFileMapping: " << GetLastError() << endl;
    return;
  }

  char* mapView = (char *)  MapViewOfFile(mapFileHandle, 
    FILE_MAP_READ, 0, 0, 0);
  if (!mapView) {
    cerr << "Error on MapViewOfFile " << GetLastError() << endl;
    return;
  }

  int i = 0;
  while (1)	{
    cout << ++i << ": " << mapView << endl;
    Sleep(1000);
  }

  // Dead code
  if (!UnmapViewOfFile(mapView))
    cerr << "Error on UnmapViewOfFile" << endl;

  CloseHandle(mapFileHandle); 
}
