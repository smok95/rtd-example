

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Nov 26 15:31:11 2019
 */
/* Compiler settings for rtdexam.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

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

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IRTDUpdateEvent,0xA43788C1,0xD91B,0x11D3,0x8F,0x39,0x00,0xC0,0x4F,0x36,0x51,0xB8);


MIDL_DEFINE_GUID(IID, IID_IRtdServer,0xEC0E6191,0xDB51,0x11D3,0x8F,0x3E,0x00,0xC0,0x4F,0x36,0x51,0xB8);


MIDL_DEFINE_GUID(IID, LIBID_rtdexamLib,0x5E4EF894,0x4DC4,0x414A,0xA4,0xFC,0x01,0x4E,0x39,0x53,0xA8,0x24);


MIDL_DEFINE_GUID(CLSID, CLSID_RTDClock,0xD61F799E,0x9F33,0x420F,0xB9,0xAC,0x5D,0x3D,0x22,0x18,0x22,0xCA);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif


