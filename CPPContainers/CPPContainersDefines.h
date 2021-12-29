#pragma once

// Cross platform DLL export import defines
#if defined(WIN)
#if defined(CPPCONTAINERS_EXPORTS)
#pragma message("Exporting CppContainers DLL Classes")
#define CPPTESTUTILS_API __declspec( dllexport )

//#define EXP_TEMPLATE
#else
#pragma message("Importing CppContainers DLL Classes")
#define CPPTESTUTILS_API __declspec(dllimport)
//#define EXP_TEMPLATE extern
#endif
#elif defined(__linux) || defined(_linux_)
#if defined(CPPCONTAINERS_EXPORTS)
#pragma message("Exporting CppContainers DLL Classes")
#define CPPTESTUTILS_API
//#define EXP_TEMPLATE
#else
#pragma message("Importing CppContainers DLL Classes")
#define CPPTESTUTILS_API
//#define EXP_TEMPLATE extern
#endif
#else
#   pragma message("*** Neither WIN or Linux defined ***")
#endif

