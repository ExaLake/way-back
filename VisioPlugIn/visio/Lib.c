/*	LIB.C - Source for Visio VSL Entry Point
 *  Copyright (C) 1991-1996 Visio Corporation. All rights reserved.
 *
 *
 *	Abstract
 *		Provides the entry point for a Visio VSL.  Implements one add-on as
 *		a demonstration of how C/C++ Automation add-ons can be run in-proc
 *		to Visio.
 *
 *	Routines:
 *
 *	VisioLibMain    Entry point that Visio calls.
 *
 */

/*	The only include dependency that is required by a VSL
 *	is vao.h. Note that vao.h depends on types defined
 *	defined in windows.h which it automatically includes
 *	if necessary.
 */

#include "vao.h"                                // Visio Add-ons interface

#define VAOEXPORT __declspec(dllexport)

/*
 *	ADD-ON DESCRIPTORS
 *
 *	This is the information needed to describe hello's Add-ons to Visio.
 *	This info is packed into an Add-on registration structure that gets
 *	sent to Visio when Visio asks this library to enumerate its Add-ons.
 */

enum AddOnIndexes
{
	IDX_DEMO                        = 1,
};


// Name shown in Visio's "run Add-on" dialog.
#ifdef _DEBUG
#define ADDON_NAME "VSL Automation Demo - DEBUG"
#else
#define ADDON_NAME "VSL Automation Demo"
#endif


static VAOREGSTRUCT stc_myAddons[] =
{
	{
	IDX_DEMO,					// Ordinal of Add-on
	VAO_AOATTS_ISACTION | VAO_AOATTS_HASABOUT | VAO_AOATTS_WAITCRSR,
	VAO_ENABLEALWAYS,			// It is is always enabled.
	0,
	0,
	ADDON_NAME,
    },
};

//
//	FUNCTION:	VisioLibMain(VAOMSG,WORD,LPVOID)
//
//	PURPOSE:	VisioLibMain() implements the Visio/Add-on protocol defined
//				in vao.h. When Visio loads this library, it will do a 
//				GetProcAddress(VisioLibMain) and then start calling
//				VisioLibMain() at appropriate times.
//
//				When Visio calls VisioLibMain(), it will pass a directive
//				(wMsg) to VisioLibMain() indicating what is to be done.
//				Associated with the message will be a word argument and a
//				far pointer argument. The meaning of these is dependent on
//				wMsg.
//
//				This sample Add-on library is pretty simple. For most types
//				of messages that Visio can pass to it, VisioLibMain() can
//				simply call the Visio Add-on utility that provides default
//				responses to Visio messages, namely VAOUtil_DefVisMainProc().
//
//				The only messages that generic.vsl's VisioLibMain() must
//				respond to are those that implement behavior specific to
//				generic.vsl. Generic.vsl must register those Add-ons it
//				implements, and it must be able to run the Add-ons it
//				implements. Running "VSL Automation Demo" entails calling
//				RunDemo and simple returning when it's done.
//

VAOEXPORT VAORC VAOCB VisioLibMain ( VAOMSG wMsg, WORD wParam, LPVOID lpParam )
	{
	VAORC result = VAORC_SUCCESS;

	switch ( wMsg )
		{
		case V2LMSG_ENUMADDONS:
			{
			// wParam:      0
			// lpParam: LPVAOV2LSTRUCT
			//
			// Visio is telling us to register this library's Add-ons.
			// The Visio Add-on utility VAOUtil_RegisterAddons() will
			// do this for us if we pass it a pointer to descriptors
			// for this lib's Add-ons, namely stc_myAddons which was
			// declared above.
			//
			result = VAOUtil_RegisterAddons(
							((LPVAOV2LSTRUCT)lpParam)->wSessID,
							stc_myAddons,
							sizeof(stc_myAddons)/sizeof(VAOREGSTRUCT));
			break;
			}

		case V2LMSG_RUN:
			{
			// wParam:      Ordinal of Add-on to run
			// lpParam: LPVAOV2LSTRUCT
			//
			// Visio is telling us to run the Add-on with the given ordinal.
			// In the case of ordinal 1, we want to run the automation demo.
			//

			int RunDemo(void);
			
			switch ( wParam )
				{
				case IDX_DEMO:
					RunDemo();
					break;
				default:
					/* Unknown Add-on ordinal passed */
					break;
				}
				
			break;
			}

		case V2LMSG_RUNABOUT:
			{
			// wParam:      Ordinal of Add-on
			// lpParam: 
			//
			// Visio is telling us to run the Add-ons about dialog.
			// In the case of ordinal 1, we want to run the automation demo.
			//

			int ShowAboutDialog(HINSTANCE);
			
			switch ( wParam )
				{
				case IDX_DEMO:
					ShowAboutDialog(VLIBUTL_hModule());
					break;
				default:
					/* Unknown Add-on ordinal passed */
					break;
				}
				
			break;
			}

		default:
			result = VAOUtil_DefVisMainProc(wMsg, wParam,
											lpParam, VLIBUTL_hModule());
			break;
		};

	return result;
	}
