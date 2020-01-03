/*	HELPERS.CPP - Helper classes for easing BSTR and VARIANT use.
 *  Copyright (C) 1996-1997 Visio Corporation. All rights reserved.
 */

#ifdef MFC_HELPERS
#include "stdafx.h"
#endif

#include <windows.h>
#include <ole2.h>
#include <winnls.h>
#include <tchar.h>

#include "helpers.h"


//	***************************************************************************
//	The default BSTR helper class implementation:

#define V_MAX_STR_CONVERT 2048

static OLECHAR szOleStr[V_MAX_STR_CONVERT];

VBstr::VBstr()
{
	m_bstr= NULL;
}

VBstr::VBstr(const VBstr FAR &other)
{
	m_bstr= SysAllocString(other.m_bstr);
}

HRESULT VBstr::AllocFromLPCTSTR(LPCTSTR lpStr)
{
	if (lpStr)
	{
#ifndef OLE2ANSI
		int nBytes= _tcslen(lpStr) + 1;
		OLECHAR *pOleStr= szOleStr;

		if (nBytes > (ULONG)(V_MAX_STR_CONVERT))
		{
			pOleStr= new OLECHAR[nBytes];
		}

		MultiByteToWideChar(GetACP(), MB_PRECOMPOSED, lpStr, -1, pOleStr, nBytes);
		m_bstr= SysAllocString(pOleStr);

		if (nBytes > (ULONG)(V_MAX_STR_CONVERT))
		{
			delete [] pOleStr;
		}
#else
		m_bstr= SysAllocString(lpStr);
#endif
	}

	return NOERROR;
}

VBstr::VBstr(LPCTSTR lpStr)
{
	m_bstr= NULL;
	AllocFromLPCTSTR(lpStr);
}

VBstr::VBstr(BSTR bstr, BOOL bAssumeResponsibility /*= FALSE*/)
{
	//	*REQUIRED*
	if (bAssumeResponsibility)
		m_bstr= bstr;
	else
		m_bstr= SysAllocString(bstr);
}

VBstr::~VBstr()
{
	if (m_bstr)
		SysFreeString(m_bstr);
}

VBstr::operator const BSTR() const
{
	//	*REQUIRED*
	return m_bstr;
}

const VBstr FAR &VBstr::operator=(const BSTR bstr)
{
	//	*REQUIRED*
	if (m_bstr)
		SysFreeString(m_bstr);
	m_bstr= SysAllocString(bstr);
	return (*this);
}

const VBstr FAR &VBstr::operator=(const VBstr &other)
{
	if (m_bstr)
		SysFreeString(m_bstr);
	m_bstr= SysAllocString(other.m_bstr);
	return (*this);
}

const VBstr FAR &VBstr::operator=(LPCTSTR lpStr)
{
	if (m_bstr)
		SysFreeString(m_bstr);
	m_bstr= NULL;
	AllocFromLPCTSTR(lpStr);
	return (*this);
}

const VBstr FAR &VBstr:: operator=(LPCOLESTR lpOlestr)
{
	if (m_bstr)
		SysFreeString(m_bstr);
	m_bstr= SysAllocString(lpOlestr);
	return (*this);
}


#define VBSTR_COMPARE		wcscmp
#define VBSTR_COMPARE_I		_wcsicmp


//	Since Borland 5.0 doesn't support wcscmp and Win95 only
//	stubs lstrcmpW, write our own:
#ifdef __BORLANDC__

	//	Neither of these will work with embedded NULL OLECHARs:
	//		(but for simple string compares, it's better than nothing...)
	int VBstr_cmp(unsigned short *s1, unsigned short *s2)
	{
        int ret;

        ret= (int)((short)*s1 - (short)*s2);
        while( (0==ret) && *s2)
                ++s1, ++s2, ret= (int)((short)*s1 - (short)*s2);

        return ret;
	}

	//	For characters outside the A to Z range, this function compares them
	//	exactly; watch out for strings with special accented characters - you may
	//	have to write your own version of this for certain applications with the
	//	Borland compiler...
	//		(but again, for simple string compares, it's better than nothing...)
	int VBstr_cmpi(unsigned short *s1, unsigned short *s2)
	{
        wchar_t f,l;

        do  {
            f = ((*s1 <= L'Z') && (*s1 >= L'A'))
                ? *s1 + L'a' - L'A'
                : *s1;
            l = ((*s2 <= L'Z') && (*s2 >= L'A'))
                ? *s2 + L'a' - L'A'
                : *s2;
            s1++;
            s2++;
        } while ( (f) && (f == l) );

        return (int)(f - l);
	}

#undef VBSTR_COMPARE
#define VBSTR_COMPARE(s1, s2)		\
		VBstr_cmp((unsigned short *)(s1), (unsigned short *)(s2))

#undef VBSTR_COMPARE_I
#define VBSTR_COMPARE_I(s1, s2)		\
		VBstr_cmpi((unsigned short *)(s1), (unsigned short *)(s2))

#endif


BOOL VBstr::Compare(const VBstr FAR &other, BOOL bCaseSensitive /*= TRUE*/) const
{
	//	Use "vbstr.Compare(other, VBSTR_CASE_INSENSITIVE)" for case-insensitive compare...
	//	Use "vbstr.Compare(other)" for case-sensitive compare...

	//	Simple string comparison function.
	//	Only works on simple NULL terminated strings.
	//	If you embed NULL OLECHARs within you BSTRs,
	//	write another function to compare them.
	//	The strings must be identical or
	//	both NULL/"empty" to return TRUE.

	if (NULL==m_bstr)
	{
		if (NULL==other.m_bstr || 0==other.m_bstr[0])
		{
			//	They are both the "empty"/NULL string:
			return TRUE;
		}
		else
		{
			//	One's NULL, but the other is non-NULL with content:
			return FALSE;
		}
	}

	if (NULL==other.m_bstr)
	{
		if (0==m_bstr[0])
		{
			//	They are both the "empty"/NULL string:
			return TRUE;
		}
		else
		{
			//	One's NULL, but the other is non-NULL with content:
			return FALSE;
		}
	}

	//	They're both non-NULL, compare:
	if (bCaseSensitive)
	{
		return (0==VBSTR_COMPARE(m_bstr, other.m_bstr));
	}
	else
	{
		return (0==VBSTR_COMPARE_I(m_bstr, other.m_bstr));
	}
}

BOOL VBstr::operator==(const VBstr FAR &other) const
{
	//	Case-sensitive!
	//	Use "vbstr.Compare(other, VBSTR_CASE_INSENSITIVE)" for case-insensitive compare...
	return Compare(other);
}

#ifdef MFC_HELPERS
void VBstr::ConvertToCString(CString FAR& cstr)
{
	if (m_bstr)
	{
#if defined(_WIN32) && !defined(OLE2ANSI)
		int	nbyte= WideCharToMultiByte(GetACP(), 0, m_bstr, -1, NULL, 0, 0, 0);
		LPTSTR lpStr= cstr.GetBuffer(nbyte);
		WideCharToMultiByte(GetACP(), 0, m_bstr, -1, lpStr, nbyte, 0, 0);
		cstr.ReleaseBuffer();
#else
		cstr= m_bstr;
#endif
	}
	else
	{
		cstr = "";
	}
}
#endif

HRESULT VBstr::ConvertToLPTSTR(LPTSTR pStr, ULONG *pnBytes)
{
	//	*pnBytes should be size of pStr buffer on entry
	//	*pnBytes is size needed if E_FAIL is returned
	//	*pnBytes is size copied if NOERROR is returned

	//	It is a BAD programming error to call this function with NULL args.
	//	Don't do it!

	//	ASSERT(pStr!=NULL);
	//	ASSERT(pnBytes!=NULL);

	int	nNeeded;	//	intentionally uninitialized - all code paths
					//	below initialize nNeeded properly

	if (m_bstr)
	{
#if defined(_WIN32) && !defined(OLE2ANSI)
		nNeeded= WideCharToMultiByte(GetACP(), 0, m_bstr, -1, NULL, 0, 0, 0);

		if ( (*pnBytes) >= ((ULONG)nNeeded) )
		{
			WideCharToMultiByte(GetACP(), 0, m_bstr, -1, pStr, nNeeded, 0, 0);
		}
		else
		{
			(*pnBytes)= (ULONG) nNeeded;
			return E_FAIL;
		}
#else
		nNeeded= _tcslen(m_bstr) + 1;

		if ( (*pnBytes) >= ((ULONG)nNeeded) )
		{
			_tcscpy(pStr, m_bstr);
		}
		else
		{
			(*pnBytes)= (ULONG) nNeeded;
			return E_FAIL;
		}
#endif
	}
	else
	{
		nNeeded= 1;

		if ( (*pnBytes) >= ((ULONG)nNeeded) )
		{
			(*pStr)= (TCHAR) 0;
		}
		else
		{
			(*pnBytes)= 1;
			return E_FAIL;
		}
	}

	(*pnBytes)= (ULONG) nNeeded;

	return NOERROR;
}


//	***************************************************************************
//	The default VARIANT helper class implementation:

VVariant::VVariant()
{
	Init();
}

VVariant::VVariant(const VVariant& other)
{
	Init();
	Copy(other.m_v);
}

VVariant::VVariant(const VARIANT& v)
{
	//	*REQUIRED*
	Init();
	Copy(v);
}

VVariant::VVariant(LPCTSTR p)
{
	Init();
	V_VT(&m_v)= VT_BSTR;
	V_BSTR(&m_v)= SysAllocString(VBstr(p));
}

VVariant::VVariant(const BSTR bstr, BOOL bAssumeResponsibility /*= FALSE*/)
{
	Init();
	V_VT(&m_v)= VT_BSTR;

	if (bAssumeResponsibility)
		V_BSTR(&m_v)= bstr;
	else
		V_BSTR(&m_v)= SysAllocString(bstr);
}

VVariant::VVariant(const long n)
{
	Init();
	V_VT(&m_v)= VT_I4;
	V_I4(&m_v)= n;
}

VVariant::VVariant(const double d)
{
	Init();
	V_VT(&m_v)= VT_R8;
	V_R8(&m_v)= d;
}

VVariant::VVariant(const LPUNKNOWN pUnk)
{
	Init();
	V_VT(&m_v)= VT_UNKNOWN;
	V_UNKNOWN(&m_v)= pUnk;
	if (pUnk)
		pUnk->AddRef();
}

VVariant::VVariant(const LPDISPATCH pDisp)
{
	Init();
	V_VT(&m_v)= VT_DISPATCH;
	V_DISPATCH(&m_v)= pDisp;
	if (pDisp)
		pDisp->AddRef();
}

VVariant::~VVariant()
{
	Clear();
}


VVariant::operator VARIANT *()
{
	//	*REQUIRED*
	return &m_v;
}

VVariant::operator VARIANT()
{
	//	*REQUIRED*
	return m_v;
}

VVariant::operator const VARIANT() const
{
	//	*REQUIRED*
	return m_v;
}

const VVariant& VVariant::operator=(const VVariant& other)
{
	Clear();
	Copy(other.m_v);
	return (*this);
}

const VVariant& VVariant::operator=(const VARIANT& v)
{
	Clear();
	Copy(v);
	return (*this);
}

const VVariant& VVariant::operator=(LPCTSTR p)
{
	Clear();
	V_VT(&m_v)= VT_BSTR;
	V_BSTR(&m_v)= SysAllocString(VBstr(p));
	return (*this);
}

const VVariant& VVariant::operator=(const BSTR bstr)
{
	Clear();
	V_VT(&m_v)= VT_BSTR;
	V_BSTR(&m_v)= SysAllocString(bstr);
	return (*this);
}

const VVariant& VVariant::operator=(const long n)
{
	Clear();
	V_VT(&m_v)= VT_I4;
	V_I4(&m_v)= n;
	return (*this);
}

const VVariant& VVariant::operator=(const double d)
{
	Clear();
	V_VT(&m_v)= VT_R8;
	V_R8(&m_v)= d;
	return (*this);
}

const VVariant& VVariant::operator=(const LPUNKNOWN pUnk)
{
	Clear();
	V_VT(&m_v)= VT_UNKNOWN;
	V_UNKNOWN(&m_v)= pUnk;
	if (pUnk)
		pUnk->AddRef();
	return (*this);
}

const VVariant& VVariant::operator=(const LPDISPATCH pDisp)
{
	Clear();
	V_VT(&m_v)= VT_DISPATCH;
	V_DISPATCH(&m_v)= pDisp;
	if (pDisp)
		pDisp->AddRef();
	return (*this);
}

void VVariant::Init(void)
{
	VariantInit(&m_v);
}

void VVariant::Clear(void)
{
	VariantClear(&m_v);
}

void VVariant::Copy(const VARIANT &v)
{
	VariantCopy(&m_v, (VARIANT *) &v);
}


//	***************************************************************************
//	Generalized SAFEARRAY helper class implementation:

HRESULT VSafeArray::Init(void)
{
	//	This Init must be called before Create. Calling it after Create
	//	would cause a memory leak...

	//	We have it so we don't duplicate a bunch of code in all the various
	//	constructors.... Set initial values of members here.

	//	Call from ALL constructors...

	m_nDims= DIM_UNINITIALIZED;
	m_vt= VT_EMPTY;
	m_pSA= NULL;

	return NOERROR;
}

VSafeArray::VSafeArray()
{
	Init();
}

VSafeArray::VSafeArray(VARTYPE vt, unsigned int nDims, SAFEARRAYBOUND FAR* pBounds)
{
	//	Generic:
	Init();
	Create(vt, nDims, pBounds);
}

VSafeArray::VSafeArray(VARTYPE vt, ULONG cElements, LONG lLbound)
{
	//	Simple 1D:
	SAFEARRAYBOUND bound[1];
	bound[0].cElements= cElements;
	bound[0].lLbound= lLbound;

	Init();
	Create(vt, 1, bound);
}

VSafeArray::VSafeArray(VARTYPE vt, ULONG cElements1, LONG lLbound1, ULONG cElements2, LONG lLbound2)
{
	//	2D:
	SAFEARRAYBOUND bound[2];
	bound[0].cElements= cElements1;
	bound[0].lLbound= lLbound1;
	bound[1].cElements= cElements2;
	bound[1].lLbound= lLbound2;

	Init();
	Create(vt, 2, bound);
}

VSafeArray::VSafeArray(VARTYPE vt, ULONG cElements1, LONG lLbound1, ULONG cElements2, LONG lLbound2, ULONG cElements3, LONG lLbound3)
{
	//	3D:
	SAFEARRAYBOUND bound[3];
	bound[0].cElements= cElements1;
	bound[0].lLbound= lLbound1;
	bound[1].cElements= cElements2;
	bound[1].lLbound= lLbound2;
	bound[2].cElements= cElements3;
	bound[2].lLbound= lLbound3;

	Init();
	Create(vt, 3, bound);
}

VSafeArray::~VSafeArray()
{
	Destroy();
}

HRESULT VSafeArray::Create(VARTYPE vt, unsigned int nDims, SAFEARRAYBOUND FAR* pBounds)
{
	HRESULT hr= NOERROR;

	Destroy();	//	Forget about anything we currently point to...

	m_nDims= nDims;
	m_vt= vt;
	m_pSA= SafeArrayCreate(vt, nDims, pBounds);

	if (NULL==m_pSA)
		hr= E_OUTOFMEMORY;

	return hr;
}

HRESULT VSafeArray::Destroy(void)
{
	HRESULT hr= NOERROR;

	if (NULL!=m_pSA)
	{
		hr= SafeArrayDestroy(m_pSA);
		m_pSA= NULL;
	}

	return hr;
}

//****************************************************************************

unsigned int VSafeArray::GetDimensions(void)
{
	if (DIM_UNINITIALIZED==m_nDims && NULL!=m_pSA)
	{
		m_nDims= SafeArrayGetDim(m_pSA);
	}

	return m_nDims;
}

long VSafeArray::GetNumberElements(unsigned int nDim /*= 1*/)
{
	return GetUpper(nDim)-GetLower(nDim)+1;
}

long VSafeArray::GetLower(unsigned int nDim /*= 1*/)
{
	long nRet= 0;

	if (DIM_UNINITIALIZED!=nDim && NULL!=m_pSA)
	{
		long nLower= 0;
		if (SUCCEEDED(SafeArrayGetLBound(m_pSA, nDim, &nLower)))
		{
			nRet= nLower;
		}
	}

	return nRet;
}

long VSafeArray::GetUpper(unsigned int nDim /*= 1*/)
{
	long nRet= 0;

	if (DIM_UNINITIALIZED!=nDim && NULL!=m_pSA)
	{
		long nUpper= 0;
		if (SUCCEEDED(SafeArrayGetUBound(m_pSA, nDim, &nUpper)))
		{
			nRet= nUpper;
		}
	}

	return nRet;
}

HRESULT VSafeArray::PutElement(long *pnIndices, void const *pData)
{
	HRESULT hr= E_FAIL;

	if (NULL!=m_pSA)
	{
		hr= SafeArrayPutElement(m_pSA, pnIndices, (void *) pData);
	}

	return hr;
}

HRESULT VSafeArray::GetElement(long *pnIndices, void *pData)
{
	HRESULT hr= E_FAIL;

	if (NULL!=m_pSA)
	{
		hr= SafeArrayGetElement(m_pSA, pnIndices, pData);
	}

	return hr;
}

VSafeArray::operator SAFEARRAY FAR* const (void) const
{
	return m_pSA;
}

VSafeArray::operator SAFEARRAY FAR* FAR* (void) const
{
	return (SAFEARRAY FAR* FAR*) &m_pSA;
}

SAFEARRAY FAR* FAR* VSafeArray::LPLPSAFEARRAY(void)
{
	//	Call this function when you are passing the SAFEARRAY ** to a method
	//	which is going to fill in the SAFEARRAY for you. ('out' args)
	Destroy();
	return &m_pSA;
}


//	***************************************************************************
//	1-dimensional concrete SAFEARRAY helper class implementation:

HRESULT VSafeArray1D::PutShort(long nIndex, short n)
{
	//	ASSERT(VT_I2==m_vt);
	return PutElement(&nIndex, &n);
}

HRESULT VSafeArray1D::PutLong(long nIndex, long n)
{
	//	ASSERT(VT_I4==m_vt);
	return PutElement(&nIndex, &n);
}

HRESULT VSafeArray1D::PutDouble(long nIndex, double d)
{
	//	ASSERT(VT_R8==m_vt);
	return PutElement(&nIndex, &d);
}

HRESULT VSafeArray1D::PutBstr(long nIndex, BSTR bstr)
{
	//	ASSERT(VT_BSTR==m_vt);
	return PutElement(&nIndex, bstr);
}

HRESULT VSafeArray1D::PutVariant(long nIndex, const VARIANT &v)
{
	//	ASSERT(VT_VARIANT==m_vt);
	return PutElement(&nIndex, &v);
}

HRESULT VSafeArray1D::PutObject(long nIndex, LPUNKNOWN pUnk)
{
	//	ASSERT(VT_UNKNOWN==m_vt || VT_DISPATCH==m_vt);
	return PutElement(&nIndex, pUnk);
}

short VSafeArray1D::GetShort(long nIndex)
{
	short n= 0;
	//	ASSERT(VT_I2==m_vt);
	if (FAILED(GetElement(&nIndex, &n)))
	{
		n= -1;
	}
	return n;
}

long VSafeArray1D::GetLong(long nIndex)
{
	long n= 0L;
	//	ASSERT(VT_I4==m_vt);
	if (FAILED(GetElement(&nIndex, &n)))
	{
		n= -1L;
	}
	return n;
}

double VSafeArray1D::GetDouble(long nIndex)
{
	double d= 0.0;
	//	ASSERT(VT_R8==m_vt);
	if (FAILED(GetElement(&nIndex, &d)))
	{
		d= -1.0;
	}
	return d;
}

BSTR VSafeArray1D::GetBstr(long nIndex)
{
	BSTR bstr= NULL;
	//	ASSERT(VT_BSTR==m_vt);
	if (FAILED(GetElement(&nIndex, &bstr)))
	{
		bstr= NULL;
	}
	//	non-NULL return MUST be SysFreeStringed
	return bstr;
}

VARIANT VSafeArray1D::GetVariant(long nIndex)
{
	VARIANT v;
	//	ASSERT(VT_VARIANT==m_vt);
	VariantInit(&v);
	if (FAILED(GetElement(&nIndex, &v)))
	{
		V_VT(&v)= VT_EMPTY;
		V_NONE(&v)= 0;
	}
	//	return MUST be VariantCleared
	return v;
}

LPUNKNOWN VSafeArray1D::GetObject(long nIndex)
{
	LPUNKNOWN pUnk= NULL;
	//	ASSERT(VT_UNKNOWN==m_vt || VT_DISPATCH==m_vt);
	if (FAILED(GetElement(&nIndex, &pUnk)))
	{
		pUnk= NULL;
	}
	else
	{
		pUnk->AddRef();
		//	non-NULL return MUST be Released...
	}
	return pUnk;
}
