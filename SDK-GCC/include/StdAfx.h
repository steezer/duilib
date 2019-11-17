#ifndef __STDAFX_H__
#define __STDAFX_H__

#ifdef __GNUC__
    #ifndef min
        #define min(a,b) (((int)(a) < (int)(b)) ? (a) : (b))
    #endif
    #ifndef max
        #define max(a,b) (((int)(a) > (int)(b)) ? (a) : (b))
    #endif
#endif

#ifndef __FILET__
    #define __DUILIB_STR2WSTR(str)	L##str
    #define _DUILIB_STR2WSTR(str)	__DUILIB_STR2WSTR(str)
    #ifdef _UNICODE
        #define __FILET__	_DUILIB_STR2WSTR(__FILE__)
        #define __FUNCTIONT__	_DUILIB_STR2WSTR(__FUNCTION__)
    #else
        #define __FILET__	__FILE__
        #define __FUNCTIONT__	__FUNCTION__
    #endif
#endif

#define _CRT_SECURE_NO_DEPRECATE

// Required for VS 2008 (fails on XP and Win2000 without this fix)
#ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0500
#endif

#include "UIlib.h"
#include <olectl.h>

#define lengthof(x) (sizeof(x)/sizeof(*x))
#define MAX(a,b) (((int)(a) > (int)(b)) ? (a) : (b))
#define MIN(a,b) (((int)(a) < (int)(b)) ? (a) : (b))
#define CLAMP(x,a,b) (MIN(b,MAX(a,x)))

#endif