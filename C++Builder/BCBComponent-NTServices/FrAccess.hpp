// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FrAccess.pas' rev: 3.00

#ifndef FrAccessHPP
#define FrAccessHPP
#include <AbstrSec.hpp>
#include <NTCommon.hpp>
#include <Security.hpp>
#include <DsgnWnds.hpp>
#include <DsgnIntf.hpp>
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

namespace Fraccess
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TAccessForm;
class PASCALIMPLEMENTATION TAccessForm : public Dsgnwnds::TDesignWindow 
{
	typedef Dsgnwnds::TDesignWindow inherited;
	
__published:
	Stdctrls::TListBox* lbxAccessItems;
	Stdctrls::TButton* btnAdd;
	Stdctrls::TButton* btnDelete;
	Stdctrls::TButton* btnEdit;
	void __fastcall lbxAccessItemsClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall btnAddClick(System::TObject* Sender);
	void __fastcall btnDeleteClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall btnEditClick(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, Forms::TCloseAction &Action);
	
public:
	Abstrsec::TNTAbstractSecurity* OwnerComponent;
	Abstrsec::TAccessList* AccessList;
	int AccessType;
	DYNAMIC void __fastcall Activated(void);
	virtual void __fastcall FormClosed(Forms::TCustomForm* Form);
	virtual void __fastcall FormModified(void);
public:
	/* TDesignWindow.Create */ __fastcall virtual TAccessForm(Classes::TComponent* AOwner) : Dsgnwnds::
		TDesignWindow(AOwner) { }
	/* TDesignWindow.Destroy */ __fastcall virtual ~TAccessForm(void) { }
	
public:
	/* TCustomForm.CreateNew */ __fastcall TAccessForm(Classes::TComponent* AOwner, int Dummy) : Dsgnwnds::
		TDesignWindow(AOwner, Dummy) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TAccessForm(HWND ParentWindow) : Dsgnwnds::TDesignWindow(
		ParentWindow) { }
	
};

class DELPHICLASS TAccessAllowedProperty;
class PASCALIMPLEMENTATION TAccessAllowedProperty : public Dsgnintf::TClassProperty 
{
	typedef Dsgnintf::TClassProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall Edit(void);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TAccessAllowedProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TAccessAllowedProperty(void) : Dsgnintf::TClassProperty() { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TAccessForm* AccessForm;

}	/* namespace Fraccess */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Fraccess;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// FrAccess
