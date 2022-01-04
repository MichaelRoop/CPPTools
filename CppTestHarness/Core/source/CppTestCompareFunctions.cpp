#include "CppTestCompareFunctions.h"
#include "../CPPVariousUtils/Cpp_toStream.h"

namespace CppTestHarness {

	bool WriteToMsgBuff(CppUtils::Cpp_stringstream& buffer, const CppUtils::Cpp_string& msg, bool success) {
		if (!success) {
			buffer << msg.c_str();
		}
		return success;
	}


	void WriteToVerboseBuffHead(const char* file, int line, CppUtils::Cpp_stringstream& buffer) {
		buffer << L("Comparison Failed,  ") << L("File : ");
		CppUtils::ToStream(buffer, CppUtils::ExtractFileName(file));
		buffer << L(", Line : ") << line << std::endl
			<< L("---------------------------------------------------------------") << std::endl
			<< L("Expected Value: ") << std::endl
			<< L("----------------") << std::endl;
	}


	void WriteToVerboseBuffMid(CppUtils::Cpp_stringstream& buffer) {
		buffer << std::endl << std::endl
			<< L("Actual Value: ") << std::endl
			<< L("-------------") << std::endl;
	}

}

