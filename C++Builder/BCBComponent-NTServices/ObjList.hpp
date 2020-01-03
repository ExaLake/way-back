// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ObjList.pas' rev: 3.00

#ifndef ObjListHPP
#define ObjListHPP
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Objlist
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TObjectList;
class PASCALIMPLEMENTATION TObjectList : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TDuplicates FDuplicates;
	bool FFreeObjectsOnDestroy;
	bool __fastcall IsDuplicatesAllowed(void);
	
protected:
	Classes::TList* FList;
	System::TObject* FParent;
	int __fastcall GetCount(void);
	
public:
	__fastcall virtual TObjectList(System::TObject* AOwner);
	__fastcall virtual ~TObjectList(void);
	virtual void __fastcall Delete(int AIndex);
	virtual void __fastcall Clear(void);
	void __fastcall Sort(Classes::TListSortCompare AFunc);
	void * __fastcall FindObject(void * P, Classes::TListSortCompare AFunc);
	int __fastcall SortedInsert(void * P, Classes::TListSortCompare AFunc);
	int __fastcall IndexOf(void * P, Classes::TListSortCompare AFunc);
	TObjectList* __fastcall GetListByExample(void * P, Classes::TListSortCompare AFunc);
	bool __fastcall Find(void * P, Classes::TListSortCompare AFunc, int &Index);
	void __fastcall Insert(int Index, void * Item);
	__property int Count = {read=GetCount, nodefault};
	__property System::TObject* Parent = {read=FParent};
	__property Classes::TList* List = {read=FList};
	__property bool FreeObjectsOnDestroy = {read=FFreeObjectsOnDestroy, write=FFreeObjectsOnDestroy, nodefault
		};
	__property Classes::TDuplicates Duplicates = {read=FDuplicates, write=FDuplicates, nodefault};
};

class DELPHICLASS TSortHolder;
class PASCALIMPLEMENTATION TSortHolder : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	System::AnsiString SortName;
	Classes::TListSortCompare SortFunction;
	TDuplicates FDuplicates;
public:
	/* TObject.Create */ __fastcall TSortHolder(void) : System::TObject() { }
	/* TObject.Destroy */ __fastcall virtual ~TSortHolder(void) { }
	
};

class DELPHICLASS TSortHolderList;
class PASCALIMPLEMENTATION TSortHolderList : public Objlist::TObjectList 
{
	typedef Objlist::TObjectList inherited;
	
__published:
	TSortHolder* __fastcall GetItem(int AIndex);
	
public:
	__property TSortHolder* Items[int AIndex] = {read=GetItem/*, default*/};
	int __fastcall GetIndexByName(System::AnsiString AName);
public:
	/* TObjectList.Create */ __fastcall virtual TSortHolderList(System::TObject* AOwner) : Objlist::TObjectList(
		AOwner) { }
	/* TObjectList.Destroy */ __fastcall virtual ~TSortHolderList(void) { }
	
};

class DELPHICLASS TListOfList;
class PASCALIMPLEMENTATION TListOfList : public Objlist::TObjectList 
{
	typedef Objlist::TObjectList inherited;
	
__published:
	TObjectList* __fastcall GetItem(int AIndex);
	
public:
	__property TObjectList* Items[int AIndex] = {read=GetItem/*, default*/};
public:
	/* TObjectList.Create */ __fastcall virtual TListOfList(System::TObject* AOwner) : Objlist::TObjectList(
		AOwner) { }
	/* TObjectList.Destroy */ __fastcall virtual ~TListOfList(void) { }
	
};

class DELPHICLASS TMultySortedList;
class PASCALIMPLEMENTATION TMultySortedList : public Objlist::TObjectList 
{
	typedef Objlist::TObjectList inherited;
	
private:
	TSortHolderList* FSortings;
	TListOfList* FSortedLists;
	
protected:
	int __fastcall GetCountOfSortings(void);
	void * __fastcall GetByIndex(int AIndex, System::AnsiString SortName);
	
public:
	__fastcall virtual TMultySortedList(System::TObject* AOwner);
	__fastcall virtual ~TMultySortedList(void);
	void __fastcall AddSorting(System::AnsiString AName, Classes::TListSortCompare AFunc, Classes::TDuplicates 
		ADuplicates);
	virtual void __fastcall Add(System::TObject* AObject);
	HIDESBASE virtual void __fastcall Delete(System::TObject* AObject);
	HIDESBASE void * __fastcall FindObject(void * P, System::AnsiString SortName);
	void * __fastcall GetFirst(System::AnsiString SortName);
	HIDESBASE TObjectList* __fastcall GetListByExample(void * P, System::AnsiString SortName);
	virtual void __fastcall Clear(void);
	__property int CountOfSortings = {read=GetCountOfSortings, nodefault};
	__property TSortHolderList* Sortings = {read=FSortings};
	__property TListOfList* SortedLists = {read=FSortedLists};
};

//-- var, const, procedure ---------------------------------------------------

}	/* namespace Objlist */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Objlist;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// ObjList
