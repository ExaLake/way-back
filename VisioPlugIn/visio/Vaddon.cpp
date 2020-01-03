/*	VADDON.CPP - Source for Visio VSL Entry Point
 *  Copyright (C) 1996-1997 Visio Corporation. All rights reserved.
 *
 *	Abstract
 *		Provides the entry point for a Visio VSL.
 *		Also provides an addon 'manager' superclass;
 *		derive classes from VAddon and we'll take
 *		care of the rest!
 *
 *	Routines:
 *		VisioLibMain    Entry point that Visio calls.
 *		VAddon::FindAddon
 *		VAddon::GetFirst
 *		VAddon::GetNext
 *		Default implementations of all VAddon methods but Run.
 */

//	Important NOTE:
//	If you build this source file into an EXE (rather than a VSL/DLL)
//	then be sure to #define VADDON_EXE on the compiler command line.

//	If you're using MFC, be sure VADDON_MFC gets defined.
//	_USRDLL is the criterion we're using to "decide" if you're
//	using MFC -- if you're using it, but don't have _USRDLL defined
//	then define VADDON_MFC on the command line.

#ifdef _USRDLL
#define VADDON_MFC
#endif

#ifdef VADDON_MFC
#include "stdafx.h"
#endif

#include "vaddon.h"



//	Only compile in the exported entry point VisioLibMain
//	if NOT being built into an EXE:

#ifndef VADDON_EXE

extern "C" {

VAOEXPORT VAORC VAOCB VisioLibMain(VAOMSG wMsg, WORD wParam, LPVOID lpParam)
	{
	VAORC result;

#ifdef VADDON_MFC
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
#endif

	result= VAORC_SUCCESS;

	switch (wMsg)
		{
		case V2LMSG_ENUMADDONS:
			{
			VAddon *pAddon= VAddon::GetFirst();

			while (NULL!=pAddon && VAORC_SUCCESS==result)
				{
				result= VAOUtil_RegisterAddons(
								((LPVAOV2LSTRUCT)lpParam)->wSessID,
								pAddon->GetRegStructPtr(),
								1);

				pAddon= VAddon::GetNext(pAddon);
				}

			break;
			}

		case V2LMSG_ISAOENABLED:
			{
			VAddon *pAddon= VAddon::FindAddon(wParam);

			if (pAddon)
				result= pAddon->IsEnabled((LPVAOV2LSTRUCT)lpParam);

			break;
			}

		case V2LMSG_RUN:
			{
			VAddon *pAddon= VAddon::FindAddon(wParam);

			if (pAddon)
				result= pAddon->Run((LPVAOV2LSTRUCT)lpParam);

			break;
			}

		case V2LMSG_RUNABOUT:
			{
			VAddon *pAddon= VAddon::FindAddon(wParam);

			if (pAddon)
				result= pAddon->About((LPVAOV2LSTRUCT)lpParam);

			break;
			}

		case V2LMSG_RUNHELP:
			{
			VAddon *pAddon= VAddon::FindAddon(wParam);

			if (pAddon)
				result= pAddon->Help((LPVAOV2LSTRUCT)lpParam);

			break;
			}

		case V2LMSG_LOAD:
			{
			VAddon *pAddon= VAddon::GetFirst();

			result= VAO_L2V_VERSION();

			while (NULL!=pAddon && VAO_L2V_VERSION()==result)
				{
				result= pAddon->Load(wParam, lpParam);

				pAddon= VAddon::GetNext(pAddon);
				}

			break;
			}

		case V2LMSG_UNLOAD:
			{
			VAddon *pAddon= VAddon::GetFirst();

			while (NULL!=pAddon && VAORC_SUCCESS==result)
				{
				result= pAddon->Unload(wParam, lpParam);

				pAddon= VAddon::GetNext(pAddon);
				}

			break;
			}

		case V2LMSG_KILLSESSION:
			{
			//	Since we don't know which VAddon instance is being
			//	told to kill its session, because wParam is 0 for
			//	V2LMSG_KILLSESSION, loop through all instances to
			//	give each one a chance to clean up after itself.
			//
			//	(A VAddon subclass would "know" if it were in a session
			//	 or not by remembering the wSessID from the Run method
			//	 in which it returned VAORC_L2V_MODELESS to Visio.)

			VAddon *pAddon= VAddon::GetFirst();

			while (NULL!=pAddon)
				{
				pAddon->KillSession((LPVAOV2LSTRUCT)lpParam);

				pAddon= VAddon::GetNext(pAddon);
				}

			//	result= VAORC_SUCCESS...
			//	...already assigned before entering switch statement

			break;
			}

		default:
			{
			result= VAOUtil_DefVisMainProc(wMsg, wParam, lpParam, VLIBUTL_hModule());
			break;
			}
		}

	return result;
	}

}	//	end extern "C"

#endif	//	VADDON_EXE


//****************************************************************************
//
//	Class VAddon implementation:
//

VAddon *VAddon::m_pFirst= NULL;
VAddon *VAddon::m_pLast= NULL;
WORD VAddon::m_wNextIndex= 1;
HINSTANCE VAddon::m_hInstance= NULL;



VAddon::VAddon(
		//	VAO_ORDINAL assigned automagically by this base class...
		VAO_ATTS atts,				// Attributes
		VAO_ENABMASK enabMask,		// Enabling policy
		VAO_INVOKEMASK invokeOnMask,
		VAO_NOTIFYMASK notifyOnMask,
		LPCTSTR lpName,
		UINT uIDName /* = INVALID_RESOURCE_ID */)
{
	//	Initialize beginning of linked list:
	if (NULL==m_pFirst)
		m_pFirst= this;

	//	Tack onto end of linked list:
	if (NULL!=m_pLast)
		m_pLast->m_pNext= this;

	m_pLast= this;
	m_pNext= NULL;

	//	Assign ordinal:
	m_wIndex= m_wNextIndex;
	m_wNextIndex++;

	//	Setup name:
	m_pName[0]= (TCHAR) 0;
	if (NULL!=lpName)
	{
		_tcsncpy(m_pName, lpName, sizeof(m_pName)-1);
		m_pName[sizeof(m_pName)-1]= (TCHAR) 0;
	}

#ifdef _DEBUG
	//	Append to the DEBUG version so it shows up differently in Visio's UI:
	if ( _tcslen(m_pName) < (VAOMAXAONAME - _tcslen(_T(" - DEBUG")) - 1) )
	{
		_tcscat(m_pName, _T(" - DEBUG"));
	}
#endif

	//	Fill in reg struct:
	m_reg.ord= m_wIndex;
	m_reg.atts= atts;
	m_reg.enabMask= enabMask;
	m_reg.invokeOnMask= invokeOnMask;
	m_reg.notifyOnMask= notifyOnMask;
	m_reg.lpName= (LPCTSTR) m_pName;

	//	If this is not INVALID_RESOURCE_ID, then we'll attempt a
	//	LoadString in the "Load" method to replace the name with:
	m_uIDName= uIDName;
}

VAddon::~VAddon()
{

}

VAOREGSTRUCT *VAddon::GetRegStructPtr(void)
{
	return &m_reg;
}

/* static */ VAddon *VAddon::FindAddon(WORD wOrdinal)
{
	//	returns VAddon with m_wIndex==wOrdinal, or NULL if not in list...
	VAddon *pFound= GetFirst();

	while (pFound!=NULL && pFound->m_wIndex!=wOrdinal)
	{
		pFound= GetNext(pFound);
	}

	return pFound;
}

/* static */ VAddon *VAddon::GetFirst(void)
{
	return m_pFirst;
}

/* static */ VAddon *VAddon::GetNext(VAddon *pCurrent)
{
	//	returns NULL when no more...

	if (pCurrent)
		return pCurrent->m_pNext;

	return NULL;
}

/* static */ void VAddon::SetInstance(HINSTANCE hInstance)
{
	//	Call this once from WinMain or InitInstance:
	m_hInstance= hInstance;
}

HINSTANCE VAddon::GetInstance(long nFlags /*= 0L*/)
{
	//	If you DON'T use MFC
	//		AND
	//	you've written your own DllMain or WinMain,
	//	forsaking all our example code, then....

	//	...You should override this function in your
	//	add-ons to provide an HINSTANCE to your
	//	DLL or EXE.

	UNUSED_ARG(nFlags);

#ifdef VADDON_MFC

	//	Use MFC's built-in function.
	return AfxGetInstanceHandle();

#else

	//	Return private data set by our own
	//	DllMain or WinMain...

	#ifdef VADDON_EXE
		return m_hInstance;
	#else
		return VLIBUTL_hModule();
	#endif

#endif
}


//****************************************************************************
//
//	Messages we have to respond to:
//

VAORC VAddon::IsEnabled(LPVAOV2LSTRUCT pV2L)
{
	UNUSED_ARG(pV2L);
	return VAORC_L2V_ENABLED;
}

//	No implementation at this abstract level...
//	MUST be overridden
//VAORC VAddon::Run(LPVAOV2LSTRUCT pV2L)
//{
//	return VAORC_SUCCESS;
//}

VAORC VAddon::About(LPVAOV2LSTRUCT pV2L)
{
	//	No-op at this abstract level...
	UNUSED_ARG(pV2L);
	return VAORC_SUCCESS;
}

VAORC VAddon::Help(LPVAOV2LSTRUCT pV2L)
{
	//	No-op at this abstract level...
	UNUSED_ARG(pV2L);
	return VAORC_SUCCESS;
}

VAORC VAddon::Load(WORD wVersion, LPVOID p)
{
	TCHAR szName[VAOMAXAONAME]= _T("");

	//	If m_uIDName is not INVALID_RESOURCE_ID, then replace
	//	m_pName with the result of a successful LoadString:

	if (INVALID_RESOURCE_ID!=m_uIDName)
	{
		if (0!=LoadString(GetInstance(), m_uIDName, &szName[0], sizeof(szName)-1))
		{
			//	Because the REGSTRUCT m_reg name field already points to
			//	our m_pName buffer, there's nothing more we have to do.
			//	The V2LMSG_ENUMADDONS call will come next and we will
			//	be registered with this resource loaded name:

			_tcscpy(m_pName, szName);

#ifdef _DEBUG
			//	Append to the DEBUG version so it shows up differently in Visio's UI:
			if ( _tcslen(m_pName) < (VAOMAXAONAME - _tcslen(_T(" - DEBUG")) - 1) )
			{
				_tcscat(m_pName, _T(" - DEBUG"));
			}
#endif
		}
	}

#ifdef VADDON_EXE
	//	Executable target:
	return VAO_L2V_VERSION();	//	special return value for 'Load'...
#else
	//	VSL target:
	//	Default common load behavior:
	return VAOUtil_DefVisMainProc(V2LMSG_LOAD, wVersion, p, GetInstance());
#endif
}

VAORC VAddon::Unload(WORD wParam, LPVOID p)
{
#ifdef VADDON_EXE
	//	Executable target:
	return VAORC_SUCCESS;
#else
	//	VSL target:
	//	Default common unload behavior:
	return VAOUtil_DefVisMainProc(V2LMSG_UNLOAD, wParam, p, GetInstance());
#endif
}

VAORC VAddon::KillSession(LPVAOV2LSTRUCT pV2L)
{
#ifdef VADDON_EXE
	//	Executable target:
	return VAORC_SUCCESS;
#else
	//	VSL target:
	//	Default common kill session behavior:
	return VAOUtil_DefVisMainProc(V2LMSG_KILLSESSION, GetIndex(), pV2L, GetInstance());
#endif
}
