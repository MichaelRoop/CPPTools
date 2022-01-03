#pragma once


#include "../CPPVariousUtils/Cpp_string.h"
#include "../CPPVariousUtils/Cpp_iostream.h"
//#include "../CPPVariousUtils/Cpp_char.h"



#if defined (_WIN32) || defined (_WIN64)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>

	#if defined(CPPINIFILE_EXPORTS)
		#pragma message("Exporting CppIniFile DLL Classes")
		#define CPPINI_API __declspec(dllexport)
		#define EXP_INI_TEMPLATE
	#else
		#pragma message("Importing CppIniFile DLL Classes")
		#define CPPINI_API __declspec(dllimport)
		#define EXP_INI_TEMPLATE extern
	#endif

#elif defined(__linux) || defined(_linux_)
	#if defined(CPPINIFILE_EXPORTS)
		#pragma message("Exporting CppIniFile DLL Classes")
		#define CPPINI_API
		#define EXP_INI_TEMPLATE
	#else
		#pragma message("Importing CppIniFile DLL Classes")
		#define CPPINI_API
		#define EXP_INI_TEMPLATE
	#endif
#else
#   pragma message("*** Neither WIN or Linux defined ***")




#endif