#pragma once
#include "CppIniFileDefines.h"
#include "CppIniTypes.h"

namespace CppIniFileNs {


	class CPPINI_API CppIniInputLine {
	public:


		/// @brief	Constructor.
		CppIniInputLine();


		/// @brief	Constructor.
		///
		/// @param	str	The string to parse and identify.
		CppIniInputLine(const CppUtils::Cpp_string& str);

		
		/// @brief	Initialise the object with the string.
		///
		/// @param	str	The string to parse and identify.
		///
		/// @return	The line type as identified by parsing.
		INI_LINE_TYPE Init(const CppUtils::Cpp_string& str);


		/// @brief	The first value created by parsing the line string.
		///
		/// This would be the only value for Section, the key name for
		///	a node, and the comment or garbage value for those types of lines.
		///
		/// @return	The first value.
		const CppUtils::Cpp_string& firstValue() const;


		/// @brief	The second value created by parsing the line string.
		///
		/// This would only apply to nodes and it would correspond to the value of
		///	the key value pair.
		///
		/// @return	The second value.
		const CppUtils::Cpp_string& secondValue() const;


		/// @brief	indicates the type of line that was parsed.
		///
		/// @return	Indicates the type of line that was parsed.
		INI_LINE_TYPE TypeOf() const;

	private:

		CppUtils::Cpp_string	m_firstValue;	///< The results of the parsing.
		CppUtils::Cpp_string	m_secondValue;	///< The results of the parsing.
		INI_LINE_TYPE			m_type;			///< The parsed line type.


		void  CheckIfBlank(const CppUtils::Cpp_string& str);


		void  CheckIfComment(const CppUtils::Cpp_string& str);


		/// @brief	A static function to encapsulate the logic of determining when a valid
		///			section name is contained in a string.
		///
		/// Here are the steps to validate.											\n
		/// 1. The string is trimed	before calling.									\n
		/// 2. The first char must be '[' and the last ']'							\n
		/// 3. The brackets are removed and the contents trimmed.					\n
		/// 4. If the remainder has characters left it is returned as section name	\n
		///
		/// @param	str	The string to validate.
		void CheckIfSectionName(const CppUtils::Cpp_string& str);


		void CheckIfNode(const CppUtils::Cpp_string& str);


		void CheckIfGarbage(const CppUtils::Cpp_string& str);
		
	};

} 
