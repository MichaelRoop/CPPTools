///--------------------------------------------------------------------------------------
/// @brief	Builds strings with for column information.
///--------------------------------------------------------------------------------------
#if !defined(CPP_BUILD_COLUMN_VALUE_STRING_H)
#define CPP_BUILD_COLUMN_VALUE_STRING_H

#include "CppTestFieldPair.h"

namespace CppTestHarness {

	///--------------------------------------------------------------------------------------
	/// @brief	Functor to Add a value to the value string on each iteration.
	///
	/// You can use this with the std::for each
	class BuildColumnValueString {
	public:

		/// @brief	Constructor.
		///
		/// @param	os			The output stringstream.
		/// @param	delimiter	The delimiter between fields.
		/// @param	strQuotes	The string delimiter character.
		BuildColumnValueString(
			Cpp_stringstream& os, const Cpp_string& delimiter, const Cpp_string& strQuotes);


		/// @brief	Function operator called on each iteration.
		///
		/// @param	field	The current field at iteration.
		virtual void operator () (const FieldPair& field);

	protected:
		Cpp_stringstream& m_os;
		Cpp_string m_delimiter;
		Cpp_string m_strQuotes;
		int m_count;


		/// @brief	Handles the building of column data.
		//
		/// @param	field	The current field at iteration.
		virtual void Build(const FieldPair& field) = 0;


		/// @brief	Helper function to concatenate string values to the value string
		///			with the proper string delimiter.
		///
		///	@param	str	The string to concatenate.
		void ConcatenateStr(const Cpp_string& str);
	};

}

#endif
