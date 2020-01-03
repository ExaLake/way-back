#include <windows.h>
#include <iostream.h>

void main(void)
{
  HANDLE mapFileHandle = OpenFileMapping(FILE_MAP_WRITE, FALSE, "shmem1");
  if (!mapFileHandle) {
    cerr << "Error on OpenFileMapping: " << GetLastError() << endl;
    return;
  }

  char* mapView = (char *) MapViewOfFile(mapFileHandle, 
    FILE_MAP_WRITE, 0, 0, 0);
  if (!mapView) {
    cerr << "Error on MapViewOfFile: " << GetLastError() << endl;
    return;
  }

  for (char c = 'a'; c < 'd'; c++)
    for (int i = 0; i < 12; i++) {
      cout << "Doing " << (char) c << " at " << i << endl;
      mapView[i] = c;
      mapView[i + 1] = '\0';
      Sleep(1000);
    }

  mapView[0] = '\0';

  if (!UnmapViewOfFile(mapView))
    cerr << "Error on UpmapViewOfFile: " << GetLastError() << endl;

  CloseHandle(mapFileHandle);  
}
