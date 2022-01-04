#include "CppTestCase.h"

namespace CppTestHarness {

	Case::Case(
		const CppUtils::Cpp_string& fixtureName,
		const CppUtils::Cpp_string& name,
		const CppUtils::Cpp_string& desc) :
		ICase(fixtureName, name, desc) {
	}


	Case::~Case() {
	}


	void Case::Reset() {
		this->Status = TestCaseStatus::ST_NONE;
		//this->m_args.clear();
		CppUtils::ResetStringStream(this->MsgBuffer);
		CppUtils::ResetStringStream(this->MsgBufferEmbedded);
		CppUtils::ResetStringStream(this->MsgBufferVerbose);
		this->SetupTimeMs = 0;
		this->ExecTimeMs = 0;
		this->CleanupTimeMs = 0;
	}

} // end namespace
