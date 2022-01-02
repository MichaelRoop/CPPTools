#pragma once

// Cross platform DLL export import defines
#if defined(_WIN32) || defined(_WIN64)
	#if defined(CPPCONTAINERS_EXPORTS)
		#pragma message("Exporting CppContainers DLL Classes")
		#define CPPCONTAINERS_API __declspec( dllexport )
	#else
		#pragma message("Importing CppContainers DLL Classes")
		#define CPPCONTAINERS_API __declspec(dllimport)
	#endif
#elif defined(__linux) || defined(_linux_)
	#if defined(CPPCONTAINERS_EXPORTS)
		#pragma message("Exporting CppContainers DLL Classes")
		#define CPPCONTAINERS_API
	#else
		#pragma message("Importing CppContainers DLL Classes")
		#define CPPCONTAINERS_API
	#endif
#else
#   pragma message("*** Neither WIN or Linux defined ***")
#endif

