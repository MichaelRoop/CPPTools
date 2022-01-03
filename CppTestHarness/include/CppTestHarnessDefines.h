///--------------------------------------------------------------------------------------
/// @brief	To export types and typedefs used by CppTestHarness classes
///
/// @author		Michael Roop
/// @date		2022
/// @version	1.0
///
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_HARNESS_DEFINES_H)
#define ICPP_TEST_HARNESS_DEFINES_H


#if defined(_WIN32) || defined (_WIN64)
#	include <Windows.h>
#	if defined(CPPTESTHARNESS_EXPORTS)
#		pragma message("Exporting CppHarness Classes")
#		define TSTHARNESS_API __declspec(dllexport)
#		define TSTHARNESS_EXPORT
#	else
#		pragma message("Importing CppHarness Classes")
#		define TSTHARNESS_API __declspec(dllimport)
#		define TSTHARNESS_EXP_TEMPLATE extern
#	endif
#elif defined(__linux) || defined(_linux_)
#	if defined(CPPTESTHARNESS_EXPORTS)
#		pragma message("Exporting CppHarness Classes")
#		define TSTHARNESS_API
#		define TSTHARNESS_EXP_TEMPLATE
#	else
#		pragma message("Importing CppHarness Classes")
#		define TSTHARNESS_API
#		define TSTHARNESS_EXP_TEMPLATE extern
#	endif
#else
#   pragma message("*** Neither _WIN32 or _WIN64 or Linux defined ***")
#endif

//disable warnings on 255 char debug symbols
#pragma warning (disable : 4786)
//disable warnings on extern before template instantiation
#pragma warning (disable : 4231)

#endif