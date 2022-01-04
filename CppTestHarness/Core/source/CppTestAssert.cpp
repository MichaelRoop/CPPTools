#include "CppTestAsserts.h"
#include "CppTestCompareFunctions.h"
#include "../CPPVariousUtils/Cpp_toStream.h"

namespace CppTestHarness {


	void CreateMsg(
		CppUtils::Cpp_stringstream& msgBuffer,
		const char* file,
		int line,
		CppUtils::Cpp_stringstream& userMsg) {

		CppUtils::ToStream(msgBuffer, CppUtils::ExtractFileName(file));
		msgBuffer << _L_(":") << line;

		if (userMsg.str().length() > 0) {
			msgBuffer << _L_(" : ") << userMsg.str();
		}
	}


	void IsTrue(
		const char* file,
		int line,
		bool condition,
		CppUtils::Cpp_stringstream& buffer,
		CppUtils::Cpp_stringstream& userMsg) {

		CppUtils::Cpp_stringstream ss;
		ss << _L_("Did not Expected false condition ");
		CreateMsg(ss, file, line, userMsg);

		if (!CompareEqual(true, condition, buffer, ss.str())) {
			throw AssertException(file, line, ss.str());
		}
		CppUtils::ResetStringStream(buffer);
		CppUtils::ResetStringStream(userMsg);
	}


	void IsFalse(
		const char* file,
		int line,
		bool condition,
		CppUtils::Cpp_stringstream& buffer,
		CppUtils::Cpp_stringstream& userMsg) {

		CppUtils::Cpp_stringstream ss;
		ss << _L_("Did not Expected true condition ");
		CreateMsg(ss, file, line, userMsg);

		if (!CompareEqual(false, condition, buffer, ss.str())) {
			throw AssertException(file, line, ss.str());
		}
		CppUtils::ResetStringStream(buffer);
		CppUtils::ResetStringStream(userMsg);
	}

	// TODO determine why these two has export in both h and cpp

	void Fail(
		const char*
		file, int line,
		CppUtils::Cpp_stringstream& buffer,
		CppUtils::Cpp_stringstream& userMsg) {

		CppUtils::Cpp_stringstream ss;
		ss << _L_("User Forced Fail ");
		CreateMsg(ss, file, line, userMsg);
		buffer << ss.str();
		throw AssertException(file, line, ss.str());
	}


	void FailOnNotThrow(
		const char* file,
		int line,
		CppUtils::Cpp_stringstream& buffer,
		CppUtils::Cpp_stringstream& userMsg) {

		CppUtils::Cpp_stringstream ss;
		ss << _L_("Test Expected Exception to be Thrown ");
		CreateMsg(ss, file, line, userMsg);
		buffer << ss.str();
		throw AssertException(file, line, ss.str());
	}

}

