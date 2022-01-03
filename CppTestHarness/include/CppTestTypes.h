///--------------------------------------------------------------------------------------
/// @brief	To export types and typedefs used by MrTest classes
///
/// @author		Michael Roop
/// @date		2022
/// @version	1.0
///
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_TYPE_H)
#define CPP_TEST_TYPE_H

#include "include/CppTestHarnessDefines.h"
#include "include/ICppTestCase.h"
#include "include/ICppTestRunSummary.h"


namespace CppTestHarness {

/// @brief	Typedef of a call back event that will be called to send back results data from 
///			one test case
typedef void (* DataLoggedEvent) (const CppTestHarness::ICase&);


/// @brief	Typedef of a call back event that will be called to send back summary data from the entire
///			group of test case run
typedef void (* TestRunSummaryData) (const MrTest::IRunSummary&);

} // end namespace

// Force export so it can be used in of std contained object 
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppTestHarness::DataLoggedEvent>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppTestHarness::DataLoggedEvent>;

// Force export so it can be used in of std contained object 
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppTestHarness::TestRunSummaryData>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppTestHarness::TestRunSummaryData>;


#endif