#include "CppTestBuildConsoleSummaryString.h"


namespace CppTestHarness {

	BuildConsoleSummaryString::BuildConsoleSummaryString(
		Cpp_stringstream& os,
		const Cpp_string& delimiter,
		const Cpp_string& strQuotes,
		ILog* theLog)
		: BuildSummaryColumnValueString(os, delimiter, strQuotes, theLog) {
	}


	void BuildConsoleSummaryString::operator () (const FieldPair& field) {
		if ((++this->m_count) > 1) {
			this->m_os << std::endl;
		}

		/// @todo We will eventually left pad to create an allignment
		this->m_os << field.first << _L_(":");
		this->Build(field);
	}

}
