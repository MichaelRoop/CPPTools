#include "CppIniSection.h"
#include "../CPPVariousUtils/Cpp_functors.h"
#include "../CPPVariousUtils/Cpp_toStream.h"

namespace CppIniFileNs {

	/// @brief	Filter out non valid nodes to produce a good set of sections.
	struct FilterNodes {

		FilterNodes(CppIniSection::NodeVector& nodeVec) : m_nodes(nodeVec) {
		}

		void operator () (const CppIniNode& theNode) {
			if (theNode.IsDataNode()) {
				m_nodes.push_back(theNode);
			}
		}
		CppIniSection::NodeVector& m_nodes; ///< Target for sections.
	};
	// -------------------- end functors ----------------


	CppIniSection::CppIniSection() {
		m_type = INI_DATA_TYPE::NON_DATA;
	}


	CppIniSection::CppIniSection(const CppIniInputLine& input) {
		m_name = input.FirstValue();
		m_type = (input.TypeOf() == INI_LINE_TYPE::SECTION
			? INI_DATA_TYPE::VALID_DATA
			: INI_DATA_TYPE::NON_DATA);
	}


	CppIniSection::CppIniSection(const CppIniSection& obj) {
		this->Init(obj);
	}


	CppIniSection& CppIniSection::operator = (const CppIniSection& rhs) {
		if (this != &rhs) {
			this->Init(rhs);
		}
		return *this;
	}


	const Cpp_string& CppIniSection::Name() const {
		return m_name;
	}


	void CppIniSection::AddNode(const CppIniInputLine& input) {
		m_nodes.push_back(CppIniNode(input));
	}


	const CppIniSection::NodeVector& CppIniSection::Nodes() const {
		return m_nodes;
	}


	const Cpp_string& CppIniSection::value(const Cpp_string& name) const {
		NodeIterator it = this->GetNode(name);
		return (it == m_nodes.end() ? m_dummyVal : it->Value());
	}


	void CppIniSection::Init(const CppIniSection& obj) {
		this->Clear();
		m_name = obj.m_name;
		m_nodes = obj.m_nodes;
		m_type = obj.m_type;
	}


	void CppIniSection::SetName(const Cpp_string& name) {
		// Setting the name always happens before loading in lines.
		this->Clear();

		m_type = INI_DATA_TYPE::VALID_DATA;
		m_name = name;
	}


	CppIniSection::NodeIterator CppIniSection::GetNode(const Cpp_string& name) const {
		return std::find_if(
			m_nodes.begin(),
			m_nodes.end(),
			CppUtils::IsNamed<CppIniNode, Cpp_string>(name)
		);
	}


	bool CppIniSection::NodeExists(const Cpp_string& name) const {
		NodeIterator it = this->GetNode(name);
		if (it == m_nodes.end() || !it->IsDataNode()) {
			return false;
		}
		return true;
	}


	void CppIniSection::Clear() {
		m_name.clear();
		m_nodes.clear();
	}


	bool CppIniSection::IsDataSection() const {
		return m_type == INI_DATA_TYPE::VALID_DATA;
	}


	const CppIniSection::NodeVector CppIniSection::GetNodesCopy() const {
		CppIniSection::NodeVector nodes;
		std::for_each(m_nodes.begin(), m_nodes.end(), FilterNodes(nodes));
		return nodes;
	}


	CppUtils::Cpp_ostream& operator << (Cpp_ostream& os, const CppIniSection& theSection) {
		if (theSection.IsDataSection()) {
			os << L("[") << theSection.Name().c_str() << L("]") << std::endl;
			std::for_each(
				theSection.Nodes().begin(),
				theSection.Nodes().end(),
				CppUtils::ToStreamClass<CppIniNode, Cpp_ostream>(os)
			);
		}
		else {
			os << theSection.Name().c_str() << std::endl;
		}
		return os;
	}

}
