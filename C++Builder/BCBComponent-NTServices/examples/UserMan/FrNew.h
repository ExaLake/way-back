//---------------------------------------------------------------------------
#ifndef FrNewH
#define FrNewH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
//---------------------------------------------------------------------------
class TFrmNew : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *Edit1;
	TButton *btnOk;
	void __fastcall Edit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrmNew(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFrmNew *FrmNew;
//---------------------------------------------------------------------------
#endif
