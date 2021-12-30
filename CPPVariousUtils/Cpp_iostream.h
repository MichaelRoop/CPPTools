#pragma once

#include "CppUtilsDefines.h"
#include <iostream>
#include <ostream>

namespace CppUtils {

#if defined(CPP_USE_WIDE_STR)
	typedef std::wostream	Cpp_ostream;
	#define mr_cout			std::wcout
#else
	typedef std::ostream	Cpp_ostream;
	#define mr_cout			std::cout
#endif


// Force export of i and o stream template class with different char types
//#if defined(WIN32) 
//	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_ostream<wchar_t, std::char_traits<wchar_t> >;
//	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_ostream<wchar_t, std::char_traits<wchar_t> >;
//	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_istream<char, std::char_traits<char> >;
//	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_ostream<char, std::char_traits<char> >;
//#endif

}


