#pragma once

// Cross platform DLL export import defines
#if defined(_WIN32) || defined(_WIN64)
	#if defined(CPPSTATEMACHINE_EXPORTS)
		#pragma message("Exporting CppStateMachine DLL Classes")
		#define CPP_SM_API __declspec(dllexport)
		//#define EXP_TEMPLATE
	#else
		#pragma message("Importing CppStateMachine DLL Classes")
		#define CPP_SM_API __declspec(dllimport)
		//#define EXP_TEMPLATE extern
	#endif
#elif defined(__linux) || defined(_linux_)
	#if defined(CPPSTATEMACHINE_EXPORTS)
		#pragma message("Exporting CppStateMachine DLL Classes")
		#define CPP_SM_API
		//#define EXP_TEMPLATE
	#else
		#pragma message("Importing CppStateMachine DLL Classes")
		#define CPP_SM_API
		//#define EXP_TEMPLATE extern
	#endif
#else
	#pragma message("*** Neither WIN or Linux defined ***")
#endif


//// Force export of the std char and wchar_t string and vector
//#if defined(_WIN32)
//   //disable warnings on 255 char debug symbols
//#pragma warning (disable : 4786)
////disable warnings on extern before template instantiation
//#pragma warning (disable : 4231)
//
//// The order is important. Do not change
//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<char>;
//EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<char, struct std::char_traits<char>, std::allocator<char> >;
//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator< std::basic_string<char, struct std::char_traits<char>, std::allocator<char> > >;
//EXP_TEMPLATE template class CPPTESTUTILS_API std::vector< std::basic_string<char, struct std::char_traits<char>, std::allocator<char> > >;
//
//
//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<wchar_t>;
//EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >;
//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator< std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> > >;
//EXP_TEMPLATE template class CPPTESTUTILS_API std::vector< std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> > >;
//#endif

// TODO - figure out a way to get the string npos exported. It will cause link failures in with classes using the npos or substring

//#endif
