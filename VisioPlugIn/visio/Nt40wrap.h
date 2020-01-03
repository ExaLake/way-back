/* NT40WRAP.H - Workaround for 'too many shape methods' problem
 * Copyright (C) 1996 Visio Corporation. All rights reserved.
 */

//	On Windows NT 4.0, if you build an executable controller,
//	calling the 105th custom interface method (or higher than
//	105th) through the dual interface causes NT to puke in RPC
//	code. Therefore, we provide this file which allows methods
//	105 and higher for our IVShape interface (DropMany and beyond)
//	to be called via IDispatch::Invoke. Fortunately for us, the
//	IVShape interface is the only Visio interface large enough to
//	have to workaround...
//
//	If you're building a controller as an EXE which will be run
//	on NT 4.0, then include this file after including VISIWRAP.H
//	in your source files.
//
//	This workaround is equivalent to 'Dim a as Object' in VB.

#ifndef _NT40WRAP_H
#define _NT40WRAP_H

#ifndef _Visiwrap_H
#include "visiwrap.h"
#endif

/******************************************************************************/
//  Declaration of class CVisioShape_NT40

class FAR CVisioShape_NT40 : public CVisioShape
{
VW_PUBLIC:
    CVisioShape_NT40()
        : CVisioShape() { m_pDispatch= NULL; }

    CVisioShape_NT40(const CVisioShape_NT40& other)
        : CVisioShape(other) { m_pDispatch= NULL; }

    CVisioShape_NT40(const ::IVShape FAR * other)
        : CVisioShape(other) { m_pDispatch= NULL; }

    const CVisioShape_NT40 FAR & operator=(const CVisioShape_NT40 FAR &other)
        {
        if ( &other != this )
			{
			ReleaseDispatch();
			CopyIP(other.GetUnknown());
			}

        return *this;
        }

    const CVisioShape_NT40 FAR & operator=(const ::IVShape FAR * other)
        {
        if ( (LPUNKNOWN)other != GetUnknown() )
			{
			ReleaseDispatch();
			CopyIP( (LPUNKNOWN)other );
			}

        return *this;
        }

    virtual ~CVisioShape_NT40() { ReleaseDispatch(); }

    ::IVShape FAR * GetIP() const { return (::IVShape FAR *) GetUnknown(); }

    operator ::IVShape FAR * () { return (::IVShape FAR *) GetUnknown(); }

VW_PUBLIC:
    HRESULT DropMany(/*VARIANT*/ SAFEARRAY FAR * FAR *ObjectsToInstance, /*double*/ SAFEARRAY FAR * FAR *xyArray, /*short*/ SAFEARRAY FAR * FAR *IDArray, short FAR *lpRet);
    HRESULT GetFormulas(/*short*/ SAFEARRAY FAR * FAR *SRCStream, /*VARIANT*/ SAFEARRAY FAR * FAR *formulaArray);
    HRESULT GetResults(/*short*/ SAFEARRAY FAR * FAR *SRCStream, short Flags, /*VARIANT*/ SAFEARRAY FAR * FAR *UnitsNamesOrCodes, /*VARIANT*/ SAFEARRAY FAR * FAR *resultArray);
    HRESULT SetFormulas(/*short*/ SAFEARRAY FAR * FAR *SRCStream, /*VARIANT*/ SAFEARRAY FAR * FAR *formulaArray, short Flags, short FAR *lpRet);
    HRESULT SetResults(/*short*/ SAFEARRAY FAR * FAR *SRCStream, /*VARIANT*/ SAFEARRAY FAR * FAR *UnitsNamesOrCodes, /*VARIANT*/ SAFEARRAY FAR * FAR *resultArray, short Flags, short FAR *lpRet);
    HRESULT FromConnects(CVisioConnects FAR &rWrap);
    HRESULT Layout();
    HRESULT BoundingBox(short Flags, double FAR *lpr8Left, double FAR *lpr8Bottom, double FAR *lpr8Right, double FAR *lpr8Top);

private:
	IDispatch FAR *GetDispatch(void);
	void ReleaseDispatch(void);

	IDispatch FAR *m_pDispatch;
};


VW_INLINE IDispatch FAR *CVisioShape_NT40::GetDispatch(void)
{
	HRESULT hr= NOERROR;

	if (NULL==m_pDispatch && NULL!=GetIP())
	{
		hr= GetIP()->QueryInterface(IID_IDispatch, (LPVOID FAR *) &m_pDispatch);
	}

	return m_pDispatch;
}


VW_INLINE void CVisioShape_NT40::ReleaseDispatch(void)
{
	if (NULL!=m_pDispatch)
	{
		m_pDispatch->Release();
		m_pDispatch= NULL;
	}
}


#define DISPID_DropMany			92
#define DISPID_GetFormulas		93
#define DISPID_GetResults		94
#define DISPID_SetFormulas		95
#define DISPID_SetResults		96
#define DISPID_FromConnects		97
#define DISPID_Layout			98
#define DISPID_BoundingBox		99


VW_INLINE HRESULT CVisioShape_NT40::DropMany(/*VARIANT*/ SAFEARRAY FAR * FAR *ObjectsToInstance, /*double*/ SAFEARRAY FAR * FAR *xyArray, /*short*/ SAFEARRAY FAR * FAR *IDArray, short FAR *lpRet)
{
    HRESULT hr= E_FAIL;
	IDispatch FAR *pDispatch= GetDispatch();

    CHECK_IP(GetIP(), CVisioShape_NT40, DropMany);

	if (NULL!=pDispatch)
	{
		unsigned short wFlags= DISPATCH_METHOD;
		DISPPARAMS dispParams;
		VARIANT vaResult;
		EXCEPINFO excepInfo;
		UINT nArgErr= (UINT) -1;	// initialize to invalid arg
		IID iidNULL= { 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };
		VARIANTARG vArgs[3];


		//	Initialize all the inputs:
		memset(&dispParams, 0, sizeof dispParams);
		dispParams.rgvarg= vArgs;
			VariantInit(&vArgs[2]);
			V_VT(&vArgs[2])= VT_ARRAY | VT_BYREF | VT_VARIANT;
			V_ARRAYREF(&vArgs[2])= ObjectsToInstance;

			VariantInit(&vArgs[1]);
			V_VT(&vArgs[1])= VT_ARRAY | VT_BYREF | VT_R8;
			V_ARRAYREF(&vArgs[1])= xyArray;

			VariantInit(&vArgs[0]);
			V_VT(&vArgs[0])= VT_ARRAY | VT_BYREF | VT_I2;
			V_ARRAYREF(&vArgs[0])= IDArray;
		dispParams.cArgs= 3;

		VariantInit(&vaResult);

		memset(&excepInfo, 0, sizeof excepInfo);

		//	Make the call:
		hr= pDispatch->Invoke(DISPID_DropMany, iidNULL, 0, wFlags, &dispParams, &vaResult, &excepInfo, &nArgErr);


		//	Because DropMany is declared as having a 'retval' in the TypeLib,
		//	we have to look to vaResult for the return value...
		if (NOERROR==hr)
		{
			if (VT_I2!=V_VT(&vaResult))
				hr= VariantChangeType(&vaResult, &vaResult, 0, VT_I2);

			if (NOERROR==hr)
			{
				if (NULL==lpRet)
					hr= E_POINTER;
				else
					(*lpRet)= (short) V_I2(&vaResult);
			}
		}

		VariantClear(&vaResult);
		VariantClear(&vArgs[0]);
		VariantClear(&vArgs[1]);
		VariantClear(&vArgs[2]);
	}

    CHECK_HRESULT(hr, CVisioShape_NT40, DropMany);

    return hr;
}


VW_INLINE HRESULT CVisioShape_NT40::GetFormulas(/*short*/ SAFEARRAY FAR * FAR *SRCStream, /*VARIANT*/ SAFEARRAY FAR * FAR *formulaArray)
{
    HRESULT hr= E_FAIL;
	IDispatch FAR *pDispatch= GetDispatch();

    CHECK_IP(GetIP(), CVisioShape_NT40, GetFormulas);

	if (NULL!=pDispatch)
	{
		unsigned short wFlags= DISPATCH_METHOD;
		DISPPARAMS dispParams;
		VARIANT vaResult;
		EXCEPINFO excepInfo;
		UINT nArgErr= (UINT) -1;	// initialize to invalid arg
		IID iidNULL= { 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };
		VARIANTARG vArgs[2];


		//	Initialize all the inputs:
		memset(&dispParams, 0, sizeof dispParams);
		dispParams.rgvarg= vArgs;
			VariantInit(&vArgs[1]);
			V_VT(&vArgs[1])= VT_ARRAY | VT_BYREF | VT_I2;
			V_ARRAYREF(&vArgs[1])= SRCStream;

			VariantInit(&vArgs[0]);
			V_VT(&vArgs[0])= VT_ARRAY | VT_BYREF | VT_VARIANT;
			V_ARRAYREF(&vArgs[0])= formulaArray;
		dispParams.cArgs= 2;

		VariantInit(&vaResult);

		memset(&excepInfo, 0, sizeof excepInfo);

		//	Make the call:
		hr= pDispatch->Invoke(DISPID_GetFormulas, iidNULL, 0, wFlags, &dispParams, &vaResult, &excepInfo, &nArgErr);

		VariantClear(&vaResult);
		VariantClear(&vArgs[0]);
		VariantClear(&vArgs[1]);
	}

    CHECK_HRESULT(hr, CVisioShape_NT40, GetFormulas);

    return hr;
}


VW_INLINE HRESULT CVisioShape_NT40::GetResults(/*short*/ SAFEARRAY FAR * FAR *SRCStream, short Flags, /*VARIANT*/ SAFEARRAY FAR * FAR *UnitsNamesOrCodes, /*VARIANT*/ SAFEARRAY FAR * FAR *resultArray)
{
    HRESULT hr= E_FAIL;
	IDispatch FAR *pDispatch= GetDispatch();

    CHECK_IP(GetIP(), CVisioShape_NT40, GetResults);

	if (NULL!=pDispatch)
	{
		unsigned short wFlags= DISPATCH_METHOD;
		DISPPARAMS dispParams;
		VARIANT vaResult;
		EXCEPINFO excepInfo;
		UINT nArgErr= (UINT) -1;	// initialize to invalid arg
		IID iidNULL= { 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };
		VARIANTARG vArgs[4];


		//	Initialize all the inputs:
		memset(&dispParams, 0, sizeof dispParams);
		dispParams.rgvarg= vArgs;
			VariantInit(&vArgs[3]);
			V_VT(&vArgs[3])= VT_ARRAY | VT_BYREF | VT_I2;
			V_ARRAYREF(&vArgs[3])= SRCStream;

			VariantInit(&vArgs[2]);
			V_VT(&vArgs[2])= VT_I2;
			V_I2(&vArgs[2])= Flags;

			VariantInit(&vArgs[1]);
			V_VT(&vArgs[1])= VT_ARRAY | VT_BYREF | VT_VARIANT;
			V_ARRAYREF(&vArgs[1])= UnitsNamesOrCodes;

			VariantInit(&vArgs[0]);
			V_VT(&vArgs[0])= VT_ARRAY | VT_BYREF | VT_VARIANT;
			V_ARRAYREF(&vArgs[0])= resultArray;
		dispParams.cArgs= 4;

		VariantInit(&vaResult);

		memset(&excepInfo, 0, sizeof excepInfo);

		//	Make the call:
		hr= pDispatch->Invoke(DISPID_GetResults, iidNULL, 0, wFlags, &dispParams, &vaResult, &excepInfo, &nArgErr);

		VariantClear(&vaResult);
		VariantClear(&vArgs[0]);
		VariantClear(&vArgs[1]);
		VariantClear(&vArgs[2]);
		VariantClear(&vArgs[3]);
	}

    CHECK_HRESULT(hr, CVisioShape_NT40, GetResults);

    return hr;
}


VW_INLINE HRESULT CVisioShape_NT40::SetFormulas(/*short*/ SAFEARRAY FAR * FAR *SRCStream, /*VARIANT*/ SAFEARRAY FAR * FAR *formulaArray, short Flags, short FAR *lpRet)
{
    HRESULT hr= E_FAIL;
	IDispatch FAR *pDispatch= GetDispatch();

    CHECK_IP(GetIP(), CVisioShape_NT40, SetFormulas);

	if (NULL!=pDispatch)
	{
		unsigned short wFlags= DISPATCH_METHOD;
		DISPPARAMS dispParams;
		VARIANT vaResult;
		EXCEPINFO excepInfo;
		UINT nArgErr= (UINT) -1;	// initialize to invalid arg
		IID iidNULL= { 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };
		VARIANTARG vArgs[3];


		//	Initialize all the inputs:
		memset(&dispParams, 0, sizeof dispParams);
		dispParams.rgvarg= vArgs;
			VariantInit(&vArgs[2]);
			V_VT(&vArgs[2])= VT_ARRAY | VT_BYREF | VT_I2;
			V_ARRAYREF(&vArgs[2])= SRCStream;

			VariantInit(&vArgs[1]);
			V_VT(&vArgs[1])= VT_ARRAY | VT_BYREF | VT_VARIANT;
			V_ARRAYREF(&vArgs[1])= formulaArray;

			VariantInit(&vArgs[0]);
			V_VT(&vArgs[0])= VT_I2;
			V_I2(&vArgs[0])= Flags;
		dispParams.cArgs= 3;

		VariantInit(&vaResult);

		memset(&excepInfo, 0, sizeof excepInfo);

		//	Make the call:
		hr= pDispatch->Invoke(DISPID_SetFormulas, iidNULL, 0, wFlags, &dispParams, &vaResult, &excepInfo, &nArgErr);


		//	Because SetFormulas is declared as having a 'retval' in the TypeLib,
		//	we have to look to vaResult for the return value...
		if (NOERROR==hr)
		{
			if (VT_I2!=V_VT(&vaResult))
				hr= VariantChangeType(&vaResult, &vaResult, 0, VT_I2);

			if (NOERROR==hr)
			{
				if (NULL==lpRet)
					hr= E_POINTER;
				else
					(*lpRet)= (short) V_I2(&vaResult);
			}
		}

		VariantClear(&vaResult);
		VariantClear(&vArgs[0]);
		VariantClear(&vArgs[1]);
		VariantClear(&vArgs[2]);
	}

    CHECK_HRESULT(hr, CVisioShape_NT40, SetFormulas);

    return hr;
}


VW_INLINE HRESULT CVisioShape_NT40::SetResults(/*short*/ SAFEARRAY FAR * FAR *SRCStream, /*VARIANT*/ SAFEARRAY FAR * FAR *UnitsNamesOrCodes, /*VARIANT*/ SAFEARRAY FAR * FAR *resultArray, short Flags, short FAR *lpRet)
{
    HRESULT hr= E_FAIL;
	IDispatch FAR *pDispatch= GetDispatch();

    CHECK_IP(GetIP(), CVisioShape_NT40, SetResults);

	if (NULL!=pDispatch)
	{
		unsigned short wFlags= DISPATCH_METHOD;
		DISPPARAMS dispParams;
		VARIANT vaResult;
		EXCEPINFO excepInfo;
		UINT nArgErr= (UINT) -1;	// initialize to invalid arg
		IID iidNULL= { 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };
		VARIANTARG vArgs[4];


		//	Initialize all the inputs:
		memset(&dispParams, 0, sizeof dispParams);
		dispParams.rgvarg= vArgs;
			VariantInit(&vArgs[3]);
			V_VT(&vArgs[3])= VT_ARRAY | VT_BYREF | VT_I2;
			V_ARRAYREF(&vArgs[3])= SRCStream;

			VariantInit(&vArgs[2]);
			V_VT(&vArgs[2])= VT_ARRAY | VT_BYREF | VT_VARIANT;
			V_ARRAYREF(&vArgs[2])= UnitsNamesOrCodes;

			VariantInit(&vArgs[1]);
			V_VT(&vArgs[1])= VT_ARRAY | VT_BYREF | VT_VARIANT;
			V_ARRAYREF(&vArgs[1])= resultArray;

			VariantInit(&vArgs[0]);
			V_VT(&vArgs[0])= VT_I2;
			V_I2(&vArgs[0])= Flags;
		dispParams.cArgs= 4;

		VariantInit(&vaResult);

		memset(&excepInfo, 0, sizeof excepInfo);

		//	Make the call:
		hr= pDispatch->Invoke(DISPID_SetResults, iidNULL, 0, wFlags, &dispParams, &vaResult, &excepInfo, &nArgErr);


		//	Because SetResults is declared as having a 'retval' in the TypeLib,
		//	we have to look to vaResult for the return value...
		if (NOERROR==hr)
		{
			if (VT_I2!=V_VT(&vaResult))
				hr= VariantChangeType(&vaResult, &vaResult, 0, VT_I2);

			if (NOERROR==hr)
			{
				if (NULL==lpRet)
					hr= E_POINTER;
				else
					(*lpRet)= (short) V_I2(&vaResult);
			}
		}

		VariantClear(&vaResult);
		VariantClear(&vArgs[0]);
		VariantClear(&vArgs[1]);
		VariantClear(&vArgs[2]);
		VariantClear(&vArgs[3]);
	}

    CHECK_HRESULT(hr, CVisioShape_NT40, SetResults);

    return hr;
}


VW_INLINE HRESULT CVisioShape_NT40::FromConnects(CVisioConnects FAR &rWrap)
{
    HRESULT hr= E_FAIL;
	IDispatch FAR *pDispatch= GetDispatch();
	IVConnects FAR *pConnects= NULL;

    CHECK_IP(GetIP(), CVisioShape_NT40, FromConnects);

	if (NULL!=pDispatch)
	{
		//	This one is a 'propget'
		unsigned short wFlags= DISPATCH_METHOD | DISPATCH_PROPERTYGET;
		DISPPARAMS dispParams;
		VARIANT vaResult;
		EXCEPINFO excepInfo;
		UINT nArgErr= (UINT) -1;	// initialize to invalid arg
		IID iidNULL= { 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };


		//	Initialize all the inputs:
		memset(&dispParams, 0, sizeof dispParams);
		dispParams.rgvarg= NULL;
		dispParams.cArgs= 0;

		VariantInit(&vaResult);

		memset(&excepInfo, 0, sizeof excepInfo);

		//	Make the call:
		hr= pDispatch->Invoke(DISPID_FromConnects, iidNULL, 0, wFlags, &dispParams, &vaResult, &excepInfo, &nArgErr);


		//	Because FromConnects is declared as having a 'retval' in the TypeLib,
		//	we have to look to vaResult for the return value...
		if (NOERROR==hr)
		{
			if (VT_DISPATCH!=V_VT(&vaResult))
				hr= VariantChangeType(&vaResult, &vaResult, 0, VT_DISPATCH);

			if (NOERROR==hr && NULL!=V_DISPATCH(&vaResult))
				hr= V_DISPATCH(&vaResult)->QueryInterface(IID_IVConnects, (LPVOID FAR *) &pConnects);
		}

		VariantClear(&vaResult);
	}

    rWrap= pConnects;

    if (NULL!=pConnects)
        pConnects->Release();

    CHECK_HRESULT(hr, CVisioShape_NT40, FromConnects);

    return hr;
}


VW_INLINE HRESULT CVisioShape_NT40::Layout()
{
    HRESULT hr= E_FAIL;
	IDispatch FAR *pDispatch= GetDispatch();

    CHECK_IP(GetIP(), CVisioShape_NT40, Layout);

	if (NULL!=pDispatch)
	{
		unsigned short wFlags= DISPATCH_METHOD;
		DISPPARAMS dispParams;
		VARIANT vaResult;
		EXCEPINFO excepInfo;
		UINT nArgErr= (UINT) -1;	// initialize to invalid arg
		IID iidNULL= { 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };


		//	Initialize all the inputs:
		memset(&dispParams, 0, sizeof dispParams);
		dispParams.rgvarg= NULL;
		dispParams.cArgs= 0;

		VariantInit(&vaResult);

		memset(&excepInfo, 0, sizeof excepInfo);

		//	Make the call:
		hr= pDispatch->Invoke(DISPID_Layout, iidNULL, 0, wFlags, &dispParams, &vaResult, &excepInfo, &nArgErr);

		VariantClear(&vaResult);
	}

    CHECK_HRESULT(hr, CVisioShape_NT40, Layout);

    return hr;
}


VW_INLINE HRESULT CVisioShape_NT40::BoundingBox(short Flags, double FAR *lpr8Left, double FAR *lpr8Bottom, double FAR *lpr8Right, double FAR *lpr8Top)
{
    HRESULT hr= E_FAIL;
	IDispatch FAR *pDispatch= GetDispatch();

    CHECK_IP(GetIP(), CVisioShape_NT40, BoundingBox);

	if (NULL!=pDispatch)
	{
		unsigned short wFlags= DISPATCH_METHOD;
		DISPPARAMS dispParams;
		VARIANT vaResult;
		EXCEPINFO excepInfo;
		UINT nArgErr= (UINT) -1;	// initialize to invalid arg
		IID iidNULL= { 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };
		VARIANTARG vArgs[5];


		//	Initialize all the inputs:
		memset(&dispParams, 0, sizeof dispParams);
		dispParams.rgvarg= vArgs;
			VariantInit(&vArgs[4]);
			V_VT(&vArgs[4])= VT_I2;
			V_I2(&vArgs[4])= Flags;

			VariantInit(&vArgs[3]);
			V_VT(&vArgs[3])= VT_BYREF | VT_R8;
			V_R8REF(&vArgs[3])= lpr8Left;

			VariantInit(&vArgs[2]);
			V_VT(&vArgs[2])= VT_BYREF | VT_R8;
			V_R8REF(&vArgs[2])= lpr8Bottom;

			VariantInit(&vArgs[1]);
			V_VT(&vArgs[1])= VT_BYREF | VT_R8;
			V_R8REF(&vArgs[1])= lpr8Right;

			VariantInit(&vArgs[0]);
			V_VT(&vArgs[0])= VT_BYREF | VT_R8;
			V_R8REF(&vArgs[0])= lpr8Top;
		dispParams.cArgs= 5;

		VariantInit(&vaResult);

		memset(&excepInfo, 0, sizeof excepInfo);

		//	Make the call:
		hr= pDispatch->Invoke(DISPID_BoundingBox, iidNULL, 0, wFlags, &dispParams, &vaResult, &excepInfo, &nArgErr);

		VariantClear(&vaResult);
		VariantClear(&vArgs[0]);
		VariantClear(&vArgs[1]);
		VariantClear(&vArgs[2]);
		VariantClear(&vArgs[3]);
		VariantClear(&vArgs[4]);
	}

    CHECK_HRESULT(hr, CVisioShape_NT40, BoundingBox);

    return hr;
}

//	Make its use 'transparent':
#undef CVisioShape
#define CVisioShape CVisioShape_NT40

//	That is, people who need to accomodate NT 4.0 Executable
//	controllers will include this file, but continue using
//	'CVisioShape' in their code. The above #define forces
//	them to use CVisioShape_NT40 instead without them even
//	having to know it... Wild, huh?

#endif	//	_NT40WRAP_H
