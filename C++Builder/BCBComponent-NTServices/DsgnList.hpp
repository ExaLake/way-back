// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DsgnList.pas' rev: 3.00

#ifndef DsgnListHPP
#define DsgnListHPP
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Dsgnlist
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDesignList;
class PASCALIMPLEMENTATION TDesignList : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TDuplicates FDuplicates;
	bool FFreeObjectsOnDestroy;
	
protected:
	Classes::TList* FList;
	int __fastcall GetCount(void);
	DYNAMIC void __fastcall GetChildren(Classes::TGetChildProc Proc, Classes::TComponent* Root);
	
public:
	__fastcall virtual TDesignList(Classes::TComponent* AOwner);
	__fastcall virtual ~TDesignList(void);
	virtual void __fastcall Delete(int AIndex);
	virtual void __fastcall Clear(void);
	HIDESBASE void __fastcall Insert(int Index, void * Item);
	__property int Count = {read=GetCount, nodefault};
	__property Classes::TList* List = {read=FList};
	__property bool FreeObjectsOnDestroy = {read=FFreeObjectsOnDestroy, write=FFreeObjectsOnDestroy, nodefault
		};
	__property Classes::TDuplicates Duplicates = {read=FDuplicates, write=FDuplicates, nodefault};
};

//-- var, const, procedure ---------------------------------------------------

}	/* namespace Dsgnlist */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Dsgnlist;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// DsgnList
