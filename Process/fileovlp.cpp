#include <windows.h>
#include <iostream.h>

void main()
{
	HANDLE fileHandle;
	BOOL success;
	char s[300000];
	DWORD numRead;
	char filename[1000];
	OVERLAPPED overlappedInfo;
	HANDLE event;
	BOOL waitSuccess;

	// get the file name
	cout << "Enter filename: ";
	cin >> filename;

	// Open the file
	fileHandle = CreateFile(filename, 
		GENERIC_READ, FILE_SHARE_WRITE,
		0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		cout << "Error number " << GetLastError()
			<< endl;
		return;
	}

	// set up the overlapped structure
	overlappedInfo.Offset = 0;
	overlappedInfo.OffsetHigh = 0;
	event = CreateEvent(0, TRUE, FALSE, 0);
	overlappedInfo.hEvent = event;

	// Read from the file
	success = ReadFile(fileHandle, s, 100000,
		&numRead, &overlappedInfo);

	// wait for the operation to finish
	if (!success &&
		GetLastError() == ERROR_IO_PENDING)
	{
		cout << "Error number = " << GetLastError()
			<< endl;  //just to see it
		do
		{
			cout << "waiting...\n";
			// check for completion
			waitSuccess = 
				WaitForSingleObject(event, 0);
		}
		while (waitSuccess == WAIT_TIMEOUT);
		// find out how many bytes were read
		GetOverlappedResult(fileHandle,
			&overlappedInfo, &numRead, FALSE);
	}
	else
		cout << "Error number = " << GetLastError()
			<< endl;  //just to see it
	// update the file pointer
	overlappedInfo.Offset += numRead;
	cout << numRead << endl;

	// Close the file
	CloseHandle(event);
	CloseHandle(fileHandle);  
}
