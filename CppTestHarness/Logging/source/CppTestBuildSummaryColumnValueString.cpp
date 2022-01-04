#include "CppTestBuildSummaryColumnValueString.h"
#include "ICppTestLog.h"
#include "CppTestEngine.h"
#include "../CPPVariousUtils/Cpp_pointerException.h"


namespace CppTestHarness {

	BuildSummaryColumnValueString::BuildSummaryColumnValueString(
		Cpp_stringstream& os,
		const Cpp_string& delimiter,
		const Cpp_string& strQuotes,
		ILog* theLog) 
		: BuildColumnValueString(os, delimiter, strQuotes),
		m_log(theLog) {
		CppUtils::Cpp_pointerException::ptrAssert(theLog, _FL_);
	}


	void BuildSummaryColumnValueString::Build(const FieldPair& field) {
		// add upper case conversion later.
		if (field.first.compare(_L_("SuccessCount")) == 0) {
			this->m_os << this->m_log->GetSuccessCount();
		}
		else if (field.first.compare(_L_("FailInitCount")) == 0) {
			this->m_os << this->m_log->GetFailInitCount();
		}
		else if (field.first.compare(_L_("FailSetupCount")) == 0) {
			this->m_os << this->m_log->GetFailSetupCount();
		}
		else if (field.first.compare(_L_("FailTestCount")) == 0) {
			this->m_os << this->m_log->GetFailTestCount();
		}
		else if (field.first.compare(_L_("FailCleanupCount")) == 0) {
			this->m_os << this->m_log->GetFailCleanupCount();
		}
		else if (field.first.compare(_L_("NotExistCount")) == 0) {
			this->m_os << this->m_log->GetNotExistCount();
		}
		else if (field.first.compare(_L_("TotalCount")) == 0) {
			this->m_os << this->m_log->GetTotalCount();
		}
		else if (field.first.compare(_L_("RunId")) == 0) {
			this->m_os << Engine::Instance().GetRunId();
		}
		else {
			//very bad
			Cpp_stringstream os;
			os << field.first
				<< _L_(": Illegal field name.  Allowed are SuccessCount, FailInitCount, FailSetupCount, FailTestCount, FailCleanupCount, NotExistCount, RunId, TotalCount.");
			Cpp_exception::assertCondition(false, _FL_, os.str());
		}
	}

}
