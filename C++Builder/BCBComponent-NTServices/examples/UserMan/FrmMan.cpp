//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "FrmMan.h"
#include "FrNew.h"
#include "FrProper.h"
#include "FrGroup.h"

//---------------------------------------------------------------------------
#pragma link "UserMan"
#pragma link "NTCommon"
#pragma resource "*.dfm"
TFrmManager *FrmManager;
//---------------------------------------------------------------------------
__fastcall TFrmManager::TFrmManager(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::FormCreate(TObject *Sender)
{
  TStringList  *List;

  List =  UserMan->GetServers("");
  try
  {
  cmbComputers->Items->Assign(List);
  if (!IsWindowsNt)
    {
    cmbComputers->Text = UserMan->GetPrimaryDomainServerName();
    }
  }  
  catch (...)
  {
  List->Free();
  };
  rbLocalClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::rbLocalClick(TObject *Sender)
{
  UserMan->MachineName = cmbComputers->Text;
  if (rbLocal->Checked)
    {lbxGroups->Items->Assign(UserMan->LocalGroups);} else
    if (rbGlobal->Checked)
       {lbxGroups->Items->Assign(UserMan->GlobalGroups);};
  if (lbxGroups->Items->Count > 0) {lbxGroups->ItemIndex = 0;};
  lbxUsers->Items->Assign(UserMan->Users);
  if (lbxUsers->Items->Count > 0) {lbxUsers->ItemIndex = 0;};

}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::cmbComputersChange(TObject *Sender)
{
  dynamic_cast<TComponent *>(Sender)->Tag = 1;
}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::cmbComputersExit(TObject *Sender)
{
  if (cmbComputers->Tag > 0)
    {
    cmbComputers->Tag = 0;
    rbLocalClick(NULL);
    };
}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::lbxGroupsClick(TObject *Sender)
{
  if (rbLocal->Checked) {UserMan->LocalGroupName   = lbxGroups->Items->Strings[lbxGroups->ItemIndex];};
  if (rbGlobal->Checked) {UserMan->GlobalGroupName = lbxGroups->Items->Strings[lbxGroups->ItemIndex];};
}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::lbxGroupsDrawItem(TWinControl *Control, int Index,
	TRect &Rect, TOwnerDrawState State)
{
  AnsiString S;

  TListBox *LB = dynamic_cast<TListBox *> (Control);
  LB->Canvas->Font->Assign(Font);
  if (State.Contains(odFocused))
    {
      LB->Canvas->Brush->Color = clActiveCaption;
      LB->Canvas->Font->Color  = clWhite;
    } else
    {
      if (State.Contains(odSelected))
        {
          LB->Canvas->Brush->Color = clGray;
          LB->Canvas->Font->Color  = clWhite;
        } else
        {
          LB->Canvas->Brush->Color = clWindow;
          LB->Canvas->Font->Color  = clBlack;
        };
    };
  LB->Canvas->FillRect(Rect);
  LB->Canvas->TextRect(Rect, Rect.Left+1, Rect.Top, LB->Items->Strings[Index]);

}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::lbxUsersClick(TObject *Sender)
{
  UserMan->UserName = lbxUsers->Items->Strings[lbxUsers->ItemIndex];
}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::NewUser1Click(TObject *Sender)
{
  FrmNew = new TFrmNew(NULL);
  try
  {
    FrmNew->Caption = "New user";
    if (FrmNew->ShowModal() == mrOk)
      {
        UserMan->Users->Add(FrmNew->Edit1->Text);
        rbLocalClick(NULL);
      }
  }
  catch (...)
  {
    delete FrmNew;
    FrmNew = NULL;
  }
  if (!(FrmNew == NULL)) {delete FrmNew;};
}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::mniDeleteClick(TObject *Sender)
{
  if ((ActiveControl == lbxUsers) && (lbxUsers->Items->Count > 0)) 
    {
      UserMan->Users->Delete(lbxUsers->ItemIndex);
    } else
    {
      if ((ActiveControl == lbxGroups) && (lbxGroups->Items->Count > 0))
        {
          if (rbLocal->Checked) {UserMan->LocalGroups->Delete(lbxGroups->ItemIndex);};
          if (rbGlobal->Checked) {UserMan->GlobalGroups->Delete(lbxGroups->ItemIndex);};
        };
    }
  rbLocalClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::NewGroup1Click(TObject *Sender)
{
  FrmNew = new TFrmNew(NULL);
  try
  {
    FrmNew->Caption = "New group";
    if (FrmNew->ShowModal() == mrOk)
      {
        if (rbLocal->Checked) {UserMan->LocalGroups->Add(FrmNew->Edit1->Text);};
        if (rbGlobal->Checked) {UserMan->GlobalGroups->Add(FrmNew->Edit1->Text);};
      rbLocalClick(NULL);
      };
  }    
  catch (...)
  {
    delete FrmNew;
    FrmNew = NULL;
  };
  if (!(FrmNew == NULL)) {delete FrmNew;}; 
}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::Exit1Click(TObject *Sender)
{
  Close();	
}
//---------------------------------------------------------------------------
void __fastcall TFrmManager::Propertiy1Click(TObject *Sender)
{
 if (ActiveControl == lbxUsers)
  {
    FrmProperty = new TFrmProperty(NULL);
    try
    {
      FrmProperty->ShowModal();
    }
    catch (...)
    {
      delete FrmProperty;
      FrmProperty = NULL;
    };
  if (!(FrmProperty == NULL)) {delete FrmProperty;};
  };

 if (ActiveControl == lbxGroups)
  {
    FrmGroups = new TFrmGroups(NULL);
    try
    {
      FrmGroups->ShowModal();
    }
    catch (...)
    {
      delete FrmGroups;
      FrmGroups = NULL;
    };
  if (!(FrmGroups == NULL)) {delete FrmGroups;};
  };
  
}
//---------------------------------------------------------------------------
