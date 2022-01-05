#pragma once
#include "CppIniFileDefines.h"
#include "CppIniNode.h"
#include "CppIniInputLine.h"
#include "CppIniTypes.h"

namespace CppIniFileNs {

	class CPPINI_EXPORT CppIniSection {
	public:

		/// @typedef	Definition of a vector of nodes.
		typedef std::vector<CppIniFileNs::CppIniNode> NodeVector;

		/// @typedef	Definition of a node vector iterator.
		typedef std::vector<CppIniFileNs::CppIniNode>::const_iterator	NodeIterator;


		/// @default constructor.
		CppIniSection();


		/// @brief	Constructor.
		///
		/// @param	input	The iniInputLine used to create the node.
		CppIniSection(const CppIniInputLine& input);


		/// @brief	Copy constructor.
		///
		/// @param	obj	The object used to construct this object.
		CppIniSection(const CppIniSection& obj);


		/// @brief	Assignement operator.
		///
		/// @param	obj	The object used to initialise this object.
		///
		/// @return	This object.
		CppIniSection& operator = (const CppIniSection& rhs);


		/// @brief	The name of the section.  Does not contain brackets.
		///
		/// @return	The name of the section.
		const CppUtils::Cpp_string& Name() const;


		/// @brief	Indicates if the section object contains data or is a placeholder.
		///
		/// @return	true if it holds data, otherwise false.
		bool IsDataSection() const;


		/// @brief	Add a node to the section.
		///
		/// @param	input	The iniInputLine used to create the node.
		void AddNode(const CppIniInputLine& input);


		/// @brief	The objects node vector.
		///
		///	WARNING:	This is an efficiency method.  It does not make a copy 
		///				but exposes the raw vector of nodes.  You must validate 
		///				each node with a call to node::isDataSection.
		///
		/// @return	The vector of nodes held by the section.
		const CppIniSection::NodeVector& Nodes() const;


		/// @brief	The value of held by the named node.
		///
		/// @param	nodeName	The name of the node to look up for the value.
		///
		/// @return	The value if found, otherwise and empty string.
		const CppUtils::Cpp_string& value(const CppUtils::Cpp_string& nodeName) const;


		/// @brief	Reset this object.
		void Clear();


		/// @brief	Set the name of the section.  All previous nodes are cleared.
		///
		/// It is presumed that the name is greater than zero length.
		///
		/// @param	name	The name of the section.
		void SetName(const CppUtils::Cpp_string& name);


		/// @brief	Retrieve an iterator that points to a named node.
		///
		///	WARNING:	This is an efficiency method.  It does not make a copy 
		///				but exposes the raw vector of nodes.  You must validate
		///				the iterator against nodes().end().  You must also 
		///				validate each node with a call to node::isDataSection.
		///
		/// @param	name	The name of the node to retrieve.
		///
		/// @return	An iterator pointing to the node if found, otherwise an invalid iterator.
		NodeIterator GetNode(const CppUtils::Cpp_string& name) const;


		/// @brief	Verifies if a named node exists and is a data node.
		///
		/// @param	name	The name of the node to retrieve.
		///
		/// @return	true if the node exists and is a Data node, otherwise false.
		bool NodeExists(const CppUtils::Cpp_string& name) const;


		/// @brief	Retrieve a copy of the vector of data nodes.
		///
		/// @return	A vector of nodes.
		const NodeVector GetNodesCopy() const;

	private:

		CppUtils::Cpp_string	m_name;		///< Node name or non data value string.		
		NodeVector				m_nodes;	///< Vector of nodes.
		INI_DATA_TYPE			m_type;		///< Defines if content is data.
		CppUtils::Cpp_string	m_dummyVal;	///< Empty dummy value string for not found. 



		/// @brief	Initialise the section.
		///
		/// @param	obj	The object used to initialise this object.
		void Init(const CppIniSection& obj);


	};



	/// <summary>Streaming function for node object</summary>
	/// <param name="os">Output stream</param>
	/// <param name="theSection">Section to stream out</param>
	/// <returns></returns>
	CppUtils::Cpp_ostream& operator << (CppUtils::Cpp_ostream& os, const CppIniSection& theSection);


}


// Force export of template containing class
CPPINI_EXTERN template class CPPINI_EXPORT std::allocator<CppIniFileNs::CppIniSection>;
CPPINI_EXTERN template class CPPINI_EXPORT std::vector<CppIniFileNs::CppIniSection>;

