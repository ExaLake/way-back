/*	VAO.H - Visio 4.0 VSL Interface
 *  Copyright (C) 1991-1997 Visio Corporation. All rights reserved.
 *
 *	This file contains definitions that define the interface between
 *	Visio and VSLs. A VSL is a dynamic link library that implements
 *	the protocol defined herein. A VSL implements one or more Add-ons.
 *	Each Add-on has a name and implements some operation. An Add-on 
 *	can be invoked from Visio in several ways, e.g. by selecting it from 
 *	Visio's Run Add-ons dialog, or by associating it with the double 
 *	click action of a shape in a Visio drawing.
 *
 *	A Visio Add-on can also be developed as an executable file instead of
 *	in a VSL. In general the advantage of doing it as a VSL is that it will 
 *	run faster and integrate with Visio slightly more seamlessly. The 
 *	advantate of doing an Add-on as an exe is that VSLs can't be developed 
 *	using certain nice development environments such as Visual Basic.
 *
 *	A VSL can be written in C or in C++. It can be built for WIN16 or
 *	for WIN32. However Visio16 will only load WIN16 VSLs and Visio32 
 *	will only load WIN32 VSLs. 
 *
 *	Implementations for the methods protyped herein can be found in vao.c.
 *	The c-cpp directory shipped with Visio contains this vao.h file and
 *	vao.c. It also contains the source files for a sample VSL written in 
 *	C and a sample VSL written in C++. The source for these sample projects 
 *	is portable to either WIN16 or WIN32, but there are separate .mak files
 *	provided for building the WIN16 or WIN32 versions of the projects.
 */

#if !defined(_VAO_H)
#define _VAO_H

#ifndef _INC_WINDOWS
#include <windows.h>
#endif

#if !defined(RC_INVOKED)
	// Structs passed between visio and vsl defined to have no padding.
	#pragma pack(1)		 
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(LOADDS)
	#if defined(_WIN32)
		#define LOADDS
	#else
		#define LOADDS _loadds
	#endif
#endif

#if !defined(VAOU_PROC)
	#define VAOU_PROC(type)	type LOADDS PASCAL FAR
#endif

// Even though definitions in this interface are "C" definitions, we want
// it to be possible to embed structures defined as part of the interface
// within C++ objects. Since structs are really classes in C++, it is
// required that C++ know whether the "this" of the struct is near or
// far. Any struct defined as part of this interface that is declared
// using VAO_EMBEDDABLE_STRUCT can be embedded within a FAR C++ instance
// as well as being used as an ordinary C structure.
//
#if !defined(VAO_EMBEDDABLE_STRUCT)
	#if defined(__cplusplus)
		#define VAO_EMBEDDABLE_STRUCT typedef struct FAR
	#else
		#define VAO_EMBEDDABLE_STRUCT typedef struct
	#endif
#endif

// Version of the VSL inteface defined herein.
#define VAO_IFMAJOR ((WORD)2)		// Major interface version number.
#define VAO_IFMINOR ((WORD)3)		// Minor interface version number.

//---------------------------------------------------------------------------
//
//	EXPECTED ADD-ON LIBRARY ENTRY POINT
//	-----------------------------------
//
//	An Add-on library is expected to have an exported entry point of type
//	VAOFUNC whose name is LPVAOENTRYNAME. When Visio loads an Add-on library
//	it determines the address of the library's entry point by calling
//	GetProcAddress() on this name.
//
//---------------------------------------------------------------------------

#define LPVAOENTRYNAME ((LPSTR)"VisioLibMain")

typedef WORD VAORC, FAR* LPVAORC;	// Visio Add-on Return code.
typedef WORD VAOMSG, FAR* LPVAOMSG; // Visio Add-on Message code.

#if defined(_WIN32)
	#define VAOCB __cdecl
#else
	#define VAOCB LOADDS PASCAL FAR
#endif

typedef VAORC (VAOCB VAOFUNC) (VAOMSG,WORD,LPVOID);

typedef VAOFUNC *LPVAOFUNC;


// VAOV2LSTRUCT
// This structure is passed by Visio to a VSL's VisioLibMain() as an argument
// accompanying most messages. 
//
VAO_EMBEDDABLE_STRUCT
	{
	HINSTANCE	hVisInst;			// Handle to running Visio instance.
	LPVAOFUNC	lpfunc; 			// Call back address in Visio.
	WORD		wSessID;			// Id of session 

	LPVOID		lpArgs; 			// Pointer to session arguments.
									// Currently always null.
									
	LPSTR		lpCmdLineArgs;		// Analog of "cmd line args" passed to
									// an exe when it gets WinExec'd. 
									// Recipient shouldn't assume this is
									// non-null or depend on any particular
									// string to be passed to it.

	} VAOV2LSTRUCT, FAR* LPVAOV2LSTRUCT;

#define VAO_INV_SESSID ((WORD)0xFFFF)


// VAOREGSTRUCT
// This structure describes an Add-on implemented by a VSL. When Visio sends
// an V2LMSG_ENUMADDONS message to a VSL, the VSL responds by sending several
// L2VMSG_REGADDON messages back to Visio. The VSL passes a pointer to a 
// VAOREGSTRUCT along with each L2VMSG_REGADDON message.
//
// A VAOREGSTRUCT describes an Add-on to Visio. In particular, it specifies:
//
//	- The Add-on's ordinal. When Visio tells the library to run an Add-on
//	  it identifies which Add-on by specifying the Add-on's ordinal.
//	- Several attributes of the Add-on.
//	- The enabling policy the Add-on wants to use.
//	- the name of the Add-on.
//

// VAO_ORDINAL: Specifies an add-on's ordinal.
//
typedef WORD VAO_ORDINAL, FAR* LPVAO_ORDINAL;

#define VAO_INV_ORD (0) 			// The ordinal no valid Add-on can have.
									// We choose 0 for invalid id because
									// resources having id's equal to
									// to VAO_ORDINAL are quite likely and
									// resid's of 0 aren't cool.


// VAO_ATTS: Specifies an add-on's attributes in the form of a mask of
// zero or more VAO_AOATTS_xxx values.
//
typedef WORD VAO_ATTS, FAR* LPVAO_ATTS;

#define VAO_AOATTS_ISACTION	0x0001	// Add-on performs actions.
#define VAO_AOATTS_HASABOUT	0x0002	// Add-on supplies an about for itself
#define VAO_AOATTS_HASHELP	0x0004	// Add-on supplies help about itself.
#define VAO_AOATTS_WAITCRSR 0x0008	// Keep wait cursor up when Add-on runs.
#define VAO_AOATTS_DONTSHOW 0x0010	// Don't show addon in menus/dialogs.


// VAO_ENABMASK: Specifies an add-on's enabling policy. Value should be
// VAO_ENABLEALWAYS, VAO_ENABLEDYNAMIC or VAO_NEEDSxxx+[VAO_ENABLEDYNAMIC].
//
typedef WORD VAO_ENABMASK, FAR* LPVAO_ENABMASK;

#define VAO_ENABLEALWAYS	0xFFFF	// Add-on is always enabled.

#define VAO_ENABLEDYNAMIC	0		// Visio should query Add-on using
									// V2LMSG_ISAOENABLED when it wants to
									// know if Add-on is enabled. Add-on
									// should respond VAORC_L2V_ENABLED or 0.

#define VAO_ENABLEDYNAMICEX	0x8000	// If Add-on is still considered enabled
									// after VAO_NEEDSxxx has been checked,
									// Visio will send V2LMSG_ISAOENABLED
									// to Add-on. Add-on should respond
									// VAORC_L2V_ENABLED or 0.

// Semi-dynamic enabling masks. If an Add-on is registered with an enabling
// mask of e.g. VAO_NEEDSDOC then Visio will consider Add-on enabled only
// if state implied by mask is in effect (e.g. only if a document is open if
// mask is VAO_NEEDSDOC). Visio won't query a semi-dynamically enabled Add-on
// to see if it is enabled unless VAO_ENABLEDYNAMICEX also set. Bits are 
// negative, e.g. consider this add-on disabled if there is no target doc. 
// If none of negative condictions met, add-on will be considered enabled.
//
#define _VAO_ND 			0x0001	// Add-on needs a document.
#define _VAO_NW 			0x0002	// Add-on needs a window.
#define _VAO_NDrW			0x0004	// Add-on needs a draw window.
#define _VAO_NStW			0x0008	// Add-on needs a stencil window.
#define _VAO_NShW			0x0010	// Add-on needs a sheet window.
#define _VAO_NIcW			0x0020	// Add-on needs an icon window.
#define _VAO_NT				0x0040	// Add-on needs a target context.
#define _VAO_NPgT			0x0080	// Add-on needs target that is a page.
#define _VAO_NMsT			0x0100	// Add-on needs target that is a master.
#define _VAO_NS 			0x0200	// Add-on needs a selection.

#define VAO_NEEDSDOC		_VAO_ND
#define VAO_NEEDSDOCWND 	_VAO_ND|_VAO_NW
#define VAO_NEEDSDRAWWND	_VAO_ND|_VAO_NW|_VAO_NDrW
#define VAO_NEEDSPAGEWND	_VAO_ND|_VAO_NW|_VAO_NDrW|_VAO_NPgT
#define VAO_NEEDSMASTERWND	_VAO_ND|_VAO_NW|_VAO_NDrW|_VAO_NMsT
#define VAO_NEEDSSTENWND	_VAO_ND|_VAO_NW|_VAO_NStW
#define VAO_NEEDSSHEETWND	_VAO_ND|_VAO_NW|_VAO_NShW
#define VAO_NEEDSICONWND	_VAO_ND|_VAO_NW|_VAO_NIcW
#define VAO_NEEDSTARGET		_VAO_ND|_VAO_NT
#define VAO_NEEDSTARGPAGE	_VAO_ND|_VAO_NT|_VAO_NPgT
#define VAO_NEEDSTARGMASTER	_VAO_ND|_VAO_NT|_VAO_NMsT
#define VAO_NEEDSSELECTION	_VAO_ND|_VAO_NT|_VAO_NS

// VAO_INVOKEMASK: Specifies what events, if any, an Add-on wants to
// be automatically invoked on. Value should be mask of zero or more
// VAO_INVOKExxx values.
//
typedef WORD VAO_INVOKEMASK, FAR* LPVAO_INVOKEMASK;

#define VAO_INVOKE_LAUNCH	0x0001	// Invoke on Visio Launch. The vsl file
									// must reside in a directory that is
									// listed in Visio's startup path list
									// for this to have an effect.

typedef WORD VAO_NOTIFYMASK, FAR* LPVAO_NOTIFYMASK;

// This is the maximum add-on name length we'll allow an add-on name to
// have (not counting the null at its end). Names over 20 or so characters
// will be truncated when made visible by the UI, so names much longer
// than that aren't particularly useful anyway.
//
#define VAOMAXAONAME 100

VAO_EMBEDDABLE_STRUCT
	{
	VAO_ORDINAL		ord;			// Ordinal of Add-on. This should be
									// a value other than VAO_INV_ORD. Each
									// Add-on registered by a given Add-on
									// library should be assigned a distinct
									// ordinal.

	VAO_ATTS		atts;			// Attributes of Add-on.
	VAO_ENABMASK	enabMask;		// Add-on's enabling policy.
	VAO_INVOKEMASK	invokeOnMask;	// 
	VAO_NOTIFYMASK	notifyOnMask;	// 

	LPCTSTR			lpName;			// Add-on's name.
									//
									//	- Visio makes a copy of the name
									//	  hence the lib needn't keep memory
									//	  pointed to by lpName around.
									//
									//	- Name can be null or "", but it
									//	  won't show up in Run Add-on
									//	  dialog and analogous dialogs.
									//
									//	- If the name isn't null, Visio will
									//	  return an error if a given Add-on
									//	  lib registers more than one Add-on
									//	  with the same name.
									//
									//	- Visio assumes name is an ansi (as
									//	  opposed to an oem) string. This
									//	  makes a difference if the name
									//	  container e.g. accented characters.
	} VAOREGSTRUCT, FAR* LPVAOREGSTRUCT;


//---------------------------------------------------------------------------
//	MESSAGES THAT CROSS THE VISIO/ADD-ON LIBRARY INTERFACE
//---------------------------------------------------------------------------


#define _VAOGEN_INVBASE	(0x0000)	// First invariant generic message/rc
#define _VAOGEN_SENBASE	(0x1000)	// First int sensitive generic message/rc

#define _V2L_INVBASE	(0x2000)	// First invariant v2l message/rc
#define _V2L_SENBASE	(0x3000)	// First int sensitive v2l message/rc

#define _L2V_INVBASE	(0x4000)	// First invariant l2v message/rc
#define _L2V_SENBASE	(0x5000)	// First int sensitive l2v message/rc

//---------------------------------------------------------------------------
//
//	MESSAGES THAT CROSS THE VISIO/ADD-ON LIBRARY INTERFACE
//	------------------------------------------------------
//
//	The "V2L" messages below are messages that Visio passes to an Add-on
//	library. The "L2V" messages are messages a library passes to Visio.
//
//	The receiver of a message should respond by returning a VAORC (Visio
//	Add-on Return Code) to the message sender. The return codes defined as
//	part of this interface are given later in this file.
//
//	Passed with each message are two parameters, a WORD and an LPVOID. In
//	many cases the LPVOID should point to a structure whose type is a function
//	of the message being sent. Definitions of the various message related
//	structures are given later in this file. Depending on the message, fields
//	in a message structure may be set by the sender or the receiver of the
//	message. In all cases the sender of the message is to be construed as
//	the owner of the memory allocated for the message structure.
//
//	Discussion of individual messages can be found later in this file.
//
//---------------------------------------------------------------------------

typedef enum
	{
	INVALID_VAOMSG			= _VAOGEN_INVBASE,	// The code no msg can have.

	// Messages that Visio sends to a VSL:
	V2LMSG_LOAD				= _V2L_INVBASE,
	V2LMSG_UNLOAD,
	V2LMSG_ENUMADDONS		= _V2L_SENBASE,
	V2LMSG_ISAOENABLED,
	V2LMSG_RUN,
	V2LMSG_RUNABOUT,
	V2LMSG_RUNHELP,
	V2LMSG_KILLSESSION,
	_V2LMSG_FIRSTFREE,

	// Messages that a VSL sends to Visio:
	L2VMSG_AVAILCALLS		= _L2V_INVBASE,	// Not for external use.
	L2VMSG_REGADDON			= _L2V_SENBASE,
	L2VMSG_UNREGADDON,
	L2VMSG_ISAOENABLED,
	L2VMSG_ISCMDENABLED,			// Not for external use.
	L2VMSG_ENABLEMENU_obsolete,		// Consume id for backwards compatibility.
	L2VMSG_ISCMDQUERY_obsolete,		// Consume id for backwards compatibility.
	L2VMSG_GETARGSIZE,				// Not for external use.
	L2VMSG_AVAILMODES_obsolete,		// Consume id for backwards compatibility.
	L2VMSG_EXECUTE,					// Not for external use.
	L2VMSG_ENUMDOCS_obsolete,		// Consume id for backwards compatibility.
	L2VMSG_ENUMCONS_obsolete,		// Consume id for backwards compatibility.
	L2VMSG_ENUMSHEETS_obsolete,		// Consume id for backwards compatibility.
	L2VMSG_SESSIONDONE,
	L2VMSG_PROMPTUSER_obsolete,		// Consume id for backwards compatibility.
	L2VMSG_DBL2ASCII_obsolete,		// Consume id for backwards compatibility.
	L2VMSG_ASCII2DBL_obsolete,		// Consume id for backwards compatibility.
	L2VMSG_GETAPPINFO_obsolete,		// Consume id for backwards compatibility.
	L2VMSG_DEBUGMSG_obsolete,		// Consume id for backwards compatibility.

	// --values below here were added to Visio 4.0--
	L2VMSG_BINDDATA,	
	L2VMSG_BOUNDDATA,	

	_L2VMSG_FIRSTFREE,

	} VAOMSG_ENUM, FAR* LPVAOMSG_ENUM;


// --------------------
// GENERIC RETURN CODES
// --------------------

#define VAORC_SUCCESS			(_VAOGEN_INVBASE+0)
											// ASSERT(VAORC_SUCCESS==0);

#define VAORC_FAILURE			(_VAOGEN_SENBASE+0)

#define VAORC_L2V_LOADFAILED	(_L2V_INVBASE+0)
								// Prescribed error response to V2LMSG_LOAD.

#define VAORC_L2V_ENABLED		(_L2V_SENBASE+0)
								// True response by lib to V2LMSG_ISAOENABLED
								// query. (False response should be 0.)

#define VAORC_L2V_MODELESS		(_L2V_SENBASE+1)
								// Prescribed lib response to V2LMSG_RUNxxx
								// meaining session persists.

#define VAORC_L2V_GOTNOABOUT	(_L2V_SENBASE+2)
								// Prescribed lib response to V2LMSG_RUNABOUT
								// meaining lib didn't respond to Visio's
								// request. Visio will respond by displaying
								// a very generic about box. Note that Visio
								// will only send V2LMSG_RUNABOUT to Add-ons
								// that declare VAO_AOATTS_HASABOUT in their
								// registration structure. So Add-ons that
								// really don't provide about should say so
								// when registering.

#define VAORC_L2V_GOTNOHELP		(_L2V_SENBASE+3)
								// Prescribed lib response to V2LMSG_RUNHELP
								// meaining lib didn't respond to Visio's
								// request. Visio will respond by displaying
								// very generic. Note that Visio will only
								// send V2LMSG_RUNHELP to Add-ons that
								// declare VAO_AOATTS_HASHELP in their
								// registration structure. So Add-ons that
								// really don't provide help should say so
								// when registering.
								
#define VAORC_L2V_BADMSG		(_L2V_SENBASE+5)
								// Lib returns this if sent illegal message.


//---------------------------------------------------------------------------
//
//	INDIVIDUAL MESSAGE DESCRIPTIONS:
//	-------------------------------
//
//	Messages sent from Visio to library
//	-----------------------------------
//
//	wmsg				wparam			lparam			return
//	----				------			------			------


//	V2LMSG_LOAD			Visio Version	LPVAOFUNC		VAO_L2V_VERSION() |
//														VAORC_L2V_LOADFAILED
//
//
//		Visio sends V2LMSG_LOAD to an Add-on library right after it has
//		done LoadLibrary() and GetProcAddress(LPVAOENTRYNAME) on the library.
//
//		The value of the wparam passed with V2LMSG_LOAD indicates the Add-on
//		interface version being used by the sending Visio. Typically the
//		receiving library shouldn't care. However, if it so chooses, it can
//		refuse to load itself based on the version of Visio it is running
//		with. WParam packs the major and minor interface version numbers
//		being used by Visio in the same fashion as described below for
//		VAO_L2V_VERSION(). [See (*) below.]
//
//		The value of the lparam passed	with V2LMSG_LOAD is a pointer to the
//		procedure in Visio the library is to call when it wants to make calls
//		back into Visio later.
//
//		Visio expects a response of VAO_L2V_VERSION() to V2LMSG_LOAD unless
//		the library fails to initialize itself. If initialization fails, the
//		response should be VAORC_L2V_LOADFAILED, in which case Visio will
//		perform an immediate FreeLibrary() and send the lib no more messages.
//
//		Note: This value should never have _L2V_INVBASE bit set in it!
//		That way we can always distinguish it from VAORC_L2V_LOADFAILED.
//
		#define VAO_L2V_VERSION() ((VAORC)( (VAO_IFMAJOR<<8) | VAO_IFMINOR ))
//
//		Visio disables library call backs when it sends V2LMSG_LOAD.
//
//		Note that a Visio INSTANCE will send V2LMSG_LOAD when it loads an
//		Add-on library. Thus a library may receive V2LMSG_LOAD multiple
//		times without receiving intervening V2LMSG_UNLOADs if multiple Visio
//		instances are running. Thus a library wanting to perform instance
//		independent initialization can take one of several tacks:
//
//		option1:	Do instance independent initialization in its LibMain().
//		option2:	Keep a global load count around that's initialized to 0,
//					incremented when V2LMSG_LOAD is received and decremented
//					when V2LMSG_UNLOAD is received. Instance Instance
//					independent initialization should then occur when
//					V2LMSG_LOAD is received and the load count is 0. Services
//					implementing this option are available in vlibutils.h/c.
//
//		(*): Visio 2.0, which implemented version 2.1 of the Add-on interface,
//		passed wparam as VAO_INV_SESSID. Versions of Visio that implement
//		version 2.2 or later of the Add-on interface pass the interface
//		version they are using in wparam as described above.
//
		#define _21VISIO VAO_INV_SESSID


//	V2LMSG_UNLOAD		undefined		NULL			moot
//
//		Visio sends V2LMSG_UNLOAD to an Add-on library right before it is
//		about to do a FreeLibrary() on the library (probably because it is
//		quitting). The library has no choice in this matter, V2LMSG_UNLOAD
//		doesn't allow the library to respond that it doesn't want to be
//		unloaded. The result a library returns in response to V2LMSG_UNLOAD
//		is really moot (but VAORC_SUCCESS is suggested).
//
//		Note that Visio doing a FreeLibrary() doesn't necessarily imply the
//		library is really about to be unloaded. Windows will decrement the
//		library's use count when Visio does the FreeLibrary() and actually
//		unload the library only if the use count decrements to zero. The use
//		count may still be non-zero if multiple instances of Visio have loaded
//		the library. If the library has instance independent cleanup that it
//		only wants to perform when it is really going to be unloaded, it can
//		put the cleanup in its WEP() procedure or maintain a use count as
//		described above in the V2LMSG_LOAD discussion.
//
//		Visio disables library call backs when it sends V2LMSG_UNLOAD.
//
//		Note that Visio will never send V2LMSG_UNLOAD to a library that has
//		modeless sessions in progress (see V2LMSG_RUN). Rather, it will send
//		V2LMSG_KILLSESSIONs until no sessions remain, then send V2LMSG_UNLOAD.


//	V2LMSG_ENUMADDONS	0				LPVAOV2LSTRUCT	VAORC
//
//		Visio sends V2LMSG_ENUMADDONS to a library when it is requesting
//		the library to enumerate its Add-ons. Typically a library will respond
//		by sending L2VMSG_REGADDON messages back to Visio.
//
//		The VAOV2LSTRUCT pointed to by lparam specifies information the
//		library will need in order to make calls back into Visio.
//
//		If the result returned by the library in response to V2LMSG_ENUMADDONS
//		isn't VAORC_SUCCESS, Visio will send an immediate V2LMSG_UNLOAD and
//		not deal further with the library. If some but not all of a library's
//		Add-ons register successfully and if the library wishes to continue,
//		it should respond VAORC_SUCCESS to V2LMSG_ENUMADDONS.


//	V2LMSG_ISAOENABLED	i				LPVAOV2LSTRUCT	VAORC_L2V_ENABLED | 0
//
//		Visio sends V2LMSG_ISAOENABLED to a library when it is requesting
//		the library to indicate whether the Add-on whose ordinal is passed
//		in wparam is enabled or not. Visio will only send this message if
//		the targeted Add-on was registered as having an enabling policy of
//		VAO_ENABLEDYNAMIC or VAO_ENABLEDYNAMICEX. In the latter case message
//		will only be sent if static tests indicate Add-on potentially enabled.
//
//		The library should respond VAORC_L2V_ENABLED or 0.
//
//		The VAOV2LSTRUCT pointed to by lparam specifies information the
//		library will need in order to make calls back into Visio.


//	V2LMSG_RUN			i				LPVAOV2LSTRUCT	VAORC_SUCCESS |
//														VAORC_L2V_MODELESS |
//														VAORC_SomeError
//
//		Visio sends V2LMSG_RUN to a library when it is requesting the library
//		to run the Add-on whose ordinal is passed in wparam. Visio will only
//		send this message if the targeted Add-on has been deemed currently
//		enabled according to the enabling policy declared for it when it was
//		registered.
//
//		The VAOV2LSTRUCT pointed to by lparam specifies information the
//		library will need in order to make calls back into Visio.
//
//		If the invoked Add-on completes whatever operation it performs in
//		response to V2LMSG_RUN, then VAORC_SUCCESS or VAORC_SomeError should
//		be returned by the library to Visio in response to the message.
//
//		If the Add-on initiated some modeless activity in response to the
//		V2LMSG_RUN (e.g. opened a window), then VAORC_L2V_MODELESS should
//		be returned in response to the message. Such a modeless session will
//		persist until the library sends L2VMSG_SESSIONDONE to Visio, or until
//		Visio sends V2LMSG_KILLSESSION to the library. Visio won't send
//		V2LMSG_UNLOAD to a library that has modeless sessions in progress.


//	V2LMSG_RUNABOUT		i				LPVAOV2LSTRUCT	VAORC_SUCCESS |
//														VAORC_L2V_MODELESS |
//														VAORC_SomeError
//
//		Visio sends V2LMSG_RUNABOUT to a library when it is requesting the
//		library to invoke "about" for the the Add-on whose ordinal is passed
//		in wparam. Visio will only send this message if the targeted Add-on
//		was declared to provide "about" when it was registered.
//
//		The VAOV2LSTRUCT pointed to by lparam specifies information the
//		library will need in order to make calls back into Visio.
//
//		The result Visio expects a library to return in response to
//		V2LMSG_RUNABOUT is exactly as described for V2LMSG_RUN.


//	V2LMSG_RUNHELP		i				LPVAOV2LSTRUCT	VAORC_SUCCESS |
//														VAORC_L2V_MODELESS |
//														VAORC_SomeError
//
//		Visio sends V2LMSG_RUNHELP to a library when it is requesting the
//		library to invoke help for the the Add-on whose ordinal is passed
//		in wparam. Visio will only send this message if the targeted Add-on
//		was declared to provide help when it was registered.
//
//		The VAOV2LSTRUCT pointed to by lparam specifies information the
//		library will need in order to make calls back into Visio.
//
//		The result Visio expects a library to return in response to
//		V2LMSG_RUNHELP is exactly as described for V2LMSG_RUN.


//	V2LMSG_KILLSESSION	0				LPVAOV2LSTRUCT	VAORC (ignored)
//
//		Visio sends V2LMSG_KILLSESSION to a library when it is mandating that
//		a session that an in progress session be terminated. The library can't
//		refuse this request.
//
//		The session to be terminated is identified in the VAOV2LSTRUCT
//		pointed to by lparam.
//
//		When it sends V2LMSG_KILLSESSION, the only call backs Visio enables
//		are the so called "shutdown" call backs.
//
//		Typically this message will be sent to a session that previously
//		"went modeless." See V2LMSG_RUN description above. However, in rare
//		cases it may also be sent to an uncompleted modal session, e.g.
//		session invokes app modal dialog, user switches to program manager,
//		then exits Windows.


//	Messages sent from library to Visio
//	-----------------------------------
//
//	When an Add-on library sends a message to Visio (really meaning it makes
//	a call back into Visio), it must always pass as wparam the id associated
//	with the session doing the calling. This id is passed by Visio to the
//	library in the LPVAOV2LSTRUCT passed as lparam on most messages sent
//	from Visio to an Add-on library, specifically in lpvaov2lstruct->wSessID.
//	The address of the procedure in Visio the library is to call is passed
//	in lpvaov2lstruct->lpfunc.
//
//	---WIN16 ONLY---
//	Note that several instances of Visio may be running at once. Although
//	chances are small that it will happen, there is no guarantee that
//	distinct instances won't invoke a session with the same id. Thus a
//	session is really keyed by (hVisInst,wSessID), both of which are passed
//	with the VAOV2LSTRUCTs passed to the lib when Visio starts a session.
//	When you pass wSessID back to Visio you're implicitly identifying the
//	session with id wSessID that belongs to the currently running Visio
//	instance. Keep this in mind if your lib keeps session specific data
//	structures. 
//
//	---WIN32 ONLY---
//	Above discussion is slightly different in win32. In the event that
//	several Visio's are running, many "instances" of a library are loaded,
//	unlike the win16 case where one instance gets loaded that is driven by
//	the many Visio instances. Thus a win32 library always thinks it is 
//	running with a lone instance of Visio. This typically makes things 
//	easier for a win32 library that wants to maintain session specific data
//	structures. It needn't take app instance into account as a component of
//	the key. 
//
//	wmsg				wparam			lparam			return
//	----				------			------			------

//	L2VMSG_REGADDON		wSessID 		LPVAOREGSTRUCT	VAORC
//
//		L2VMSG_REGADDON tells Visio to register an Add-on implemented by
//		an Add-on library. The Add-on is described by the VAOREGSTRUCT
//		pointed to by lparam. The library should fill out the VAOREGSTRUCT
//		prior to sending L2VMSG_REGADDON.
//
//		Typically a library sends L2VMSG_REGADDON in response to receiving
//		V2LMSG_ENUMADDONS from Visio. However, V2LMSG_ENUMADDONS can be sent
//		at other times if a library finds occasion for doing so.


//	L2VMSG_UNREGADDON	wSessID 		LPVAOREGSTRUCT	VAORC
//
//		L2VMSG_UNREGADDON tells Visio to unregister an Add-on that was
//		previously registered. The VAOREGSTRUCT pointed to by lparam says
//		which Add-on to unregister. Only the ordinal of the Add-on needs to
//		be specified in the VAOREGSTRUCT.


//	L2VMSG_ISAOENABLED	wSessID 		LPVAOREGSTRUCT	VAORC_V2L_ENABLED | 0
//
//		L2VMSG_ISAOENABLED passes a VAOREGSTRUCT in which an Add-on enabling
//		policy is specified to Visio and Visio returns whether the policy
//		evaluates at the moment to enabled or disabled. The VAOREGSTRUCT may
//		be the registration structure for an actual Add-on, but that need
//		not be the case. Only the enabling policy field of the VAOREGSTRUCT
//		needs to be filled out. Visio ignores the other VAOREGSTRUCT fields.
//		If the specified policy is VAO_ENABLEDYNAMIC (i.e. the library
//		evaluates the enabledness of an add-on) then Visio will return 0,
//		otherwise it will use the same logic it uses to determine whether
//		a statically enabled Add-on with the specified enabling policy is
//		enabled or not. Visio returns VAORC_V2L_ENABLED or 0.


//	L2VMSG_SESSIONDONE	wSessID 		NULL			VAORC
//
//		A library sends L2VMSG_SESSIONDONE to Visio when it wants to end
//		on its own volition a session that previously "went modeless" (see
//		V2LMSG_RUN description).
//
//		L2VMSG_SESSIONDONE might be used e.g. if the library opened a window
//		in response to V2LMSG_RUN. When the user closes the window, the
//		library would send L2VMSG_SESSIONDONE to Visio. Note that if Visio
//		wants a library to end a modeless session, e.g. when it's quitting,
//		then it will send V2LMSG_KILLSESSION to the library. A library can
//		respond to V2LMSG_KILLSESSION by sending L2VMSG_SESSIONDONE, but it
//		need not do so.


//	L2VMSG_BINDDATA		wSessID 		LPVOID			VAORC
//
//		A library sends L2VMSG_BINDDATA to Visio when it wants to associate
//		an arbitrary pointer with a session. The pointer can be retrieved 
//		later using L2VMSG_BOUNDDATA.


//	L2VMSG_BOUNDDATA	wSessID 		LPVOID FAR*		VAORC
//
//		A library sends L2VMSG_BOUNDDATA to Visio to retrieve the pointer 
//		that was most recently bound to the session via L2VMSG_BINDDATA.
//		Null is returned if L2VMSG_BINDDATA has never been invoked on 
//		the session.



// The implementations for the following few methods can be found in vao.c.
// VAOUtil_DefVisMainProc() provides default handling for a message sent from
// Visio to a VSL's VisioLibMain proc. You can see an example of its use in
// lib.c. VAOUtil_SetVisCallBack() need only be called if you decide not to 
// let VAOUtil_DefVisMainProc() handle the V2LMSG_LOAD message from Visio. 
// VAOUtil_VisCallBack() provides the address of the proc in Visio that a VSL
// is to call in order to send messages to. You'll probably find little reason
// to use it. VAOUtil_RegisterAddons() is used by a VSL to register its Add-ons
// with Visio. See lib.c for an example of its use. VAOUtil_SendEndSession() is 
// to be called by a "modeless" session when it wants to end itself. 
//
VAOU_PROC(VAORC) VAOUtil_DefVisMainProc ( VAOMSG	wMsg,
									  	  WORD		wParam,
									  	  LPVOID	lpParam,
									  	  HINSTANCE	hResources );


VAOU_PROC(VOID)	VAOUtil_SetVisCallBack	( LPVAOFUNC lpfunc );


VAOU_PROC(LPVAOFUNC) VAOUtil_VisCallBack ( void );


#if !defined(_WIN32)
VAOU_PROC(HINSTANCE) VAOUtil_hAppInst ( void );
#endif


VAOU_PROC(VAORC) VAOUtil_RegisterAddons ( WORD			 wSessID,
									  	  LPVAOREGSTRUCT lpRegStructArray,
									  	  WORD			 nRegStructs );

#define VAOUtil_SendEndSession(wSessID) 									\
			((*((LPVAOFUNC)(VAOUtil_VisCallBack())))						\
										(L2VMSG_SESSIONDONE,				\
									  	(wSessID),							\
									  	(LPVOID)NULL))

// gbl_hDLLModule is the instance handle for the dll this code is running
// in. It gets set by LibMain() or DllMain() when this dll gets loaded. 
//
extern HINSTANCE gbl_hDLLModule;

#define VLIBUTL_hModule() gbl_hDLLModule

#if !defined(RC_INVOKED)
	// Resume to using default struct packing.
	#pragma pack()
#endif

#define VAOEXPORT __declspec(dllexport)

#ifdef __BORLANDC__
#define UNUSED_ARG(x) if (x) { }
#else
#define UNUSED_ARG(x)
#endif

#if defined(__cplusplus)
	}	/* End of extern "C" { */
#endif

#endif /* _VAO_H */
