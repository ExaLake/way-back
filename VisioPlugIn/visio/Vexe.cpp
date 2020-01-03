/*	VEXE.CPP - WinMain and Window Procedure for VAddon derived classes.
 *  Copyright (C) 1991-1996 Visio Corporation. All rights reserved.
 *
 *	Abstract
 *		This file implements the standard Windows message loop and window
 *		procedure for EXE based VAddon subclasses.
 *		Allows VAddon-derived classes to be compiled into an EXE with no
 *		additional effort!
 */

#include <windows.h>
#include <ole2.h>

#if !defined (_WIN32)
	#include <dispatch.h>
#endif

#include "vaddon.h"

LONG CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
BOOL InitMenu(HWND hWnd);

void UnloadAddons(void);
void LoadAddons(void);
void EnumAddonsAndAddMenus(HWND hWnd);

HANDLE g_hInst;
LPSTR g_lpszCmdLine;

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

	g_lpszCmdLine= lpszCmdLine;

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
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName =  NULL;
    wc.lpszClassName = "VAddonExe";

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
	int x = 32;
	int y = 32;

    g_hInst = hInstance;
	VAddon::SetInstance(hInstance);

#ifdef _DEBUG
	#define WINDOW_TITLE "VAddon EXE Shell - DEBUG"
	y += winh + 16;	//	DEBUG window shows up below Release window...
#else
	#define WINDOW_TITLE "VAddon EXE Shell"
#endif

    hWnd = CreateWindow("VAddonExe", WINDOW_TITLE,
                    	WS_OVERLAPPEDWINDOW, x, y,
		            	winw, winh, NULL, NULL, hInstance, NULL);

    if (!hWnd) return (FALSE);

	if (!InitMenu(hWnd)) return (FALSE);

	LoadAddons();
	EnumAddonsAndAddMenus(hWnd);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return (TRUE);
	}

BOOL InitMenu(HWND hWnd)
{
	HMENU hMainMenu= CreateMenu();
	HMENU hFileMenu= CreatePopupMenu();
	HMENU hRunMenu= CreatePopupMenu();
	HMENU hAboutMenu= CreatePopupMenu();
	HMENU hHelpMenu= CreatePopupMenu();

	if (NULL==hMainMenu || NULL==hFileMenu || NULL==hRunMenu || NULL==hAboutMenu || NULL==hHelpMenu)
		return FALSE;

	AppendMenu(hFileMenu, MF_STRING, 100, "&About VAddon EXE Shell...");
	AppendMenu(hFileMenu, MF_STRING, 101, "E&xit");
	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT) hFileMenu, "&File");

//	AppendMenu(hRunMenu, MF_STRING, 999, "RemoveMe");
	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT) hRunMenu, "&Run");

//	AppendMenu(hAboutMenu, MF_STRING, 999, "RemoveMe");
	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT) hAboutMenu, "&About");

//	AppendMenu(hHelpMenu, MF_STRING, 999, "RemoveMe");
	AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT) hHelpMenu, "&Help");

	SetMenu(hWnd, hMainMenu);

	return TRUE;
}

void UnloadAddons(void)
	{
	VAddon *pAddon= VAddon::GetFirst();
	while (NULL!=pAddon)
		{
		pAddon->Unload(0, NULL);
		pAddon= VAddon::GetNext(pAddon);
		}
	}

void LoadAddons(void)
	{
	VAddon *pAddon= VAddon::GetFirst();
	while (NULL!=pAddon)
		{
		pAddon->Load(VAO_L2V_VERSION(), NULL);
		pAddon= VAddon::GetNext(pAddon);
		}
	}

#define RUN_MASK	0x4000
#define ABOUT_MASK	0x2000
#define HELP_MASK	0x1000

void EnumAddonsAndAddMenus(HWND hWnd)
	{
	VAddon *pAddon= NULL;
	HMENU hMenuRun= NULL;
	HMENU hMenuAbout= NULL;
	HMENU hMenuHelp= NULL;
	HMENU hMenu= NULL;
	WORD w= 0;


	if (NULL!=hWnd)
		hMenu= GetMenu(hWnd);

	if (NULL!=hMenu)
		{
		//	File 0, Run 1, About 2, Help 3
		hMenuRun= GetSubMenu(hMenu, 1);
		hMenuAbout= GetSubMenu(hMenu, 2);
		hMenuHelp= GetSubMenu(hMenu, 3);

		pAddon= VAddon::GetFirst();
		while (NULL!=pAddon)
			{
			w= pAddon->GetIndex();

			AppendMenu(hMenuRun, MF_STRING, (w | RUN_MASK), pAddon->GetName());
			AppendMenu(hMenuAbout, MF_STRING, (w | ABOUT_MASK), pAddon->GetName());
			AppendMenu(hMenuHelp, MF_STRING, (w | HELP_MASK), pAddon->GetName());

			pAddon= VAddon::GetNext(pAddon);
			}

//		DeleteMenu(hMenuRun, 0, MF_BYPOSITION);		//	The "RemoveMe" item...
//		DeleteMenu(hMenuAbout, 0, MF_BYPOSITION);	//	The "RemoveMe" item...
//		DeleteMenu(hMenuHelp, 0, MF_BYPOSITION);	//	The "RemoveMe" item...
		}
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
		        case 100:
					MessageBox(hWnd, "VAddon EXE Shell\n\nCopyright (c) 1996 Visio Corporation.\nAll rights reserved.\n\nWritten by David Cole.", "About", MB_OK);
		            break;

		        case 101:
					DestroyWindow(hWnd);
		            break;

		        default:
					{
						if (wParam & RUN_MASK)
							{
							VAddon *pAddon= VAddon::FindAddon(wParam & ~RUN_MASK);
							if (NULL!=pAddon)
								{
								pAddon->Run(NULL);
								}
							return 0;
							}
						else if (wParam & ABOUT_MASK)
							{
							VAddon *pAddon= VAddon::FindAddon(wParam & ~ABOUT_MASK);
							if (NULL!=pAddon)
								{
								pAddon->About(NULL);
								}
							return 0;
							}
						else if (wParam & HELP_MASK)
							{
							VAddon *pAddon= VAddon::FindAddon(wParam & ~HELP_MASK);
							if (NULL!=pAddon)
								{
								pAddon->Help(NULL);
								}
							return 0;
							}
					}
		            return (DefWindowProc(hWnd, message, wParam, lParam));
		        }
	        break;

	    case WM_INITMENU:
			{
			HMENU hMenu= (HMENU) wParam;
			if (NULL!=hMenu)
				{
				VAddon *pAddon= VAddon::GetFirst();
				while (NULL!=pAddon)
					{
					//	Enable or disable the 'Run' menu item based on what the addon says:
					if (pAddon->IsEnabled(NULL))
						EnableMenuItem(hMenu, (pAddon->GetIndex() | RUN_MASK), MF_BYCOMMAND|MF_ENABLED);
					else
						EnableMenuItem(hMenu, (pAddon->GetIndex() | RUN_MASK), MF_BYCOMMAND|MF_GRAYED);

					pAddon= VAddon::GetNext(pAddon);
					}
				return 0;
				}

            return (DefWindowProc(hWnd, message, wParam, lParam));
			}
	        break;

		case WM_DESTROY:
			UnloadAddons();
	        PostQuitMessage(0);
	        break;

	    default:
	        return (DefWindowProc(hWnd, message, wParam, lParam));
	    }

    return 0;
	}
