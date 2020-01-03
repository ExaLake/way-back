#include <windows.h>
#include <iostream.h>

void main()
{
  HANDLE mapFileHandle = OpenFileMapping(
    FILE_MAP_WRITE, 0, "fichmapp");
  if (!mapFileHandle)	{
    cerr << "Error OpenFileMapping: " << GetLastError() << endl;
    return;
  }

  char *mapView = (char *) MapViewOfFile(mapFileHandle, 
    FILE_MAP_WRITE, 0, 0, 0);
  if (!mapView) {
    cerr << "Error on MapViewOfFile: " << GetLastError() << endl;
    return;
  }

  for (int i = 4; i < 12; i++) {
    mapView[i] = 'X';
    Sleep(1000);
  }

  if (!UnmapViewOfFile(mapView))
    cerr << "Error on UnmapViewOfFile: " << GetLastError() << endl;

  CloseHandle(mapFileHandle);
}
