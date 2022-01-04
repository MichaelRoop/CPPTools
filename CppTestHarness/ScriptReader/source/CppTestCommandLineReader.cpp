#include "CppTestCommandLineReader.h"
#include "Cpp_macroDefines.h"

namespace CppTestHarness {

	CommandLineReader::CommandLineReader(
		const Cpp_string& line, Cpp_char nameDelimiter, Cpp_char argDelimiter)
		: ScriptReaderBase(L("CommandLine"), nameDelimiter, argDelimiter),
		m_line(CppUtils::Trim(line)),
		m_used(false) {
	}


	void CommandLineReader::Open() {
		this->m_used = false;
	}


	TestInfoObject CommandLineReader::GetNextTest(Cpp_string& fixtureName) {
		TestInfoObject testInfo;
		if (!this->m_used) {
			this->m_used = true;
			if (!this->m_line.empty() && this->m_line[0] != _L_('#')) {
				testInfo.SetNull(false);
				this->ProcessLine(fixtureName, testInfo, this->m_line);
			}
		}
		return testInfo;
	}

}
