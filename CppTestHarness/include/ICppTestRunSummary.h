///--------------------------------------------------------------------------------------
/// @brief	Interface for test run summary data
///
/// @author		Michael Roop
/// @date		2022
/// @version	1.0
///
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_RUN_SUMMARY_H)
#define ICPP_TEST_RUN_SUMMARY_H

#include "ICppTestCase.h"
#include "include/CppTestHarnessDefines.h"
#include "../CPPVariousUtils/Cpp_string.h"

namespace CppTestHarness {

	///--------------------------------------------------------------------------------------
	///	@brief	Holder for test case summary data
	///--------------------------------------------------------------------------------------
	class TSTHARNESS_API IRunSummary {
	public:

		/// @brief	Get the total number of test of a given status
		/// @param	status	The total number of tests of this status will be returned
		virtual int Total(CppTestHarness::ICase::TestCaseStatus status) const = 0;


		/// @brief	Get the total number of test run
		virtual int Total() const = 0;

	};

} 

#endif
