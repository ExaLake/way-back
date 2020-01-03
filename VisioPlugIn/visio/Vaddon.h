/*	VADDON.H
 *  Copyright (C) 1996-1997 Visio Corporation. All rights reserved.
 *
 *	Abstract
 *		Provides an easy-to-subclass VAddon class.
 *
 */

//	You, the user of VAddon, will derive a class from VAddon, override the
//	Run method and instantiate it...
//
//	Simplest case example is:
//	==================================================================
//	#define ATTS (VAO_AOATTS_ISACTION | VAO_AOATTS_HASABOUT | VAO_AOATTS_WAITCRSR)
//
//	class MyAddon : public VAddon {
//	public:
//		MyAddon(LPCTSTR pName):VAddon(ATTS, VAO_ENABLEALWAYS, 0, 0, pName) { };
//		VAORC Run(LPVAOV2LSTRUCT pV2L) { MessageBeep(0xFFFFFFFF); return VAORC_SUCCESS; };
//	};
//
//	MyAddon addon1("Addon 1");
//	MyAddon addon2("Addon 2");
//	==================================================================

#ifndef _VADDON_H
#define _VADDON_H

#include "vao.h"
#include <tchar.h>


#define INVALID_RESOURCE_ID	((UINT)(-1))


class VAddon {

public:
	//	The one and only meaningful constructor:
	VAddon(
		//	VAO_ORDINAL assigned automagically by this base class...
		VAO_ATTS atts,					// Attributes
		VAO_ENABMASK enabMask,			// Enabling policy
		VAO_INVOKEMASK invokeOnMask,
		VAO_NOTIFYMASK notifyOnMask,
		LPCTSTR lpName,
		UINT uIDName= INVALID_RESOURCE_ID);

	virtual ~VAddon();

	virtual VAORC IsEnabled(LPVAOV2LSTRUCT pV2L);		//	optionally overridden
	virtual VAORC Run(LPVAOV2LSTRUCT pV2L)= 0;			//	the pure virtual which MUST be overridden
	virtual VAORC About(LPVAOV2LSTRUCT pV2L);			//	optionally overridden
	virtual VAORC Help(LPVAOV2LSTRUCT pV2L);			//	optionally overridden
	virtual VAORC Load(WORD wVersion, LPVOID p);		//	optionally overridden
	virtual VAORC Unload(WORD wParam, LPVOID p);		//	optionally overridden
	virtual VAORC KillSession(LPVAOV2LSTRUCT pV2L);		//	optionally overridden

	virtual HINSTANCE GetInstance(long nFlags= 0L);		//	optionally overridden

	VAOREGSTRUCT *GetRegStructPtr(void);
	inline WORD GetIndex(void) { return m_wIndex; };
	inline TCHAR *GetName(void) { return m_pName; };

	static VAddon *FindAddon(WORD wOrdinal);
	static VAddon *GetFirst(void);
	static VAddon *GetNext(VAddon *pCurrent);		//	returns NULL when no more...
	static void SetInstance(HINSTANCE hInstance);

protected:
	UINT			m_uIDName;			//	either INVALID_RESOURCE_ID or the ID of
										//	of a string resource in the instance
										//	GetInstance(); used to get the name from
										//	a resource in VAddon::Load

private:
	WORD			m_wIndex;			//	VAO_ORDINAL
	TCHAR			m_pName[VAOMAXAONAME];
	VAOREGSTRUCT	m_reg;
	VAddon			*m_pNext;

	static VAddon		*m_pFirst;
	static VAddon		*m_pLast;
	static WORD			m_wNextIndex;
	static HINSTANCE	m_hInstance;

private:
	//	Unimplemented stuff to prevent compiler from generating default versions
	//	and to disallow end-user use:
	VAddon();
	VAddon(const VAddon &other);
	operator=(const VAddon &other);
};

#endif	//	_VADDON_H
