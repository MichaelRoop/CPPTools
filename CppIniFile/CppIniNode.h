#pragma once
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

		CppUtils::Cpp_string m_name;	///< Node name or non data value string.
		CppUtils::Cpp_string m_value;	///< Node value.
		INI_DATA_TYPE  		 m_type;	///< Defines if content is data.


	};

	/// @brief	Streaming function for node object.
///
/// @param	os		The output stream.
/// @param	theNode	The node object to stream out.
///
/// @return	The output stream object.
	CppUtils::Cpp_ostream& operator << (CppUtils::Cpp_ostream& os, const CppIniNode& theNode);




}

//// Force export of template containing class
//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<mr_inireader::node>;
//EXP_TEMPLATE template class CPPTESTUTILS_API std::vector<mr_inireader::node>;

