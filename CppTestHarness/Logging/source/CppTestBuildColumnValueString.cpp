#include "CppTestBuildColumnValueString.h"

namespace CppTestHarness {

	BuildColumnValueString::BuildColumnValueString(
		Cpp_stringstream& os,
		const Cpp_string& delimiter,
		const Cpp_string& strQuotes) 
		: m_os(os),
		m_delimiter(delimiter),
		m_strQuotes(strQuotes),
		m_count(0) {
	}


	void BuildColumnValueString::operator () (const FieldPair& field) {
		if ((++this->m_count) > 1) {
			this->m_os << _L_(",");
		}
		this->Build(field);
	}


	void BuildColumnValueString::ConcatenateStr(const Cpp_string& str) {
		this->m_os << this->m_strQuotes.c_str() << str.c_str() << this->m_strQuotes.c_str();
	}

}

