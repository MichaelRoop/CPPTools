#include "CppIniInputLine.h"


namespace CppIniFileNs {

	CppIniInputLine::CppIniInputLine() {
		this->m_type = INI_LINE_TYPE::UNDEFINED;
	}


	CppIniInputLine::CppIniInputLine(const Cpp_string& str) {
		this->m_type = INI_LINE_TYPE::UNDEFINED;
		this->Init(str);
	}

	
	INI_LINE_TYPE CppIniInputLine::Init(const Cpp_string& str) {
		// Clean out any old values
		m_firstValue = L("");
		m_secondValue = L("");
		m_type = INI_LINE_TYPE::UNDEFINED;
		Cpp_string line = CppUtils::Trim(str);

		// The order is important.  Once it has found a match, no other checking
		// will be done on the line.
		this->CheckIfBlank(line);
		this->CheckIfSectionName(line);
		this->CheckIfComment(line);
		this->CheckIfNode(line);
		this->CheckIfGarbage(line);
		return this->TypeOf();
	}


	void CppIniInputLine::CheckIfBlank(const Cpp_string& str) {
		if (m_type == INI_LINE_TYPE::UNDEFINED) {
			if (str.empty()) {
				m_type = INI_LINE_TYPE::BLANK;
				m_firstValue = str;
			}
		}
	}


	/// <summary>
	/// Determines if the value is a section
	/// Here are the steps to validate.
	/// 1. The string is trimed	before calling.
	/// 2. The first char must be '[' and the last ']'
	/// 3. The brackets are removed and the contents trimmed.
	/// 4. If the remainder has characters left it is returned as section name
	/// </summary>
	/// <param name="str">The string to analyse</param>
	void CppIniInputLine::CheckIfSectionName(const Cpp_string& str) {
		if (m_type == INI_LINE_TYPE::UNDEFINED) {
			if (str.size() > 2 && str[0] == L('[') && str[str.length() - 1] == L(']')) {
				m_type = INI_LINE_TYPE::SECTION;
				m_firstValue = CppUtils::Trim(str.substr(1, str.length() - 2));
			}
		}
	}


	void CppIniInputLine::CheckIfComment(const Cpp_string& str) {
		if (m_type == INI_LINE_TYPE::UNDEFINED) {
			if (str[0] == L('#') || str[0] == L('*')) {
				m_type = INI_LINE_TYPE::COMMENT;
				m_firstValue = str;
			}
		}
	}


	void CppIniInputLine::CheckIfNode(const Cpp_string& str) {
		if (m_type == INI_LINE_TYPE::UNDEFINED) {
			Cpp_string::size_type pos = str.find(L("="));
			if (pos > 0 && pos != Cpp_string::npos) {
				Cpp_string name;
				pos = 0;
				if (CppUtils::StrTokenize(pos, str, name, L('='))) {
					// Check if there is any chars on left side of '='.
					name = CppUtils::Trim(name);
					if (!name.empty()) {
						m_type = INI_LINE_TYPE::NODE;
						m_firstValue = name;

						/// @todo Probably just replace with substring of remainder of string.
						CppUtils::StrTokenize(pos, str, m_secondValue, L('='));
						m_secondValue = CppUtils::Trim(m_secondValue);
					}
				}
			}
		}
	}


	void CppIniInputLine::CheckIfGarbage(const Cpp_string& str) {
		if (m_type == INI_LINE_TYPE::UNDEFINED) {
			m_firstValue = str;
			m_type = INI_LINE_TYPE::GARBAGE;
		}
	}


	const Cpp_string& CppIniInputLine::FirstValue() const {
		return m_firstValue;
	}


	const Cpp_string& CppIniInputLine::SecondValue() const {
		return m_secondValue;
	}



	INI_LINE_TYPE CppIniInputLine::TypeOf() const {
		return m_type;
	}
	
}


