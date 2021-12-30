#pragma once

namespace CppUtils {

///--------------------------------------------------------------------------------------
/// @file	Cpp_char.h
/// @brief	Cross char width char functions.
///
/// @author		Michael Roop
/// @date		2021
/// @version	1.0
///
/// @todo	Make char versions for trim functions.
///
/// Copyright 2021 Michael Roop
///--------------------------------------------------------------------------------------

#if defined(CPP_USE_WIDE_STR)
#pragma message("CPP_USE_WIDE_STR defined")
	typedef wchar_t			Cpp_char;
	/// @brief	Variable with const string macro.
	#define L(str) L##str
	#define _L_(str) L##str
#else
	typedef char			Cpp_char;
	/// @brief	Variable with const string macro.
	#define L( str ) str
	#define _L_( str ) str
#endif

/// @todo	Make char versions for trim functions.
//mr_string TrimRight( const mr_string& str );
//
//
//mr_string TrimLeft( const mr_string& str );
//
//
//mr_string Trim( const mr_string& str );


}


