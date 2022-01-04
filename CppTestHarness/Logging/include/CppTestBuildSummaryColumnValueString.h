#if !defined(CPP_TEST_BUILD_SUMMARY_COLUMN_VALUE_STRING_H)
#define CPP_TEST_BUILD_SUMMARY_COLUMN_VALUE_STRING_H

#include "CppTestHarnessDefines.h"
#include "CppTestBuildColumnValueString.h"


namespace CppTestHarness {

	class ILog;	///< Forward declaration of iTestLog interface.


	///--------------------------------------------------------------------------------------
	/// @brief	Functor to Add a value to the value string on each iteration.
	///
	/// You can use this with the std::for each
	class BuildSummaryColumnValueString : public BuildColumnValueString {

	public:

		/// @brief	Constructor.
		///
		/// @param	os			The output stringstream.
		/// @param	delimiter	The delimiter between fields.
		/// @param	strQuotes	The string delimiter character.
		/// @param	theLog		The iTestLog to query for the column data.
		BuildSummaryColumnValueString(
			Cpp_stringstream& os,
			const Cpp_string& delimiter,
			const Cpp_string& strQuotes,
			ILog* theLog
		);

	protected:

		ILog* m_log; ///< Pointer to the testLog;


		/// @brief	Handles the building of column data.
		//
		/// @param	field	The current field at iteration.
		virtual void Build(const FieldPair& field);
	};

}

#endif

