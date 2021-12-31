#include "Cpp_exceptions.h"
#include "Cpp_sstream.h"
#include "Cpp_toStream.h" 
#include <assert.h>

namespace CppUtils {


	Cpp_exception::Cpp_exception() {
		m_line = 0;
	}



	Cpp_exception::Cpp_exception(const char* file, int line, const Cpp_string& msg)
		: exception(),
		m_fileName((file == NULL ? "" : file)),
		m_line(line),
		m_msg(msg) {
		assert(file);
	}


	Cpp_exception::Cpp_exception(const Cpp_exception& obj) {
		this->m_fileName = obj.m_fileName;
		this->m_line = obj.m_line;
		this->m_msg = obj.m_msg;
	}


	Cpp_exception::~Cpp_exception() {
	}


	const Cpp_string& Cpp_exception::msg() const {
		return this->m_msg;
	}


	const Cpp_string Cpp_exception::fileName() const {
		// We never use this value to open a file so we are safe to always convert its width.
		Cpp_stringstream ss;
		ToStream(ss, ExtractFileName(this->m_fileName));
		return ss.str();
	}


	int Cpp_exception::fileLine() const {
		return this->m_line;
	}


	const Cpp_string Cpp_exception::longMsg() const {
		Cpp_stringstream ss;
		ss << L("Exception:")
			<< this->fileName().c_str() << L(":") << this->m_line << L(" ") << this->m_msg.c_str();
		return ss.str();
	}


	void Cpp_exception::assertCondition(
		bool condition, const char* file, int line, const Cpp_string& msg) {
		if (!condition) {
			throw Cpp_exception(file, line, msg);
		}
	}

}

