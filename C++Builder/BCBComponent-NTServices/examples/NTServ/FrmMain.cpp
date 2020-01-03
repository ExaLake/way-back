//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <vcl/dstring.h>
#include <stdio.h>

#pragma hdrstop

#include "FrmMain.h"
#include "FrmNew.h"
#include "FrmProp.h"
//---------------------------------------------------------------------------
#pragma link "TService"
#pragma link "NTCommon"
#pragma resource "*.dfm"
#include "NT_vs_95.hpp"
#include "typeinfo.h"

TFrmSrvMngr *FrmSrvMngr;
//---------------------------------------------------------------------------
__fastcall TFrmSrvMngr::TFrmSrvMngr(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::FormCreate(TObject *Sender)
{
TStringList *List;

List = new TStringList;
lbxServices->ItemHeight = lbxServices->Canvas->TextHeight("A")+2;
List = NTService->GetServers("");
  try
  {
    cmbComputer->Items->Assign(List);
  }
  catch ( ... )
  {
    List->Free();
  };
  if (!IsWindowsNt) {
   cmbComputer->Text = GetPrimaryDomainServerName().c_str();
  }
  btnRefreshClick(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::btnRefreshClick(TObject *Sender)
{
  TEnumSevices AType;
  TServiceStates AState;

  NTService->ActiveManager = false;
  AState.Clear(); AState <<  STATE_ACTIVE << STATE_INACTIVE;
  AType.Clear();  AType << PROCESS;
  if (cbxDevices->Checked) {AType << DRIVER;};
  NTService->MachineName = Trim(cmbComputer->Text);
  NTService->ManagerAccess.Clear();
  NTService->ManagerAccess << M_CONNECT << M_ENUMERATE_SERVICE;
  List->Free(); List = 0; 
  lbxServices->Clear();
  List = NTService->GetServiceList(AState, AType);
  for (int i = 0; i < List->Count; i++) lbxServices->Items->Add(List->Items[i]->ServiceName);
  NTService->ActiveManager = false;
  if (lbxServices->Items->Count > 0) lbxServices->ItemIndex = 0;
  SetButtonStates();
}
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::FormDestroy(TObject *Sender)
{
  List->Free();
}

//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::SetButtonStates()
{
  if ((!List == 0) && (List->Count > 0))
    {
    if (List->Items[lbxServices->ItemIndex]->CurrentState == STOPPED)
      {
      btnStart->Enabled = true;
      btnStop->Enabled = false;
      };
    if (List->Items[lbxServices->ItemIndex]->CurrentState == RUNNING)
      {
      btnStart->Enabled = false;
      btnStop->Enabled = true;
      };
    } else
    {
    btnStart->Enabled = false;
    btnStop->Enabled = false;
    };
 };

void __fastcall TFrmSrvMngr::cbxDevicesClick(TObject *Sender)
{
  btnRefreshClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::cbxReadOnlyClick(TObject *Sender)
{
  btnDelete->Enabled  = !cbxReadOnly->Checked;
  btnNewService->Enabled = !cbxReadOnly->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::lbxServicesClick(TObject *Sender)
{
  SetButtonStates();
}
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::lbxServicesDrawItem(TWinControl *Control,
	int Index, TRect &Rect, TOwnerDrawState State)
{
  AnsiString S;

  if (State.Contains(odSelected) || State.Contains(odFocused))
    {
    lbxServices->Canvas->Brush->Color = clActiveCaption;
    lbxServices->Canvas->Pen->Color = clWhite;
    } else
    {
    lbxServices->Canvas->Brush->Color = clWindow;
    lbxServices->Canvas->Pen->Color  = clBlack;
    };
  lbxServices->Canvas->FillRect(Rect);
  lbxServices->Canvas->TextRect(Rect, Rect.Left + 1, Rect.Top, List->Items[Index]->DisplayedName);
  switch (List->Items[Index]->CurrentState) {
    case STOPPED:           {S = "Stopped"; break;}
    case START_PENDING:     {S = "Starting"; break;}
    case STOP_PENDING:      {S = "Stopping"; break;}
    case RUNNING:           {S = "Running"; break;}
    case CONTINUE_PENDING:  {S = "Continueing"; break;}
    case PAUSE_PENDING:     {S = "Pausing"; break;}
    case PAUSED:            {S = "Paused"; break;}
   default: S = "Unknown";
  };
  Rect.Left = Rect.Right - lbxServices->Canvas->TextWidth(S);
  lbxServices->Canvas->TextRect(Rect, Rect.Left + 1, Rect.Top, S);
}
//---------------------------------------------------------------------------

void __fastcall TFrmSrvMngr::Wait()
{
//  TControl *Control;

  for ( int i = 0; i < ControlCount; i++)
   {
//     Control = Controls[i];
//     if (typeid(Control) == typeid(TButton))
//       {Controls[i]->Enabled = false;};
   }
     tmrWait->Enabled = true;
};

void __fastcall TFrmSrvMngr::tmrWaitTimer(TObject *Sender)
{
  tmrWait->Enabled = false;
//  for (int i = 0; to ControlCount - 1 do
//    if Controls[i] is TButton then (Controls[i] as TButton).Enabled := true;
  btnRefreshClick(NULL);
  cbxReadOnlyClick(NULL);
  SetButtonStates();
}
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::btnStartClick(TObject *Sender)
{
  Wait();
  NTService->ManagerAccess.Clear();
  NTService->ManagerAccess << M_CONNECT << M_ENUMERATE_SERVICE;
  NTService->ServiceAccess.Clear();
  NTService->ServiceAccess << S_ALL_ACCESS;
  NTService->ServiceName   = List->Items[lbxServices->ItemIndex]->ServiceName;
  NTService->ActiveManager = true;
  NTService->ActiveService = true;
  NTService->Startservice();
  NTService->ActiveService = false;
  NTService->ActiveManager = false;
  btnRefreshClick(NULL);

}
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::btnStopClick(TObject *Sender)
{
  NTService->ManagerAccess.Clear();
  NTService->ManagerAccess  << M_CONNECT << M_ENUMERATE_SERVICE;
  NTService->ServiceAccess.Clear();
  NTService->ServiceAccess  << S_ALL_ACCESS;
  NTService->ActiveManager = true;
  NTService->ServiceName   = List->Items[lbxServices->ItemIndex]->ServiceName;
  NTService->ActiveService = true;
  NTService->ControlService(CONTROL_STOP);
  NTService->ActiveService = false;
  NTService->ActiveManager = false;
  Wait();
  btnRefreshClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::btnCloseClick(TObject *Sender)
{
  Close();	
}
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::btnNewServiceClick(TObject *Sender)
{

  FrmNewService =  new TFrmNewService(this);
    try
    {
    if (FrmNewService->ShowModal() == mrOk)
      {
      NTService->ManagerAccess.Clear();
      NTService->ManagerAccess << M_CONNECT << M_CREATE_SERVICE;
      NTService->ServiceType.Clear();
      NTService->ServiceType << WIN32_OWN_PROCESS;
      NTService->ErrorControl << ERROR_NORMAL;
      NTService->ServiceName  = FrmNewService->EdtServiceName->Text;
      NTService->DisplayName  = FrmNewService->EdtDisplayName->Text;
      NTService->BinaryPathName = FrmNewService->EdtFileName->Text;
      NTService->ServiceStartName = "LocalSystem";
      switch (FrmNewService->rgbStartType->ItemIndex)
        {
          case 0: {NTService->StartType = AUTO_START; break;}
          case 1: {NTService->StartType = DEMAND_START; break;}
          case 2: {NTService->StartType = DISABLED; break;}
        }
      NTService->ActiveManager = true;
      NTService->Createservice();
      NTService->ActiveManager = false;
      Wait();
      btnRefreshClick(NULL);
      Application->MessageBox("The service has been created successefuly.", "Information", IDOK);
      }
    }
    catch ( ... )
    {
      delete FrmNewService;
      FrmNewService = NULL;
    }
  if (!(FrmNewService == NULL)) {delete FrmNewService;};
};
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::btnDeleteClick(TObject *Sender)
{
  if (Application->MessageBox("Are you sure to delete service ?. It may cause system damage !",
                "Warning", IDOK	+ IDCANCEL) == IDCANCEL) return;
  NTService->ManagerAccess.Clear();
  NTService->ManagerAccess << M_CONNECT << M_ENUMERATE_SERVICE;
  NTService->ServiceAccess.Clear();
  NTService->ServiceAccess << S_ALL_ACCESS;
  NTService->ServiceName  = List->Items[lbxServices->ItemIndex]->ServiceName;
  NTService->ActiveManager = true;
  NTService->ActiveService = true;
  NTService->DeleteService();
  NTService->ActiveService = false;
  NTService->ActiveManager = false;
  Wait();
  btnRefreshClick(NULL);
  Application->MessageBox("The specified service has been marked for deletion.", "Information", IDOK);
}
//---------------------------------------------------------------------------
void __fastcall TFrmSrvMngr::btnPropertiesClick(TObject *Sender)
{
 TServiceTypes AServiceType;
 FrmProperty = new TFrmProperty(this);
 try
   {
    FrmProperty->btnChange->Enabled = !cbxReadOnly->Checked;
    FrmProperty->EdtServiceName->Text = List->Items[lbxServices->ItemIndex]->ServiceName;
    NTService->ServiceName   = FrmProperty->EdtServiceName->Text;
    NTService->ManagerAccess.Clear();
    NTService->ManagerAccess << M_CONNECT;
    NTService->ServiceAccess.Clear();
    NTService->ServiceAccess << S_QUERY_CONFIG;
    NTService->ActiveManager = true;
    NTService->ActiveService = true;
    FrmProperty->EdtDisplayName->Text      = NTService->DisplayName;
    FrmProperty->EdtBinaryFile->Text       = NTService->BinaryPathName;
    try {NTService->GetOrderGroupList(FrmProperty->cmbLoadOrder->Items);} catch (...) {};
    FrmProperty->cmbLoadOrder->Text        = NTService->LoadOrder;
    FrmProperty->edtOrderWithinGroup->Text = IntToStr(NTService->TagId);
    FrmProperty->memDependencies->Lines->Assign(NTService->Dependencies);
    FrmProperty->edtAccount->Text          = NTService->ServiceStartName;
    FrmProperty->edtPassword->Text         = "****************";
    FrmProperty->edtAccount->Tag           = 0;
    FrmProperty->edtPassword->Tag          = 0;

    if (NTService->StartType == BOOT_START)   {FrmProperty->rgpStartup->ItemIndex = 0;} else
    if (NTService->StartType == SYSTEM_START) {FrmProperty->rgpStartup->ItemIndex = 1;} else
    if (NTService->StartType == AUTO_START)   {FrmProperty->rgpStartup->ItemIndex = 2;} else
    if (NTService->StartType == DEMAND_START) {FrmProperty->rgpStartup->ItemIndex = 3;} else
    if (NTService->StartType == DISABLED)     {FrmProperty->rgpStartup->ItemIndex = 4;};

    if (NTService->ErrorControl == ERROR_IGNORE)  {FrmProperty->rgpError->ItemIndex = 0;} else
    if (NTService->ErrorControl == ERROR_NORMAL)  {FrmProperty->rgpError->ItemIndex = 1;} else
    if (NTService->ErrorControl == ERROR_SEVERE)  {FrmProperty->rgpError->ItemIndex = 2;} else
    if (NTService->ErrorControl == ERROR_CRITICAL){FrmProperty->rgpError->ItemIndex = 3;};

    FrmProperty->cbxKernelDriver->Checked = NTService->ServiceType.Contains(KERNEL_DRIVER);
    FrmProperty->cbxFileDriver->Checked   = NTService->ServiceType.Contains(FILE_SYSTEM_DRIVER);
    FrmProperty->cbxAdapter->Checked      = NTService->ServiceType.Contains(ADAPTER);
    FrmProperty->cbxRecognizer->Checked   = NTService->ServiceType.Contains(RECOGNIZER_DRIVER);
    FrmProperty->cmbWin32Own->Checked     = NTService->ServiceType.Contains(WIN32_OWN_PROCESS);
    FrmProperty->cbxWin32Shared->Checked  = NTService->ServiceType.Contains(WIN32_SHARE_PROCESS);
    FrmProperty->cbxInteractive->Checked  = NTService->ServiceType.Contains(INTERACTIVE_PROCESS);

    NTService->ActiveService = false;
    NTService->ActiveManager = false;
    if (FrmProperty->ShowModal() == mrOk)
      {
      if (Application->MessageBox("Are you sure to change service properties?. It may cause system damage !",
                "Warning", MB_OKCANCEL	) == IDOK)
        {
        NTService->ManagerAccess.Clear();
        NTService->ManagerAccess << M_CONNECT << M_MODIFY_BOOT_CONFIG;
        NTService->ServiceAccess.Clear();
        NTService->ServiceAccess << S_ALL_ACCESS;
        NTService->ActiveManager = true;
        NTService->ActiveService = true;

        try
        {
        AServiceType.Clear();
        if (FrmProperty->cbxKernelDriver->Checked) {AServiceType << KERNEL_DRIVER;};
        if (FrmProperty->cbxFileDriver->Checked)   {AServiceType << FILE_SYSTEM_DRIVER;};
        if (FrmProperty->cbxAdapter->Checked)      {AServiceType << ADAPTER;};
        if (FrmProperty->cbxRecognizer->Checked)   {AServiceType << RECOGNIZER_DRIVER;};
        if (FrmProperty->cmbWin32Own->Checked)     {AServiceType << WIN32_OWN_PROCESS;};
        if (FrmProperty->cbxWin32Shared->Checked)  {AServiceType << WIN32_SHARE_PROCESS;};
        if (FrmProperty->cbxInteractive->Checked)  {AServiceType << INTERACTIVE_PROCESS;};
        NTService->ServiceType = AServiceType;

        switch (FrmProperty->rgpStartup->ItemIndex)
        {
         case 0: {NTService->StartType = BOOT_START; break;}
         case 1: {NTService->StartType = SYSTEM_START; break;}
         case 2: {NTService->StartType = AUTO_START; break;}
         case 3: {NTService->StartType = DEMAND_START; break;}
         case 4: {NTService->StartType = DISABLED; break;}
        };

        switch (FrmProperty->rgpError->ItemIndex)
         {
         case 0: {NTService->ErrorControl = ERROR_IGNORE; break;};
         case 1: {NTService->ErrorControl = ERROR_NORMAL; break;};
         case 2: {NTService->ErrorControl = ERROR_SEVERE; break;};
         case 3: {NTService->ErrorControl = ERROR_CRITICAL; break;};
        };

        NTService->BinaryPathName      = FrmProperty->EdtBinaryFile->Text;
        NTService->DisplayName         = FrmProperty->EdtDisplayName->Text;
        NTService->LoadOrder           = FrmProperty->cmbLoadOrder->Text;
        NTService->Dependencies        = FrmProperty->memDependencies->Lines;
        if  ((FrmProperty->edtAccount->Tag > 0) || (FrmProperty->edtPassword->Tag > 0))
          {
          NTService->Password            = FrmProperty->edtPassword->Text;
          NTService->ServiceStartName    = FrmProperty->edtAccount->Text;
          };
        }
        catch (...)
        {
        NTService->ActiveService = false;
        NTService->ActiveManager = false;
        throw;
        };

        Wait();
        btnRefreshClick(NULL);
        };
      }
   }
   catch ( ... )
   {
    delete FrmProperty;
    FrmProperty = NULL;
    throw;
   };
 if (!(FrmProperty == NULL)) {delete FrmProperty;};
}
//---------------------------------------------------------------------------
