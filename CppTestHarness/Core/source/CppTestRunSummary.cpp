#include "CppTestRunSummary.h"
#include "../CPPVariousUtils/Cpp_exceptions.h"
#include "../CPPVariousUtils/Cpp_macroDefines.h"

namespace CppTestHarness {


	RunSummary::RunSummary(const CaseCounter& counter) :
		m_Success(counter.SuccessCount()),
		m_FailFixtureSetup(counter.FailFixtureSetupCount()),
		m_FailSetup(counter.FailSetupCount()),
		m_FailTest(counter.FailTestCount()),
		m_FailTeardown(counter.FailTeardownCount()),
		m_Disabled(counter.DisabledCount()),
		m_NotFound(counter.NotFoundCount()) {
	}


	int RunSummary::Total(ICase::TestCaseStatus status) const {
		switch (status) {
		case ICase::TestCaseStatus::ST_SUCCESS:				return this->m_Success;
		case ICase::TestCaseStatus::ST_FAIL_SETUP:			return this->m_FailSetup;
		case ICase::TestCaseStatus::ST_FAIL_TEST:			return this->m_FailTest;
		case ICase::TestCaseStatus::ST_FAIL_CLEANUP:		return this->m_FailTeardown;
		case ICase::TestCaseStatus::ST_FAIL_FIXTURE_SETUP:	return this->m_FailFixtureSetup;
		case ICase::TestCaseStatus::ST_FAIL_FIXTURE_TEARDOWN: return 0; // TODO - remove this type
		case ICase::TestCaseStatus::ST_DISABLED:			return this->m_Disabled;
		case ICase::TestCaseStatus::ST_NOT_EXISTS:			return this->m_NotFound;
		case ICase::TestCaseStatus::ST_NONE:				return 0;
		default:
			throw CppUtils::Cpp_exception(_FL_, _L_("Unhandled test state type"));
		}
	}


	int RunSummary::Total() const {
		return this->m_Success +
			this->m_FailFixtureSetup +
			this->m_FailSetup +
			this->m_FailTest +
			this->m_FailTeardown +
			this->m_Disabled +
			this->m_NotFound;
	}

}
