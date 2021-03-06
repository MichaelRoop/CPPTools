#if !defined(CPP_TEST_BUILD_CONSOLE_SUMMARY_STRING_H)
#define CPP_TEST_BUILD_CONSOLE_SUMMARY_STRING_H

#include "CppTestHarnessDefines.h"
#include "CppTestBuildSummaryColumnValueString.h"


namespace CppTestHarness {

	///--------------------------------------------------------------------------------------
	/// @brief	Functor to Add a value to the value string on each iteration.
	///
	/// You can use this with the std::for each
	class BuildConsoleSummaryString : public BuildSummaryColumnValueString {

	public:

		/// @brief	Function operator called on each iteration.
		///
		/// @param	field	The current field at iteration.
		void operator () (const FieldPair& field);


		/// @brief	Constructor.
		///
		/// @param	os			The output stringstream.
		/// @param	delimiter	The delimiter between fields.
		/// @param	strQuotes	The string delimiter character.
		/// @param	theLog		The iTestLog to query for the column data.
		BuildConsoleSummaryString(
			Cpp_stringstream& os,
			const Cpp_string& delimiter,
			const Cpp_string& strQuotes,
			ILog* theLog
		);
	};


}

#endif

