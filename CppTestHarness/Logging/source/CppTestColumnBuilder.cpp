#include "CppTestColumnBuilder.h"
#include "CppTestBuildColumnInfoString.h"
#include "CppTestBuildTestCaseColumnValueString.h"
#include "CppTestBuildSummaryColumnValueString.h"
#include "CppTestBuildConsoleSummaryString.h"
#include <algorithm>

namespace CppTestHarness {

	Cpp_string ColumnBuilder::CreateColumnHeaders(
		const FieldVector& fieldInfo,
		const Cpp_string& delimiter) {
		Cpp_stringstream os;
		std::for_each(
			fieldInfo.begin(),
			fieldInfo.end(),
			BuildColumnInfoString(os, _L_(" "), delimiter, BuildColumnInfoString::ColumnInfoParts::NAME_ONLY)
		);
		return os.str();
	}


	Cpp_string ColumnBuilder::CreateColumnNameTypeStr(
		const FieldVector& fieldInfo,
		const Cpp_string& nameTypeDelimiter,
		const Cpp_string& colDelimiter) {
		Cpp_stringstream os;
		std::for_each(
			fieldInfo.begin(),
			fieldInfo.end(),
			BuildColumnInfoString(os, nameTypeDelimiter, colDelimiter, BuildColumnInfoString::ColumnInfoParts::NAME_TYPE)
		);
		return os.str();
	}


	Cpp_string ColumnBuilder::CreateColumnData(
		const FieldVector& fieldInfo,
		const Cpp_string& delimiter,
		const Cpp_string& strQuotes,
		ICase& testCase) {
		// I cannot use a factory to create the build objects since the for_each will fail with a
		// C2893.  It cannot access a derived class through a virtual base class.
		Cpp_stringstream os;
		std::for_each(
			fieldInfo.begin(),
			fieldInfo.end(),
			BuildTestCaseColumnValueString(os, delimiter, strQuotes, testCase)
		);
		return os.str();
	}


	Cpp_string ColumnBuilder::CreateColumnData(
		const FieldVector& fieldInfo,
		const Cpp_string& delimiter,
		const Cpp_string& strQuotes,
		ILog* theLog
	) {
		Cpp_stringstream os;
		std::for_each(
			fieldInfo.begin(),
			fieldInfo.end(),
			BuildSummaryColumnValueString(os, delimiter, strQuotes, theLog)
		);
		return os.str();

		///// @todo we will chose this by querying the log object for its output type
		//mr_utils::mr_stringstream os;
		//std::for_each( 
		//	fieldInfo.begin(), 
		//	fieldInfo.end(), 
		//	buildConsoleSummaryString( os, delimiter, strQuotes, theLog )
		//);
		//return os.str();
	}

}
