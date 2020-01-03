//---------------------------------------------------------------------------
#ifndef FrGroupH
#define FrGroupH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TFrmGroups : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *edtDescription;
	TMemo *memMembers;
	TButton *btnCancel;
	TButton *btnOK;
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrmGroups(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFrmGroups *FrmGroups;
//---------------------------------------------------------------------------
#endif
