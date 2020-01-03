#include <windows.h>
#include <stdio.h>


typedef HRESULT (STDAPICALLTYPE *CTLREGPROC)() ; // Requires stdole.h


void main(int argc, char **argv)
	{
	HANDLE hLibrary;
	CTLREGPROC DLLRegisterServer;

	if(argc != 3)
		{
		printf("Command line format: ocxreg <control.ocx> <install/uninstall>\n");
		return;
		}

	if(strncmp(argv[2],"install",7) != 0 && strncmp(argv[2],"uninstall",9) != 0 &&
		strncmp(argv[2],"INSTALL",7) != 0 && strncmp(argv[2],"UNINSTALL",9) != 0)
		{
		printf("Command line format: ocxreg <control.ocx> <install/uninstall>\n");
		}

	if(OleInitialize(NULL) != S_OK)
		{
		printf("Could not initialize OLE libraries.\n");
		OleUninitialize();
		return;
		}


	hLibrary = LoadLibrary(argv[1]);

	if(hLibrary == NULL)
		{
		printf("Could not load OCX\n");
		OleUninitialize();
		return;
		}


	
	// Install
	if(strncmp(argv[2],"install",7) == 0 || strncmp(argv[2],"INSTALL",9) == 0)
		DLLRegisterServer = (CTLREGPROC)GetProcAddress(hLibrary,"DllRegisterServer");
	else
		DLLRegisterServer = (CTLREGPROC)GetProcAddress(hLibrary,"DllUnregisterServer");

	if(DLLRegisterServer == NULL)
		printf("Could not find exported function\n");
	else
		{
		if(SUCCEEDED(DLLRegisterServer()))
			printf("Success\n");
		else
			printf("Failure\n");
		}
	
	FreeLibrary(hLibrary);
	OleUninitialize();
	}