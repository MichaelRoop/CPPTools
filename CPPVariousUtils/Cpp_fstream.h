#pragma once
#include "CppUtilsDefines.h"
#include <fstream>

namespace CppUtils {

	// Narrow and wide type definitions
#if defined(CPP_USE_WIDE_STR)
	typedef std::wifstream	Cpp_ifstream;
	typedef std::wofstream	Cpp_ofstream;
#else
	typedef std::ifstream	Cpp_ifstream;
	typedef std::ofstream	Cpp_ofstream;
#endif

}

// Force export of std file stream template classe with different char types 
#if defined(_WIN32) 
	// DONT THINK EXPORT TEMPLATE CLASS with CPPUTILS_API
	EXP_UTILS_TEMPLATE template class std::basic_filebuf<wchar_t, std::char_traits<wchar_t> >;
	EXP_UTILS_TEMPLATE template class std::basic_filebuf<char, std::char_traits<char> >;

	EXP_UTILS_TEMPLATE template class std::basic_ifstream<wchar_t, std::char_traits<wchar_t> >;
	EXP_UTILS_TEMPLATE template class std::basic_ofstream<wchar_t, std::char_traits<wchar_t> >;
	EXP_UTILS_TEMPLATE template class std::basic_ifstream<char, std::char_traits<char> >;
	EXP_UTILS_TEMPLATE template class std::basic_ofstream<char, std::char_traits<char> >;
#endif

