//---------------------------------------------------------------------------
#ifndef FrmManH
#define FrmManH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "UserMan.hpp"
#include "NTCommon.hpp"
#include <vcl\Menus.hpp>
//---------------------------------------------------------------------------
class TFrmManager : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TComboBox *cmbComputers;
	TRadioButton *rbLocal;
	TRadioButton *rbGlobal;
	TListBox *lbxGroups;
	TNTUserMan *UserMan;
	TMainMenu *MainMenu1;
	TMenuItem *Menu1;
	TMenuItem *NewUser1;
	TMenuItem *NewGroup1;
	TMenuItem *N1;
	TMenuItem *mniDelete;
	TMenuItem *Propertiy1;
	TMenuItem *N2;
	TMenuItem *Exit1;
	TLabel *Label2;
	TListBox *lbxUsers;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall rbLocalClick(TObject *Sender);
	void __fastcall cmbComputersChange(TObject *Sender);
	void __fastcall cmbComputersExit(TObject *Sender);
	void __fastcall lbxGroupsClick(TObject *Sender);
	void __fastcall lbxGroupsDrawItem(TWinControl *Control, int Index, TRect &Rect,
	TOwnerDrawState State);
	void __fastcall lbxUsersClick(TObject *Sender);
	void __fastcall NewUser1Click(TObject *Sender);
	void __fastcall mniDeleteClick(TObject *Sender);
	void __fastcall NewGroup1Click(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	
	void __fastcall Propertiy1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrmManager(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFrmManager *FrmManager;
//---------------------------------------------------------------------------
#endif
