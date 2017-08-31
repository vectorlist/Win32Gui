#pragma once

#define SAFE_DELETE(x)	if(x){ delete (x); x = nullptr;}

#define CPP_98	199711L

#if __cplusplus <= CPP_98
#define CPP11_SUPPORTED true
#else
#define CPP11_SUPPORTED	false
#endif

//in VS 2015 indent dosent supported
#define CLASS_DISABLE_COPY_ASSIGN(T)\
	T(const T&) = delete;				\
	T& operator=(const T&) = delete;	


#include <iostream>

#define LOG					std::cout
#define ENDN				"\n"
#define ENDL				std::endl

#define PAUSE				system("pause")

//=========================================================
//API
//#define API_EXPORT __declspec(dllexport)

#if defined(API_EXPORT)
#define WINDOW_API	API_EXPORT
#else
#define WINDOW_API	//nothing
#endif

#define SYSTEM_WINDOWS

//====================== Begine End Namespace =================================
#define BEGIN_GLOBAL		namespace Global{
#define END_GLOBAL			}

#define BEGIN_LOCAL			namespace Local{
#define END_LOCAL			}

#define UNUSED(x) [&x]{}()

#undef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCSIG__