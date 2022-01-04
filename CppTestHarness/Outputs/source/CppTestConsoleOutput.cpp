#include "CppTestConsoleOutput.h"
#include "../CPPVariousUtils/Cpp_iostream.h"


namespace CppTestHarness {

	bool ConsoleOutput::InitOutput() {
		return true;
	}


	void ConsoleOutput::CloseOutput() {
		; // Nothing to do.
	}


	bool ConsoleOutput::Write(const Cpp_string& str) {
		 Cpp_cout << str.c_str() << std::endl;
		return true;
	}

}
