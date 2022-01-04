#include "CppTestAssertException.h"


namespace CppTestHarness {


	AssertException::AssertException(const char* file, int line, const Cpp_string& msg)
		: Cpp_exception(file, line, msg) {
	}

	AssertException::AssertException(const AssertException& obj)
		: Cpp_exception(obj) {
	}


	AssertException::~AssertException() throw() {
	}

}

