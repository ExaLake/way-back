/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 5/22/98 8:50:33 AM
  Comments: Runtime class
 ************************************/

#ifndef __RTTIMACROS_
#define __RTTIMACROS_

//This file contains macros used to simulate RTTI's and dynamic
//creation of objects using only the class name.
//Used by the DECLARE_DERIVED_CLASS
//In fact, creating an object of this type adds a new element to the ma

class CRuntimeClassControl
{
public:
	static CMapStringToPtr* m_pClassMap;
	CRuntimeClassControl(CString str, void* pFct)
	{
		if(!m_pClassMap)
			m_pClassMap = new CMapStringToPtr;

		ASSERT(m_pClassMap != NULL);
		(*m_pClassMap)[str] = pFct;
	}
	~CRuntimeClassControl()
	{
		if(m_pClassMap){
			delete m_pClassMap;
			m_pClassMap = NULL;
		}
	}

};

//Put this macro inside the declaration of a base class for a
//hierarchy. You can create objects of types derived from this
//class calling the baseClassName::CreateObject with the class
//name parameter. Each derived class must add its name and a pointer
//to a factory method without parameters ( it must use 
//the DECLARE_DERIVED_CLASS(derivedClassName,baseClassName) macro

// Macro DECLARE_BASE_CLASS( baseClassName )
#define DECLARE_BASE_CLASS(baseClassName) \
typedef baseClassName* (*pfnCreateObjectFn)();\
public:\
	virtual CString GetClassName() {return CString(#baseClassName);}\
	static baseClassName* CreateObject(CString strClassName)\
	{\
		void* fnCreate = NULL;\
		if( (*CRuntimeClassControl::m_pClassMap).Lookup(strClassName,fnCreate) )\
			return ((pfnCreateObjectFn)(fnCreate))();\
		 return NULL;\
	};

// In the derived classes must exist function CreateObject!
// Macro DECLARE_DERIVED_CLASS(derivedClassName,baseClassName)
#define DECLARE_DERIVED_CLASS(derivedClassName) \
public:\
	virtual CString GetClassName() {return CString(#derivedClassName);}\
	static derivedClassName* CreateObject()\
	{\
		return new derivedClassName;\
	};\
public:\
	static CRuntimeClassControl m_rcc;

// Macro IMPLEMENT_DERIVED_CLASS(derivedClassName,baseClassName) is implement of DECLARE_DERIVED_CLASS
#define IMPLEMENT_DERIVED_CLASS(derivedClassName,baseClassName) \
	CRuntimeClassControl derivedClassName::m_rcc(#derivedClassName,derivedClassName::CreateObject);

#endif //__RTTIMACROS_



