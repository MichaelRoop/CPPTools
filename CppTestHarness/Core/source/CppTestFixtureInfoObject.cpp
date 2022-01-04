#include "CppTestFixtureInfoObject.h"


namespace CppTestHarness {


	TestFixtureInfoObject::TestFixtureInfoObject(const CppUtils::Cpp_string& name)
		: m_name(CppUtils::Trim(name)) {
	}


	TestFixtureInfoObject::~TestFixtureInfoObject() {
		// Nothing to do
	}


	const CppUtils::Cpp_string& TestFixtureInfoObject::GetName() const {
		return this->m_name;
	}


	const void TestFixtureInfoObject::SetName(CppUtils::Cpp_string& name) {
		this->m_name = CppUtils::Trim(name);
	}


	const std::vector<TestInfoObject>& TestFixtureInfoObject::GetTestInfoVector() {
		return this->m_tests;
	}


	void TestFixtureInfoObject::AddTestInfo(const TestInfoObject& info) {
		this->m_tests.push_back(info);
	}

}

