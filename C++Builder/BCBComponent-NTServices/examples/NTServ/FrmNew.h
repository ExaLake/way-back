//---------------------------------------------------------------------------
#ifndef FrmNewH
#define FrmNewH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmNewService : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *EdtServiceName;
	TLabel *Label2;
	TEdit *EdtDisplayName;
	TLabel *Label3;
	TEdit *EdtFileName;
	TSpeedButton *spbBrowse;
	TRadioGroup *rgbStartType;
	TButton *btnCancel;
	TButton *btnCreate;
	void __fastcall spbBrowseClick(TObject *Sender);
	void __fastcall EdtServiceNameChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrmNewService(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFrmNewService *FrmNewService;
//---------------------------------------------------------------------------
#endif
