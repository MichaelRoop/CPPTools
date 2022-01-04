#include "CppTestVectorLineReader.h"
#include "Cpp_macroDefines.h"
#include <algorithm>

namespace CppTestHarness {

	VectorLineReader::VectorLineReader(
		const std::vector<Cpp_string>& lines,
		Cpp_char nameDelimiter,
		Cpp_char argDelimiter) :
		ScriptReaderBase(L("VectorOfLines"), nameDelimiter, argDelimiter),
		m_lines(lines),
		m_index(0) {

		this->SortVector();
		this->Open();
	}


	void VectorLineReader::Open() {
		this->m_index = 0;
	}


	TestInfoObject VectorLineReader::GetNextTest(Cpp_string& fixtureName) {
		TestInfoObject		testInfo;
		if (this->m_index < this->m_lines.size()) {
			if (!this->m_lines[m_index].empty() && this->m_lines[this->m_index][0] != _L_('#')) {
				testInfo.SetNull(false);
				this->ProcessLine(fixtureName, testInfo, this->m_lines[m_index]);
			}
			this->m_index++;
		}
		return testInfo;
	}


	void VectorLineReader::SortVector() {
		// TODO - implement sorting by fixture and test cases within fixture
		std::sort(this->m_lines.begin(), this->m_lines.end());
	}

}
