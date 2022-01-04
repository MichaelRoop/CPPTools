#include "CppTestCaseCounter.h"
#include "ICppTestCase.h"
#include "CppTestRunSummary.h"
#include "../CPPVariousUtils/Cpp_exceptions.h"
#include "CppTestHarnessDefines.h"

namespace CppTestHarness {

	CaseCounter::CaseCounter() {
		this->Reset();
	}


	void CaseCounter::Count(const ICase& testCase) {
		switch (testCase.Status) {
		case  ICase::TestCaseStatus::ST_SUCCESS:
			++this->m_success;
			break;
		case ICase::TestCaseStatus::ST_FAIL_TEST:
			++this->m_failTest;
			break;
		case ICase::TestCaseStatus::ST_FAIL_SETUP:
			++this->m_failSetup;
			break;
		case ICase::TestCaseStatus::ST_FAIL_CLEANUP:
			++this->m_failTeardown;
			break;
		case ICase::TestCaseStatus::ST_FAIL_FIXTURE_SETUP:
			++this->m_failFixtureSetup;
			break;
		case ICase::TestCaseStatus::ST_DISABLED:
			++this->m_disabled;
			break;
		case ICase::TestCaseStatus::ST_NOT_EXISTS:
			++this->m_notFound;
			break;
			// TODO - REMOVE - fixture teardown never counted - no test case to save it to
		case ICase::TestCaseStatus::ST_FAIL_FIXTURE_TEARDOWN:
			//	++this->m_stFailCleanupCount;
			break;
		default:
			// TODO stream the enum class
			CppUtils::Cpp_stringstream ss;
			ss << _L_("Invalid testCase state:") << ICase::ToString(testCase.Status);
			throw CppUtils::Cpp_exception(_FL_, ss.str());
		}
	}


	/// @brief	Called to reset internal state
	void CaseCounter::Reset() {
		this->m_success = 0;
		this->m_failFixtureSetup = 0;
		this->m_failSetup = 0;
		this->m_failTest = 0;
		this->m_failTeardown = 0; // TODO - remove since we are not tracking it
		this->m_notFound = 0;
		this->m_disabled = 0;
	}


	CppUtils::CppSharedPtr<IRunSummary> CaseCounter::Summary(const CppUtils::Cpp_string& runId) const {
		return CppUtils::CppSharedPtr<IRunSummary>(new RunSummary(*this));
	}


	int CaseCounter::SuccessCount() const {
		return this->m_success;
	}


	int CaseCounter::FailFixtureSetupCount() const {
		return this->m_failFixtureSetup;
	}


	int CaseCounter::FailSetupCount() const {
		return this->m_failSetup;
	}


	int CaseCounter::FailTestCount() const {
		return this->m_failTest;
	}


	int CaseCounter::FailTeardownCount() const {
		return this->m_failTeardown;
	}


	int CaseCounter::NotFoundCount() const {
		return this->m_notFound;
	}


	int CaseCounter::DisabledCount() const {
		return this->m_disabled;
	}


}
