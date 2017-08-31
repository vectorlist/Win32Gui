#pragma once


//Type
typedef char				int8;
typedef unsigned char		uint8;
typedef short				int16;
typedef unsigned short		uint16;
typedef signed int			int32;
typedef unsigned int		uint32;

//typedef unsigned int		uint

#if COMPILER == COMPILER_MSVC
typedef __int64				int64;
typedef unsigned __int64	uint64;
#else
typedef long long			int64;
typedef unsigned long long	uint64;
#endif

#include <array>
#include <ostream>

using ivec2 = std::array<int32, 2>;

inline std::ostream& operator<<(std::ostream &os, const ivec2& data)
{
	os << "ivec2( " << data[0] << ", " << data[1] << ")";
	return os;
}

#define LNULL				0L