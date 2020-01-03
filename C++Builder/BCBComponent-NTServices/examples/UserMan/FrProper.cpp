//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "FrProper.h"
#include "FrmMan.h"
#include "NTCommon.hpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFrmProperty *FrmProperty;
//---------------------------------------------------------------------------
__fastcall TFrmProperty::TFrmProperty(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmProperty::FormCreate(TObject *Sender)
{
  edtUserName->Text   = FrmManager->UserMan->UserName;
  edtDomain->Text     = FrmManager->UserMan->UserInfo->Domain;
  edtFullName->Text   = FrmManager->UserMan->UserInfo->FullName;
  edtComment->Text    = FrmManager->UserMan->UserInfo->Comment;
  edtPassword->Text   = "********";
  edtConfirm->Text    = "********";
  cbxScript->Checked          = FrmManager->UserMan->UserInfo->Options.Contains(F_SCRIPT);
  cbxAccountDisabled->Checked = FrmManager->UserMan->UserInfo->Options.Contains(F_ACCOUNTDISABLE);
  cbxHomDirReq->Checked       = FrmManager->UserMan->UserInfo->Options.Contains(F_HOMEDIR_REQUIRED);
  cbxLocked->Checked          = FrmManager->UserMan->UserInfo->Options.Contains(F_LOCKOUT);
  cbxPasswordNotReq->Checked  = FrmManager->UserMan->UserInfo->Options.Contains(F_PASSWD_NOTREQD);
  cbxCannotChange->Checked    = FrmManager->UserMan->UserInfo->Options.Contains(F_PASSWD_CANT_CHANGE);
  cbxNeverExpired->Checked    = FrmManager->UserMan->UserInfo->Options.Contains(F_DONT_EXPIRE_PASSWD);
  edtLogonCount->Text = IntToStr(FrmManager->UserMan->UserInfo->LogonCount);
  edtBadCount->Text   = IntToStr(FrmManager->UserMan->UserInfo->BadPasswordCount);
  int tmpInt;
  tmpInt = FrmManager->UserMan->UserInfo->LastLogon;
  if (tmpInt == cnst1970) {edtLastLogon->Text = "never";}
    else edtLastLogon->Text  = DateTimeToStr(FrmManager->UserMan->UserInfo->LastLogon);
  tmpInt = FrmManager->UserMan->UserInfo->LastLogOff;
  if (tmpInt == cnst1970) {edtLastLogoff->Text = "never";}
    else edtLastLogoff->Text  = DateTimeToStr(FrmManager->UserMan->UserInfo->LastLogOff);
  edtHomeDir->Text      = FrmManager->UserMan->UserInfo->HomeDir;
  edtWorkstations->Text = FrmManager->UserMan->UserInfo->Workstations;
  if (FrmManager->rbLocal->Checked) 
    {
    rgrLoc_Glob->ItemIndex = 0;
    lbxMemberOf->Items->Assign(FrmManager->UserMan->MemberOfLocal);
    lbxNotMemberOf->Items->Assign(FrmManager->UserMan->LocalGroups);
    } else
    {
    rgrLoc_Glob->ItemIndex = 1;
    lbxMemberOf->Items->Assign(FrmManager->UserMan->MemberOfGlob);
    lbxNotMemberOf->Items->Assign(FrmManager->UserMan->GlobalGroups);
    }
  for (int i = 0; i < lbxMemberOf->Items->Count; i++)
    {
    if (!(lbxNotMemberOf->Items->IndexOf(lbxMemberOf->Items->Strings[i]) == -1))
      {lbxNotMemberOf->Items->Delete(lbxNotMemberOf->Items->IndexOf(lbxMemberOf->Items->Strings[i]));};
    }  
}
//---------------------------------------------------------------------------
void __fastcall TFrmProperty::OnControlChange(TObject *Sender)
{
  dynamic_cast<TControl *> (Sender)->Tag = 1;
}
//---------------------------------------------------------------------------
void __fastcall TFrmProperty::lbxMemberOfClick(TObject *Sender)
{
  btnToRight->Enabled =  lbxMemberOf->SelCount > 0;
  btnToLeft->Enabled  =  lbxNotMemberOf->SelCount > 0;
}
//---------------------------------------------------------------------------
void __fastcall TFrmProperty::btnToRightClick(TObject *Sender)
{
  MoveItems(lbxMemberOf, lbxNotMemberOf);
}
//---------------------------------------------------------------------------
void __fastcall TFrmProperty::btnToLeftClick(TObject *Sender)
{
  MoveItems(lbxNotMemberOf, lbxMemberOf);
}
//---------------------------------------------------------------------------

void __fastcall  TFrmProperty::MoveItems(TListBox *LBXSource, TListBox *LBXDest)
{
  int index;

  for (int i = 0; i < LBXSource->Items->Count; i++)
    {
    if (LBXSource->Selected[i]) 
      {
      LBXDest->Items->AddObject(LBXSource->Items->Strings[i],LBXSource->Items->Objects[i]);
      };
    }  
  for (int i = 0; i < LBXDest->Items->Count; i++)
    {
    index = LBXSource->Items->IndexOf(LBXDest->Items->Strings[i]);
    if (!(index == -1)) {LBXSource->Items->Delete(index);};
    };
    
  lbxMemberOfClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFrmProperty::btnOkClick(TObject *Sender)
{
  TUserFlags Opt;

  if (
     ((edtPassword->Tag > 0) || (edtConfirm->Tag > 0)) &&
     (!(edtPassword->Text == edtConfirm->Text))
     )
     { ShowMessage("Password and confirmation do not match !"); return; };

  FrmManager->UserMan->UserInfo->FullName = edtFullName->Text;
  FrmManager->UserMan->UserInfo->Comment  = edtComment->Text;
  FrmManager->UserMan->UserInfo->Password = edtPassword->Text;
  Opt.Clear();;
  if  (cbxScript->Checked) {Opt << F_SCRIPT;};
  if  (cbxAccountDisabled->Checked) {Opt << F_ACCOUNTDISABLE;};
  if  (cbxHomDirReq->Checked) {Opt << F_HOMEDIR_REQUIRED;};
  if  (cbxLocked->Checked) {Opt << F_LOCKOUT;};
  if  (cbxPasswordNotReq->Checked) {Opt << F_PASSWD_NOTREQD;};
  if  (cbxCannotChange->Checked) {Opt << F_PASSWD_CANT_CHANGE;};
  if  (cbxNeverExpired->Checked) {Opt << F_DONT_EXPIRE_PASSWD;};
  FrmManager->UserMan->UserInfo->Options = Opt;
  FrmManager->UserMan->UserInfo->HomeDir = edtHomeDir->Text;
  FrmManager->UserMan->UserInfo->Workstations = edtWorkstations->Text;
  if (FrmManager->rbLocal->Checked)
    {
    FrmManager->UserMan->MemberOfLocal = lbxMemberOf->Items;
    } else
    {
    FrmManager->UserMan->MemberOfGlob = lbxMemberOf->Items;
    };
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------