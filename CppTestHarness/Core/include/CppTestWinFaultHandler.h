#if !defined(CPP_TEST_WIN_FAULT_HANDLER_H)
#define CPP_TEST_WIN_FAULT_HANDLER_H

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>
#include <excpt.h>
#include "../CPPVariousUtils/Cpp_string.h"

namespace CppTestHarness {

	class ITestCaseHolder;

	/// <summary>
	/// Handles the translation of structured exceptions to catch IO level faults as well  
	/// as regular exceptions
	/// </summary>
	class WinExceptionHandler {
	public:

		/// @breif	Process the windows structured exception information
		static int Process(
			unsigned int code, struct _EXCEPTION_POINTERS* ep, ITestCaseHolder* currentTestCase);

	private:
		static int StuffMsg(
			ITestCaseHolder* currentTestCase, const CppUtils::Cpp_string& msg);

	};

}

#endif
