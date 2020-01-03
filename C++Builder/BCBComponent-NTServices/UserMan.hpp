// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'UserMan.pas' rev: 3.00

#ifndef UserManHPP
#define UserManHPP
#include <NTCommon.hpp>
#include <DsgnIntf.hpp>
#include <NetApi32.hpp>
#include <lmErr.hpp>
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

namespace Userman
{
//-- type declarations -------------------------------------------------------
typedef System::AnsiString TUserName;

typedef System::AnsiString TMachineName;

typedef System::AnsiString TPassword;

enum TUserFlag { F_SCRIPT, F_ACCOUNTDISABLE, F_HOMEDIR_REQUIRED, F_LOCKOUT, F_PASSWD_NOTREQD, F_PASSWD_CANT_CHANGE, 
	F_DONT_EXPIRE_PASSWD };

typedef Set<TUserFlag, F_SCRIPT, F_DONT_EXPIRE_PASSWD>  TUserFlags;

enum TUserPriv { USR_PRIV_UNKNOWN, USR_PRIV_GUEST, USR_PRIV_USER, USR_PRIV_ADMIN };

enum TOperatorFlag { OP_PRINT, OP_COMM, OP_SERVER, OP_ACCOUNTS };

typedef Set<TOperatorFlag, OP_PRINT, OP_ACCOUNTS>  TOperatorFlags;

enum TFilterAccount { FLT_TEMP_DUPLICATE_ACCOUNT, FLT_NORMAL_ACCOUNT, FLT_PROXY_ACCOUNT, FLT_INTERDOMAIN_TRUST_ACCOUNT, 
	FLT_WORKSTATION_TRUST_ACCOUNT, FLT_SERVER_TRUST_ACCOUNT };

typedef Set<TFilterAccount, FLT_TEMP_DUPLICATE_ACCOUNT, FLT_SERVER_TRUST_ACCOUNT>  TFilterAccountSet
	;

class DELPHICLASS TUserInfo;
class DELPHICLASS TNTUserMan;
class PASCALIMPLEMENTATION TNTUserMan : public Ntcommon::TNTPersistent 
{
	typedef Ntcommon::TNTPersistent inherited;
	
private:
	System::AnsiString FUserName;
	Classes::TStrings* FGlobalGroups;
	Classes::TStrings* FLocalGroups;
	Classes::TStrings* FMemberOfGlob;
	Classes::TStrings* FMemberOfLocal;
	Classes::TStrings* FLocalGroupMembers;
	Classes::TStrings* FGlobalGroupMembers;
	Classes::TStrings* FUsers;
	TUserInfo* FUserInfo;
	System::AnsiString FLocalGroupName;
	System::AnsiString FGlobalGroupName;
	
protected:
	void __fastcall SetUserName(System::AnsiString AValue);
	void __fastcall SetLocalGroupName(System::AnsiString AValue);
	void __fastcall SetGlobalGroupName(System::AnsiString AValue);
	virtual void __fastcall SetMachineName(System::AnsiString AValue);
	Classes::TStrings* __fastcall _GetGlobalGroups(void);
	void __fastcall SetGlobalGroups(Classes::TStrings* AValue);
	void __fastcall SetLocalGroups(Classes::TStrings* AValue);
	Classes::TStrings* __fastcall _GetLocalGroups(void);
	Classes::TStrings* __fastcall GetMemberOfGlob(void);
	void __fastcall SetMemberOfGlob(Classes::TStrings* AValue);
	Classes::TStrings* __fastcall GetMemberOfLocal(void);
	void __fastcall SetMemberOfLocal(Classes::TStrings* AValue);
	Classes::TStrings* __fastcall _GetUsers(void);
	void __fastcall SetUsers(Classes::TStrings* AValue);
	bool __fastcall UserNameExists(void);
	void __fastcall SetStringsField(Classes::TStrings* OldValue, Classes::TStrings* NewValue, Classes::TStrings* 
		FUserManList);
	Classes::TStrings* __fastcall _GetLocalGroupMembers(void);
	void __fastcall _SetLocalGroupMembers(Classes::TStrings* List);
	Classes::TStrings* __fastcall _GetGlobalGroupMembers(void);
	void __fastcall _SetGlobalGroupMembers(Classes::TStrings* List);
	System::AnsiString __fastcall GetGlobalGroupComment();
	void __fastcall SetGlobalGroupComment(System::AnsiString AValue);
	System::AnsiString __fastcall GetLocalGroupComment();
	void __fastcall SetLocalGroupComment(System::AnsiString AValue);
	int __fastcall GetGlobalGroupId(void);
	void __fastcall SetGlobalGroupId(int AValue);
	Classes::TStringList* __fastcall GetLocalGroupMembers(System::AnsiString AServerName, System::AnsiString 
		AGroupName);
	void __fastcall SetLocalGroupMembers(System::AnsiString AServerName, System::AnsiString AGroupName, 
		Classes::TStrings* List);
	Classes::TStringList* __fastcall GetGlobalGroupMembers(System::AnsiString AServerName, System::AnsiString 
		AGroupName);
	void __fastcall SetGlobalGroupMembers(System::AnsiString AServerName, System::AnsiString AGroupName
		, Classes::TStrings* List);
	
public:
	virtual void __fastcall Loaded(void);
	Classes::TStringList* __fastcall GetLocalGroups(System::AnsiString AServerName);
	Classes::TStringList* __fastcall GetGlobalGroups(System::AnsiString AServerName);
	Classes::TStringList* __fastcall GetUsers(System::AnsiString AComputerName, TFilterAccountSet Filter
		);
	void __fastcall ChangeUserName(System::AnsiString NewName);
	void __fastcall DeleteUser(System::AnsiString AUserName);
	void __fastcall AddUser(System::AnsiString AUserName, System::AnsiString APassword);
	
__published:
	__property MachineName ;
	__fastcall virtual TNTUserMan(Classes::TComponent* AOwner);
	__fastcall virtual ~TNTUserMan(void);
	__property System::AnsiString UserName = {read=FUserName, write=SetUserName};
	__property System::AnsiString LocalGroupName = {read=FLocalGroupName, write=SetLocalGroupName};
	__property System::AnsiString GlobalGroupName = {read=FGlobalGroupName, write=SetGlobalGroupName};
	__property Classes::TStrings* GlobalGroups = {read=_GetGlobalGroups, write=SetGlobalGroups, stored=false
		};
	__property Classes::TStrings* LocalGroups = {read=_GetLocalGroups, write=SetLocalGroups, stored=false
		};
	__property Classes::TStrings* MemberOfGlob = {read=GetMemberOfGlob, write=SetMemberOfGlob, stored=false
		};
	__property Classes::TStrings* MemberOfLocal = {read=GetMemberOfLocal, write=SetMemberOfLocal, stored=false
		};
	__property Classes::TStrings* Users = {read=_GetUsers, write=SetUsers, stored=false};
	__property TUserInfo* UserInfo = {read=FUserInfo, write=FUserInfo, stored=false};
	__property Classes::TStrings* LocalGroupMembers = {read=_GetLocalGroupMembers, write=_SetLocalGroupMembers
		, stored=false};
	__property Classes::TStrings* GlobalGroupMembers = {read=_GetGlobalGroupMembers, write=_SetGlobalGroupMembers
		, stored=false};
	__property System::AnsiString GlobalGroupComment = {read=GetGlobalGroupComment, write=SetGlobalGroupComment
		, stored=false};
	__property System::AnsiString LocalGroupComment = {read=GetLocalGroupComment, write=SetLocalGroupComment
		, stored=false};
	__property int GlobalGroupId = {read=GetGlobalGroupId, write=SetGlobalGroupId, stored=false, nodefault
		};
};

class PASCALIMPLEMENTATION TUserInfo : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TNTUserMan* Owner;
	System::AnsiString FComment;
	TUserFlags FOptions;
	TOperatorFlags FOperatorRights;
	System::AnsiString FFullName;
	TUserPriv FPrivilege;
	System::TDateTime FPasswordDate;
	System::AnsiString FHomeDir;
	System::AnsiString FHomeDirDrive;
	System::AnsiString FScriptPath;
	System::TDateTime FLastLogon;
	System::TDateTime FLastLogOff;
	System::TDateTime FAccountExpires;
	int FMaxStorage;
	System::AnsiString FLogonServer;
	int FLogonCount;
	void *FUserSID;
	System::AnsiString FWorkstations;
	int FBadPasswordCount;
	int FCountryCode;
	int FCodePage;
	System::AnsiString FPassword;
	System::AnsiString FDomain;
	System::AnsiString FProfile;
	bool FPasswordExpired;
	
protected:
	void __fastcall ClearUserInformation(void);
	void __fastcall GetUserInformation(void);
	bool __fastcall SetUserInformation(void * Buffer, int Level);
	void __fastcall SetOptions(TUserFlags AValue);
	void __fastcall SetFullName(System::AnsiString AValue);
	void __fastcall SetComment(System::AnsiString AValue);
	void __fastcall SetPrivilege(TUserPriv AValue);
	void __fastcall SetPasswordDate(System::TDateTime AValue);
	void __fastcall SetHomeDir(System::AnsiString AValue);
	void __fastcall SetScriptPath(System::AnsiString AValue);
	void __fastcall SetLastLogon(System::TDateTime AValue);
	void __fastcall SetLastLogOff(System::TDateTime AValue);
	void __fastcall SetAccountExpires(System::TDateTime AValue);
	void __fastcall SetMaxStorage(int AValue);
	void __fastcall SetLogonServer(System::AnsiString AValue);
	void __fastcall SetLogonCount(int AValue);
	void __fastcall SetWorkstations(System::AnsiString AValue);
	void __fastcall SetBadPasswordCount(int AValue);
	void __fastcall SetCountryCode(int AValue);
	void __fastcall SetCodePage(int AValue);
	void __fastcall SetOperatorRights(TOperatorFlags AValue);
	void __fastcall SetPassword(System::AnsiString AValue);
	void __fastcall SetDomain(System::AnsiString AValue);
	void __fastcall SetHomeDirDrive(System::AnsiString AValue);
	void __fastcall SetProfile(System::AnsiString AVAlue);
	void __fastcall SetPasswordExpired(bool AValue);
	
public:
	__fastcall virtual TUserInfo(TNTUserMan* AOwner);
	__fastcall virtual ~TUserInfo(void);
	__property void * UserSID = {read=FUserSID};
	
__published:
	__property System::AnsiString Comment = {read=FComment, write=SetComment, stored=false};
	__property TUserFlags Options = {read=FOptions, write=SetOptions, stored=false, nodefault};
	__property System::AnsiString FullName = {read=FFullName, write=SetFullName, stored=false};
	__property TUserPriv Privilege = {read=FPrivilege, write=SetPrivilege, stored=false, nodefault};
	__property System::TDateTime PasswordDate = {read=FPasswordDate, write=SetPasswordDate, stored=false
		};
	__property System::AnsiString HomeDir = {read=FHomeDir, write=SetHomeDir, stored=false};
	__property System::AnsiString ScriptPath = {read=FScriptPath, write=SetScriptPath, stored=false};
	__property System::TDateTime LastLogon = {read=FLastLogon, write=SetLastLogon, stored=false};
	__property System::TDateTime LastLogOff = {read=FLastLogOff, write=SetLastLogOff, stored=false};
	__property System::TDateTime AccountExpires = {read=FAccountExpires, write=SetAccountExpires, stored=false
		};
	__property System::AnsiString LogonServer = {read=FLogonServer, write=SetLogonServer, stored=false}
		;
	__property int LogonCount = {read=FLogonCount, write=SetLogonCount, stored=false, nodefault};
	__property int BadPasswordCount = {read=FBadPasswordCount, write=SetBadPasswordCount, stored=false, 
		nodefault};
	__property int CountryCode = {read=FCountryCode, write=SetCountryCode, stored=false, nodefault};
	__property int CodePage = {read=FCodePage, write=SetCodePage, stored=false, nodefault};
	__property System::AnsiString Workstations = {read=FWorkstations, write=SetWorkstations, stored=false
		};
	__property int MaxStorage = {read=FMaxStorage, write=SetMaxStorage, stored=false, nodefault};
	__property TOperatorFlags OperatorRights = {read=FOperatorRights, write=SetOperatorRights, stored=false
		, nodefault};
	__property System::AnsiString Password = {read=FPassword, write=SetPassword, stored=false};
	__property System::AnsiString Domain = {read=FDomain, write=SetDomain, stored=false};
	__property System::AnsiString HomeDirDrive = {read=FHomeDirDrive, write=SetHomeDirDrive, stored=false
		};
	__property System::AnsiString Profile = {read=FProfile, write=SetProfile, stored=false};
	__property bool PasswordExpired = {read=FPasswordExpired, write=SetPasswordExpired, stored=false, nodefault
		};
};

class DELPHICLASS TUserManList;
class PASCALIMPLEMENTATION TUserManList : public Classes::TStringList 
{
	typedef Classes::TStringList inherited;
	
private:
	TNTUserMan* Owner;
	bool DoNotPerformAPI;
	
public:
	__fastcall virtual TUserManList(TNTUserMan* AOwner);
	virtual int __fastcall Add(const System::AnsiString S);
	virtual void __fastcall Delete(int Index);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
public:
	/* TStringList.Destroy */ __fastcall virtual ~TUserManList(void) { }
	
};

class DELPHICLASS TMemberOfLocal;
class PASCALIMPLEMENTATION TMemberOfLocal : public Userman::TUserManList 
{
	typedef Userman::TUserManList inherited;
	
public:
	virtual int __fastcall Add(const System::AnsiString S);
	virtual void __fastcall Delete(int Index);
public:
	/* TUserManList.Create */ __fastcall virtual TMemberOfLocal(TNTUserMan* AOwner) : Userman::TUserManList(
		AOwner) { }
	
public:
	/* TStringList.Destroy */ __fastcall virtual ~TMemberOfLocal(void) { }
	
};

class DELPHICLASS TMemberOfGlob;
class PASCALIMPLEMENTATION TMemberOfGlob : public Userman::TUserManList 
{
	typedef Userman::TUserManList inherited;
	
public:
	virtual int __fastcall Add(const System::AnsiString S);
	virtual void __fastcall Delete(int Index);
public:
	/* TUserManList.Create */ __fastcall virtual TMemberOfGlob(TNTUserMan* AOwner) : Userman::TUserManList(
		AOwner) { }
	
public:
	/* TStringList.Destroy */ __fastcall virtual ~TMemberOfGlob(void) { }
	
};

class DELPHICLASS TLocalGroups;
class PASCALIMPLEMENTATION TLocalGroups : public Userman::TUserManList 
{
	typedef Userman::TUserManList inherited;
	
public:
	virtual int __fastcall Add(const System::AnsiString S);
	virtual void __fastcall Delete(int Index);
public:
	/* TUserManList.Create */ __fastcall virtual TLocalGroups(TNTUserMan* AOwner) : Userman::TUserManList(
		AOwner) { }
	
public:
	/* TStringList.Destroy */ __fastcall virtual ~TLocalGroups(void) { }
	
};

class DELPHICLASS TLocalGroupMembers;
class PASCALIMPLEMENTATION TLocalGroupMembers : public Userman::TUserManList 
{
	typedef Userman::TUserManList inherited;
	
public:
	virtual int __fastcall Add(const System::AnsiString S);
	virtual void __fastcall Delete(int Index);
public:
	/* TUserManList.Create */ __fastcall virtual TLocalGroupMembers(TNTUserMan* AOwner) : Userman::TUserManList(
		AOwner) { }
	
public:
	/* TStringList.Destroy */ __fastcall virtual ~TLocalGroupMembers(void) { }
	
};

class DELPHICLASS TGlobalGroupMembers;
class PASCALIMPLEMENTATION TGlobalGroupMembers : public Userman::TUserManList 
{
	typedef Userman::TUserManList inherited;
	
public:
	virtual int __fastcall Add(const System::AnsiString S);
	virtual void __fastcall Delete(int Index);
public:
	/* TUserManList.Create */ __fastcall virtual TGlobalGroupMembers(TNTUserMan* AOwner) : Userman::TUserManList(
		AOwner) { }
	
public:
	/* TStringList.Destroy */ __fastcall virtual ~TGlobalGroupMembers(void) { }
	
};

class DELPHICLASS TGlobalGroups;
class PASCALIMPLEMENTATION TGlobalGroups : public Userman::TUserManList 
{
	typedef Userman::TUserManList inherited;
	
public:
	virtual int __fastcall Add(const System::AnsiString S);
	virtual void __fastcall Delete(int Index);
public:
	/* TUserManList.Create */ __fastcall virtual TGlobalGroups(TNTUserMan* AOwner) : Userman::TUserManList(
		AOwner) { }
	
public:
	/* TStringList.Destroy */ __fastcall virtual ~TGlobalGroups(void) { }
	
};

class DELPHICLASS TUsers;
class PASCALIMPLEMENTATION TUsers : public Userman::TUserManList 
{
	typedef Userman::TUserManList inherited;
	
public:
	virtual int __fastcall Add(const System::AnsiString S);
	virtual void __fastcall Delete(int Index);
public:
	/* TUserManList.Create */ __fastcall virtual TUsers(TNTUserMan* AOwner) : Userman::TUserManList(AOwner
		) { }
	
public:
	/* TStringList.Destroy */ __fastcall virtual ~TUsers(void) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TOperatorFlags __fastcall DWORDToOperatorFlags(int AValue);
extern PACKAGE int __fastcall OperatorFlagsToDWORD(TOperatorFlags AValue);
extern PACKAGE int __fastcall FilterToDWORD(TFilterAccountSet AVAlue);
extern PACKAGE TUserFlags __fastcall DWORDToTUserFlags(int AValue);
extern PACKAGE int __fastcall TUserFlagsToDWORD(TUserFlags AValue);
extern PACKAGE TUserPriv __fastcall DWORDToPrivilage(int AValue);
extern PACKAGE int __fastcall UserPrivToDWORD(TUserPriv AValue);
extern PACKAGE System::AnsiString __fastcall GetPrivilegeName(int ACod);

}	/* namespace Userman */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Userman;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// UserMan
