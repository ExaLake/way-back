/* This is the prototype test for wrap process to monitor process's 
   stdout and stderr. if it find an error message, it will display on the
   screen */

#include <windows.h>
#include <iostream.h>

// BUFFERSIZE value is selected from Richard Stevens book
const int BUFFERSIZE = 8192;


void main(int argc, char ** argv)
{
	char buf[BUFFERSIZE];
	HANDLE ReadPipe, WritePipe;
	unsigned long n;                         // number of bytes to read
	
	  

	SECURITY_ATTRIBUTES PipeAttr;
	STARTUPINFO si;
	PROCESS_INFORMATION child;

	PipeAttr.nLength = sizeof(PipeAttr);
	PipeAttr.lpSecurityDescriptor = NULL;
	PipeAttr.bInheritHandle = TRUE;
	
	if (CreatePipe(&ReadPipe,
				   &WritePipe,
				   &PipeAttr,
				   0) == 0)
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		cout << lpMsgBuf << endl;
		LocalFree( lpMsgBuf );
		ExitProcess(1);
	}

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdOutput = WritePipe;
	if (CreateProcess(NULL,
					 "bsp",
					 NULL,
					 NULL,
					 TRUE,
					 0,
					 NULL,
					 NULL,
					 &si,
					 &child) == 0)
					 
		cout << "CreateProcess ERROR" << endl;

	

	while (ReadFile(ReadPipe,(void *)buf,BUFFERSIZE, &n, NULL) && n!=0)
	{
		buf[n] = 0;
		cout << "receive input:" << endl;
		cout << buf << endl;
		CloseHandle(WritePipe);
	}
	CloseHandle(ReadPipe);
	cout << "child process finish" << endl;
}

