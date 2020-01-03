/*	MAIN.C - Window Procedure for GENERIC.EXE Demo
 *  Copyright (C) 1991-1996 Visio Corporation. All rights reserved.
 *
 *	Abstract
 *		This file implements the standard Windows message loop and window
 *		procedure for the GENERIC.EXE demo.
 */
 
#include <windows.h>
#include <ole2.h> 

#if !defined (_WIN32)
	#include <dispatch.h>  
#endif

#include "resource.h"

int RunDemo(void);
void ShowAboutDialog(HINSTANCE);
LONG CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);

HANDLE stc_hInst;

/**************************************************************************
 *+ WinMain
 *
 *	The main message loop and application initialization.
 */
#ifdef __BORLANDC__
#pragma argsused
#endif 
int PASCAL WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine,
	int nCmdShow) 
	{
    MSG msg;
    HRESULT hResult;
    
    if ( hPrevInstance || !InitApplication(hInstance) )
    	return (FALSE);

	if ( !InitInstance(hInstance, nCmdShow) )
        return (FALSE);

	hResult = OleInitialize(NULL);
	if (hResult != NOERROR )
		return (FALSE);

    while (GetMessage(&msg, NULL, 0, 0))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
    
	OleUninitialize();
    
    return (msg.wParam);
	}


/**************************************************************************
 *+ InitApplication
 *
 *	One time initialization to register the window class.
 */
 
BOOL InitApplication(HANDLE hInstance)
	{
    WNDCLASS  wc;

    wc.style = 0;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DISPATCH));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName =  "MainMenu";
    wc.lpszClassName = "GenericDemo";

    return (RegisterClass(&wc));
	}


/**************************************************************************
 *+ InitInstance
 *
 *	Per instance initialization.  Creates the frame window.
 */

BOOL InitInstance(HANDLE hInstance, int nCmdShow)
	{
	HWND hWnd;

	/* Make window small.
	 */
	LONG dwBaseUnits = GetDialogBaseUnits();
	int winw = (150 * LOWORD(dwBaseUnits))/4;
	int winh = (50 * HIWORD(dwBaseUnits))/8;

    stc_hInst = hInstance;
        
#ifdef _DEBUG
	#define WINDOW_TITLE "Visio Automation Demo - DEBUG"
#else
	#define WINDOW_TITLE "Visio Automation Demo"
#endif

    hWnd = CreateWindow("GenericDemo", WINDOW_TITLE,
                    	WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		            	winw, winh, NULL, NULL, hInstance, NULL);

    if (!hWnd) return (FALSE);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    
    return (TRUE);
	}

/**************************************************************************
 *+ MainWndProc
 *
 *	Frame window procedure.  The only special thing it does it run the 
 *	demo when the Run Demo menu entry is selected.
 */

LONG CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	switch (message)
	    {
	    case WM_COMMAND:
	        switch (wParam)
		        {
		        case IDM_EXIT:
		            DestroyWindow(hWnd);
		            break;
		            
		        case IDM_RUNDEMO:
						RunDemo();
		            break;
		    
		    	case IDM_ABOUT:
		    		ShowAboutDialog(stc_hInst);
		    		break;        
		    		
		        default:
		            return (DefWindowProc(hWnd, message, wParam, lParam));
		        }
	        
	        break;
	        
		case WM_DESTROY:
	        PostQuitMessage(0);
	        break;
	            
	    default:
	        return (DefWindowProc(hWnd, message, wParam, lParam));
	    }
    
    return 0;
	}
