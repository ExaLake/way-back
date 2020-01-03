/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Nov 28 18:24:24 1999
 */
/* Compiler settings for C:\project\COMObject\COMObject.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IObject1 = {0xC1ADB650,0xA5BF,0x11D3,{0x86,0x51,0x00,0xC0,0x15,0x01,0xBD,0xC4}};


const IID LIBID_COMOBJECTLib = {0xC1ADB643,0xA5BF,0x11D3,{0x86,0x51,0x00,0xC0,0x15,0x01,0xBD,0xC4}};


const CLSID CLSID_Object1 = {0xC1ADB651,0xA5BF,0x11D3,{0x86,0x51,0x00,0xC0,0x15,0x01,0xBD,0xC4}};


#ifdef __cplusplus
}
#endif

