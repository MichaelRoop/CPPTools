///--------------------------------------------------------------------------------------
/// @brief	Handle the cross platform selection of segfault capture 
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_SEGFAULT_HANDLER_H)
#define CPP_TEST_SEGFAULT_HANDLER_H

#if defined (_WIN32) || defined (_WIN64)
#	include "CppTestWinFaultHandler.h"
#else
#endif

namespace CppTestHarness {


#if defined (_WIN32) || defined (_WIN64)
#	define START_SEGFAULT_CATCH_BLOCK	__try {	
#	define END_SEGFAULT_CATCH_BLOCK		} __except(WinExceptionHandler::Process(GetExceptionCode(), GetExceptionInformation(), this->m_currentTestCase)) {}
#else
#	define START_SEGFAULT_CATCH_BLOCK	try {	
#	define END_SEGFAULT_CATCH_BLOCK		} catch (...) {}
#endif


} // end namespace

#endif
