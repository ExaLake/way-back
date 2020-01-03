// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FrRBrows.pas' rev: 3.00

#ifndef FrRBrowsHPP
#define FrRBrowsHPP
#include <BrowsReg.hpp>
#include <RegSecur.hpp>
#include <ComCtrls.hpp>
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

namespace Frrbrows
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFrmRegBrowser;
class PASCALIMPLEMENTATION TFrmRegBrowser : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Comctrls::TTreeView* tvRegistry;
	Stdctrls::TButton* btnOk;
	Stdctrls::TButton* btnCancel;
	Controls::TImageList* imlFolders;
	Stdctrls::TEdit* edtPath;
	Stdctrls::TLabel* Label1;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall tvRegistryExpanded(System::TObject* Sender, Comctrls::TTreeNode* Node);
	void __fastcall tvRegistryGetImageIndex(System::TObject* Sender, Comctrls::TTreeNode* Node);
	void __fastcall tvRegistryChange(System::TObject* Sender, Comctrls::TTreeNode* Node);
	void __fastcall btnOkClick(System::TObject* Sender);
	
private:
	Browsreg::TBrowseRegistry* Reg;
	void __fastcall InitTree(void);
	void __fastcall AddChildren(Comctrls::TTreeNode* ANode, bool IsRecursive);
	Comctrls::TTreeNode* __fastcall FindChildByName(Comctrls::TTreeNode* ANode, System::AnsiString AName
		);
	System::AnsiString __fastcall GetNodePath(Comctrls::TTreeNode* ANode);
	
public:
	Regsecur::TNTRegSecurity* Component;
public:
	/* TCustomForm.Create */ __fastcall virtual TFrmRegBrowser(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	/* TCustomForm.CreateNew */ __fastcall TFrmRegBrowser(Classes::TComponent* AOwner, int Dummy) : Forms::
		TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TFrmRegBrowser(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TFrmRegBrowser(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TFrmRegBrowser* FrmRegBrowser;

}	/* namespace Frrbrows */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Frrbrows;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// FrRBrows
