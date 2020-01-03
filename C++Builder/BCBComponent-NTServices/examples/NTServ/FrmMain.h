//---------------------------------------------------------------------------
#ifndef FrmMainH
#define FrmMainH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "TService.hpp"
#include "NTCommon.hpp"
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmSrvMngr : public TForm
{
__published:	// IDE-managed Components
	TNTService *NTService;
	TCheckBox *cbxDevices;
	TCheckBox *cbxReadOnly;
	TListBox *lbxServices;
	TComboBox *cmbComputer;
	TLabel *Label1;
	TButton *btnRefresh;
	TButton *btnStart;
	TButton *btnStop;
	TButton *btnNewService;
	TButton *btnDelete;
	TButton *btnProperties;
	TButton *btnClose;
	TTimer *tmrWait;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnRefreshClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall cbxDevicesClick(TObject *Sender);
	void __fastcall cbxReadOnlyClick(TObject *Sender);
	void __fastcall lbxServicesClick(TObject *Sender);
	void __fastcall lbxServicesDrawItem(TWinControl *Control, int Index,
	TRect &Rect, TOwnerDrawState State);
	void __fastcall tmrWaitTimer(TObject *Sender);
	void __fastcall btnStartClick(TObject *Sender);
	void __fastcall btnStopClick(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall btnNewServiceClick(TObject *Sender);
	void __fastcall btnDeleteClick(TObject *Sender);
	void __fastcall btnPropertiesClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    TEnumList *List;
	__fastcall TFrmSrvMngr(TComponent* Owner);
    void __fastcall SetButtonStates();
    void __fastcall Wait();


};
//---------------------------------------------------------------------------
extern TFrmSrvMngr *FrmSrvMngr;
//---------------------------------------------------------------------------
#endif
