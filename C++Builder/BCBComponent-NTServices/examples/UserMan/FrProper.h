//---------------------------------------------------------------------------
#ifndef FrProperH
#define FrProperH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmProperty : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *edtUserName;
	TLabel *Label2;
	TEdit *edtDomain;
	TLabel *Label3;
	TEdit *edtFullName;
	TLabel *Label4;
	TEdit *edtComment;
	TBevel *Bevel1;
	TLabel *Label5;
	TEdit *edtPassword;
	TLabel *Label6;
	TEdit *edtConfirm;
	TCheckBox *cbxScript;
	TCheckBox *cbxAccountDisabled;
	TCheckBox *cbxHomDirReq;
	TCheckBox *cbxLocked;
	TCheckBox *cbxPasswordNotReq;
	TCheckBox *cbxCannotChange;
	TCheckBox *cbxNeverExpired;
	TBevel *Bevel3;
	TLabel *Label7;
	TEdit *edtLogonCount;
	TLabel *Label8;
	TEdit *edtBadCount;
	TLabel *Label9;
	TEdit *edtLastLogon;
	TLabel *Label10;
	TEdit *edtLastLogoff;
	TLabel *Label11;
	TEdit *edtHomeDir;
	TLabel *Label12;
	TEdit *edtWorkstations;
	TRadioGroup *rgrLoc_Glob;
	TLabel *Label13;
	TListBox *lbxMemberOf;
	TButton *btnToRight;
	TButton *btnToLeft;
	TLabel *Label14;
	TListBox *lbxNotMemberOf;
	TButton *btnCancel;
	TButton *btnOk;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall OnControlChange(TObject *Sender);
	void __fastcall lbxMemberOfClick(TObject *Sender);
	void __fastcall btnToRightClick(TObject *Sender);
	void __fastcall btnToLeftClick(TObject *Sender);
	void __fastcall btnOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrmProperty(TComponent* Owner);
    void __fastcall  MoveItems(TListBox *LBXSource, TListBox *LBXDest);

};
//---------------------------------------------------------------------------
extern TFrmProperty *FrmProperty;
//---------------------------------------------------------------------------
#endif
