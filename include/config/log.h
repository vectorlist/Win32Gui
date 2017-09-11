#pragma once

#include <string>
#include <macroconfig.h>
#include <iostream>
#include <Windows.h>
#include <assert.h>

#define LOG_ERROR(x)			Log::LogError(x)
#define LOG_FORMAT(x, ...)		Log::LogFormat(x, ##__VA_ARGS__)
#define LOG_ASSERT(x,xx)		Log::LogAssert(x,xx)
#define LOG_FATAL(x)			Log::LogError((x) + std::string("\n") + __PRETTY_FUNCTION__ + " [" + __FILE__ + ":" + std::to_string(__LINE__) + "]\n")

class Log
{
public:
	Log(){}

	static void LogError(const std::string &code);
	static void LogAssert(bool con, const std::string &code);
	template<typename ... Args>
	static std::string LogFormat(const std::string& format, Args ... args);
};

inline void Log::LogError(const std::string &code)
{
	MessageBoxA(NULL, code.c_str(), "Error", MB_OK);
	//MessageBox(NULL, TEXT(a), TEXT("Error"), MB_OK);
}

inline void Log::LogAssert(bool b, const std::string &code)
{
	if (b) {
		MessageBoxA(NULL, code.c_str(), "Error", MB_OK);
		assert(0 && code.c_str());
	}
}

template<typename ... Args>
inline std::string Log::LogFormat(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1);
}

