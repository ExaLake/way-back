#define STRICT
#include <windows.h>
#include <winsock.h>
#include <tchar.h>
#include "resource.h"

// work around the fact that WCE 1.x headers do not define _T
#if !defined(_T)
#define _T  __TEXT
#endif

#if defined(_WIN32_WCE)
    #define SOCKET_CLIENT
#elif defined(WIN32)
    #define SOCKET_SERVER
#endif

const short iSockPort = 2048;

#define MAX_RETRIES 10
#define DELAY_TIME  1000
#define MAX_CHARS   32
#define TEXT_MAX    MAX_CHARS+1

BOOL CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, 
                      WPARAM wParam, LPARAM lParam); 
void HandleConnect(SOCKET *psock, HWND hwndDlg);
void Disconnect(SOCKET *psock, HWND hwndDlg);

#if defined(SOCKET_SERVER)
BOOL ServerConnect(SOCKET *psock, HWND hwndDlg);
void HandleSend(SOCKET *psock, HWND hwndDlg);
BOOL SendText(SOCKET sock, LPCTSTR pcszText);
#else
BOOL ClientConnect(SOCKET *psock, HWND hwndDlg);
struct ReceiveData
{
    SOCKET  sock;
    HWND    hwndDlg;
};
DWORD WINAPI ReceiveText(LPVOID lpv);
#endif

int WINAPI WinMain (HINSTANCE hInstance, 
                    HINSTANCE hPrevInstance,
#if defined(_WIN32_WCE)
                    LPWSTR lpCmdLine, 
#else
                    LPSTR lpCmdLine,
#endif
                    int nCmdShow)
{
    WORD    wVersion;
    WSADATA wsaData;
 
    wVersion = MAKEWORD( 2, 0 );
    WSAStartup(wVersion, &wsaData);
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDLG), 
              NULL, (DLGPROC)DlgProc);
    WSACleanup();
    return 0;
}

#if defined(SOCKET_SERVER)

BOOL ServerConnect(SOCKET *psock, HWND hwndDlg)
{
    BOOL                fSuccess = FALSE;
    int                 nRetries = 0;
    struct sockaddr_in  addrT;
    int                 nRet;

    memset(&addrT, 0, sizeof(addrT));
    addrT.sin_family = AF_INET;
    addrT.sin_port = htons(iSockPort);
    addrT.sin_addr.s_addr = INADDR_ANY;

    nRet = bind(*psock, (PSOCKADDR)&addrT, sizeof(addrT));

    if ( nRet != SOCKET_ERROR )
    {
        if ( listen(*psock, 0) != SOCKET_ERROR )
        {
            while ((fSuccess == FALSE) && 
                   (++nRetries < MAX_RETRIES))
            {
                struct fd_set  fds;
                struct timeval tv = { DELAY_TIME / 1000, 
                                      DELAY_TIME % 1000 }; 
                FD_ZERO (&fds);
                FD_SET (*psock, &fds);
                
                if (select(0, &fds, NULL, NULL, &tv) == 0)
                    continue;
                if (FD_ISSET(*psock, &fds))
                {
                    // accept the connection and close the 
                    // socket we were listening to 
                    SOCKET oldsock = *psock;

                    *psock = accept(oldsock, NULL, 0);
                    closesocket(oldsock);
                    fSuccess = (*psock != INVALID_SOCKET);
                }
            }
        }
    }
    return fSuccess;
}

BOOL SendText(SOCKET sock, LPCTSTR pcszText)
{
    BOOL    fSuccess = FALSE;
    UINT    nDataLen;
        
    nDataLen = (_tcslen(pcszText)*sizeof(TCHAR))+sizeof(TCHAR);

    if ( sock != INVALID_SOCKET )
    {
        UINT nCount = send(sock, (LPCSTR)pcszText, nDataLen, 0);
        if ( nCount != SOCKET_ERROR )
            fSuccess = ( nCount == nDataLen );
    }
    return fSuccess;
}

#else

BOOL ClientConnect(SOCKET *psock, HWND hwndDlg)
{
    BOOL                fSuccess = FALSE;
    int                 nRetries = 0, nRet;
    struct sockaddr_in  addrT;
    PHOSTENT            phe;

    // ppp_peer returns the IP adress of the host machine
    // if CE Services is running or NULL otherwise
    if ( !(phe = gethostbyname("ppp_peer")) )
    {
        MessageBox(hwndDlg, _T("Error"), 
                   _T("Can't get ppp_peer"), MB_OK);

        return FALSE;
    }
    for (fSuccess = FALSE;
         nRetries < MAX_RETRIES && !fSuccess;
         nRetries++, Sleep(DELAY_TIME)
         )
    {
        memset(&addrT, 0, sizeof(addrT));
        addrT.sin_family = AF_INET;
        addrT.sin_port = htons(iSockPort);
        addrT.sin_addr.s_addr = *(long *)phe->h_addr; 

        nRet = connect(*psock, (PSOCKADDR)&addrT, sizeof(addrT));

        if ( nRet != SOCKET_ERROR) 
            fSuccess = TRUE;
    }

    return fSuccess;
}

DWORD WINAPI ReceiveText(LPVOID lpv)
{
    TCHAR       chText[TEXT_MAX];

    // cache the passed socket and HWND so that we don't 
    // continually use the data in the caller's procedure
    struct ReceiveData *prd = (struct ReceiveData*)lpv;
    SOCKET              sock = prd->sock;
    HWND                hwndDlg = prd->hwndDlg;

    if ( sock != INVALID_SOCKET )
    {
        // loop until we can't receive any data from the socket 
        while ( TRUE )
        {
            UINT nCount;
            nCount = recv(sock, (LPSTR)chText, 
                          TEXT_MAX*sizeof(TCHAR), 0);
            if ( nCount == SOCKET_ERROR || nCount <= 0 )
                break;
            SetWindowText(GetDlgItem(hwndDlg, IDC_TEXT), chText);
        }
    }
    return 0;
}

#endif

void Disconnect(SOCKET *psock, HWND hwndDlg)
{
    // disconnect communication and update the UI
    if ( *psock != INVALID_SOCKET)
    {
        closesocket(*psock);
        *psock = INVALID_SOCKET;
    }

#if defined(SOCKET_SERVER)
    EnableWindow(GetDlgItem(hwndDlg, IDC_TEXT), FALSE);
    EnableWindow(GetDlgItem(hwndDlg, IDC_SEND), FALSE);
#endif

    SetWindowText(GetDlgItem(hwndDlg, IDC_CONNECT), 
                  _T("&Connect"));
}

// window function for the dialog box

BOOL CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, 
                      WPARAM wParam, LPARAM lParam)
{

    BOOL                bRet = FALSE;
    static SOCKET       s_Socket = INVALID_SOCKET;
    
    switch( uMsg )
    {
        case WM_INITDIALOG:
        {
            HWND hwndEdit = GetDlgItem(hwndDlg, IDC_TEXT);

            SendMessage(hwndEdit, EM_LIMITTEXT, MAX_CHARS, 0);

#if defined(SOCKET_SERVER)
            EnableWindow(hwndEdit, FALSE);
            EnableWindow(GetDlgItem(hwndDlg, IDC_SEND), FALSE);
#else
            // change client UI to reflect receive only state
            SendMessage(hwndEdit, EM_SETREADONLY, TRUE, 0);
            ShowWindow(GetDlgItem(hwndDlg, IDC_SEND), SW_HIDE);
#endif
        }
        break;

        case WM_COMMAND:
        {
            int     nID = LOWORD(wParam);
            int     wNotify = HIWORD(wParam);
            HWND    hwndCtl = (HWND)lParam;

            // handle click on the connect, send, or cancel button
            if ( wNotify == BN_CLICKED )
            {
              switch( nID )
              {
                case IDCANCEL:
                    Disconnect(&s_Socket, hwndDlg);
                    EndDialog(hwndDlg, IDCANCEL);
                    bRet = TRUE;
                    break;
                case IDC_CONNECT:
                    HandleConnect(&s_Socket, hwndDlg);
                    bRet = TRUE;
                    break;
#if defined(SOCKET_SERVER)
                  case IDC_SEND:
                    HandleSend(&s_Socket, hwndDlg);
                    bRet = TRUE;
                    break;
#endif
              }
          }
      }
      break;
    }
    return bRet;
}

void HandleConnect(SOCKET *psock, HWND hwndDlg)
{
#if defined(SOCKET_CLIENT)
    static struct ReceiveData  rd;
    DWORD                      dwTID;
#endif

    if ( *psock == INVALID_SOCKET )
    {
        // connect to the client/server
        BOOL fSuccess = FALSE;
        *psock = socket(AF_INET, SOCK_STREAM, 0);
        if ( *psock != INVALID_SOCKET )
        {
            EnableWindow(hwndDlg, FALSE);

            #if defined(SOCKET_SERVER)
                fSuccess = ServerConnect(psock, hwndDlg);
            #else
                fSuccess = ClientConnect(psock, hwndDlg);
            #endif

            EnableWindow(hwndDlg, TRUE);

            if ( fSuccess == FALSE )
            {
                MessageBox(hwndDlg, _T("Failed to connect"), 
                           _T("Error"), MB_OK);
                closesocket(*psock);
                *psock = INVALID_SOCKET;
            }
            else
            {
                SetWindowText(GetDlgItem(hwndDlg, IDC_CONNECT), 
                              _T("&Disconnect"));
                #if defined(SOCKET_SERVER)
                    EnableWindow(GetDlgItem(hwndDlg, IDC_TEXT), 
                                 TRUE);
                    EnableWindow(GetDlgItem(hwndDlg, IDC_SEND), 
                                 TRUE);
                #else
                    rd.sock = *psock;
                    rd.hwndDlg = hwndDlg;

                    // Launch thread to receive text and put
                    // it in the edit box. The thread will 
                    // terminate itself when the socket 
                    // becomes invalid.
                    CreateThread(NULL, 0, ReceiveText, &rd, 0, &dwTID);
                #endif
            }
        }
    }
    else
        // disconnect from the client/server
        Disconnect(psock, hwndDlg);
    return;
}

#ifdef SOCKET_SERVER

void HandleSend(SOCKET *psock, HWND hwndDlg)
{
    if ( *psock == INVALID_SOCKET )
    {
        MessageBox(hwndDlg, _T("No connection available"), 
                _T("Error"), MB_OK);
        Disconnect(psock, hwndDlg);
    }
    else
    {
        TCHAR chText[TEXT_MAX];

        // get the text from the edit box and send 
        // it to the client
        memset(chText, 0, TEXT_MAX*sizeof(TCHAR));
        GetWindowText(GetDlgItem(hwndDlg, IDC_TEXT), 
                      chText,TEXT_MAX);
        if ( lstrlen(chText) && SendText(*psock, chText) == FALSE )
        {
          MessageBox(hwndDlg,_T("Send failed"),_T("Error"), MB_OK);
          Disconnect(psock, hwndDlg);
        }
    }
}

#endif
