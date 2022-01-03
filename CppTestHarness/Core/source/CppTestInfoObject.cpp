///--------------------------------------------------------------------------------------
/// @brief	cross platform and char width holder for test information.
///
/// @author		Michael Roop
///
///--------------------------------------------------------------------------------------
#include "include/CppTestInfoObject.h"


namespace CppTestHarness {

TestInfoObject::TestInfoObject() {
	this->m_isActive = false;
	this->m_isNull = true;
	this->m_name = new CppUtils::Cpp_string();
	this->m_arguments = new std::vector<ICaseArgument>();
}


bool TestInfoObject::IsActive() const {
	return this->m_isActive;
}


void TestInfoObject::SetActive(bool active) {
	this->m_isActive = active;
}


bool TestInfoObject::IsNull() const {
	return this->m_isNull;
}


void TestInfoObject::SetNull(bool isNull) {
	this->m_isNull = isNull;
}


const CppUtils::Cpp_string& TestInfoObject::GetName() const {
	return *this->m_name;
}


void TestInfoObject::SetName(const CppUtils::Cpp_string& name) {
	*this->m_name = name;
}


const std::vector<ICaseArgument>& TestInfoObject::GetArguments() const {
	return *this->m_arguments;
}


void TestInfoObject::AddArgument(const CppUtils::Cpp_string& name, const CppUtils::Cpp_string& value) {
	this->m_arguments->push_back(ICaseArgument(name, value));
}


} // end namespace MrTest
