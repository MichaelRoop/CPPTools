#if defined (_WIN32) || defined (_WIN64)

#include "CppTestWinFaultHandler.h"
#include "ICppTestCaseHolder.h"

namespace CppTestHarness {

	int WinExceptionHandler::StuffMsg(ITestCaseHolder* currentTestCase, const Cpp_string& msg) {
		if (currentTestCase != 0) {
			CppUtils::ResetStringStream(currentTestCase->Data()->MsgBuffer);
			currentTestCase->Data()->MsgBuffer << msg;
		}
		else {
			// Nothing to do
		}
		return EXCEPTION_EXECUTE_HANDLER;
	}


	int WinExceptionHandler::Process(unsigned int code, struct _EXCEPTION_POINTERS* ep, ITestCaseHolder* testCase) {
		switch (code) {
		case EXCEPTION_ACCESS_VIOLATION:
			return StuffMsg(testCase, L("Access Violation"));
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			return StuffMsg(testCase, L("Caught devide by zero fault"));
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			return StuffMsg(testCase, L("EXCEPTION_DATATYPE_MISALIGNMENT"));
		case EXCEPTION_BREAKPOINT:
			return StuffMsg(testCase, L("EXCEPTION_BREAKPOINT"));
		case EXCEPTION_SINGLE_STEP:
			return StuffMsg(testCase, L("EXCEPTION_SINGLE_STEP"));
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			return StuffMsg(testCase, L("EXCEPTION_ARRAY_BOUNDS_EXCEEDED"));
		case EXCEPTION_FLT_DENORMAL_OPERAND:
			return StuffMsg(testCase, L("EXCEPTION_FLT_DENORMAL_OPERAND"));
		case EXCEPTION_FLT_INEXACT_RESULT:
			return StuffMsg(testCase, L("EXCEPTION_FLT_INEXACT_RESULT"));
		case EXCEPTION_FLT_INVALID_OPERATION:
			return StuffMsg(testCase, L("EXCEPTION_FLT_INVALID_OPERATION"));
		case EXCEPTION_FLT_OVERFLOW:
			return StuffMsg(testCase, L("EXCEPTION_FLT_OVERFLOW"));
		case EXCEPTION_FLT_STACK_CHECK:
			return StuffMsg(testCase, L("EXCEPTION_FLT_STACK_CHECK"));
		case EXCEPTION_FLT_UNDERFLOW:
			return StuffMsg(testCase, L("EXCEPTION_FLT_UNDERFLOW"));
		case EXCEPTION_INT_OVERFLOW:
			return StuffMsg(testCase, L("EXCEPTION_INT_OVERFLOW"));
		case EXCEPTION_PRIV_INSTRUCTION:
			return StuffMsg(testCase, L("EXCEPTION_PRIV_INSTRUCTION"));
		case EXCEPTION_IN_PAGE_ERROR:
			return StuffMsg(testCase, L("EXCEPTION_IN_PAGE_ERROR"));
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			return StuffMsg(testCase, L("EXCEPTION_ILLEGAL_INSTRUCTION"));
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			return StuffMsg(testCase, L("EXCEPTION_NONCONTINUABLE_EXCEPTION"));
		case EXCEPTION_STACK_OVERFLOW:
			return StuffMsg(testCase, L("EXCEPTION_STACK_OVERFLOW"));
		case EXCEPTION_INVALID_DISPOSITION:
			return StuffMsg(testCase, L("EXCEPTION_INVALID_DISPOSITION"));
		case EXCEPTION_GUARD_PAGE:
			return StuffMsg(testCase, L("EXCEPTION_GUARD_PAGE"));
		case EXCEPTION_INVALID_HANDLE:
			return StuffMsg(testCase, L("EXCEPTION_INVALID_HANDLE"));
			//case 0xE04D5343:
			//	return StuffMsg(testCase, L("ZOWEE - Caught a real exception........"));

			//case EXCEPTION_POSSIBLE_DEADLOCK:
			//	return StuffMsg(testCase, L("EXCEPTION_POSSIBLE_DEADLOCK"));

		default:

			//_set_se_translator(ep[0]);


			// this is where reqular exceptions come
			//return EXCEPTION_CONTINUE_SEARCH;
			//printf("-------------------Default\n");

			return EXCEPTION_EXECUTE_HANDLER;
		}
	}


}

#endif