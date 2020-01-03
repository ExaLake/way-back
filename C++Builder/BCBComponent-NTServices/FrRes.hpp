// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FrRes.pas' rev: 3.00

#ifndef FrResHPP
#define FrResHPP
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

namespace Frres
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFrmResources;
class PASCALIMPLEMENTATION TFrmResources : public Frabstr::TShareEditAbstract 
{
	typedef Frabstr::TShareEditAbstract inherited;
	
__published:
	void __fastcall btnDisconnectClick(System::TObject* Sender);
	
public:
	virtual void __fastcall FillLineValueInfo(int Index);
public:
	/* TCustomForm.Create */ __fastcall virtual TFrmResources(Classes::TComponent* AOwner) : Frabstr::TShareEditAbstract(
		AOwner) { }
	/* TCustomForm.CreateNew */ __fastcall TFrmResources(Classes::TComponent* AOwner, int Dummy) : Frabstr::
		TShareEditAbstract(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TFrmResources(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TFrmResources(HWND ParentWindow) : Frabstr::TShareEditAbstract(
		ParentWindow) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TFrmResources* FrmResources;

}	/* namespace Frres */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Frres;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// FrRes
