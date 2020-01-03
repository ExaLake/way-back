//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "FrmNew.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFrmNewService *FrmNewService;
//---------------------------------------------------------------------------
__fastcall TFrmNewService::TFrmNewService(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmNewService::spbBrowseClick(TObject *Sender)
{
  TOpenDialog *Dialog;
  Dialog = new TOpenDialog(this);
  try
  {
    Dialog->FileName   = EdtFileName->Text;
    Dialog->DefaultExt = "*.exe";
    Dialog->Filter     = "Executable files (*.exe)|*.exe|All files (*.*)|*.*|";
    if (Dialog->Execute()) {EdtFileName->Text = Dialog->FileName;};
  }
  catch (...)
  {
   Dialog->Free();
  } 
}
//---------------------------------------------------------------------------
void __fastcall TFrmNewService::EdtServiceNameChange(TObject *Sender)
{
  btnCreate->Enabled =
    (!(EdtFileName->Text == "")) &&
    (!(EdtDisplayName->Text == "")) &&
    (!(EdtServiceName->Text == ""));
}
//---------------------------------------------------------------------------
