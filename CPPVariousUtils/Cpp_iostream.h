#pragma once

#include "CppUtilsDefines.h"
#include <iostream>
#include <ostream>

namespace CppUtils {

#if defined(CPP_USE_WIDE_STR)
	typedef std::wostream	Cpp_ostream;
	#define Cpp_cout		std::wcout
#else
	typedef std::ostream	Cpp_ostream;
	#define Cpp_cout		std::cout
#endif


// Force export of i and o stream template class with different char types
#if defined(_WIN32) || defined (_WIN64) 
	EXP_UTILS_TEMPLATE template class std::basic_ostream<wchar_t, std::char_traits<wchar_t> >;
	EXP_UTILS_TEMPLATE template class std::basic_ostream<wchar_t, std::char_traits<wchar_t> >;
	EXP_UTILS_TEMPLATE template class std::basic_istream<char, std::char_traits<char> >;
	EXP_UTILS_TEMPLATE template class std::basic_ostream<char, std::char_traits<char> >;
#endif

}


