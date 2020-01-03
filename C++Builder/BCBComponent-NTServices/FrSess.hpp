// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FrSess.pas' rev: 3.00

#ifndef FrSessHPP
#define FrSessHPP
#include <FrAbstr.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
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

namespace Frsess
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFrmSessions;
class PASCALIMPLEMENTATION TFrmSessions : public Frabstr::TShareEditAbstract 
{
	typedef Frabstr::TShareEditAbstract inherited;
	
__published:
	void __fastcall btnDisconnectClick(System::TObject* Sender);
	
public:
	virtual void __fastcall FillLineValueInfo(int Index);
public:
	/* TCustomForm.Create */ __fastcall virtual TFrmSessions(Classes::TComponent* AOwner) : Frabstr::TShareEditAbstract(
		AOwner) { }
	/* TCustomForm.CreateNew */ __fastcall TFrmSessions(Classes::TComponent* AOwner, int Dummy) : Frabstr::
		TShareEditAbstract(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TFrmSessions(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TFrmSessions(HWND ParentWindow) : Frabstr::TShareEditAbstract(
		ParentWindow) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TFrmSessions* FrmSessions;

}	/* namespace Frsess */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Frsess;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// FrSess
