#include "CppTestBuildColumnInfoString.h"

namespace CppTestHarness {

	BuildColumnInfoString::BuildColumnInfoString(
		Cpp_stringstream& os,
		const Cpp_string& nameTypeDelimiter,
		const Cpp_string& unitDelimiter,
		ColumnInfoParts	parts) 
		: m_os(os),
		m_nameTypeDelimiter(nameTypeDelimiter),
		m_unitDelimiter(unitDelimiter),
		m_parts(parts),
		m_count(0) {
	}


	void BuildColumnInfoString::operator () (const FieldPair& field) {
		if ((++this->m_count) > 1) {
			m_os << this->m_unitDelimiter;
		}

		switch (this->m_parts) {
		case ColumnInfoParts::NAME_ONLY:
			this->m_os << field.first;
			break;
		case ColumnInfoParts::TYPE_ONLY:
			this->m_os << field.second;
			break;
		case ColumnInfoParts::NAME_TYPE:
			this->m_os << field.first << this->m_nameTypeDelimiter << field.second;
			break;
		default:
			Cpp_exception::assertCondition(false, _FL_, _L_("Unhandled case"));
		}
	}


}
