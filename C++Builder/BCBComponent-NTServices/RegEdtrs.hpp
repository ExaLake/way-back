// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'RegEdtrs.pas' rev: 3.00

#ifndef RegEdtrsHPP
#define RegEdtrsHPP
#include <TypInfo.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Windows.hpp>
#include <DsgnIntf.hpp>
#include <Registry.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Regedtrs
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TEventEntryProperty;
class PASCALIMPLEMENTATION TEventEntryProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TEventEntryProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TEventEntryProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TShareNameProperty;
class PASCALIMPLEMENTATION TShareNameProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TShareNameProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TShareNameProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TDialogProperty;
class PASCALIMPLEMENTATION TDialogProperty : public Dsgnintf::TClassProperty 
{
	typedef Dsgnintf::TClassProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TDialogProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TDialogProperty(void) : Dsgnintf::TClassProperty() { }
	
};

class DELPHICLASS TSessionProperty;
class PASCALIMPLEMENTATION TSessionProperty : public Regedtrs::TDialogProperty 
{
	typedef Regedtrs::TDialogProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TSessionProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TSessionProperty(void) : Regedtrs::TDialogProperty() { }
	
};

class DELPHICLASS TUsageProperty;
class PASCALIMPLEMENTATION TUsageProperty : public Regedtrs::TDialogProperty 
{
	typedef Regedtrs::TDialogProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TUsageProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TUsageProperty(void) : Regedtrs::TDialogProperty() { }
	
};

class DELPHICLASS TResourceProperty;
class PASCALIMPLEMENTATION TResourceProperty : public Regedtrs::TDialogProperty 
{
	typedef Regedtrs::TDialogProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TResourceProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TResourceProperty(void) : Regedtrs::TDialogProperty() { }
	
};

class DELPHICLASS TConnectionProperty;
class PASCALIMPLEMENTATION TConnectionProperty : public Regedtrs::TDialogProperty 
{
	typedef Regedtrs::TDialogProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TConnectionProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TConnectionProperty(void) : Regedtrs::TDialogProperty() { }
	
};

class DELPHICLASS TLoadOrderProperty;
class PASCALIMPLEMENTATION TLoadOrderProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TLoadOrderProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TLoadOrderProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TServiceNameProperty;
class PASCALIMPLEMENTATION TServiceNameProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TServiceNameProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TServiceNameProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TUserNameProperty;
class PASCALIMPLEMENTATION TUserNameProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TUserNameProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TUserNameProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TLocalGroupNameProperty;
class PASCALIMPLEMENTATION TLocalGroupNameProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TLocalGroupNameProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TLocalGroupNameProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TGlobalGroupNameProperty;
class PASCALIMPLEMENTATION TGlobalGroupNameProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TGlobalGroupNameProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TGlobalGroupNameProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TMachineNameProperty;
class PASCALIMPLEMENTATION TMachineNameProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TMachineNameProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TMachineNameProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TRootKeyProperty;
class PASCALIMPLEMENTATION TRootKeyProperty : public Dsgnintf::TIntegerProperty 
{
	typedef Dsgnintf::TIntegerProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
	virtual void __fastcall SetValue(const System::AnsiString Value);
	virtual System::AnsiString __fastcall GetValue();
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TRootKeyProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TRootKeyProperty(void) : Dsgnintf::TIntegerProperty() { }
	
};

class DELPHICLASS TPasswordProperty;
class PASCALIMPLEMENTATION TPasswordProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual System::AnsiString __fastcall GetValue();
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TPasswordProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TPasswordProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TDateTimeProperty;
class PASCALIMPLEMENTATION TDateTimeProperty : public Dsgnintf::TFloatProperty 
{
	typedef Dsgnintf::TFloatProperty inherited;
	
public:
	virtual System::AnsiString __fastcall GetValue();
	virtual void __fastcall SetValue(const System::AnsiString Value);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TDateTimeProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TDateTimeProperty(void) : Dsgnintf::TFloatProperty() { }
	
};

class DELPHICLASS TDateTimeNeverProperty;
class PASCALIMPLEMENTATION TDateTimeNeverProperty : public Dsgnintf::TFloatProperty 
{
	typedef Dsgnintf::TFloatProperty inherited;
	
public:
	virtual System::AnsiString __fastcall GetValue();
	virtual void __fastcall SetValue(const System::AnsiString Value);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TDateTimeNeverProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TDateTimeNeverProperty(void) : Dsgnintf::TFloatProperty() { }
	
};

class DELPHICLASS TRegPathProperty;
class PASCALIMPLEMENTATION TRegPathProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TRegPathProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TRegPathProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TFileNameProperty;
class PASCALIMPLEMENTATION TFileNameProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
public:
	/* TPropertyEditor.Destroy */ __fastcall virtual ~TFileNameProperty(void) { }
	
public:
	/* TObject.Create */ __fastcall TFileNameProperty(void) : Dsgnintf::TStringProperty() { }
	
};

class DELPHICLASS TDwordAsSetProperty;
class PASCALIMPLEMENTATION TDwordAsSetProperty : public Dsgnintf::TIntegerProperty 
{
	typedef Dsgnintf::TIntegerProperty inherited;
	
private:
	Classes::TList* SubProps;
	Dsgnintf::TComponentList* ChildList;
	void __fastcall GetSubProps(Dsgnintf::TPropertyEditor* PropEdit);
	void __fastcall SetChildValues(void);
	
public:
	__fastcall virtual ~TDwordAsSetProperty(void);
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual System::AnsiString __fastcall GetValue();
	virtual void __fastcall SetValue(const System::AnsiString Value);
	virtual void __fastcall GetProperties(Dsgnintf::TGetPropEditProc Proc);
	void __fastcall SetDWORD(int AValue);
public:
	/* TObject.Create */ __fastcall TDwordAsSetProperty(void) : Dsgnintf::TIntegerProperty() { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Regedtrs */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Regedtrs;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// RegEdtrs
