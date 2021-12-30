#pragma once

#include "CppUtilsDefines.h"
#include <sstream>

///--------------------------------------------------------------------------------------
/// @file	mr_sstream.h
/// @brief	Cross char witdh defines for string stream class.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------

namespace CppUtils {

	// defines a string stream that is wide or narrow depending on MR_USE_WIDE_STR define
#if defined(CPP_USE_WIDE_STR)
	typedef std::wstringstream	Cpp_stringstream;
	typedef std::wistringstream	Cpp_istringstream;
	typedef std::wostringstream	Cpp_ostringstream;
#else
	typedef std::stringstream	Cpp_stringstream;
	typedef std::istringstream	Cpp_istringstream;
	typedef std::ostringstream	Cpp_ostringstream;
#endif

/// @brief	Rest the mr_stringstream so it can be reused
///
/// @param	ss	The mr_stringstream to reset
CPPUTILS_API void ResetStringStream(Cpp_stringstream& ss);


	// Force export of std string stream template classe with different char types 
#if defined(WIN) 
	EXP_TEMPLATE template class CPPUTILS_API std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >;
	EXP_TEMPLATE template class CPPUTILS_API std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >;
#endif

}




