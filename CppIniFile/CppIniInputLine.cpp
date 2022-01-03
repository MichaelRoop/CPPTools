#include "CppIniInputLine.h"


namespace CppIniFileNs {

	CppIniInputLine::CppIniInputLine() {
		this->m_type = INI_LINE_TYPE::UNDEFINED;
	}


	CppIniInputLine::CppIniInputLine(const CppUtils::Cpp_string& str) {
		this->m_type = INI_LINE_TYPE::UNDEFINED;
		this->Init(str);
	}

	
	INI_LINE_TYPE CppIniInputLine::Init(const CppUtils::Cpp_string& str) {
		// Clean out any old values
		m_firstValue = L("");
		m_secondValue = L("");
		m_type = INI_LINE_TYPE::UNDEFINED;
		CppUtils::Cpp_string line = CppUtils::Trim(str);

		// The order is important.  Once it has found a match, no other checking
		// will be done on the line.
		this->CheckIfBlank(line);
		this->CheckIfSectionName(line);
		this->CheckIfComment(line);
		this->CheckIfNode(line);
		this->CheckIfGarbage(line);
		return this->TypeOf();
	}


	void CppIniInputLine::CheckIfBlank(const CppUtils::Cpp_string& str) {
		if (m_type == INI_LINE_TYPE::UNDEFINED) {
			if (str.empty()) {
				m_type = INI_LINE_TYPE::BLANK;
				m_firstValue = str;
			}
		}
	}


	void CppIniInputLine::CheckIfSectionName(const CppUtils::Cpp_string& str) {
		if (m_type == INI_LINE_TYPE::UNDEFINED) {
			if (str.size() > 2 && str[0] == L('[') && str[str.length() - 1] == L(']')) {
				m_type = INI_LINE_TYPE::SECTION;
				m_firstValue = CppUtils::Trim(str.substr(1, str.length() - 2));
			}
		}
	}


	void CppIniInputLine::CheckIfComment(const CppUtils::Cpp_string& str) {
		if (m_type == INI_LINE_TYPE::UNDEFINED) {
			if (str[0] == L('#') || str[0] == L('*')) {
				m_type = INI_LINE_TYPE::COMMENT;
				m_firstValue = str;
			}
		}
	}


	void CppIniInputLine::CheckIfNode(const CppUtils::Cpp_string& str) {
		if (m_type == INI_LINE_TYPE::UNDEFINED) {
			CppUtils::Cpp_string::size_type pos = str.find(L("="));
			if (pos > 0 && pos != CppUtils::Cpp_string::npos) {
				CppUtils::Cpp_string name;
				pos = 0;
				if (CppUtils::MrTokenize(pos, str, name, L('='))) {
					// Check if there is any chars on left side of '='.
					name = CppUtils::Trim(name);
					if (!name.empty()) {
						m_type = INI_LINE_TYPE::NODE;
						m_firstValue = name;

						/// @todo Probably just replace with substring of remainder of string.
						CppUtils::MrTokenize(pos, str, m_secondValue, L('='));
						m_secondValue = CppUtils::Trim(m_secondValue);
					}
				}
			}
		}
	}


	void CppIniInputLine::CheckIfGarbage(const CppUtils::Cpp_string& str) {
		if (m_type == INI_LINE_TYPE::UNDEFINED) {
			m_firstValue = str;
			m_type = INI_LINE_TYPE::GARBAGE;
		}
	}


	const CppUtils::Cpp_string& CppIniInputLine::firstValue() const {
		return m_firstValue;
	}


	const CppUtils::Cpp_string& CppIniInputLine::secondValue() const {
		return m_secondValue;
	}



	INI_LINE_TYPE CppIniInputLine::TypeOf() const {
		return m_type;
	}
	
}


