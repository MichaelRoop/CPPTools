#if !defined(CPP_INI_NODE_H)
#define CPP_INI_NODE_H


#include "CppIniFileDefines.h"
#include "CppIniInputLine.h"
#include "CppIniTypes.h"

namespace CppIniFileNs {

	class CPPINI_EXPORT CppIniNode {
	public:

		/// @brief	Constructor.
		///
		/// @param	inLIne	The iniInputLine that constains the node datat.
		CppIniNode(const CppIniInputLine& inLine);


		/// @brief	Copy Constructor.
		///
		/// @param	obj	The node used to construct this node.
		CppIniNode(const CppIniNode& obj);


		/// @brief	Assignement operator.
		///
		/// @param	obj	The node used to initialise this node.
		CppIniNode& operator = (const CppIniNode& rhs);


		/// @brief	The value of the node.  It will be blank if the node is not a data node.
		///
		/// @return	The value of the node.
		const CppUtils::Cpp_string& Value() const;


		/// @brief	Holds the key portion of the key value pair or the garbage string if the 
		///			node is not a valid data node.
		///
		/// @return	The key name if valid or the garbage string.
		const CppUtils::Cpp_string& Name() const;


		/// @brief	Returns whether the node is a valid data node or not.
		///
		/// @return	true if the node is a valid data node, otherwise false.
		bool IsDataNode() const;


		/// @brief	Default constructor in private scope prevent default construction.
		CppIniNode();

	private:

		/// @brief	Initialise the object with the values from another object.
		///
		/// @param	obj	The object that has the values used to initialise this object.
		void Init(const CppIniNode& obj);

	private:

		Cpp_string m_name;
		Cpp_string m_value;
		INI_DATA_TYPE m_type;

	};
	
	/// <summary>Streaming function for ini node</summary>
	/// <param name="os">The output stream</param>
	/// <param name="node">The node to steam out</param>
	/// <returns>The output stream</returns>
	Cpp_ostream& operator << (Cpp_ostream& os, const CppIniNode& node);

}

// Force export of template containing class
CPPINI_EXTERN template class CPPINI_EXPORT std::allocator<CppIniFileNs::CppIniNode>;
CPPINI_EXTERN template class CPPINI_EXPORT std::vector<CppIniFileNs::CppIniNode>;


#endif
