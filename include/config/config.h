#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <platformconfig.h>
#include <stdconfig.h>
#include <typeconfig.h>
#include <macroconfig.h>
#include <log.h>

//winapi

#include <gdiobj.h>
#include <Point.h>
#include <rect.h>
#include <painter.h>
#include <wincore.h>
#include <win32utils.h>
#include <event.h>
#include <polygon.h>
#include <tchar.h>
#include <colordef.h>

//Common Control
#include <CommCtrl.h>
#pragma comment (lib, "comctl32.lib")

//GDI+ 
#include <gdi+.h>

#define OVERRIDE		override

#define SCREEN_X		GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_Y		GetSystemMetrics(SM_CYSCREEN)

#define CENTER_X(x)		(SCREEN_X - (x)) / 2
#define CENTER_Y(y)		(SCREEN_Y - (y)) / 2