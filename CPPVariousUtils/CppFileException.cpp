#include "CppFileException.h"
#include "Cpp_sstream.h"
#include "Cpp_toStream.h"

namespace CppUtils {

	CppFileException::CppFileException(
		const char* file, int line, const Cpp_string& msg, const Cpp_string& fileName)
		: Cpp_exception(file, line, msg),
		m_fileName(fileName) {
	}


	CppFileException::~CppFileException() {
	}


	const Cpp_string CppFileException::longMsg() const {
		Cpp_stringstream ss;
		ss << Cpp_exception::longMsg() << L(" : ") << m_fileName;
		return ss.str();
	}


}