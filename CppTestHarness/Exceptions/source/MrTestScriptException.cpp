#include "CppTestScriptException.h"
#include "../CPPVariousUtils/Cpp_toStream.h"


namespace CppTestHarness {

	ScriptException::ScriptException(
		const char* file, 
		int line, 
		const Cpp_string& msg, 
		const Cpp_string& scriptFileName, 
		const Cpp_string& scriptLine)
			: Cpp_exception(file, line, msg),
			m_scriptFileName(scriptFileName),
			m_scriptLine(scriptLine) {
		/// @todo Track down why this is happening.  If a value of '\' or '/' is 
		///			passed in as file name then we can not init the sriptException file 
		///			name object at all.  Weirdness.
	}


	ScriptException::~ScriptException() throw() {
	}


	const Cpp_string ScriptException::LongMsg() const {
		Cpp_stringstream ss;
		ss << Cpp_exception::longMsg() << L(" : ") << CppUtils::ExtractFileName(this->m_scriptFileName);

		if (!m_scriptLine.empty()) {
			ss << L(" : ") << m_scriptLine.c_str();
		}
		return ss.str();
	}


}