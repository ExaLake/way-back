// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Security.pas' rev: 3.00

#ifndef SecurityHPP
#define SecurityHPP
#include <NT_vs_95.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Security
{
//-- type declarations -------------------------------------------------------
typedef int *P_ACCESS_MASK;

typedef int T_ACCESS_MASK;

struct T_ACE_HEADER;
typedef T_ACE_HEADER *P_ACE_HEADER;

struct T_ACE_HEADER
{
	Byte AceType;
	Byte AceFlags;
	Word AceSize;
} ;

typedef Byte TWellKnownSid[12];

struct T_ACCESS_ALLOWED_ACE
{
	T_ACE_HEADER Header;
	int Mask;
	int SidStart;
} ;

typedef T_ACCESS_ALLOWED_ACE *P_ACCESS_ALLOWED_ACE;

struct T_ACCESS_DENIED_ACE
{
	T_ACE_HEADER Header;
	int Mask;
	int SidStart;
} ;

typedef T_ACCESS_DENIED_ACE *P_ACCESS_DENIED_ACE;

struct T_SYSTEM_AUDIT_ACE
{
	T_ACE_HEADER Header;
	int Mask;
	int SidStart;
} ;

typedef T_SYSTEM_AUDIT_ACE *P_SYSTEM_AUDIT_ACE;

struct T_SYSTEM_ALARM_ACE
{
	T_ACE_HEADER Header;
	int Mask;
	int SidStart;
} ;

typedef T_SYSTEM_ALARM_ACE *P_SYSTEM_ALARM_ACE;

struct T_COMPOUND_ACCESS_ALLOWED_ACE;
typedef T_COMPOUND_ACCESS_ALLOWED_ACE *P_COMPOUND_ACCESS_ALLOWED_ACE;

struct T_COMPOUND_ACCESS_ALLOWED_ACE
{
	T_ACE_HEADER Header;
	int Mask;
	Word CompoundAceType;
	Word Reserved;
	int SidStart;
} ;

struct T_ACL_SIZE_INFORMATION
{
	int AceCount;
	int AclBytesInUse;
	int AclBytesFree;
} ;

typedef T_ACL_SIZE_INFORMATION *P_ACL_SIZE_INFORMATION;

enum TPolicy_Information_Class { PolicyNothing, PolicyAuditLogInformation, PolicyAuditEventsInformation, 
	PolicyPrimaryDomainInformation, PolicyPdAccountInformation, PolicyAccountDomainInformation, PolicyLsaServerRoleInformation, 
	PolicyReplicaSourceInformation, PolicyDefaultQuotaInformation, PolicyModificationInformation, PolicyAuditFullSetInformation, 
	PolicyAuditFullQueryInformation };

typedef void *LSA_HANDLE;

typedef int NTSTATUS;

typedef int *PLSA_ENUMERATION_HANDLE;

typedef int TLSA_ENUMERATION_HANDLE;

typedef void *TSIDArray[536870911];

typedef TSIDArray *PSIDArray;

struct TLSA_UNICODE_STRING;
typedef TLSA_UNICODE_STRING *PLSA_UNICODE_STRING;

struct TLSA_UNICODE_STRING
{
	Word Length;
	Word MaximumLength;
	wchar_t *Buffer;
} ;

typedef TLSA_UNICODE_STRING TLSA_UNICODE_STRING_Arr[268435455];

typedef TLSA_UNICODE_STRING_Arr *PLSA_UNICODE_STRING_Arr;

struct TLSA_TRANSLATED_SID;
typedef TLSA_TRANSLATED_SID *PLSA_TRANSLATED_SID;

struct TLSA_TRANSLATED_SID
{
	int Use;
	int RelativeId;
	int DomainIndex;
} ;

struct TLSA_TRANSLATED_NAME;
typedef TLSA_TRANSLATED_NAME *PLSA_TRANSLATED_NAME;

struct TLSA_TRANSLATED_NAME
{
	int Use;
	TLSA_UNICODE_STRING Name;
	int DomainIndex;
} ;

typedef TLSA_TRANSLATED_NAME TLSA_TRANSLATED_NAME_Arr[134217727];

typedef TLSA_TRANSLATED_NAME_Arr *PLSA_TRANSLATED_NAME_Arr;

struct TLSA_OBJECT_ATTRIBUTES;
typedef TLSA_OBJECT_ATTRIBUTES *PLSA_OBJECT_ATTRIBUTES;

struct TLSA_OBJECT_ATTRIBUTES
{
	int Length;
	int RootDirectory;
	TLSA_UNICODE_STRING *ObjectName;
	int Attributes;
	void *SecurityDescriptor;
	void *SecurityQualityOfService;
} ;

struct TLSA_TRUST_INFORMATION;
typedef TLSA_TRUST_INFORMATION *PLSA_TRUST_INFORMATION;

struct TLSA_TRUST_INFORMATION
{
	TLSA_UNICODE_STRING Name;
	void *Sid;
} ;

typedef TLSA_TRUST_INFORMATION TLSA_TRUST_INFORMATION_ARR[178956970];

typedef TLSA_TRUST_INFORMATION_ARR *PLSA_TRUST_INFORMATION_ARR;

struct TLSA_REFERENCED_DOMAIN_LIST
{
	int Entries;
	TLSA_TRUST_INFORMATION_ARR *Domains;
} ;

typedef TLSA_REFERENCED_DOMAIN_LIST *PLSA_REFERENCED_DOMAIN_LIST;

struct TLUIDAndAttributes;
typedef TLUIDAndAttributes *PLUIDAndAttributes;

#pragma pack(push, 1)
struct TLUIDAndAttributes
{
	_LARGE_INTEGER Luid;
	int Attributes;
} ;
#pragma pack(pop)

struct TTokenPrivileges;
typedef TTokenPrivileges *PTokenPrivileges;

struct TTokenPrivileges
{
	int PrivilegeCount;
	TLUIDAndAttributes Privileges[1];
} ;

typedef int __stdcall (*TLsaOpenPolicy)(PLSA_UNICODE_STRING ServerName, PLSA_OBJECT_ATTRIBUTES ObjectAttributes
	, int DesiredAccess, void * &PolicyHandle);

typedef int __stdcall (*TLsaEnumerateTrustedDomains)(void * PolicyHandle, int &EnumerationContext, PLSA_TRUST_INFORMATION_ARR 
	&Buffer, int PreferedMaximumLength, int &CountReturned);

typedef int __stdcall (*TLsaClose)(void * ObjectHandle);

typedef int __stdcall (*TLsaFreeMemory)(void * Buffer);

typedef int __stdcall (*TLsaQueryInformationPolicy)(void * PolicyHandle, TPolicy_Information_Class InformationClass
	, void * &Buffer);

typedef int __stdcall (*TLsaNtStatusToWinError)(int Status);

typedef int __stdcall (*TLsaLookupSids)(void * PolicyHandle, int Count, void * Sids, PLSA_REFERENCED_DOMAIN_LIST 
	&ReferencedDomains, void * &Names);

typedef BOOL __stdcall (*TGetFileSecurity)(char * lpFileName, int RequestedInformation, Windows::PSecurityDescriptor 
	pSecurityDescriptor, int nLength, int &lpnLengthNeeded);

typedef BOOL __stdcall (*TMakeAbsoluteSD)(Windows::PSecurityDescriptor pSelfRelativeSecurityDescriptor
	, Windows::PSecurityDescriptor pAbsoluteSecurityDescriptor, int &lpdwAbsoluteSecurityDescriptorSi, 
	_ACL &pDacl, int &lpdwDaclSize, _ACL &pSacl, int &lpdwSaclSize, void * pOwner, int &lpdwOwnerSize, 
	void * pPrimaryGroup, int &lpdwPrimaryGroupSize);

typedef BOOL __stdcall (*TGetSecurityDescriptorOwner)(Windows::PSecurityDescriptor pSecurityDescriptor
	, void * &pOwner, BOOL &lpbOwnerDefaulted);

typedef BOOL __stdcall (*TSetSecurityDescriptorOwner)(Windows::PSecurityDescriptor pSecurityDescriptor
	, void * pOwner, BOOL bOwnerDefaulted);

typedef BOOL __stdcall (*TSetFileSecurity)(char * lpFileName, int SecurityInformation, Windows::PSecurityDescriptor 
	pSecurityDescriptor);

typedef BOOL __stdcall (*TGetSecurityDescriptorDacl)(Windows::PSecurityDescriptor pSecurityDescriptor
	, BOOL &lpbDaclPresent, PACL &pDacl, BOOL &lpbDaclDefaulted);

typedef int __stdcall (*TGetLengthSid)(void * pSid);

typedef BOOL __stdcall (*TInitializeAcl)(_ACL &pAcl, int nAclLength, int dwAclRevision);

typedef BOOL __stdcall (*TAddAccessDeniedAce)(_ACL &pAcl, int dwAceRevision, int AccessMask, void * 
	pSid);

typedef BOOL __stdcall (*TAddAccessAllowedAce)(_ACL &pAcl, int dwAceRevision, int AccessMask, void * 
	pSid);

typedef BOOL __stdcall (*TAddAuditAccessAce)(_ACL &pAcl, int dwAceRevision, int dwAccessMask, void * 
	pSid, BOOL bAuditSuccess, BOOL bAuditFailure);

typedef BOOL __stdcall (*TGetAce)(const _ACL &pAcl, int dwAceIndex, void * &pAce);

typedef BOOL __stdcall (*TSetSecurityDescriptorDacl)(Windows::PSecurityDescriptor pSecurityDescriptor
	, BOOL bDaclPresent, PACL pDacl, BOOL bDaclDefaulted);

enum TAclInformationClass { AclInfoPad, AclRevisionInformation, AclSizeInformation };

typedef BOOL __stdcall (*TGetAclInformation)(const PACL pAcl, void * pAclInformation, int nAclInformationLength
	, TAclInformationClass dwAclInformationClass);

typedef BOOL __stdcall (*TSetSecurityDescriptorSacl)(Windows::PSecurityDescriptor pSecurityDescriptor
	, BOOL bSaclPresent, PACL pSacl, BOOL bSaclDefaulted);

typedef BOOL __stdcall (*TGetSecurityDescriptorSacl)(Windows::PSecurityDescriptor pSecurityDescriptor
	, BOOL &lpbSaclPresent, PACL &pSacl, BOOL &lpbSaclDefaulted);

typedef BOOL __stdcall (*TMakeSelfRelativeSD)(Windows::PSecurityDescriptor pAbsoluteSecurityDescriptor
	, Windows::PSecurityDescriptor pSelfRelativeSecurityDescriptor, int &lpdwBufferLength);

typedef BOOL __stdcall (*TInitializeSecurityDescriptor)(Windows::PSecurityDescriptor pNewSecurityDescriptor
	, int dwRevision);

typedef int __stdcall (*TRegGetKeySecurity)(HKEY hKey, int SecurityInformation, Windows::PSecurityDescriptor 
	pSecurityDescriptor, int &lpcbSecurityDescriptor);

typedef int __stdcall (*TRegSetKeySecurity)(HKEY hKey, int SecurityInformation, void * pSecurityDescriptor
	);

//-- var, const, procedure ---------------------------------------------------
#define ACL_REVISION (Byte)(2)
#define SECURITY_DESCRIPTOR_REVISION (Byte)(1)
#define OWNER_SECURITY_INFORMATION (Byte)(1)
#define GROUP_SECURITY_INFORMATION (Byte)(2)
#define DACL_SECURITY_INFORMATION (Byte)(4)
#define SACL_SECURITY_INFORMATION (Byte)(8)
#define ACCESS_ALLOWED_ACE_TYPE (Byte)(0)
#define ACCESS_DENIED_ACE_TYPE (Byte)(1)
#define SYSTEM_AUDIT_ACE_TYPE (Byte)(2)
#define SYSTEM_ALARM_ACE_TYPE (Byte)(3)
#define ACCESS_ALLOWED_COMPOUND_ACE_TYPE (Byte)(4)
#define OBJECT_INHERIT_ACE (Byte)(1)
#define CONTAINER_INHERIT_ACE (Byte)(2)
#define NO_PROPAGATE_INHERIT_ACE (Byte)(4)
#define INHERIT_ONLY_ACE (Byte)(8)
#define VALID_INHERIT_FLAGS (Byte)(15)
#define SUCCESSFUL_ACCESS_ACE_FLAG (Byte)(64)
#define FAILED_ACCESS_ACE_FLAG (Byte)(128)
#define _FILE_MAP_READ (Byte)(137)
#define _FILE_MAP_WRITE (Word)(278)
#define _FILE_MAP_EXECUTE (Byte)(160)
#define _FILE_MAP_SPECIFIC_ALL (Word)(511)
#define SECURITY_NULL_SID_AUTHORITY (Byte)(0)
#define SECURITY_WORLD_SID_AUTHORITY (Byte)(1)
#define SECURITY_LOCAL_SID_AUTHORITY (Byte)(2)
#define SECURITY_CREATOR_SID_AUTHORITY (Byte)(3)
#define SECURITY_NT_AUTHORITY (Byte)(5)
extern PACKAGE Byte SECURITY_LOCAL_SYSTEM_SID[12];
#define STATUS_SUCCESS (Byte)(0)
#define STATUS_INVALID_INFO_CLASS (int)(-1073741821)
#define STATUS_ACCESS_VIOLATION (int)(-1073741819)
#define STATUS_NO_SUCH_USER (int)(-1073741724)
#define STATUS_WRONG_PASSWORD (int)(-1073741718)
#define STATUS_PASSWORD_RESTRICTION (int)(-1073741716)
#define STATUS_LOGON_FAILURE (int)(-1073741715)
#define STATUS_ACCOUNT_RESTRICTION (int)(-1073741714)
#define STATUS_INVALID_LOGON_HOURS (int)(-1073741713)
#define STATUS_INVALID_WORKSTATION (int)(-1073741712)
#define STATUS_PASSWORD_EXPIRED (int)(-1073741711)
#define STATUS_ACCOUNT_DISABLED (int)(-1073741710)
#define STATUS_INSUFFICIENT_RESOURCES (int)(-1073741670)
#define STATUS_ACCOUNT_EXPIRED (int)(-1073741421)
#define STATUS_PASSWORD_MUST_CHANGE (int)(-1073741276)
#define STATUS_ACCOUNT_LOCKED_OUT (int)(-1073741260)
#define POLICY_VIEW_LOCAL_INFORMATION (Byte)(1)
#define POLICY_VIEW_AUDIT_INFORMATION (Byte)(2)
#define POLICY_GET_PRIVATE_INFORMATION (Byte)(4)
#define POLICY_TRUST_ADMIN (Byte)(8)
#define POLICY_CREATE_ACCOUNT (Byte)(16)
#define POLICY_CREATE_SECRET (Byte)(32)
#define POLICY_CREATE_PRIVILEGE (Byte)(64)
#define POLICY_SET_DEFAULT_QUOTA_LIMITS (Byte)(128)
#define POLICY_SET_AUDIT_REQUIREMENTS (Word)(256)
#define POLICY_AUDIT_LOG_ADMIN (Word)(512)
#define POLICY_SERVER_ADMIN (Word)(1024)
#define POLICY_LOOKUP_NAMES (Word)(2048)
#define POLICY_ALL_ACCESS (int)(987135)
#define POLICY_READ (int)(131078)
#define POLICY_WRITE (int)(133112)
#define POLICY_EXECUTE (int)(133121)
#define SE_INTERACTIVE_LOGON_NAME "SeInteractiveLogonRight"
#define SE_NETWORK_LOGON_NAME "SeNetworkLogonRight"
#define SE_BATCH_LOGON_NAME "SeBatchLogonRight"
#define SE_SERVICE_LOGON_NAME "SeServiceLogonRight"
#define SE_CREATE_TOKEN_NAME "SeCreateTokenPrivilege"
#define SE_ASSIGNPRIMARYTOKEN_NAME "SeAssignPrimaryTokenPrivilege"
#define SE_LOCK_MEMORY_NAME "SeLockMemoryPrivilege"
#define SE_INCREASE_QUOTA_NAME "SeIncreaseQuotaPrivilege"
#define SE_UNSOLICITED_INPUT_NAME "SeUnsolicitedInputPrivilege"
#define SE_MACHINE_ACCOUNT_NAME "SeMachineAccountPrivilege"
#define SE_TCB_NAME "SeTcbPrivilege"
#define SE_SECURITY_NAME "SeSecurityPrivilege"
#define SE_TAKE_OWNERSHIP_NAME "SeTakeOwnershipPrivilege"
#define SE_LOAD_DRIVER_NAME "SeLoadDriverPrivilege"
#define SE_SYSTEM_PROFILE_NAME "SeSystemProfilePrivilege"
#define SE_SYSTEMTIME_NAME "SeSystemtimePrivilege"
#define SE_PROF_SINGLE_PROCESS_NAME "SeProfileSingleProcessPrivilege"
#define SE_INC_BASE_PRIORITY_NAME "SeIncreaseBasePriorityPrivilege"
#define SE_CREATE_PAGEFILE_NAME "SeCreatePagefilePrivilege"
#define SE_CREATE_PERMANENT_NAME "SeCreatePermanentPrivilege"
#define SE_BACKUP_NAME "SeBackupPrivilege"
#define SE_RESTORE_NAME "SeRestorePrivilege"
#define SE_SHUTDOWN_NAME "SeShutdownPrivilege"
#define SE_DEBUG_NAME "SeDebugPrivilege"
#define SE_AUDIT_NAME "SeAuditPrivilege"
#define SE_SYSTEM_ENVIRONMENT_NAME "SeSystemEnvironmentPrivilege"
#define SE_CHANGE_NOTIFY_NAME "SeChangeNotifyPrivilege"
#define SE_REMOTE_SHUTDOWN_NAME "SeRemoteShutdownPrivilege"
extern PACKAGE TLsaOpenPolicy LsaOpenPolicy;
extern PACKAGE TLsaEnumerateTrustedDomains LsaEnumerateTrustedDomains;
extern PACKAGE TLsaClose LsaClose;
extern PACKAGE TLsaFreeMemory LsaFreeMemory;
extern PACKAGE TLsaQueryInformationPolicy LsaQueryInformationPolicy;
extern PACKAGE TLsaNtStatusToWinError LsaNtStatusToWinError;
extern PACKAGE TLsaLookupSids LsaLookupSids;
extern PACKAGE TGetFileSecurity GetFileSecurity;
extern PACKAGE TMakeAbsoluteSD MakeAbsoluteSD;
extern PACKAGE TGetSecurityDescriptorOwner GetSecurityDescriptorOwner;
extern PACKAGE TSetSecurityDescriptorOwner SetSecurityDescriptorOwner;
extern PACKAGE TSetFileSecurity SetFileSecurity;
extern PACKAGE TGetSecurityDescriptorDacl GetSecurityDescriptorDacl;
extern PACKAGE TGetLengthSid GetLengthSid;
extern PACKAGE TInitializeAcl InitializeAcl;
extern PACKAGE TAddAccessDeniedAce AddAccessDeniedAce;
extern PACKAGE TAddAccessAllowedAce AddAccessAllowedAce;
extern PACKAGE TAddAuditAccessAce AddAuditAccessAce;
extern PACKAGE TGetAce GetAce;
extern PACKAGE TSetSecurityDescriptorDacl SetSecurityDescriptorDacl;
extern PACKAGE TGetAclInformation GetAclInformation;
extern PACKAGE TSetSecurityDescriptorSacl SetSecurityDescriptorSacl;
extern PACKAGE TGetSecurityDescriptorSacl GetSecurityDescriptorSacl;
extern PACKAGE TMakeSelfRelativeSD MakeSelfRelativeSD;
extern PACKAGE TInitializeSecurityDescriptor InitializeSecurityDescriptor;
extern PACKAGE TRegGetKeySecurity RegGetKeySecurity;
extern PACKAGE TRegSetKeySecurity RegSetKeySecurity;
extern "C" BOOL __stdcall AdjustTokenPrivileges(int TokenHandle, BOOL DisableAllPrivileges, PTokenPrivileges 
	NewState, int BufferLength, PTokenPrivileges PreviousState, int &ReturnLength);
extern PACKAGE void __fastcall DestroyLsaString(PLSA_UNICODE_STRING LsaString);
extern PACKAGE void __fastcall InitLsaString(PLSA_UNICODE_STRING LsaString, System::AnsiString S);

}	/* namespace Security */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Security;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// Security
