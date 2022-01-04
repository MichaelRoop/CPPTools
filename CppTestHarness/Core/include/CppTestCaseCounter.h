#if !defined(CPP_TEST_CASE_COUNTER_H)
#define CPP_TEST_CASE_COUNTER_H

#include "ICppTestRunSummary.h"
#include "../CPPVariousUtils/CppSharedPtr.h"
#include "../CPPVariousUtils/Cpp_string.h"

namespace CppTestHarness {

	class ICase;

	/// <summary>Accumatalate summary information on test cases through a run</summary>
	class CaseCounter {
	public:

		/// @brief	Constructor
		CaseCounter();


		/// @brief	Increment counts with test case information
		void Count(const ICase& testCase);


		/// @brief	Called to reset internal state
		void Reset();


		/// @brief	Get a snapshot of the latest test summary data
		CppUtils::CppSharedPtr<IRunSummary> Summary(const CppUtils::Cpp_string& runId) const;


		/// @brief	Number of test with status success
		int SuccessCount() const;


		/// @brief	Number of test with status Fixture Setup Failed
		int FailFixtureSetupCount() const;


		/// @brief	Number of test with status Setup Failed
		int FailSetupCount() const;


		/// @brief	Number of test with status Test Failed
		int FailTestCount() const;


		/// @brief	Number of test with status Teardown Failed
		int FailTeardownCount() const;


		/// @brief	Number of test with status Not Found
		int NotFoundCount() const;


		/// @brief	Number of test with status Disabled
		int DisabledCount() const;

	public:
		int m_success;			///< Counter for successful tests.
		int	m_failFixtureSetup;	///< Counter tests that failed on fixture setup.
		int	m_failSetup;		///< Counter tests that failed on setup.
		int	m_failTest;			///< Counter tests that failed on test.
		int	m_failTeardown;		///< Counter tests that failed on teardown.
		int	m_notFound;			///< Counter tests not found.
		int	m_disabled;			///< Counter tests not found.

	};

} // end namespace 


#endif
