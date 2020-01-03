//==========================================================================;
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (c) 1992 - 1999  Microsoft Corporation.  All Rights Reserved.
//
//--------------------------------------------------------------------------;
//
// DVcrPage.cpp  Property page for DVcrControl
// 
// Revision: 0.9 2-3-98
//

#include "pch.h"
#include <XPrtDefs.h>  // sdk\inc  
#include "DVcrPage.h"
#include "resource.h"


         
// -------------------------------------------------------------------------
// CDVcrControlProperties
// -------------------------------------------------------------------------

CUnknown *
CALLBACK
CDVcrControlProperties::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr) 
{
    DbgLog((LOG_TRACE, 1, TEXT("CDVcrControlProperties::CreateInstance.")));

    CUnknown *punk = new CDVcrControlProperties(lpunk, phr);

    if (punk == NULL) {
        *phr = E_OUTOFMEMORY;
    }

    return punk;
}

#define WAIT_BEFORE_ISSUE_ANOTHER_CMD     2000    // 2 seconds
#define MAX_NOTIFY_CMD_RETRIES               2    // It should be just 1 if it does not support notify cmd.

DWORD
CDVcrControlProperties::MainThreadProc(
    )
{
    HRESULT hr;// End this Thread.
    HANDLE  EventHandles[2];
    HANDLE  hEvent = NULL;
    DWORD   WaitStatus;
    DWORD   dwFinalRC;
    LONG    lXPrtState;
    LONG    lRetries = MAX_NOTIFY_CMD_RETRIES;


    //
    // Get an event, which will be signalled in COMIntf when the pending operation is completed.
    //
    hr = m_pDVcrExtTransport->GetStatus(ED_NOTIFY_HEVENT_GET, (long *) &hEvent);
    if(NOERROR != hr) {
        DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: Get hEvent failed, hr %x"), hr));                        
        return 1; 
    }

#ifdef DEBUG
    // Indicate notification capability; for debug only.
    ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_NOTIFY_ON), TRUE);        
#endif

    while (m_hThread && hEvent && m_hThreadEndEvent) {

        // Serialize issuing cmd among threads (COMIntf allows only one active cmd)
        EnterCriticalSection(&m_csIssueCmd);  
            lXPrtState = 0;
            hr = m_pDVcrExtTransport->GetStatus(ED_MODE_CHANGE_NOTIFY, &lXPrtState);
        LeaveCriticalSection(&m_csIssueCmd); 


        if(hr == E_PENDING) {             
            // Expect this call to complete asychronously.                      
            EventHandles[0] = hEvent;
            EventHandles[1] = m_hThreadEndEvent;
            WaitStatus = WaitForMultipleObjects(2, EventHandles, FALSE, INFINITE);

            if(WAIT_OBJECT_0 == WaitStatus) {  
                dwFinalRC = GetLastError();  // COMIntf will properly SetLastError()
                DbgLog((LOG_TRACE, 1, TEXT("MainThreadProc:GetStatus final RC %dL, XPrtState %dL->%dL"), dwFinalRC, m_lCurXPrtState, lXPrtState));
                UpdateTransportState(lXPrtState);

            } else if (WAIT_OBJECT_0+1 == WaitStatus) {
                DbgLog((LOG_TRACE, 1, TEXT("m_hThreadEndEvent event thread exiting")));
                break;  // End this Thread.

            } else {
                DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: WaitStatus %x, GetLastError() 0x%x"), WaitStatus, GetLastError()));                
                break;  // End this Thread.
            }

        } else {          
            // Unexpected (or error) behaviour has occurred; Thread basically can end now.            
            switch(HRESULT_CODE(hr)) {
            case NOERROR:                 // STATUS_SUCCESS (Complete Notification sychronously ??)
                DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: GetStatus(ED_MODE_CHANGE_NOTIFY) complted sychronously? hr %x"), hr));            
                break;
            case ERROR_GEN_FAILURE:       // STATUS_UNSUCCESSFUL (rejected)
                DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: GetStatus(ED_MODE_CHANGE_NOTIFY) UNSUCCESSFUL, hr %x"), hr));            
                break;
            case ERROR_INVALID_FUNCTION:  // STATUS_NOT_IMPLEMENTED
                DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: GetStatus(ED_MODE_CHANGE_NOTIFY) NOT_IMPLEMENTED, hr %x"), hr));            
                break;
            case ERROR_CRC:               // STATUS_DEVICE_DATA_ERROR (Data did not get to device)
                // Most likely, device was not ready to accept another command, wait and try again.
                DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: GetStatus(ED_MODE_CHANGE_NOTIFY) CRC/DATA error! hr %x"), hr));            
                break;
            case ERROR_SEM_TIMEOUT:       // STATUS_IO_TIMEOUT (Operation not supported or device removed ?)
                DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: GetStatus(ED_MODE_CHANGE_NOTIFY) timeout! hr %x"), hr));            
                break;
            case ERROR_INVALID_PARAMETER: // STATUS_INVALID_PARAMETER 
                DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: GetStatus(ED_MODE_CHANGE_NOTIFY) invalid parameter! hr %x"), hr));            
                break;
            default:
                DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: GetStatus(ED_MODE_CHANGE_NOTIFY) unknown RC; hr %x"), hr));                        
            break;
            } 

            lRetries--;
            if(lRetries) {
                // Device might be unstable; Must wait and check if this thread is signalled to end.
                WaitStatus = WaitForSingleObjectEx(m_hThreadEndEvent, WAIT_BEFORE_ISSUE_ANOTHER_CMD, FALSE);                
                if(WaitStatus == WAIT_OBJECT_0) 
                    break; // End this Thread.
                
            } else {
                DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: break out of the main loop. %x")));                        
               break;
            }
        }
    }
    
    // Since "lXPrtState" is local, we MUST tell COMIntf that we no longer need the event and wants to
    // to cancel(ignore) pending dev control cmd and do not write to "lXPrtState" after this.   
    hr = m_pDVcrExtTransport->GetStatus(ED_NOTIFY_HEVENT_RELEASE, (long *) &hEvent);
    if(hr != NOERROR) {
        DbgLog((LOG_ERROR, 1, TEXT("MainThreadProc: Release hEvent failed, hr %x"), hr));                        
    }

#ifdef DEBUG
    // Indicate notification capability; for debug only.
    ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_NOTIFY_ON), FALSE);        
#endif

    return 1; 
}


DWORD
WINAPI
CDVcrControlProperties::InitialThreadProc(
    CDVcrControlProperties *pThread
    )
{
    return pThread->MainThreadProc();
}



HRESULT
CDVcrControlProperties::CreateNotifyThread(void)
{
    HRESULT hr = NOERROR;

    if (m_hThreadEndEvent == NULL) {
        m_hThreadEndEvent = CreateEvent( NULL, TRUE, FALSE, NULL );\

        if (m_hThreadEndEvent != NULL) {
            ASSERT(m_hThread == NULL);
            DWORD ThreadId;
            m_hThread = 
                ::CreateThread( 
                    NULL
                    , 0
                    , (LPTHREAD_START_ROUTINE) (InitialThreadProc)
                    , (LPVOID) (this)
                    , 0
                    , &ThreadId
                    );

            if (m_hThread == NULL) {
                hr = HRESULT_FROM_WIN32(GetLastError());
                DbgLog((LOG_ERROR, 1, TEXT("CDVcrControlProperties: CreateNotifyThread() failed hr %x"), hr));
                CloseHandle(m_hThreadEndEvent), m_hThreadEndEvent = NULL;

            } else {
                DbgLog((LOG_TRACE, 2, TEXT("CDVcrControlProperties: CreateNotifyThread() ThreadEndEvent %ld, Thread %ld"),m_hThreadEndEvent, m_hThread));
            }

        } else {
            hr = HRESULT_FROM_WIN32(GetLastError());
            DbgLog((LOG_ERROR, 1, TEXT("CDVcrControlProperties:CreateNotifyThread, CreateEvent(m_hThreadEndEvent) failed hr %x"), hr));
        }
    }

    return hr;
}


void
CDVcrControlProperties::ExitThread(
    )
{
    //
    // Check if a thread was created
    //
    if (m_hThread) {
        ASSERT(m_hThreadEndEvent != NULL);

        // End the main thread and will cause the thread to exit        
        if (SetEvent(m_hThreadEndEvent)) {
            //
            // Synchronize with thread termination.
            //
            DbgLog((LOG_TRACE, 1, TEXT("CDVcrControlProperties:Wait for thread to terminate")));
            WaitForSingleObjectEx(m_hThread, INFINITE, FALSE);  // Exit when thread terminate
            DbgLog((LOG_TRACE, 1, TEXT("CDVcrControlProperties: Thread terminated")));

        } else {
            DbgLog((LOG_ERROR, 1, TEXT("SetEvent() failed hr %x"), GetLastError()));
        }

        CloseHandle(m_hThreadEndEvent), m_hThreadEndEvent = NULL;
        CloseHandle(m_hThread),         m_hThread = NULL;
    }
}


//
// Constructor
//
// Create a Property page object 

CDVcrControlProperties::CDVcrControlProperties(LPUNKNOWN lpunk, HRESULT *phr)
    : CBasePropertyPage(NAME("DVcrControl Property Page") 
                      , lpunk
                      , IDD_DVcrControlProperties 
                      , IDS_DVCRCONTROLPROPNAME
                      )
    , m_pDVcrExtDevice(NULL) 
    , m_pDVcrExtTransport(NULL) 
    , m_pDVcrTmCdReader(NULL) 
    , m_hThreadEndEvent(NULL)
    , m_hThread(NULL)
    , m_lCurXPrtState(ED_MODE_STOP)
    , m_bIConLoaded(FALSE)
    , m_idTimer(0)
{
    DbgLog((LOG_TRACE, 1, TEXT("Constructing CDVcrControlProperties...")));
    // To serialize issuing command among threads    
    InitializeCriticalSection(&m_csIssueCmd);
}

// destructor
CDVcrControlProperties::~CDVcrControlProperties()
{
    DbgLog((LOG_TRACE, 1, TEXT("Destroying CDVcrControlProperties...")));
    DeleteCriticalSection(&m_csIssueCmd);
}

//
// OnConnect
//
// Give us the filter to communicate with

HRESULT 
CDVcrControlProperties::OnConnect(IUnknown *pUnknown)
{
    // Ask the filter for its control interface
    DbgLog((LOG_TRACE, 1, TEXT("CDVcrControlProperties::OnConnect.")));

    HRESULT 
    hr = pUnknown->QueryInterface(IID_IAMExtDevice,(void **)&m_pDVcrExtDevice);
    if (FAILED(hr)) {
        DbgLog((LOG_ERROR, 1, TEXT("CDVcrControlProperties::OnConnect: IAMExtDevice failed with hr %x."), hr));
        return hr;
    }

    hr = pUnknown->QueryInterface(IID_IAMExtTransport,(void **)&m_pDVcrExtTransport);
    if (FAILED(hr)) {
        DbgLog((LOG_ERROR, 1, TEXT("CDVcrControlProperties::OnConnect: IAMExtTransport failed with hr %x."), hr));
        m_pDVcrExtDevice->Release();
        m_pDVcrExtDevice = NULL;
        return hr;
    }

    hr = pUnknown->QueryInterface(IID_IAMTimecodeReader,(void **)&m_pDVcrTmCdReader);
    if (FAILED(hr)) {
        DbgLog((LOG_ERROR, 1, TEXT("CDVcrControlProperties::OnConnect: IAMTimecodeReader failed with hr %x."), hr));
        m_pDVcrExtDevice->Release();
        m_pDVcrExtDevice = NULL;
        m_pDVcrExtTransport->Release();
        m_pDVcrExtTransport = NULL;
        return hr;
    }

    return NOERROR;
}


//
// OnDisconnect
//
// Release the interface

HRESULT 
CDVcrControlProperties::OnDisconnect()
{
    // Release the interface
    DbgLog((LOG_TRACE, 1, TEXT("CDVcrControlProperties::OnDisConnect.")));

    ExitThread();

    if (m_pDVcrExtDevice) {
        m_pDVcrExtDevice->Release();
        m_pDVcrExtDevice = NULL;
    }

    if (m_pDVcrExtTransport) {
        m_pDVcrExtTransport->Release();
        m_pDVcrExtTransport = NULL;
    }

    if (m_pDVcrTmCdReader) {
        m_pDVcrTmCdReader->Release();
        m_pDVcrTmCdReader = NULL;
    }

    return NOERROR;
}


//
// Load an icon to on top of the push button.
//
HRESULT 
CDVcrControlProperties::LoadIconOnTopOfButton(int IDD_PBUTTON, int IDD_ICON)
{
    HWND hWndPButton;
    HICON hIcon;

    hWndPButton = GetDlgItem (m_hwnd, IDD_PBUTTON);
    hIcon = (HICON) LoadImage(g_hInst, MAKEINTRESOURCE(IDD_ICON), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    // Note:The system automatically deletes these resources when the process that created them terminates.
    // But if this property page is open/close many time, this wil increase its working set size. 
    // To release resource, call DestroyIcon(hIcon)
    
    return SendMessage(hWndPButton, BM_SETIMAGE, IMAGE_ICON, (LPARAM) hIcon);
}


//
// OnActivate
//
// Called on dialog creation

HRESULT 
CDVcrControlProperties::OnActivate(void)
{
    long lCurXPrtState;


    DbgLog((LOG_TRACE, 1, TEXT("CDVcrControlProperties::OnActivate.")));

// TODO: This funciton is called whenever this window became the focus
// Exclude functions that needs not be called more than once for efficiency.


#if 0  // For reference only.
    LPOLESTR pName = NULL;
    char szName[MAX_PATH];

    // Get Device ID: will return a unique ID
    m_pDVcrExtDevice->get_ExternalDeviceID(&pName);
    WideCharToMultiByte(CP_ACP, 0, pName, -1, szName, MAX_PATH, 0, 0);
    SetDlgItemText(m_hwnd, IDC_STATIC_DEV_ID, (LPCTSTR)szName);
    QzTaskMemFree(pName), pName = NULL;

    // Get version; return AVC VCR subunit version, such as "2.0.1"
    m_pDVcrExtDevice->get_ExternalDeviceVersion(&pName);
    WideCharToMultiByte(CP_ACP, 0, pName, -1, szName, MAX_PATH, 0, 0);
    SetDlgItemText(m_hwnd, IDC_STATIC_DEV_VERSION, (LPCTSTR)szName);
    QzTaskMemFree(pName), pName = NULL;
#endif

    // Query and update tape information
    // This will tell us if there is a tape of not.
    UpdateTapeInfo();


    // Device type is only valid if there is a tape;
    // That is why UpdateTapeInfo() is called prior to this.
    UpdateDevTypeInfo();


#ifndef DEBUG
    // Only Available for Debug build.
    ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_AVC_SEND),FALSE);
    ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_AVC_SEND),FALSE);
    ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_AVC_RESP),FALSE);
    // ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_RESPONSE),FALSE);
#endif



    // Enable this when TIMECODE/ATN search is implemented.
    ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_ATN_SEARCH),    FALSE);


    // Set current transport state and tue control accordingly
    m_pDVcrExtTransport->get_Mode(&lCurXPrtState);
    UpdateTransportState(lCurXPrtState);           


    // Get time code from current media position
    UpdateTimecode();    


#ifndef DEBUG
    ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_NOTIFY_ON), FALSE);        
#endif


    //
    // Create a thread to track transport state change
    //
    HRESULT hr;
        
    // When this thread is created, we need to start serialize issuing commadn
    hr = CreateNotifyThread();
    if (FAILED(hr)) {
        DbgLog((LOG_ERROR, 1, TEXT("CDVcrControlProperties: CreateNotifyThread failed hr %x"), hr));    
    }     

    return NOERROR;
}

//
// OnDeactivate
//
// Called on dialog destruction

HRESULT
CDVcrControlProperties::OnDeactivate(void)
{
    DbgLog((LOG_TRACE, 1, TEXT("CDVcrControlProperties::OnDeactivate.")));
    return NOERROR;
}


//
// OnApplyChanges
//
// User pressed the Apply button, remember the current settings

HRESULT 
CDVcrControlProperties::OnApplyChanges(void)
{
 
    DbgLog((LOG_TRACE, 1, TEXT("CDVcrControlProperties::OnApplyChanges.")));
    return NOERROR;
}



void
CDVcrControlProperties::UpdateTapeInfo(   
    )
{
    HRESULT hr;
    LONG lInSignalMode = 0;
    LONG lMediaType = 0;
    BOOL bRecordInhibit = FALSE;
    TCHAR szBuf[32];

    EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads

    // Input signal mode (NTSC/PAL, SD/SDL)
    // Set Medium info
    hr = m_pDVcrExtTransport->GetStatus(ED_MEDIA_TYPE, &lMediaType);
 
    if(SUCCEEDED (hr)) {

        if(lMediaType == ED_MEDIA_NOT_PRESENT) {
            LoadString(g_hInst, IDS_TAPE_FORMAT_NOT_INSERTED, szBuf, sizeof(szBuf));
            SetDlgItemText(m_hwnd, IDC_TXT_TAPE_FORMAT, (LPCTSTR)szBuf);

            ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_TAPE_INSERTED),  TRUE);

            ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_WRITE_PROTECTED),FALSE);

        } else {
            // If it is present, it better be ED_MEDIA_DVC
            ASSERT(lMediaType == ED_MEDIA_DVC);

            ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_TAPE_INSERTED),FALSE);

            // There is a tape so get its tape format.
            m_pDVcrExtTransport->GetTransportBasicParameters(ED_TRANSBASIC_INPUT_SIGNAL, &lInSignalMode, NULL);
            if(ED_TRANSBASIC_SIGNAL_525_60_SD == lInSignalMode) {
                LoadString(g_hInst, IDS_TAPE_FORMAT_525_60_SD, szBuf, sizeof(szBuf));
                m_lAvgTimePerFrame = 33;  // 33 milli-sec (29.97 FPS)
            } else if(ED_TRANSBASIC_SIGNAL_525_60_SDL == lInSignalMode) {
                LoadString(g_hInst, IDS_TAPE_FORMAT_525_60_SDL, szBuf, sizeof(szBuf));
                m_lAvgTimePerFrame = 33;  // 33 milli-sec (29.97 FPS)
            } else if(ED_TRANSBASIC_SIGNAL_625_50_SD == lInSignalMode) {
                LoadString(g_hInst, IDS_TAPE_FORMAT_525_50_SD, szBuf, sizeof(szBuf));
                m_lAvgTimePerFrame = 40;  // 40 milli-sec (25FPS)
            } else if(ED_TRANSBASIC_SIGNAL_625_50_SDL == lInSignalMode) {
                LoadString(g_hInst, IDS_TAPE_FORMAT_525_50_SDL, szBuf, sizeof(szBuf));
                m_lAvgTimePerFrame = 40;  // 40 milli-sec (25FPS)
            } else {
                wsprintf(szBuf, "Format %x", lInSignalMode);  // Unsupported but still want to know if it is used.
                m_lAvgTimePerFrame = 33;  // 33 milli-sec (29.97 FPS); default
            }
            SetDlgItemText(m_hwnd, IDC_TXT_TAPE_FORMAT, (LPCTSTR)szBuf);

            // Is it write protected ?
            ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_WRITE_PROTECTED),TRUE);
            m_pDVcrExtTransport->GetStatus(ED_RECORD_INHIBIT, (long *)&bRecordInhibit);
            if(bRecordInhibit)    
                LoadString(g_hInst, IDS_TAPE_WRITE_PROTECTED, szBuf, sizeof(szBuf));
            else 
                LoadString(g_hInst, IDS_TAPE_WRITABLE, szBuf, sizeof(szBuf));
            SetDlgItemText(m_hwnd, IDC_TXT_WRITE_PROTECTED, (LPCTSTR)szBuf);
        }
    } else {
        DbgLog((LOG_ERROR, 1, TEXT("Get ED_MEDIA_TYPE failed hr %x"), hr));
    }

    LeaveCriticalSection(&m_csIssueCmd);
}

void
CDVcrControlProperties::UpdateDevTypeInfo()
{
    LONG lDeviceType = 0;
    TCHAR szBuf[32];

    // Note: Device type is only accurate if there is a tape in there.
    // It can return: 0 (Undetermined), ED_DEVTYPE_VCR or ED_DEVTYPE_CAMERA
    m_pDVcrExtDevice->GetCapability(ED_DEVCAP_DEVICE_TYPE, &lDeviceType, 0);

    if(!m_bIConLoaded) {
        // Load resource used in the dialog box
        LoadIconOnTopOfButton(IDC_BTN_DV_PLAY,    IDI_PLAY);
        LoadIconOnTopOfButton(IDC_BTN_DV_PAUSE,   IDI_PAUSE);
        LoadIconOnTopOfButton(IDC_BTN_DV_STOP,    IDI_STOP_EJECT);
        LoadIconOnTopOfButton(IDC_BTN_DV_RWND,    IDI_RWND);
        LoadIconOnTopOfButton(IDC_BTN_DV_FFWD,    IDI_FFWD);
        LoadIconOnTopOfButton(IDC_BTN_DV_STEP_FWD,IDI_STEP_FWD);
        LoadIconOnTopOfButton(IDC_BTN_DV_STEP_REV,IDI_STEP_REV);
        LoadIconOnTopOfButton(IDC_BTN_DV_RECORD,  IDI_RECORD);
        LoadIconOnTopOfButton(IDC_BTN_DV_RECORD_PAUSE,IDI_RECORD_PAUSE);
        m_bIConLoaded = TRUE;
    }

    if(lDeviceType == 0) {
        // Pretend that we are VCR device with no tape!
        LoadString(g_hInst, IDS_DEVTYPE_VCR, szBuf, sizeof(szBuf));
        SetDlgItemText(m_hwnd, IDC_GBX_DEVICE_TYPE, szBuf);

        // Hide just about everything!
        ShowWindow(GetDlgItem(m_hwnd, IDC_CHK_SLOW),      FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_PLAY),   FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_PAUSE),  FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STOP),   FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_RWND),   FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_FFWD),   FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_FWD), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_REV), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_RECORD), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_RECORD_PAUSE), FALSE);

        
        ShowWindow(GetDlgItem(m_hwnd, IDC_GBX_TIMECODE), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_HH_COLON), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_MM_COLON), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_SS_COMMA), FALSE);

        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_HH), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_MM), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_SS), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_FF), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_ATN_BF), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_ATN),    FALSE);

    } else if(lDeviceType == ED_DEVTYPE_VCR) {

        LoadString(g_hInst, IDS_DEVTYPE_VCR, szBuf, sizeof(szBuf));
        SetDlgItemText(m_hwnd, IDC_GBX_DEVICE_TYPE, szBuf);

        // Show everything!
        ShowWindow(GetDlgItem(m_hwnd, IDC_CHK_SLOW),      TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_PLAY),   TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_PAUSE),  TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STOP),   TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_RWND),   TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_FFWD),   TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_FWD), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_REV), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_RECORD), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_RECORD_PAUSE), TRUE);


        ShowWindow(GetDlgItem(m_hwnd, IDC_GBX_TIMECODE), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_HH_COLON), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_MM_COLON), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_SS_COMMA), TRUE);

        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_HH), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_MM), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_SS), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_FF), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_ATN_BF), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_ATN),    TRUE);


    } else {
        LoadString(g_hInst, IDS_DEVTYPE_CAMERA, szBuf, sizeof (szBuf));
        SetDlgItemText(m_hwnd, IDC_GBX_DEVICE_TYPE, szBuf);

        ShowWindow(GetDlgItem(m_hwnd, IDC_CHK_SLOW),      FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_PLAY),   FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_PAUSE),  FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STOP),   FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_RWND),   FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_FFWD),   FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_FWD), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_REV), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_CHK_SLOW),        FALSE);
        // Camera: can only RECORD and RECORD_PAUSE
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_RECORD),       TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_RECORD_PAUSE), TRUE);


        ShowWindow(GetDlgItem(m_hwnd, IDC_GBX_TIMECODE), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_HH_COLON), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_MM_COLON), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_TXT_SS_COMMA), TRUE);

        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_HH), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_MM), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_SS), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_TC_FF), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_ATN_BF), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_EDT_ATN),    TRUE);
    } 
}

void
CDVcrControlProperties::UpdateTransportState(
    long lNewXPrtState
    )
{

    BOOL bSetTimer = FALSE;
    BOOL bKillTimer = FALSE;


    switch(lNewXPrtState) {
    case ED_MODE_PLAY:
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_REV), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_FWD), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_CHK_SLOW),        TRUE);
        bSetTimer = TRUE;
        break;

    case ED_MODE_STEP_FWD:
    case IDC_BTN_DV_STEP_REV:
        bSetTimer = TRUE;
        break;

    case ED_MODE_FREEZE:
        // NOTE: Some DV cannot go from STOP->PLAY_PAUSE
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_REV), TRUE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_FWD), TRUE);    
        ShowWindow(GetDlgItem(m_hwnd, IDC_CHK_SLOW),        TRUE);
        bKillTimer = TRUE;
        break;
    case ED_MODE_PLAY_SLOWEST_FWD:
    case ED_MODE_PLAY_FASTEST_FWD:
    case ED_MODE_PLAY_SLOWEST_REV:
    case ED_MODE_PLAY_FASTEST_REV:
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_REV), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_FWD), FALSE); 
        bSetTimer = TRUE;
        break;
    case ED_MODE_STOP:
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_REV), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_FWD), FALSE);        
        ShowWindow(GetDlgItem(m_hwnd, IDC_CHK_SLOW),        FALSE);
        bKillTimer = TRUE;
        break;
    case ED_MODE_FF:
    case ED_MODE_REW:
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_REV), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_FWD), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_CHK_SLOW),        FALSE);
        bKillTimer = TRUE;
        break;
    case ED_MODE_RECORD:
    case ED_MODE_RECORD_FREEZE:
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_REV), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_BTN_DV_STEP_FWD), FALSE);
        ShowWindow(GetDlgItem(m_hwnd, IDC_CHK_SLOW),        FALSE);
        break;
    default:
        break;
    }

    if(bSetTimer && m_idTimer == 0) {
        m_idTimer = SetTimer(
            m_hwnd,             // handle to window for timer messages
            1,                  // timer identifier           
            m_lAvgTimePerFrame, // time-out value
            0                   // pointer to timer procedure; 0 to use WM_TIMER
        );
        if(!m_idTimer) {
            DbgLog((LOG_ERROR, 1, TEXT("UpdateTransportState: SetTimer() error %x, AvgTimePerFrame %d"), GetLastError(), m_lAvgTimePerFrame));    
        } else {
            DbgLog((LOG_TRACE, 1, TEXT("UpdateTransportState: SetTimer(), TimerId %d, AvgTimePerFrame %d"), m_idTimer, m_lAvgTimePerFrame));    
        }
    }

    if(bKillTimer && m_idTimer != 0) {
        if(!KillTimer(
            m_hwnd,      // handle to window that installed timer
            1 // uIDEvent   // timer identifier
            )) {
            DbgLog((LOG_ERROR, 1, TEXT("UpdateTransportState: KillTimer() error %x"), GetLastError()));    
        } else {
            DbgLog((LOG_TRACE, 1, TEXT("UpdateTransportState: KillTimer() suceeded")));    
        }

        m_idTimer = 0;
    }

    m_lCurXPrtState = lNewXPrtState;
}


//
// Convert hour:minute:second:frame in binary coded decimal (BCD) 
// into a string and display it.
//

HRESULT 
CDVcrControlProperties::DisplayTimecode(PTIMECODE_SAMPLE pTimecodeSamp)
{
    HRESULT hr;
    char szBuf[32];

    if(pTimecodeSamp->dwFlags == ED_DEVCAP_TIMECODE_READ) {

        wsprintf(szBuf, "%.2x", (pTimecodeSamp->timecode.dwFrames & 0xff000000) >> 24);
        hr = SetWindowText(GetDlgItem (m_hwnd, IDC_EDT_TC_HH), szBuf);

        wsprintf(szBuf, "%.2x", (pTimecodeSamp->timecode.dwFrames & 0x00ff0000) >> 16);
        hr = SetWindowText(GetDlgItem (m_hwnd, IDC_EDT_TC_MM), szBuf);

        wsprintf(szBuf, "%.2x", (pTimecodeSamp->timecode.dwFrames & 0x0000ff00) >> 8);
        hr = SetWindowText(GetDlgItem (m_hwnd, IDC_EDT_TC_SS), szBuf);

        wsprintf(szBuf, "%.2x", (pTimecodeSamp->timecode.dwFrames & 0x000000ff));
        hr = SetWindowText(GetDlgItem (m_hwnd, IDC_EDT_TC_FF), szBuf);

    } else {            
        hr = SetWindowText(GetDlgItem (m_hwnd, IDC_EDT_ATN_BF), pTimecodeSamp->dwUser ? "1":"0");

        wsprintf(szBuf, "%d", pTimecodeSamp->timecode.dwFrames );            
        hr = SetWindowText(GetDlgItem (m_hwnd, IDC_EDT_ATN), szBuf);
    }

    return hr;
}

//
// Convert string (lower case only) string to number
//
HRESULT
CDVcrControlProperties::DVcrConvertString2Number(
    char *pszAvcRaw, PBYTE pbAvcRaw, PLONG pByteRtn)
{
    char szTemp[1024], *pszTemp, ch1, ch2;
    long cntStrLen = strlen(pszAvcRaw), i, j;

    // remove blank space
    pszTemp = pszAvcRaw;
    for (i=j=0; i < cntStrLen+1; i++) {
       if(*pszTemp != ' ') {
          szTemp[j] = *pszTemp;
          j++;
       }
       pszTemp++;
    }
    
    cntStrLen = j--;  // less eol char.

    // xlate two characters to one byte
    *pByteRtn = cntStrLen/2;
    // Only use lower case
    for (i=0; i < *pByteRtn; i++) {
        // Take two bytes and translte it to a number
        ch1 = szTemp[i*2]   > '9' ? szTemp[i*2] -   'a' + 10: szTemp[i*2] -   '0';
        ch2 = szTemp[i*2+1] > '9' ? szTemp[i*2+1] - 'a' + 10: szTemp[i*2+1] - '0';        
        *(pbAvcRaw+i) = ch1 * 16 + ch2;
        DbgLog((LOG_TRACE, 2, TEXT("%d) %.2x"), i, *(pbAvcRaw+i)));
    }

    return S_OK;
}


HRESULT
CDVcrControlProperties::DVcrConvertNumber2String(
    char *pszAvcRaw, PBYTE pbAvcRaw, LONG cntByte)
{
    long i;
    BYTE n;

    // Only accept lower case
    for (i=0; i < cntByte; i++) {
         n = *(pbAvcRaw+i);
         *(pszAvcRaw+i*3)   = n / 16 > 9 ? n / 16 + 'a'-10 : n / 16 + '0';
         *(pszAvcRaw+i*3+1) = n % 16 > 9 ? n % 16 + 'a'-10 : n % 16 + '0';
         *(pszAvcRaw+i*3+2) = ' ';
    }

    *(pszAvcRaw+i*3) = 0;

    return S_OK;
}

void
CDVcrControlProperties::UpdateTimecode(
    )
{
    TIMECODE_SAMPLE TimecodeSample;

    if(!m_pDVcrTmCdReader) 
        return;   

    TimecodeSample.timecode.dwFrames = 0;
    TimecodeSample.dwFlags = ED_DEVCAP_TIMECODE_READ;

    EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads
    if(S_OK == m_pDVcrTmCdReader->GetTimecode(&TimecodeSample)) {
        DisplayTimecode(&TimecodeSample);                
        TimecodeSample.dwFlags = ED_DEVCAP_ATN_READ;
        if(S_OK == m_pDVcrTmCdReader->GetTimecode(&TimecodeSample))
             DisplayTimecode(&TimecodeSample);                
        }    
    LeaveCriticalSection(&m_csIssueCmd); 
}


//
// OnReceiveMessages
//
// Handles the messages for our property window

INT_PTR
CDVcrControlProperties::OnReceiveMessage( 
    HWND hwnd
    , UINT uMsg
    , WPARAM wParam
    , LPARAM lParam) 
{
    HRESULT hr = NOERROR;
    int iNotify = HIWORD (wParam);

    switch (uMsg) {

    case WM_INITDIALOG:
        return (INT_PTR)TRUE;    

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case IDC_BTN_DV_PLAY:
            if(m_pDVcrExtTransport) {
                EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads
                if(NOERROR == (hr = m_pDVcrExtTransport->put_Mode(ED_MODE_PLAY)))
                    UpdateTransportState(ED_MODE_PLAY);
                LeaveCriticalSection(&m_csIssueCmd); 
            }
            break;

        case IDC_BTN_DV_PAUSE:
            if(m_pDVcrExtTransport) {
                EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads
                if(NOERROR == (hr = m_pDVcrExtTransport->put_Mode(ED_MODE_FREEZE)))
                    UpdateTransportState(ED_MODE_FREEZE);
                LeaveCriticalSection(&m_csIssueCmd); 
            }
            break;

        case IDC_BTN_DV_STEP_FWD:
            if(m_pDVcrExtTransport) {
                EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads
                if(NOERROR == (hr = m_pDVcrExtTransport->put_Mode(ED_MODE_STEP_FWD)))
                    UpdateTransportState(ED_MODE_STEP_FWD);  
                LeaveCriticalSection(&m_csIssueCmd); 
            }
            break;

        case IDC_BTN_DV_STEP_REV:
            if(m_pDVcrExtTransport) {
                EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads
                if(NOERROR == ( hr = m_pDVcrExtTransport->put_Mode(ED_MODE_STEP_REV)))
                    UpdateTransportState(ED_MODE_STEP_REV);      
                LeaveCriticalSection(&m_csIssueCmd); 
            }
            break;

        case IDC_BTN_DV_STOP:
            if(m_pDVcrExtTransport) {
                EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads
                if(NOERROR == (hr = m_pDVcrExtTransport->put_Mode(ED_MODE_STOP)))
                    UpdateTransportState(ED_MODE_STOP);
                LeaveCriticalSection(&m_csIssueCmd); 
            }
            break;  

        case IDC_BTN_DV_FFWD:
            if(m_pDVcrExtTransport) {
                EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads
                if(m_lCurXPrtState == ED_MODE_STOP) {
                    if(NOERROR == (hr = m_pDVcrExtTransport->put_Mode(ED_MODE_FF)))
                        UpdateTransportState(ED_MODE_FF);
                } else {
                    HRESULT hrChecked;
                    long lMode;

                    hrChecked = SendMessage (GetDlgItem(m_hwnd, IDC_CHK_SLOW),BM_GETCHECK, 0, 0);
                    lMode = hrChecked == BST_CHECKED ? ED_MODE_PLAY_SLOWEST_FWD : ED_MODE_PLAY_FASTEST_FWD;
                    if(NOERROR == (hr = m_pDVcrExtTransport->put_Mode(lMode)))
                        UpdateTransportState(lMode);
                }            
                LeaveCriticalSection(&m_csIssueCmd); 
            }
            break;

        case IDC_BTN_DV_RWND:
            if(m_pDVcrExtTransport) {
                EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads                
                if(m_lCurXPrtState == ED_MODE_STOP) {
                    if(NOERROR == (hr = m_pDVcrExtTransport->put_Mode(ED_MODE_REW)))
                        UpdateTransportState(ED_MODE_REW);
                } else {
                    HRESULT hrChecked;
                    long lMode;

                    hrChecked = SendMessage (GetDlgItem(m_hwnd, IDC_CHK_SLOW),BM_GETCHECK, 0, 0);
                    lMode = hrChecked == BST_CHECKED ? ED_MODE_PLAY_SLOWEST_REV : ED_MODE_PLAY_FASTEST_REV;
                    if(NOERROR == (hr = m_pDVcrExtTransport->put_Mode(lMode)))
                        UpdateTransportState(lMode);
                }
                LeaveCriticalSection(&m_csIssueCmd); 
            }
            break;         

        case IDC_BTN_DV_RECORD:
            if(m_pDVcrExtTransport) {
                EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads
                if(NOERROR == (hr = m_pDVcrExtTransport->put_Mode(ED_MODE_RECORD)))
                    UpdateTransportState(ED_MODE_RECORD);
                LeaveCriticalSection(&m_csIssueCmd); 
            }
            break; 

        case IDC_BTN_DV_RECORD_PAUSE:
            if(m_pDVcrExtTransport) {
                EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads
                if(NOERROR == (hr = m_pDVcrExtTransport->put_Mode(ED_MODE_RECORD_FREEZE)))
                    UpdateTransportState(ED_MODE_RECORD_FREEZE);
                LeaveCriticalSection(&m_csIssueCmd); 
            }
            break; 

        case IDC_BTN_TAPE_INSERTED:         
            // User press this to inform us that a tape has been inserted so update tape info.
            Sleep(3000);  // Give DV tape some time to settle.
            UpdateTapeInfo();
            UpdateDevTypeInfo();
            UpdateTimecode();
            return (INT_PTR)TRUE;
            break;

        case IDC_BTN_AVC_SEND: 
        {
            char szAvcRaw[512*2];  // need two character to represent one byte of number 
            BYTE bAvcRaw[512];
            LONG cntByte;

            GetWindowText(GetDlgItem(m_hwnd, IDC_EDT_AVC_SEND), szAvcRaw, 512);
            DbgLog((LOG_TRACE, 1, TEXT("%d bytes, %s"), strlen(szAvcRaw), szAvcRaw));
            DVcrConvertString2Number(szAvcRaw, bAvcRaw, &cntByte);          

            if(cntByte >= 3) {

                if(m_pDVcrExtTransport) {

                    EnterCriticalSection(&m_csIssueCmd); // Serialize cmd among threads
                    hr = m_pDVcrExtTransport->GetTransportBasicParameters(ED_RAW_EXT_DEV_CMD, &cntByte, (LPOLESTR *)bAvcRaw);
                    LeaveCriticalSection(&m_csIssueCmd);                   
                    if(SUCCEEDED (hr) && cntByte >= 3) 
                        DVcrConvertNumber2String(szAvcRaw, bAvcRaw, cntByte);
                    else {
                        switch(HRESULT_CODE(hr)) {
                        case ERROR_GEN_FAILURE:       // STATUS_UNSUCCESSFUL (rejected)
                            strcpy(szAvcRaw, "Operation rejected!");
                            break;
                        case ERROR_INVALID_FUNCTION:  // STATUS_NOT_IMPLEMENTED
                            strcpy(szAvcRaw, "Not implemented!");
                            break;
                        case ERROR_CRC:               // STATUS_DEVICE_DATA_ERROR (Data did not get to device)
                            // Most likely, device was not ready to accept another command, wait and try again.
                            strcpy(szAvcRaw, "Device data error: busy!");
                            break;
                        case ERROR_SEM_TIMEOUT:       // STATUS_IO_TIMEOUT (Operation not supported or device removed ?)
                            strcpy(szAvcRaw, "Operation timed out!");
                            break;
                        case ERROR_INVALID_PARAMETER: // STATUS_INVALID_PARAMETER 
                            strcpy(szAvcRaw, "Invalid parameter!");
                            break;
                        default:
                            strcpy(szAvcRaw, "Unknown error!");
                        break;
                        }
                    }

                } else {
                    strcpy(szAvcRaw, "Transport interface not supported!");                 
                }

            } else 
                strcpy(szAvcRaw, "Entry (< 3) error!");

            SetWindowText(GetDlgItem(m_hwnd, IDC_EDT_AVC_RESP), szAvcRaw);

            //
            // Note: do not track transport state using RAW AVC cmd
            //
        }


        default:
            return (INT_PTR)FALSE;
            //hr = E_NOTIMPL;
            break;
        }

        break;


    case WM_TIMER:
        UpdateTimecode();
        break;

    default:
        return (INT_PTR)FALSE;

    }


    if(NOERROR != hr) {      
        // Possibly the tape has been removed ?
        UpdateTapeInfo();        
    }

    return (INT_PTR)TRUE;
}


//
// SetDirty
//
// notifies the property page site of changes

void 
CDVcrControlProperties::SetDirty()
{
    m_bDirty = TRUE;
    if (m_pPageSite)
        m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);
}























