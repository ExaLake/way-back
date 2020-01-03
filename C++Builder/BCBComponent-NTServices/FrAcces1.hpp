// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FrAcces1.pas' rev: 3.00

#ifndef FrAcces1HPP
#define FrAcces1HPP
#include <ExtCtrls.hpp>
#include <AbstrSec.hpp>
#include <RegSecur.hpp>
#include <NTShare.hpp>
#include <FilSecur.hpp>
#include <StdCtrls.hpp>
#include <Dialogs.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Messages.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fracces1
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFrmEditAccess;
class PASCALIMPLEMENTATION TFrmEditAccess : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TGroupBox* gbxFilePermissions;
	Stdctrls::TCheckBox* cbxRead;
	Stdctrls::TCheckBox* cbxWrite;
	Stdctrls::TCheckBox* cbxExecute;
	Stdctrls::TCheckBox* cbxDelete;
	Stdctrls::TCheckBox* cbxPermission;
	Stdctrls::TCheckBox* cbxOwnership;
	Stdctrls::TCheckBox* cbxFullContol;
	Stdctrls::TGroupBox* grbKeyPermissions;
	Stdctrls::TCheckBox* cbxKamQueryValue;
	Stdctrls::TCheckBox* cbxKamSetValue;
	Stdctrls::TCheckBox* cbxKamCreateSubKey;
	Stdctrls::TCheckBox* cbxKamEnumSubKey;
	Stdctrls::TCheckBox* cbxKamNotify;
	Stdctrls::TCheckBox* cbxKamCreateLink;
	Stdctrls::TCheckBox* cbxKamDelete;
	Stdctrls::TCheckBox* cbxKamWriteDAC;
	Stdctrls::TCheckBox* cbxKamFullControl;
	Stdctrls::TCheckBox* cbxKamReadControl;
	Stdctrls::TCheckBox* cbxKamWriteOwner;
	Extctrls::TPanel* pnlButtons;
	Stdctrls::TButton* btnCancel;
	Stdctrls::TButton* btnOk;
	Extctrls::TPanel* pnlUserName;
	Stdctrls::TGroupBox* grbFlags;
	Stdctrls::TCheckBox* cbxObjectInherit;
	Stdctrls::TCheckBox* cbxContainer;
	Stdctrls::TCheckBox* cbxInheritOnly;
	Stdctrls::TCheckBox* cbxNoPropogate;
	Stdctrls::TCheckBox* cbxSuccessAudit;
	Stdctrls::TCheckBox* cbxFailureAudit;
	Stdctrls::TLabel* lblUserName;
	Stdctrls::TEdit* edtUserName;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall btnOkClick(System::TObject* Sender);
	
public:
	Abstrsec::TAccessItem* Item;
public:
	/* TCustomForm.Create */ __fastcall virtual TFrmEditAccess(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	/* TCustomForm.CreateNew */ __fastcall TFrmEditAccess(Classes::TComponent* AOwner, int Dummy) : Forms::
		TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TFrmEditAccess(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TFrmEditAccess(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TFrmEditAccess* FrmEditAccess;

}	/* namespace Fracces1 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Fracces1;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// FrAcces1
