///--------------------------------------------------------------------------------------
/// @brief	Builds strings with for column information for test cases.
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_BUILD_TEST_CASE_COLUMN_VALUE_STRING_H)
#define CPP_TEST_BUILD_TEST_CASE_COLUMN_VALUE_STRING_H

#include "CppTestBuildColumnValueString.h"

namespace CppTestHarness {

	class ICase;	///< Forward declaration of testCase.

	///--------------------------------------------------------------------------------------
	/// @brief	Functor to Add a value to the value string on each iteration.
	///
	/// You can use this with the std::for each
	class BuildTestCaseColumnValueString : public BuildColumnValueString {

	public:

		/// @brief	Constructor.
		///
		/// @param	os			The output stringstream.
		/// @param	delimiter	The delimiter between fields.
		/// @param	strQuotes	The string delimiter character.
		BuildTestCaseColumnValueString(
			Cpp_stringstream& os,
			const Cpp_string& delimiter,
			const Cpp_string& strQuotes,
			ICase& testCase
		);

	private:

		ICase& m_testCase; ///< The testCase to log column values.


		/// @brief	Handles the building of column data.
		/// @param	field	The current field at iteration.
		virtual void Build(const FieldPair& field);


		/// @brief	Helper function to concatenate string values to the value string
		///			with the proper string delimiter, specificaly for the verbose field.
		///	@param	str	The string to concatenate.
		void ConcatenateVerboseBufferStr(const Cpp_string& str);
	};

}

#endif

