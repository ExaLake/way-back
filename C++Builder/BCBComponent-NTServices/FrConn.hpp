// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FrConn.pas' rev: 3.00

#ifndef FrConnHPP
#define FrConnHPP
#include <ComCtrls.hpp>
#include <StdCtrls.hpp>
#include <FrAbstr.hpp>
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

namespace Frconn
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFrmConnections;
class PASCALIMPLEMENTATION TFrmConnections : public Frabstr::TShareEditAbstract 
{
	typedef Frabstr::TShareEditAbstract inherited;
	
__published:
	void __fastcall btnDisconnectClick(System::TObject* Sender);
	
public:
	virtual void __fastcall FillLineValueInfo(int Index);
public:
	/* TCustomForm.Create */ __fastcall virtual TFrmConnections(Classes::TComponent* AOwner) : Frabstr::
		TShareEditAbstract(AOwner) { }
	/* TCustomForm.CreateNew */ __fastcall TFrmConnections(Classes::TComponent* AOwner, int Dummy) : Frabstr::
		TShareEditAbstract(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TFrmConnections(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TFrmConnections(HWND ParentWindow) : Frabstr::TShareEditAbstract(
		ParentWindow) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TFrmConnections* FrmConnections;

}	/* namespace Frconn */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Frconn;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// FrConn
