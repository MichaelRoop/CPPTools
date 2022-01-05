#pragma once


#include "../CPPVariousUtils/Cpp_string.h"
#include "../CPPVariousUtils/Cpp_iostream.h"
//#include "../CPPVariousUtils/Cpp_char.h"
#include "../CPPVariousUtils/CppSharedPtr.h"


using CppUtils::Cpp_string;
using CppUtils::Cpp_ostream;
using CppUtils::CppSharedPtr;


#if defined (_WIN32) || defined (_WIN64)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>

	#if defined(CPPINIFILE_EXPORTS)
		#pragma message("Exporting CppIniFile DLL Classes")
		#define CPPINI_EXPORT __declspec(dllexport)
		#define CPPINI_EXTERN
	#else
		#pragma message("Importing CppIniFile DLL Classes")
		#define CPPINI_EXPORT __declspec(dllimport)
		#define CPPINI_EXTERN extern
	#endif

#elif defined(__linux) || defined(_linux_)
	#if defined(CPPINIFILE_EXPORTS)
		#pragma message("Exporting CppIniFile DLL Classes")
		#define CPPINI_EXPORT
		#define CPPINI_EXTERN
	#else
		#pragma message("Importing CppIniFile DLL Classes")
		#define CPPINI_EXPORT
		#define CPPINI_EXTERN
	#endif
#else
#   pragma message("*** Neither WIN or Linux defined ***")




#endif