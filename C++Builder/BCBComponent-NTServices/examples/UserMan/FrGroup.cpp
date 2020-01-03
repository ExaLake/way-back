//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "FrGroup.h"
#include "FrmMan.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFrmGroups *FrmGroups;
//---------------------------------------------------------------------------
__fastcall TFrmGroups::TFrmGroups(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmGroups::FormCreate(TObject *Sender)
{
  Caption = Caption + ' '+ FrmManager->lbxGroups->Items->Strings[FrmManager->lbxGroups->ItemIndex];
  if (FrmManager->rbLocal->Checked)
    {
      memMembers->Lines->Assign(FrmManager->UserMan->LocalGroupMembers);
      edtDescription->Text = FrmManager->UserMan->LocalGroupComment;
    };
  if (FrmManager->rbGlobal->Checked)
    {
      memMembers->Lines->Assign(FrmManager->UserMan->GlobalGroupMembers);
      edtDescription->Text = FrmManager->UserMan->GlobalGroupComment;
    };
}
//---------------------------------------------------------------------------