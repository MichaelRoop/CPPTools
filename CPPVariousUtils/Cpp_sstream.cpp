#include "pch.h"
#include "Cpp_sstream.h"
#include "Cpp_string.h"

namespace CppUtils {

	void ResetStringStream(Cpp_stringstream& ss) {
		// set a new string held by the string stream
		ss.str(CppUtils::Cpp_string());

		// Clear any error state back to goodbit
		ss.clear();
	}

}

