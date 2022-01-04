#include "CppTestLog.h"
#include "CppTestCase.h"

namespace CppTestHarness {

	Log::Log()
		: m_stSuccessCount(0),
		m_stFailInitCount(0),
		m_stFailSetupCount(0),
		m_stFailTestCount(0),
		m_stFailCleanupCount(0),
		m_stNotExistCount(0),
		m_overwrite(false) {
	}


	Log::Log(CppSharedPtr<ILogOutput>& output, CppSharedPtr<ILog>& summaryLog)
		: m_output(output),
		m_summaryLog(summaryLog),
		m_stSuccessCount(0),
		m_stFailInitCount(0),
		m_stFailSetupCount(0),
		m_stFailTestCount(0),
		m_stFailCleanupCount(0),
		m_stNotExistCount(0),
		m_overwrite(false) {
	}


	Log::~Log() {
		if (this->m_output.IsValid()) {
			this->m_output->CloseOutput();
		}
	}


	bool Log::LogTest(ICase& testCase) {
		switch (testCase.Status) {
		case ICase::TestCaseStatus::ST_SUCCESS:
			++this->m_stSuccessCount;
			break;
		case ICase::TestCaseStatus::ST_FAIL_SETUP:
			++this->m_stFailSetupCount;
			break;
		case ICase::TestCaseStatus::ST_FAIL_TEST:
			++this->m_stFailTestCount;
			break;
		case ICase::TestCaseStatus::ST_FAIL_CLEANUP:
			++this->m_stFailCleanupCount;
			break;
		case ICase::TestCaseStatus::ST_NOT_EXISTS:
			++this->m_stNotExistCount;
			break;

		case ICase::TestCaseStatus::ST_DISABLED:
			//++this->m_stNotExistCount;
			// TODO - add disabled count
			break;

			// TODO - Need to modify this with fixture specific counters?
		case ICase::TestCaseStatus::ST_FAIL_FIXTURE_SETUP:
			++this->m_stFailSetupCount;
			break;
		case ICase::TestCaseStatus::ST_FAIL_FIXTURE_TEARDOWN:
			++this->m_stFailCleanupCount;
			break;

		default:
			Cpp_stringstream ss;
			ss << _L_("Invalid testCase state:") << testCase.Status;
			throw Cpp_exception(_FL_, ss.str());
		}

		return this->WriteEntry(testCase);
	}


	bool Log::Summarize() {
		if (this->m_summaryLog.IsValid()) {
			return this->m_summaryLog->WriteSummaryEntry(this);
		}
		return false;
	}


	bool Log::OverwriteExistingLog() const {
		return this->m_overwrite;
	}


	int Log::GetSuccessCount() const {
		return this->m_stSuccessCount;
	}

	int Log::GetFailInitCount() const {
		return this->m_stFailInitCount;
	}


	int Log::GetFailSetupCount() const {
		return this->m_stFailSetupCount;
	}


	int Log::GetFailTestCount() const {
		return this->m_stFailTestCount;
	}


	int Log::GetFailCleanupCount() const {
		return this->m_stFailCleanupCount;
	}


	int Log::GetNotExistCount() const {
		return this->m_stNotExistCount;
	}


	int Log::GetTotalCount() const {
		return
			this->m_stSuccessCount +
			this->m_stFailInitCount +
			this->m_stFailSetupCount +
			this->m_stFailTestCount +
			this->m_stFailCleanupCount +
			this->m_stNotExistCount;
	}


}

