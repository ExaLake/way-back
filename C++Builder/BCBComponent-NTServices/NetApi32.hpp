// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'NetApi32.pas' rev: 3.00

#ifndef NetApi32HPP
#define NetApi32HPP
#include <NT_vs_95.hpp>
#include <lmErr.hpp>
#include <Messages.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Netapi32
{
//-- type declarations -------------------------------------------------------
typedef int NET_API_STATUS;

typedef Byte TByteBuf[2147483647];

typedef TByteBuf *PByteBuf;

struct TUser_info_0;
typedef TUser_info_0 *PUser_info_0;

struct TUser_info_0
{
	void *usri0_name;
} ;

typedef TUser_info_0 TUser_Info_0_Arr[536870911];

typedef TUser_Info_0_Arr *PUser_Info_0_Arr;

struct TGroup_Users_Info_0;
typedef TGroup_Users_Info_0 *PGroup_Users_Info_0;

struct TGroup_Users_Info_0
{
	void *grui0_name;
} ;

typedef TGroup_Users_Info_0 TGroup_Users_Info_0_Arr[536870911];

typedef TGroup_Users_Info_0_Arr *PGroup_Users_Info_0_Arr;

struct TLocalGroup_Users_Info_0;
typedef TLocalGroup_Users_Info_0 *PLocalGroup_Users_Info_0;

struct TLocalGroup_Users_Info_0
{
	void *lgrui0_name;
} ;

typedef TLocalGroup_Users_Info_0 TLocalGroup_Users_Info_0_Arr[536870911];

typedef TLocalGroup_Users_Info_0_Arr *PLocalGroup_Users_Info_0_Arr;

struct TUser_Info_1;
typedef TUser_Info_1 *PUser_Info_1;

struct TUser_Info_1
{
	void *usri1_name;
	void *usri1_password;
	int usri1_password_age;
	int usri1_priv;
	void *usri1_home_dir;
	void *usri1_comment;
	int usri1_flags;
	void *usri1_script_path;
} ;

typedef TUser_Info_1 TUser_Info_1_Arr[67108863];

typedef TUser_Info_1_Arr *PUser_Info_1_Arr;

struct TUser_Info_2;
typedef TUser_Info_2 *PUser_Info_2;

struct TUser_Info_2
{
	void *usri2_name;
	void *usri2_password;
	int usri2_password_age;
	int usri2_priv;
	void *usri2_home_dir;
	void *usri2_comment;
	int usri2_flags;
	void *usri2_script_path;
	int usri2_auth_flags;
	void *usri2_full_name;
	void *usri2_usr_comment;
	void *usri2_parms;
	void *usri2_workstations;
	int usri2_last_logon;
	int usri2_last_logoff;
	int usri2_acct_expires;
	int usri2_max_storage;
	int usri2_units_per_week;
	Byte *usri2_logon_hours;
	int usri2_bad_pw_count;
	int usri2_num_logons;
	void *usri2_logon_server;
	int usri2_country_code;
	int usri2_code_page;
} ;

typedef TUser_Info_2 TUser_Info_2_Arr[22369621];

typedef TUser_Info_2_Arr *PUser_Info_2_Arr;

struct TUser_Info_3;
typedef TUser_Info_3 *PUser_Info_3;

struct TUser_Info_3
{
	void *usri3_name;
	void *usri3_password;
	int usri3_password_age;
	int usri3_priv;
	void *usri3_home_dir;
	void *usri3_comment;
	int usri3_flags;
	void *usri3_script_path;
	int usri3_auth_flags;
	void *usri3_full_name;
	void *usri3_usr_comment;
	void *usri3_parms;
	void *usri3_workstations;
	int usri3_last_logon;
	int usri3_last_logoff;
	int usri3_acct_expires;
	int usri3_max_storage;
	int usri3_units_per_week;
	Byte *usri3_logon_hours;
	int usri3_bad_pw_count;
	int usri3_num_logons;
	void *usri3_logon_server;
	int usri3_country_code;
	int usri3_code_page;
	int usri3_user_id;
	int usri3_primary_group_id;
	void *usri3_profile;
	void *usri3_home_dir_drive;
	int usri3_password_expired;
} ;

typedef TUser_Info_3 TUser_Info_3_Arr[18512790];

typedef TUser_Info_3_Arr *PUser_Info_3_Arr;

struct TUSER_INFO_1003;
typedef TUSER_INFO_1003 *PUSER_INFO_1003;

struct TUSER_INFO_1003
{
	void *usri1003_password;
} ;

struct TUSER_INFO_1005
{
	int usri1005_priv;
} ;

typedef TUSER_INFO_1005 *PUSER_INFO_1005;

struct TUSER_INFO_1006;
typedef TUSER_INFO_1006 *PUSER_INFO_1006;

struct TUSER_INFO_1006
{
	void *usri1006_home_dir;
} ;

struct TUSER_INFO_1007;
typedef TUSER_INFO_1007 *PUSER_INFO_1007;

struct TUSER_INFO_1007
{
	void *usri1007_comment;
} ;

struct TUSER_INFO_1008
{
	int usri1008_flags;
} ;

typedef TUSER_INFO_1008 *PUSER_INFO_1008;

struct TUSER_INFO_1009;
typedef TUSER_INFO_1009 *PUSER_INFO_1009;

struct TUSER_INFO_1009
{
	void *usri1009_script_path;
} ;

struct TUSER_INFO_1010
{
	int usri1010_auth_flags;
} ;

typedef TUSER_INFO_1010 *PUSER_INFO_1010;

struct TUSER_INFO_1011;
typedef TUSER_INFO_1011 *PUSER_INFO_1011;

struct TUSER_INFO_1011
{
	void *usri1011_full_name;
} ;

struct TUSER_INFO_1014;
typedef TUSER_INFO_1014 *PUSER_INFO_1014;

struct TUSER_INFO_1014
{
	void *usri1014_workstations;
} ;

struct TUSER_INFO_1017
{
	int usri1017_acct_expires;
} ;

typedef TUSER_INFO_1017 *PUSER_INFO_1017;

struct TUSER_INFO_1018
{
	int usri1018_max_storage;
} ;

typedef TUSER_INFO_1018 *PUSER_INFO_1018;

struct TUSER_INFO_1024
{
	int usri1024_country_code;
} ;

typedef TUSER_INFO_1024 *PUSER_INFO_1024;

struct TUSER_INFO_1052;
typedef TUSER_INFO_1052 *PUSER_INFO_1052;

struct TUSER_INFO_1052
{
	void *usri1052_profile;
} ;

struct TUSER_INFO_1053;
typedef TUSER_INFO_1053 *PUSER_INFO_1053;

struct TUSER_INFO_1053
{
	void *usri1053_home_dir_drive;
} ;

struct TNet_Display_User;
typedef TNet_Display_User *PNet_Display_User;

struct TNet_Display_User
{
	void *usri1_name;
	void *usri1_comment;
	int usri1_flags;
	void *usri1_full_name;
	int usri1_user_id;
	int usri1_next_index;
} ;

typedef TNet_Display_User TNet_Display_User_Arr[89478485];

typedef TNet_Display_User_Arr *PNet_Display_User_Arr;

struct TNet_Display_Group;
typedef TNet_Display_Group *PNet_Display_Group;

struct TNet_Display_Group
{
	void *grpi3_name;
	void *grpi3_comment;
	int grpi3_group_id;
	int grpi3_attributes;
	int grpi3_next_index;
} ;

typedef TNet_Display_Group TNet_Display_Group_Arr[107374182];

typedef TNet_Display_Group_Arr *PNet_Display_Group_Arr;

struct TGroup_Info_0;
typedef TGroup_Info_0 *PGroup_Info_0;

struct TGroup_Info_0
{
	void *grpi0_name;
} ;

typedef TGroup_Info_0 TGroup_Info_0_Arr[536870911];

typedef TGroup_Info_0_Arr *PGroup_Info_0_Arr;

struct TGroup_Info_1;
typedef TGroup_Info_1 *PGroup_Info_1;

struct TGroup_Info_1
{
	void *grpi1_name;
	void *grpi1_comment;
} ;

typedef TGroup_Info_1 TGroup_Info_1_Arr[268435455];

typedef TGroup_Info_1_Arr *PGroup_Info_1_Arr;

struct TGroup_Info_2;
typedef TGroup_Info_2 *PGroup_Info_2;

struct TGroup_Info_2
{
	void *grpi2_name;
	void *grpi2_comment;
	int grpi2_group_id;
	int grpi2_attributes;
} ;

typedef TGroup_Info_2 TGroup_Info_2_Arr[134217727];

typedef TGroup_Info_2_Arr *PGroup_Info_2_Arr;

struct TGroup_Info_1002;
typedef TGroup_Info_1002 *PGroup_Info_1002;

struct TGroup_Info_1002
{
	void *grpi1002_comment;
} ;

typedef TGroup_Info_1002 TGroup_Info_1002_Arr[536870911];

typedef TGroup_Info_1002_Arr *PGroup_Info_1002_Arr;

struct TLocalGroup_Info_0;
typedef TLocalGroup_Info_0 *PLocalGroup_Info_0;

struct TLocalGroup_Info_0
{
	void *lgrpi0_name;
} ;

typedef TLocalGroup_Info_0 TLocalGroup_Info_0_Arr[536870911];

typedef TLocalGroup_Info_0_Arr *PLocalGroup_Info_0_Arr;

struct TLocalGroup_Info_1;
typedef TLocalGroup_Info_1 *PLocalGroup_Info_1;

struct TLocalGroup_Info_1
{
	void *lgrpi1_name;
	void *lgrpi1_comemnt;
} ;

typedef TLocalGroup_Info_1 TLocalGroup_Info_1_Arr[268435455];

typedef TLocalGroup_Info_1_Arr *PLocalGroup_Info_1_Arr;

struct TLocalGroup_Info_1002;
typedef TLocalGroup_Info_1002 *PLocalGroup_Info_1002;

struct TLocalGroup_Info_1002
{
	void *lgrpi1002_comemnt;
} ;

typedef TLocalGroup_Info_1002 TLocalGroup_Info_1002_Arr[536870911];

typedef TLocalGroup_Info_1002_Arr *PLocalGroup_Info_1002_Arr;

struct TLocalGroup_Members_Info_0;
typedef TLocalGroup_Members_Info_0 *PLocalGroup_Members_Info_0;

struct TLocalGroup_Members_Info_0
{
	void *lgrmi0_sid;
} ;

typedef TLocalGroup_Members_Info_0 TLocalGroup_Members_Info_0_Arr[536870911];

typedef TLocalGroup_Members_Info_0_Arr *PLocalGroup_Members_Info_0_Arr;

struct TLocalGroup_Members_Info_3;
typedef TLocalGroup_Members_Info_3 *PLocalGroup_Members_Info_3;

struct TLocalGroup_Members_Info_3
{
	void *lgrmi3_domainandname;
} ;

typedef TLocalGroup_Members_Info_3 TLocalGroup_Members_Info_3_Arr[536870911];

typedef TLocalGroup_Members_Info_3_Arr *PLocalGroup_Members_Info_3_Arr;

struct TShare_Info_0;
typedef TShare_Info_0 *PShare_Info_0;

struct TShare_Info_0
{
	void *shi0_netname;
} ;

typedef TShare_Info_0 TShare_Info_0_Arr[536870911];

typedef TShare_Info_0_Arr *PShare_Info_0_Arr;

struct TShare_Info_1;
typedef TShare_Info_1 *PShare_Info_1;

struct TShare_Info_1
{
	void *shi1_netname;
	int shi1_type;
	void *shi1_remark;
} ;

typedef TShare_Info_1 TShare_Info_1_Arr[178956970];

typedef TShare_Info_1_Arr *PShare_Info_1_Arr;

struct TShare_Info_2;
typedef TShare_Info_2 *PShare_Info_2;

struct TShare_Info_2
{
	void *shi2_netname;
	int shi2_type;
	void *shi2_remark;
	int shi2_permissions;
	int shi2_max_uses;
	int shi2_current_uses;
	void *shi2_path;
	void *shi2_passwd;
} ;

typedef TShare_Info_2 TShare_Info_2_Arr[67108863];

typedef TShare_Info_2_Arr *PShare_Info_2_Arr;

struct TShare_Info_502;
typedef TShare_Info_502 *PShare_Info_502;

struct TShare_Info_502
{
	void *shi502_netname;
	int shi502_type;
	void *shi502_remark;
	int shi502_permissions;
	int shi502_max_uses;
	int shi502_current_uses;
	void *shi502_path;
	void *shi502_passwd;
	int shi502_reserved;
	void *shi502_security_descriptor;
} ;

struct TShare_Info_1004;
typedef TShare_Info_1004 *PShare_Info_1004;

struct TShare_Info_1004
{
	void *shi1004_remark;
} ;

struct TShare_Info_1006
{
	int shi1006_max_uses;
} ;

typedef TShare_Info_1006 *PShare_Info_1006;

struct TShare_Info_1501;
typedef TShare_Info_1501 *PShare_Info_1501;

struct TShare_Info_1501
{
	int shi1501_reserved;
	void *shi1501_security_descriptor;
} ;

typedef _NETRESOURCEA TNetResourceArr[67108863];

typedef TNetResourceArr *PNetResourceArr;

struct TServer_Info_100;
typedef TServer_Info_100 *PServer_Info_100;

struct TServer_Info_100
{
	int sv100_platform_id;
	void *sv100_name;
} ;

typedef TServer_Info_100 TServer_Info_100_Arr[268435455];

typedef TServer_Info_100_Arr *PServer_Info_100_Arr;

struct TServer_Info_402;
typedef TServer_Info_402 *PServer_Info_402;

struct TServer_Info_402
{
	int sv402_ulist_mtime;
	int sv402_glist_mtime;
	int sv402_alist_mtime;
	void *sv402_alerts;
	int sv402_security;
	int sv402_numadmin;
	int sv402_lanmask;
	void *sv402_guestacct;
	int sv402_chdevs;
	int sv402_chdevq;
	int sv402_chdevjobs;
	int sv402_connections;
	int sv402_shares;
	int sv402_openfiles;
	int sv402_sessopens;
	int sv402_sessvcs;
	int sv402_sessreqs;
	int sv402_opensearch;
	int sv402_activelocks;
	int sv402_numreqbuf;
	int sv402_sizreqbuf;
	int sv402_numbigbuf;
	int sv402_numfiletasks;
	int sv402_alertsched;
	int sv402_erroralert;
	int sv402_logonalert;
	int sv402_accessalert;
	int sv402_diskalert;
	int sv402_netioalert;
	int sv402_maxauditsz;
	void *sv402_srvheuristics;
} ;

struct TServer_Info_403;
typedef TServer_Info_403 *PServer_Info_403;

struct TServer_Info_403
{
	int sv403_ulist_mtime;
	int sv403_glist_mtime;
	int sv403_alist_mtime;
	void *sv403_alerts;
	int sv403_security;
	int sv403_numadmin;
	int sv403_lanmask;
	void *sv403_guestacct;
	int sv403_chdevs;
	int sv403_chdevq;
	int sv403_chdevjobs;
	int sv403_connections;
	int sv403_shares;
	int sv403_openfiles;
	int sv403_sessopens;
	int sv403_sessvcs;
	int sv403_sessreqs;
	int sv403_opensearch;
	int sv403_activelocks;
	int sv403_numreqbuf;
	int sv403_sizreqbuf;
	int sv403_numbigbuf;
	int sv403_numfiletasks;
	int sv403_alertsched;
	int sv403_erroralert;
	int sv403_logonalert;
	int sv403_accessalert;
	int sv403_diskalert;
	int sv403_netioalert;
	int sv403_maxauditsz;
	void *sv403_srvheuristics;
	int sv403_auditedevents;
	int sv403_autoprofile;
	void *sv403_autopath;
} ;

struct TSession_Info_0;
typedef TSession_Info_0 *PSession_Info_0;

struct TSession_Info_0
{
	void *sesi0_cname;
} ;

typedef TSession_Info_0 TSession_Info_0_Arr[536870911];

typedef TSession_Info_0_Arr *PSession_Info_0_Arr;

struct TSession_Info_1;
typedef TSession_Info_1 *PSession_Info_1;

struct TSession_Info_1
{
	void *sesi1_cname;
	void *sesi1_username;
	int sesi1_time;
	int sesi1_idle_time;
	int sesi1_user_flags;
} ;

typedef TSession_Info_1 TSession_Info_1_Arr[107374182];

typedef TSession_Info_1_Arr *PSession_Info_1_Arr;

struct TSession_Info_10;
typedef TSession_Info_10 *PSession_Info_10;

struct TSession_Info_10
{
	void *sesi10_cname;
	void *sesi10_username;
	int sesi10_time;
	int sesi10_idle_time;
} ;

typedef TSession_Info_10 TSession_Info_10_Arr[134217727];

typedef TSession_Info_10_Arr *PSession_Info_10_Arr;

struct TSession_Info_502;
typedef TSession_Info_502 *PSession_Info_502;

struct TSession_Info_502
{
	void *sesi502_cname;
	void *sesi502_username;
	int sesi502_num_opens;
	int sesi502_time;
	int sesi502_idle_time;
	int sesi502_user_flags;
	void *sesi502_cltype_name;
	void *sesi502_transport;
} ;

typedef TSession_Info_502 TSession_Info_502_Arr[67108863];

typedef TSession_Info_502_Arr *PSession_Info_502_Arr;

struct TFile_Info_3;
typedef TFile_Info_3 *PFile_Info_3;

struct TFile_Info_3
{
	int fi3_id;
	int fi3_permissions;
	int fi3_num_locks;
	void *fi3_pathname;
	void *fi3_username;
} ;

typedef TFile_Info_3 TFile_Info_3_Arr[107374182];

typedef TFile_Info_3_Arr *PFile_Info_3_Arr;

typedef int __stdcall (*TNetServerEnum)(void * servername, int level, void * &bufptr, int prefmaxlen
	, int &entriesread, int &totalentries, int servertype, void * domain, int &resume_handle);

typedef int __stdcall (*TNetApiBufferFree)(void * P);

typedef int __stdcall (*TNetUserEnum)(void * Servername, int Level, int Filter, void * &bufptr, int 
	prefmaxlen, int &entriesread, int &totalentries, int &resume_handle);

typedef int __stdcall (*TNetUserGetInfo)(void * servername, void * username, int level, void * &bufptr
	);

typedef int __stdcall (*TNetQueryDisplayInformation)(void * servername, int level, int Index, int EntriesRequested
	, int PreferredMaximumLength, int &ReturnedEntryCount, void * &SortedBuffer);

typedef int __stdcall (*TNetGetDisplayInformationIndex)(void * servername, int level, void * Prefix, 
	int &Index);

typedef int __stdcall (*TNetGroupEnum)(void * servername, int level, void * &bufptr, int prefmaxlen, 
	int &entriesread, int &totalentries, int &resume_handle);

typedef int __stdcall (*TNetLocalGroupEnum)(void * servername, int level, void * &bufptr, int prefmaxlen
	, int &entriesread, int &totalentries, int &resume_handle);

typedef int __stdcall (*TNetUserGetGroups)(void * servername, void * username, int level, void * &bufptr
	, int prefmaxlen, int &entriesread, int &totalentries);

typedef int __stdcall (*TNetUserGetLocalGroups)(void * servername, void * username, int Flags, int level
	, void * &bufptr, int prefmaxlen, int &entriesread, int &totalentries);

typedef int __stdcall (*TNetLocalGroupAddMembers)(void * servername, void * LocalGroupName, int level
	, void * Buf, int membercount);

typedef int __stdcall (*TNetLocalGroupDelMembers)(void * servername, void * LocalGroupName, int level
	, void * Buf, int membercount);

typedef int __stdcall (*TNetGroupAddUser)(void * servername, void * GroupName, void * username);

typedef int __stdcall (*TNetGroupDelUser)(void * servername, void * GroupName, void * username);

typedef int __stdcall (*TNetLocalGroupAdd)(void * servername, int level, void * buf, int &parm_err);
	

typedef int __stdcall (*TNetLocalGroupDel)(void * servername, void * LocalGroupName);

typedef int __stdcall (*TNetGroupAdd)(void * servername, int level, void * buf, int &parm_err);

typedef int __stdcall (*TNetGroupDel)(void * servername, void * LocalGroupName);

typedef int __stdcall (*TNetUserSetInfo)(void * servername, void * username, int level, void * buf, 
	int &parm_err);

typedef int __stdcall (*TNetUserAdd)(void * servername, int level, void * buf, int &parm_err);

typedef int __stdcall (*TNetUserDel)(void * servername, void * username);

typedef int __stdcall (*TNetGroupGetUsers)(void * servername, void * GroupName, int level, void * &bufptr
	, int prefmaxlen, int &entriesread, int &totalentries, int &resumeHandle);

typedef int __stdcall (*TNetLocalGroupGetMembers)(void * servername, void * GroupName, int level, void * 
	&bufptr, int prefmaxlen, int &entriesread, int &totalentries, int &resumeHandle);

typedef int __stdcall (*TNetLocalGroupSetMembers)(void * servername, void * LocalGroupName, int level
	, void * buf, int totalentries);

typedef int __stdcall (*TNetGroupSetUsers)(void * servername, void * groupname, int level, void * buf
	, int NewMemberCount);

typedef int __stdcall (*TNetGroupGetInfo)(void * servername, void * groupname, int level, void * &buf
	);

typedef int __stdcall (*TNetGroupSetInfo)(void * servername, void * groupname, int level, void * buf
	, int &parm_err);

typedef int __stdcall (*TNetLocalGroupGetInfo)(void * servername, void * LocalGroupName, int level, 
	void * &buf);

typedef int __stdcall (*TNetLocalGroupSetInfo)(void * servername, void * LocalGroupName, int level, 
	void * buf, int &parm_err);

typedef int __stdcall (*TNetShareGetInfo)(void * servername, void * netname, int level, void * &buf)
	;

typedef int __stdcall (*TNetShareSetInfo)(void * servername, void * netname, int level, void * buf, 
	int &parm_err);

typedef int __stdcall (*TNetServerGetInfo)(void * servername, int level, void * &buf);

typedef int __stdcall (*TNetSessionEnum)(void * servername, void * UncClientName, void * username, int 
	level, void * &buf, int prefmaxlen, int &entriesread, int &totalentries, int &resume_handle);

typedef int __stdcall (*TNetSessionDel)(void * servername, void * UncClientName, void * username);

typedef int __stdcall (*TNetFileEnum)(void * servername, void * basepath, void * username, int level
	, void * &buf, int prefmaxlen, int &entriesread, int &totalentries, int &resume_handle);

typedef int __stdcall (*TNetFileClose)(void * servername, int fileid);

typedef int __stdcall (*TNetShareAdd)(void * servername, int level, void * buf, int &parm_err);

typedef int __stdcall (*TNetShareDel)(void * servername, void * netname, int reserved);

typedef int __stdcall (*TNetShareEnum)(void * servername, int level, void * &buf, int prefmaxlen, int 
	&entriesread, int &totalentries, int &resume_handle);

typedef int __stdcall (*TNetGetAnyDCName)(void * servername, void * DomainName, void * &Buf);

typedef int __stdcall (*TNetGetDCName)(void * servername, void * DomainName, void * &Buf);

//-- var, const, procedure ---------------------------------------------------
#define FILTER_TEMP_DUPLICATE_ACCOUNT (Byte)(1)
#define FILTER_NORMAL_ACCOUNT (Byte)(2)
#define FILTER_PROXY_ACCOUNT (Byte)(4)
#define FILTER_INTERDOMAIN_TRUST_ACCOUNT (Byte)(8)
#define FILTER_WORKSTATION_TRUST_ACCOUNT (Byte)(16)
#define FILTER_SERVER_TRUST_ACCOUNT (Byte)(32)
#define USER_PRIV_GUEST (Byte)(0)
#define USER_PRIV_USER (Byte)(1)
#define USER_PRIV_ADMIN (Byte)(2)
#define SV_TYPE_WORKSTATION (Byte)(1)
#define SV_TYPE_SERVER (Byte)(2)
#define SV_TYPE_SQLSERVER (Byte)(4)
#define SV_TYPE_DOMAIN_CTRL (Byte)(8)
#define SV_TYPE_DOMAIN_BAKCTRL (Byte)(16)
#define SV_TYPE_TIME_SOURCE (Byte)(32)
#define SV_TYPE_AFP (Byte)(64)
#define SV_TYPE_NOVELL (Byte)(128)
#define SV_TYPE_DOMAIN_MEMBER (Word)(256)
#define SV_TYPE_PRINTQ_SERVER (Word)(512)
#define SV_TYPE_DIALIN_SERVER (Word)(1024)
#define SV_TYPE_XENIX_SERVER (Word)(2048)
#define SV_TYPE_SERVER_UNIX (Word)(2048)
#define SV_TYPE_NT (Word)(4096)
#define SV_TYPE_WFW (Word)(8192)
#define SV_TYPE_SERVER_MFPN (Word)(16384)
#define SV_TYPE_SERVER_NT (int)(32768)
#define SV_TYPE_POTENTIAL_BROWSER (int)(65536)
#define SV_TYPE_BACKUP_BROWSER (int)(131072)
#define SV_TYPE_MASTER_BROWSER (int)(262144)
#define SV_TYPE_DOMAIN_MASTER (int)(524288)
#define SV_TYPE_SERVER_OSF (int)(1048576)
#define SV_TYPE_SERVER_VMS (int)(2097152)
#define SV_TYPE_WINDOWS (int)(4194304)
#define SV_TYPE_DFS (int)(8388608)
#define SV_TYPE_ALTERNATE_XPORT (int)(536870912)
#define SV_TYPE_LOCAL_LIST_ONLY (int)(1073741824)
#define SV_TYPE_DOMAIN_ENUM (int)(0x80000000)
#define SV_TYPE_ALL (Shortint)(-1)
#define UF_SCRIPT (Byte)(1)
#define UF_ACCOUNTDISABLE (Byte)(2)
#define UF_HOMEDIR_REQUIRED (Byte)(8)
#define UF_LOCKOUT (Byte)(16)
#define UF_PASSWD_NOTREQD (Byte)(32)
#define UF_PASSWD_CANT_CHANGE (Byte)(64)
#define UF_TEMP_DUPLICATE_ACCOUNT (Word)(256)
#define UF_NORMAL_ACCOUNT (Word)(512)
#define UF_INTERDOMAIN_TRUST_ACCOUNT (Word)(2048)
#define UF_WORKSTATION_TRUST_ACCOUNT (Word)(4096)
#define UF_SERVER_TRUST_ACCOUNT (Word)(8192)
#define UF_MACHINE_ACCOUNT_MASK (Word)(14336)
#define UF_ACCOUNT_TYPE_MASK (Word)(15104)
#define UF_DONT_EXPIRE_PASSWD (int)(65536)
#define UF_MNS_LOGON_ACCOUNT (int)(131072)
#define UF_SETTABLE_BITS (int)(211835)
#define TIMEQ_FOREVER (Shortint)(-1)
#define USER_MAXSTORAGE_UNLIMITED (Shortint)(-1)
#define AF_OP_PRINT (Byte)(1)
#define AF_OP_COMM (Byte)(2)
#define AF_OP_SERVER (Byte)(4)
#define AF_OP_ACCOUNTS (Byte)(8)
#define STYPE_DISKTREE (Byte)(0)
#define STYPE_PRINTQ (Byte)(1)
#define STYPE_DEVICE (Byte)(2)
#define STYPE_IPC (Byte)(3)
#define ACCESS_NONE (Byte)(0)
#define ACCESS_READ (Byte)(1)
#define ACCESS_WRITE (Byte)(2)
#define ACCESS_CREATE (Byte)(4)
#define ACCESS_EXEC (Byte)(8)
#define ACCESS_DELETE (Byte)(16)
#define ACCESS_ATRIB (Byte)(32)
#define ACCESS_PERM (Byte)(64)
#define ACCESS_FINDFIRST (Byte)(128)
#define ACCESS_GROUP (int)(32768)
#define ACCESS_ALL (Byte)(255)
#define SV_USERSECURITY (Byte)(1)
#define SV_SHARESECURITY (Byte)(0)
#define SESS_GUEST (Byte)(1)
#define SESS_NOENCRYPTION (Byte)(2)
extern PACKAGE TNetServerEnum NetServerEnum;
extern PACKAGE TNetApiBufferFree NetApiBufferFree;
extern PACKAGE TNetUserEnum NetUserEnum;
extern PACKAGE TNetUserGetInfo NetUserGetInfo;
extern PACKAGE TNetQueryDisplayInformation NetQueryDisplayInformation;
extern PACKAGE TNetGetDisplayInformationIndex NetGetDisplayInformationIndex;
extern PACKAGE TNetGroupEnum NetGroupEnum;
extern PACKAGE TNetLocalGroupEnum NetLocalGroupEnum;
extern PACKAGE TNetUserGetGroups NetUserGetGroups;
extern PACKAGE TNetUserGetLocalGroups NetUserGetLocalGroups;
extern PACKAGE TNetLocalGroupAddMembers NetLocalGroupAddMembers;
extern PACKAGE TNetLocalGroupDelMembers NetLocalGroupDelMembers;
extern PACKAGE TNetGroupAddUser NetGroupAddUser;
extern PACKAGE TNetGroupDelUser NetGroupDelUser;
extern PACKAGE TNetLocalGroupAdd NetLocalGroupAdd;
extern PACKAGE TNetLocalGroupDel NetLocalGroupDel;
extern PACKAGE TNetGroupAdd NetGroupAdd;
extern PACKAGE TNetGroupDel NetGroupDel;
extern PACKAGE TNetUserSetInfo NetUserSetInfo;
extern PACKAGE TNetUserAdd NetUserAdd;
extern PACKAGE TNetUserDel NetUserDel;
extern PACKAGE TNetGroupGetUsers NetGroupGetUsers;
extern PACKAGE TNetLocalGroupGetMembers NetLocalGroupGetMembers;
extern PACKAGE TNetLocalGroupSetMembers NetLocalGroupSetMembers;
extern PACKAGE TNetGroupSetUsers NetGroupSetUsers;
extern PACKAGE TNetGroupGetInfo NetGroupGetInfo;
extern PACKAGE TNetGroupSetInfo NetGroupSetInfo;
extern PACKAGE TNetLocalGroupGetInfo NetLocalGroupGetInfo;
extern PACKAGE TNetLocalGroupSetInfo NetLocalGroupSetInfo;
extern PACKAGE TNetShareGetInfo NetShareGetInfo;
extern PACKAGE TNetShareSetInfo NetShareSetInfo;
extern PACKAGE TNetServerGetInfo NetServerGetInfo;
extern PACKAGE TNetSessionEnum NetSessionEnum;
extern PACKAGE TNetSessionDel NetSessionDel;
extern PACKAGE TNetFileEnum NetFileEnum;
extern PACKAGE TNetFileClose NetFileClose;
extern PACKAGE TNetShareAdd NetShareAdd;
extern PACKAGE TNetShareDel NetShareDel;
extern PACKAGE TNetShareEnum NetShareEnum;
extern PACKAGE TNetGetAnyDCName NetGetAnyDCName;
extern PACKAGE TNetGetDCName NetGetDCName;

}	/* namespace Netapi32 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Netapi32;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// NetApi32
