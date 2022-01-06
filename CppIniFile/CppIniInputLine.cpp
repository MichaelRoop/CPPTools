#include "CppIniInputLine.h"

namespace CppIniFileNs {

	class CppIniInputLineImpl {

	public:
		CppIniInputLineImpl() {
			this->m_type = INI_LINE_TYPE::UNDEFINED;
		}

		CppIniInputLineImpl(const Cpp_string& str) {
			this->m_type = INI_LINE_TYPE::UNDEFINED;
			this->Init(str);
		}

		~CppIniInputLineImpl() { 
			// nothing to do
		}

		INI_LINE_TYPE Init(const Cpp_string& str) {
			// Clean out any old values
			m_firstValue = _L_("");
			m_secondValue = _L_("");
			m_type = INI_LINE_TYPE::UNDEFINED;
			Cpp_string line = CppUtils::Trim(str);

			// Check order is important
			if (!IsBlank(line)) {
				if (!IsSectionName(line)) {
					if (!IsComment(line)) {
						if (!IsNode(line)) {
							m_firstValue = str;
							m_type = INI_LINE_TYPE::GARBAGE;
						}
					}
				}
			}
			return this->m_type;
		}


		bool IsBlank(const Cpp_string& str) {
			if (str.empty()) {
				m_type = INI_LINE_TYPE::BLANK;
				m_firstValue = str;
				return true;
			}
			return false;
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
		bool IsSectionName(const Cpp_string& str) {
			if (str.size() > 2 && str[0] == _L_('[') && str[str.length() - 1] == _L_(']')) {
				m_type = INI_LINE_TYPE::SECTION;
				m_firstValue = CppUtils::Trim(str.substr(1, str.length() - 2));
				return true;
			}
			return false;
		}


		bool IsComment(const Cpp_string& str) {
			if (str[0] == _L_('#') || str[0] == _L_('*')) {
				m_type = INI_LINE_TYPE::COMMENT;
				m_firstValue = str;
				return true;
			}
			return false;
		}


		bool IsNode(const Cpp_string& str) {
			Cpp_string::size_type pos = str.find(_L_("="));
			if (pos > 0 && pos != Cpp_string::npos) {
				Cpp_string name;
				pos = 0;
				if (CppUtils::StrTokenize(pos, str, name, _L_('='))) {
					// Check if there is any chars on left side of '='.
					name = CppUtils::Trim(name);
					if (!name.empty()) {
						m_firstValue = name;

						/// substring of remainder of string.
						CppUtils::StrTokenize(pos, str, m_secondValue, _L_('='));
						m_secondValue = CppUtils::Trim(m_secondValue);
						if (!m_secondValue.empty()) {
							m_type = INI_LINE_TYPE::NODE;
							return true;
						}
					}
				}
			}
			return false;
		}

		Cpp_string	m_firstValue;
		Cpp_string	m_secondValue;
		INI_LINE_TYPE m_type;
	};


	CppIniInputLine::CppIniInputLine() {
		m_impl = new CppIniInputLineImpl();
	}


	CppIniInputLine::CppIniInputLine(const Cpp_string& str) {
		Cleanup();
		m_impl = new CppIniInputLineImpl(str);
	}


	CppIniInputLine::~CppIniInputLine() {
		Cleanup();
	}


	INI_LINE_TYPE CppIniInputLine::Init(const Cpp_string& str) {
		return m_impl->Init(str);
	}


	const Cpp_string& CppIniInputLine::FirstValue() const {
		return m_impl->m_firstValue;
	}


	const Cpp_string& CppIniInputLine::SecondValue() const {
		return m_impl->m_secondValue;
	}


	INI_LINE_TYPE CppIniInputLine::TypeOf() const {
		return m_impl->m_type;
	}


	void CppIniInputLine::Cleanup() {
		if (m_impl != NULL) {
			delete m_impl;
			m_impl = NULL;
		}
	}
	
}


