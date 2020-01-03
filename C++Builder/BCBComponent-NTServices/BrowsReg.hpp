// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'BrowsReg.pas' rev: 3.00

#ifndef BrowsRegHPP
#define BrowsRegHPP
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Registry.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Browsreg
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TBrowseRegistry;
class PASCALIMPLEMENTATION TBrowseRegistry : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	HKEY FCurrentKey;
	HKEY FRootKey;
	System::AnsiString FCurrentPath;
	bool FCloseRootKey;
	int FAccessMask;
	void __fastcall SetRootKey(HKEY Value);
	
protected:
	void __fastcall ChangeKey(HKEY Value, const System::AnsiString Path);
	HKEY __fastcall GetBaseKey(bool Relative);
	void __fastcall SetCurrentKey(HKEY Value);
	void * __fastcall GetData(const System::AnsiString Name, int &BufLen, int &RegData);
	
public:
	__fastcall TBrowseRegistry(void);
	__fastcall virtual ~TBrowseRegistry(void);
	void __fastcall CloseKey(void);
	void __fastcall GetKeyNames(Classes::TStrings* Strings);
	int __fastcall OpenKey(const System::AnsiString Key);
	bool __fastcall RegistryConnect(const System::AnsiString UNCName);
	__property HKEY CurrentKey = {read=FCurrentKey, nodefault};
	__property System::AnsiString CurrentPath = {read=FCurrentPath};
	__property HKEY RootKey = {read=FRootKey, write=SetRootKey, nodefault};
	__property int AccessMask = {read=FAccessMask, write=FAccessMask, nodefault};
	System::AnsiString __fastcall ReadString(const System::AnsiString Name);
};

//-- var, const, procedure ---------------------------------------------------
#define KEY_BROWSE_ACCESS (Byte)(8)
#define KEY_READ_CONTROL (int)(131072)
#define KEY_WRITE_CONTROL (int)(786432)

}	/* namespace Browsreg */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Browsreg;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// BrowsReg
