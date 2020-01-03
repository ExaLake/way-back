/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Nov 19 14:25:32 1999
 */
/* Compiler settings for C:\Development\Code Samples\DCOM\DrawCtl\DrawCtl.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
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

const IID IID_IDrawCtl = {0x48DDCC1E,0x1FE0,0x11D0,{0xB9,0x1B,0x00,0x00,0x00,0x00,0x00,0x00}};


const IID LIBID_DRAWCTLLib = {0x48DDCC1B,0x1FE0,0x11D0,{0xB9,0x1B,0x00,0x00,0x00,0x00,0x00,0x00}};


const CLSID CLSID_CDrawCtl = {0x48DDCC1D,0x1FE0,0x11D0,{0xB9,0x1B,0x00,0x00,0x00,0x00,0x00,0x00}};


const IID IID_IDrawServ = {0x330E9E75,0xDF48,0x11CF,{0x8E,0x2C,0x00,0xA0,0xC9,0x0D,0xC9,0x4B}};


#ifdef __cplusplus
}
#endif

