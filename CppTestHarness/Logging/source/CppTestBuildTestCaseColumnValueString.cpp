#include "CppTestBuildTestCaseColumnValueString.h"
#include "CppTestCase.h"
#include "CppTestEngine.h"

namespace CppTestHarness {

	BuildTestCaseColumnValueString::BuildTestCaseColumnValueString(
		Cpp_stringstream& os,
		const Cpp_string& delimiter,
		const Cpp_string& strQuotes,
		ICase& testCase)
		: BuildColumnValueString(os, delimiter, strQuotes),
		m_testCase(testCase) {
	}


	void BuildTestCaseColumnValueString::Build(const FieldPair& field) {
		// add upper case conversion later.
		if (field.first.compare(_L_("ID")) == 0) {
			this->ConcatenateStr(this->m_testCase.Name);
		}
		else if (field.first.compare(_L_("Description")) == 0) {
			this->ConcatenateStr(this->m_testCase.Description);
		}
		else if (field.first.compare(_L_("Status")) == 0) {
			this->ConcatenateStr(Case::ToString(this->m_testCase.Status));
		}
		else if (field.first.compare(_L_("Message")) == 0) {
			this->ConcatenateStr(this->m_testCase.MsgBuffer.str());
		}
		else if (field.first.compare(_L_("SetupTime")) == 0) {
			this->m_os << this->m_testCase.SetupTimeMs;
		}
		else if (field.first.compare(_L_("ExecTime")) == 0) {
			this->m_os << this->m_testCase.ExecTimeMs;
		}
		else if (field.first.compare(_L_("CleanupTime")) == 0) {
			this->m_os << this->m_testCase.CleanupTimeMs;
		}
		else if (field.first.compare(_L_("RunId")) == 0) {
			this->m_os << Engine::Instance().GetRunId();
		}
		else if (field.first.compare(_L_("VerboseMessage")) == 0) {
			this->ConcatenateVerboseBufferStr(this->m_testCase.MsgBufferVerbose.str());
		}
		else {
			//very bad
			Cpp_stringstream os;
			os << field.first
				<< _L_(": Illegal field name.  Allowed are ID, Description, Status, SetupTime, ExecTime, CleanupTime, RunId Message, VerboseMessage.");
			Cpp_exception::assertCondition(false, _FL_, os.str());
		}
	}


	void BuildTestCaseColumnValueString::ConcatenateVerboseBufferStr(const Cpp_string& str) {
		this->m_os << m_strQuotes.c_str();
		if (!str.empty()) {
			this->m_os << std::endl
				<< L("-----------------------------------") << std::endl
				<< str.c_str()
				<< std::endl
				<< std::endl;
		}
		this->m_os << m_strQuotes.c_str();
	}

}
