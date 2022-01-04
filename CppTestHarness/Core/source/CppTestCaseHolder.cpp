#include "CppTestCaseHolder.h"
#include "CppTestCase.h"
#include <assert.h>


namespace CppTestHarness {

	TestCaseHolder::TestCaseHolder(
		IFixture::Ifixture_method_ptr testPtr, 
		const CppUtils::Cpp_string& fixtureName, 
		const CppUtils::Cpp_string& name,
		const CppUtils::Cpp_string& description)
		: m_test(testPtr),
		m_testData(new Case(fixtureName, name, description)) {
	}


	TestCaseHolder::~TestCaseHolder() {
		if (this->m_testData != 0) {
			delete this->m_testData;
			this->m_testData = 0;
		}
	}


	IFixture::Ifixture_method_ptr TestCaseHolder::Pointer() const {
		return this->m_test;
	}


	ICase* TestCaseHolder::Data() const {
		return this->m_testData;
	}


	void TestCaseHolder::Reset() {
		assert(this->m_testData);
		this->m_testData->Reset();
	}

}

