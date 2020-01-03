// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FrAbstr.pas' rev: 3.00

#ifndef FrAbstrHPP
#define FrAbstrHPP
#include <ObjList.hpp>
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

namespace Frabstr
{
//-- type declarations -------------------------------------------------------
struct TLineRec;
typedef TLineRec *PLineRec;

struct TLineRec
{
	char *Header;
	int Width;
	char *Value;
} ;

typedef TLineRec TLineInfo[178956970];

typedef TLineInfo *PLineInfo;

class DELPHICLASS TShareEditAbstract;
class PASCALIMPLEMENTATION TShareEditAbstract : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Comctrls::THeaderControl* hdrSessions;
	Stdctrls::TListBox* lbxSessions;
	Stdctrls::TScrollBar* scrHoriz;
	Stdctrls::TButton* btnDisconnect;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall lbxSessionsDrawItem(Controls::TWinControl* Control, int Index, const Windows::TRect 
		&Rect, Stdctrls::TOwnerDrawState State);
	void __fastcall hdrSessionsSectionResize(Comctrls::THeaderControl* HeaderControl, Comctrls::THeaderSection* 
		Section);
	void __fastcall scrHorizChange(System::TObject* Sender);
	void __fastcall scrHorizScroll(System::TObject* Sender, Stdctrls::TScrollCode ScrollCode, int &ScrollPos
		);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall lbxSessionsClick(System::TObject* Sender);
	
public:
	TLineInfo *LineInfo;
	int Sections;
	Objlist::TObjectList* List;
	void __fastcall FillLineHeaderInfo(void);
	virtual void __fastcall FillLineValueInfo(int Index) = 0;
public:
	/* TCustomForm.Create */ __fastcall virtual TShareEditAbstract(Classes::TComponent* AOwner) : Forms::
		TForm(AOwner) { }
	/* TCustomForm.CreateNew */ __fastcall TShareEditAbstract(Classes::TComponent* AOwner, int Dummy) : 
		Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TShareEditAbstract(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TShareEditAbstract(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TShareEditAbstract* ShareEditAbstract;

}	/* namespace Frabstr */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Frabstr;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// FrAbstr
