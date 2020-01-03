/*	HELPERS.H - Helper classes for easing BSTR and VARIANT and SAFEARRAY use.
 *  Copyright (C) 1996-1997 Visio Corporation. All rights reserved.
 */

#ifndef HELPERS_____
#define HELPERS_____

/******************************************************************************/
//
//	YOU can define your own "helper classes" for string and variant
//	args to OLE automation methods. The required elements are listed
//	below in our example helper classes. These classes are what make it
//	easy to create clean C++ code to drive OLE Automation objects.
//
//	You may use the example helper classes as is or you may derive your own
//	to use.


/******************************************************************************/
//
//	*** Scenarios ***    (scenarii?)
//
//	(do ONE of the following)
//
//
//	<1>	#define NO_HELPERS
//			BSTR_HELPER_CLASS    == BSTR
//			VARIANT_HELPER_CLASS == VARIANT
//
//	<2>	#define BSTR_HELPER_CLASS or VARIANT_HELPER_CLASS independently.
//
//	<3>	#define MFC_HELPERS
//			BSTR_HELPER_CLASS    == VString     (...if you didn't define your own.)
//			VARIANT_HELPER_CLASS == COleVariant (...if you didn't define your own.)
//
//	<4>	Don't #define anything and take the defaults:
//			BSTR_HELPER_CLASS    == VBstr    (...if you didn't define your own.)
//			VARIANT_HELPER_CLASS == VVariant (...if you didn't define your own.)
//
//
//	*** IMPORTANT ***
//
//	If you want a VARIANT helper class, but NO BSTR helper class:
//		#define BSTR_HELPER_CLASS		BSTR
//		#define NO_BSTR_HELPER			//	<--- *** Important ***
//		#define VARIANT_HELPER_CLASS	MyVariantHelper
//
//	The NO_BSTR_HELPER definition is how we know whether to do a SysFreeString
//	internal to the wrapper class methods. If it's NOT defined, we do a
//	SysFreeString after getting a BSTR from an OLE method and passing a copy
//	of it to the BSTR_HELPER_CLASS through its assignment operator.
//	If there is no BSTR_HELPER_CLASS, then we just do a straight BSTR assignment
//	and if we did a SysFreeString "for you," you'd probably get a little
//	perturbed about it!


/******************************************************************************/
//	For those who require no!! help:

#ifdef NO_HELPERS

#undef BSTR_HELPER_CLASS
#undef VARIANT_HELPER_CLASS

#define BSTR_HELPER_CLASS		BSTR
#define NO_BSTR_HELPER

#define VARIANT_HELPER_CLASS	VARIANT
#define NO_VARIANT_HELPER

#endif	//	NO_HELPERS


#ifdef MFC_HELPERS
#include <afx.h>	//	MFC file where CString is defined
#endif

/******************************************************************************/
//	The default BSTR helper class interface:

#define VBSTR_CASE_INSENSITIVE 0

class VBstr
{
// Constructors
public:
	VBstr();
	VBstr(const VBstr FAR &other);							//	a good idea since our constructors allocate memory...
	VBstr(LPCTSTR lpStr);									//	construct from LPCTSTR / const char * / CString
	VBstr(BSTR bstr, BOOL bAssumeResponsibility= FALSE);	//	*REQUIRED* for compiling with wrapper classes

	virtual ~VBstr();


// Operations
public:
	operator const BSTR() const;							//	*REQUIRED* for compiling with wrapper classes
	const VBstr FAR &operator=(const BSTR bstr);			//	*REQUIRED* for compiling with wrapper classes
	const VBstr FAR &operator=(const VBstr FAR &other);		//	a good idea since we have a copy constructor...
	const VBstr FAR &operator=(LPCTSTR lpStr);				//	useful -- requested!
	const VBstr FAR &operator=(LPCOLESTR lpOlestr);			//	useful -- requested!

	BOOL operator==(const VBstr FAR &other) const;			//	comparison operator -- case sensitive
	BOOL Compare(const VBstr FAR &other, BOOL bCaseSensitive= TRUE) const;

#ifdef MFC_HELPERS
	void ConvertToCString(CString FAR& cstr);
#endif

	HRESULT ConvertToLPTSTR(LPTSTR pStr, ULONG *pnBytes);

private:
	HRESULT AllocFromLPCTSTR(LPCTSTR lpStr);				//	called ONLY from constructor/operator=
	BSTR m_bstr;
};



/******************************************************************************/
//	The default VARIANT helper class interface:

class VVariant
{
public:
	VVariant();
	VVariant(const VVariant& other);
	VVariant(const VARIANT& v);				//	*REQUIRED* for compiling with wrapper classes
	VVariant(LPCTSTR p);
	VVariant(const BSTR bstr, BOOL bAssumeResponsibility= FALSE);
	VVariant(const long n);
	VVariant(const double d);
	VVariant(const LPUNKNOWN pUnk);
	VVariant(const LPDISPATCH pDisp);

	virtual ~VVariant();


	operator VARIANT *();						//	*REQUIRED* for compiling with wrapper classes
	operator VARIANT();							//	*REQUIRED* for compiling with wrapper classes
	operator const VARIANT() const;				//	*REQUIRED* for compiling with wrapper classes

	const VVariant& operator=(const VVariant& other);
	const VVariant& operator=(const VARIANT& v);
	const VVariant& operator=(LPCTSTR p);
	const VVariant& operator=(const BSTR bstr);
	const VVariant& operator=(const long n);
	const VVariant& operator=(const double d);
	const VVariant& operator=(const LPUNKNOWN pUnk);
	const VVariant& operator=(const LPDISPATCH pDisp);

private:
	VARIANT m_v;

	void Init(void);
	void Clear(void);

public:
	void Copy(const VARIANT &v);
};



/******************************************************************************/
//	The default SAFEARRAY helper class interface:


#define DIM_UNINITIALIZED	(unsigned int)(-1)


class VSafeArray {

public:
	//	Empty (good for passing as output arg to, for example, "Collection.GetNames"):
	VSafeArray();

	//	Generic:
	VSafeArray(VARTYPE vt, unsigned int nDims, SAFEARRAYBOUND FAR* pBounds);

	//	Simple 1D:
	VSafeArray(VARTYPE vt, ULONG cElements, LONG lLbound);

	//	2D:
	VSafeArray(VARTYPE vt, ULONG cElements1, LONG lLbound1, ULONG cElements2, LONG lLbound2);

	//	3D:
	VSafeArray(VARTYPE vt, ULONG cElements1, LONG lLbound1, ULONG cElements2, LONG lLbound2, ULONG cElements3, LONG lLbound3);

	virtual ~VSafeArray();

	virtual BOOL IsSet(void) { return (NULL!=m_pSA); };

	virtual unsigned int GetDimensions(void);
	virtual long GetNumberElements(unsigned int nDim= 1);
	virtual long GetLower(unsigned int nDim= 1);
	virtual long GetUpper(unsigned int nDim= 1);

	virtual HRESULT PutElement(long *pnIndices, void const *pData);
	virtual HRESULT GetElement(long *pnIndices, void *pData);

	//	These two merely grant access to data member or its address:
	operator SAFEARRAY FAR* const (void) const;
	operator SAFEARRAY FAR* FAR* (void) const;

	//	This one cleans out the data member before giving back its address:
	virtual SAFEARRAY FAR* FAR* LPLPSAFEARRAY(void);	//	pass as an 'out' arg; i.e. filled in by called function...

protected:
	virtual HRESULT Init(void);
	virtual HRESULT Create(VARTYPE vt, unsigned int nDims, SAFEARRAYBOUND FAR* pBounds);
	virtual HRESULT Destroy(void);

private:
	unsigned int m_nDims;
	VARTYPE m_vt;
	SAFEARRAY FAR* m_pSA;
};


//	1D case - putters and getters for basic element types:

class VSafeArray1D : public VSafeArray {

public:
	//	Empty (good for passing as input arg):
	VSafeArray1D() { };												//	parent class does it all...

	//	Simple 1D:
	VSafeArray1D(VARTYPE vt, ULONG cElements, LONG lLbound) :
			VSafeArray(vt, cElements, lLbound) { };					//	parent class does it all...

	virtual ~VSafeArray1D() { };									//	parent class does it all...

	virtual HRESULT PutShort(long nIndex, short n);
	virtual HRESULT PutLong(long nIndex, long n);
	virtual HRESULT PutDouble(long nIndex, double d);
	virtual HRESULT PutBstr(long nIndex, BSTR bstr);
	virtual HRESULT PutVariant(long nIndex, const VARIANT &v);
	virtual HRESULT PutObject(long nIndex, LPUNKNOWN pUnk);

	virtual short GetShort(long nIndex);
	virtual long GetLong(long nIndex);
	virtual double GetDouble(long nIndex);
	virtual BSTR GetBstr(long nIndex);
	virtual VARIANT GetVariant(long nIndex);
	virtual LPUNKNOWN GetObject(long nIndex);
};



/******************************************************************************/
//	For those using MFC requiring help:

#ifdef MFC_HELPERS

//	Get rid of const-ness default for wrapper class input arguments:
//		(allows operator const BSTR to be a non-const method;
//		 that is, we can do a data member assignment inside of it...)
#define VW_CONST

class VString : public CString
{
public:
//	Inherited from CString, straight pass-throughs:
	VString() { }
	VString(const VString& stringSrc) : CString(stringSrc) { }
	VString(TCHAR ch, int nRepeat = 1) : CString(ch, nRepeat) { }
	VString(LPCSTR lpsz) : CString(lpsz) { }
	VString(LPCWSTR lpsz) : CString(lpsz) { }
	VString(LPCTSTR lpch, int nLength) : CString(lpch, nLength) { }
	VString(const unsigned char* psz) : CString(psz) { }


//	The class "VString" requires the class VBstr...
//	It uses VBstr to accomplish assignments and conversions:

private:
	VBstr m_vbstr;	//	Destroyed when VString is destroyed...

//	Add these three *REQUIRED* ops:
public:
	VString(const BSTR bstr, BOOL bAssumeResponsibility= FALSE)
	{
		VBstr vb(bstr);
		vb.ConvertToCString(*this);
		if (bAssumeResponsibility && bstr)
			SysFreeString(bstr);
	}

	operator const BSTR()
	{
		m_vbstr= (LPCTSTR) this;
		return m_vbstr;
	}

	const VString &operator=(const BSTR bstr)
	{
		VBstr vb(bstr);
		vb.ConvertToCString(*this);
		return (*this);
	}
};

#ifndef BSTR_HELPER_CLASS
#define BSTR_HELPER_CLASS		VString
#endif

#ifndef VARIANT_HELPER_CLASS
#define VARIANT_HELPER_CLASS	COleVariant
#endif

#endif	//	MFC_HELPERS


/******************************************************************************/
//	For those requiring the simplest level of help:

#ifndef BSTR_HELPER_CLASS
#define BSTR_HELPER_CLASS		VBstr
#endif

#ifndef VARIANT_HELPER_CLASS
#define VARIANT_HELPER_CLASS	VVariant
#endif


/******************************************************************************/
//	Abstract use of helpers regardless of which set you're actually using:

#define H_Str(s)			(   BSTR_HELPER_CLASS( (LPCTSTR) (s) )			 )
#define H_Long(v)			(   VARIANT_HELPER_CLASS( (const long) (v) )     )
#define H_StrVar(v)			(   VARIANT_HELPER_CLASS( (const char *) (v) )   )


#endif	//	HELPERS_____
