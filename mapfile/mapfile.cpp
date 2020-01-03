#include <windows.h>
#include <iostream.h>

void main()
{
  char filename[MAX_PATH];

  cout << "Enter filename: ";
  cin >> filename;

  HANDLE fileHandle = CreateFile(filename, GENERIC_READ, 0,
    0, OPEN_EXISTING, 0, 0);
  if (fileHandle == INVALID_HANDLE_VALUE) {
    cerr << "Error on CreateFile: " << GetLastError() << endl;
    return;
  }

  // create the mapping 
  HANDLE mapFileHandle = CreateFileMapping(
    fileHandle, 0, PAGE_READONLY,
    0, 0, "mapfile");
  if (!mapFileHandle)	{
    cerr << "Error on CreateFileMapping: " << GetLastError() << endl;
    return;
  }

  // map the file to an address
  char *mapView = (char *) MapViewOfFile(mapFileHandle, 
    FILE_MAP_READ, 0, 0, 0);
  if (!mapView) {
    cerr << "Error on MapViewOfFile: " << GetLastError() << endl;
    return;
  }

	// dump the file
  cout << mapView << endl;

  if (!UnmapViewOfFile(mapView)) 
    cerr << "problem unmapping" << endl;

  CloseHandle(mapFileHandle);
  CloseHandle(fileHandle);  
}
