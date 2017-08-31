#pragma once

#define PLATFORM_WIN32			1
#define PLATFORM_LINUX			2
#define PLATFORM_OSX			3
#define PLATFORM_IOS			4
#define PLATFORM_ANDROID		5

#define COMPILER_MSVC			1
#define COMPILER_GNUC			2
#define COMPILER_INTER			3
#define COMPILER_CLANG			4

#define PLATFORM_BIT_x86_32		1
#define PLATFORM_BIT_x86_64		2

#if defined(_MSC_VER)
#define COMPILER				COMPILER_MSVC
#define COMPILER_VER			_MSC_VER
#define THREADLOCAL				__declspec(thread)
#undef	__PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__		__FUNCSIG__
#else
#pragma error "Unknown compiler."
#endif

#if defined(__WIN32__) || defined(_WIN32)
#define PLATFORM				PLATFORM_WIN32
#elif defined(__APPLE_CC__)
#define PLATFORM				PLATFORM_OSX
#else
#define PLATFORM				PLATFORM_LINUX
#endif

//find platform current bit
#if defined(__x86_64__) || defined(_M_X64)
#define PLATFORM_BIT			PLATFORM_BIT_x86_64
#else
#define PLATFORM_BIT			PLATFORM_BIT_x86_32			
#endif

//secure versions aren't multiplatform, so we won't be using them
#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

