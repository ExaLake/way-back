//---------------------------------------------------------------------------
#ifndef FrmPropH
#define FrmPropH
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
	TEdit *EdtServiceName;
	TLabel *Label2;
	TEdit *EdtDisplayName;
	TLabel *Label3;
	TEdit *EdtBinaryFile;
	TLabel *Label4;
	TComboBox *cmbLoadOrder;
	TLabel *Label5;
	TEdit *edtOrderWithinGroup;
	TLabel *Label6;
	TEdit *edtAccount;
	TLabel *Label7;
	TEdit *edtPassword;
	TLabel *Dependencies;
	TMemo *memDependencies;
	TRadioGroup *rgpStartup;
	TRadioGroup *rgpError;
	TGroupBox *grpServiceType;
	TCheckBox *cbxKernelDriver;
	TCheckBox *cbxFileDriver;
	TCheckBox *cbxAdapter;
	TCheckBox *cbxRecognizer;
	TCheckBox *cmbWin32Own;
	TCheckBox *cbxWin32Shared;
	TCheckBox *cbxInteractive;
	TButton *btnCancel;
	TButton *btnChange;
private:	// User declarations
public:		// User declarations
	__fastcall TFrmProperty(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFrmProperty *FrmProperty;
//---------------------------------------------------------------------------
#endif
