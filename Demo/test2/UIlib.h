#ifndef __UILIB__
#define __UILIB__

#ifndef DUILIB_API
#define DUILIB_API 
#endif

//#define UILIB_COMDAT __declspec(selectany)
#define UILIB_COMDAT __declspec(selectany)

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stddef.h>
#include <richedit.h>
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>
#include <stdio.h>

#include "UIActiveX.h"

#endif