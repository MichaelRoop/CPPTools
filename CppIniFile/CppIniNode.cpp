#include "CppIniNode.h"

namespace CppIniFileNs {

	CppIniNode::CppIniNode(const CppIniInputLine& inLine) {
		// Always safe to copy over second value.
		m_name = inLine.firstValue();
		m_value = inLine.secondValue();
		m_type = (inLine.TypeOf() == INI_LINE_TYPE::NODE
			? INI_DATA_TYPE::VALID_DATA
			: INI_DATA_TYPE::NON_DATA);
	}


	CppIniNode::CppIniNode(const CppIniNode& obj) {
		this->Init(obj);
	}


	CppIniNode& CppIniNode::operator = (const CppIniNode& rhs) {
		if (this != &rhs) {
			this->Init(rhs);
		}
		return *this;
	}


	const CppUtils::Cpp_string& CppIniNode::Value() const {
		return m_value;
	}


	const CppUtils::Cpp_string& CppIniNode::Name() const {
		return m_name;
	}


	bool CppIniNode::IsDataNode() const {
		return m_type == INI_DATA_TYPE::VALID_DATA;
	}


	CppIniNode::CppIniNode() {
		m_type = INI_DATA_TYPE::NON_DATA;
	}


	void CppIniNode::Init(const CppIniNode& obj) {
		m_name = obj.m_name;
		m_value = obj.m_value;
		m_type = obj.m_type;
	}


	CppUtils::Cpp_ostream& operator << (CppUtils::Cpp_ostream& os, const CppIniNode& theNode) {
		os << theNode.Name().c_str();
		if (theNode.IsDataNode()) {
			os << L("=") << theNode.Value().c_str();
		}
		os << std::endl;
		return os;
	}


}

