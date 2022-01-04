#include "CppTestFixtureTestCaseNames.h"

namespace CppTestHarness {


	FixutureTestCaseNames::FixutureTestCaseNames(const CppUtils::Cpp_string& name)
		: m_name(name) {
	}


	FixutureTestCaseNames::FixutureTestCaseNames(const FixutureTestCaseNames& obj) {
		this->m_name = obj.m_name;
		this->m_testCaseNames = obj.m_testCaseNames;
	}


	const CppUtils::Cpp_string& FixutureTestCaseNames::FixtureName() const {
		return this->m_name;
	}


	const std::vector<CppUtils::Cpp_string>& FixutureTestCaseNames::TestCaseNames() const {
		return this->m_testCaseNames;
	}


	void FixutureTestCaseNames::AddTestCaseName(const CppUtils::Cpp_string& name) {
		this->m_testCaseNames.push_back(name);
	}

} 