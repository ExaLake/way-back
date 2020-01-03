// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SidStore.pas' rev: 3.00

#ifndef SidStoreHPP
#define SidStoreHPP
#include <SysUtils.hpp>
#include <ObjList.hpp>
#include <Classes.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Sidstore
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TSidHolder;
class PASCALIMPLEMENTATION TSidHolder : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	void *FSID;
	int FLen;
	System::AnsiString FUserName;
	System::AnsiString FDomain;
	__fastcall virtual ~TSidHolder(void);
	void __fastcall SetData(void * ASID, int ALen, System::AnsiString AUserName, System::AnsiString ADomain
		);
	__property System::AnsiString UserName = {read=FUserName};
	__property System::AnsiString Domain = {read=FDomain};
public:
	/* TObject.Create */ __fastcall TSidHolder(void) : System::TObject() { }
	
};

class DELPHICLASS TSidStore;
class PASCALIMPLEMENTATION TSidStore : public Objlist::TObjectList 
{
	typedef Objlist::TObjectList inherited;
	
__published:
	TSidHolder* FCompareSID;
	
public:
	__fastcall virtual TSidStore(System::TObject* AOwner);
	__fastcall virtual ~TSidStore(void);
	void __fastcall Add(void * ASid, int ALen, System::AnsiString AUserName, System::AnsiString ADomain
		);
	int __fastcall FindAccount(void * ASid, int ALen);
	void __fastcall GetAccount(int AIndex, System::AnsiString &AUserName, System::AnsiString &ADomain);
		
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TSidStore* SidStorage;

}	/* namespace Sidstore */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Sidstore;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// SidStore
