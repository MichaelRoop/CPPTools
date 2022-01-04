#include "CppTestFileScriptReader.h"
#include "Cpp_pointerException.h"
#include "Cpp_macroDefines.h"
#include "../CPPVariousUtils/Cpp_toStream.h"


namespace CppTestHarness {

	FileScriptReader::FileScriptReader(
		const Cpp_string& filename, Cpp_char nameDelimiter, Cpp_char argDelimiter)
		: ScriptReaderBase(filename, nameDelimiter, argDelimiter),
		m_filename(filename) {
	}


	void FileScriptReader::Open() {
		CppUtils::Cpp_pointerException::ptrAssert(this->m_filename.c_str(), _FL_);
		this->FileAssert(!this->m_filename.empty(), _FL_, _L_("Empty File Name"));
		this->m_scriptStream.open(CppUtils::ToCharPtr(m_filename).c_str());
		this->FileAssert(this->m_scriptStream.is_open(), _FL_, _L_("File not open"));
	}


	TestInfoObject FileScriptReader::GetNextTest(Cpp_string& fixtureName) {
		const int size = 2048;
		Cpp_char buff[size];
		TestInfoObject		testInfo;
		this->FileAssert(this->m_scriptStream.is_open(), _FL_, _L_("File not open"));

		while (this->m_scriptStream.getline(buff, size)) {
			Cpp_string line(CppUtils::Trim(Cpp_string(buff)));
			if (!line.empty() && line[0] != _L_('#')) {
				testInfo.SetNull(false);
				this->ProcessLine(fixtureName, testInfo, buff);
				break;
			}
		}
		return testInfo;
	}

}
