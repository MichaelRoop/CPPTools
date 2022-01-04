#include "CppTestFileOutput.h"
#include "../CPPVariousUtils/Cpp_toStream.h"

namespace CppTestHarness {


	FileOutput::FileOutput(const std::string& filename) : ILogOutput(), m_filename(filename) {
	}


	bool FileOutput::InitOutput() {
		if (m_file.is_open()) {
			m_file.close();
		}

		Cpp_exception::assertCondition(!m_filename.empty(), FL, L("No file name"));
		this->m_file.open(m_filename.c_str());

		Cpp_stringstream ss;
		CppUtils::ToStream(ss, this->m_filename) << _L_(" cannot be opened");
		Cpp_exception::assertCondition(this->m_file.is_open(), _FL_, ss.str());

		return m_file.is_open();
	}


	void FileOutput::CloseOutput() {
		if (this->m_file.is_open()) {
			this->m_file.close();
		}
	}


	bool FileOutput::Write(const Cpp_string& str) {
		if (!this->m_file.is_open()) {
			Cpp_stringstream ss;
			CppUtils::ToStream(ss, this->m_filename) << _L_(" cannot be opened");
			Cpp_exception::assertCondition(false, FL, ss.str());
			return false;
		}
		this->m_file << str.c_str() << std::endl;
		return true;
	}

}
