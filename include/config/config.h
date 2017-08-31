#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <platformconfig.h>
#include <stdconfig.h>
#include <typeconfig.h>
#include <macroconfig.h>


//winapi
#include <brush.h>
#include <Point.h>
#include <win32utils.h>

#include <log.h>


#define OVERRIDE		override

#define SCREEN_X		GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_Y		GetSystemMetrics(SM_CYSCREEN)

#define CENTER_X(x)		(SCREEN_X - (x)) / 2
#define CENTER_Y(y)		(SCREEN_Y - (y)) / 2