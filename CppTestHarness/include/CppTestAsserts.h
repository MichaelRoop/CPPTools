///--------------------------------------------------------------------------------------
/// @file	MrTestAssert.h
/// @brief	Assert on compare methods
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_ASSERT_H)
#define CPP_TEST_ASSERT_H

#include "include/CppTestHarnessDefines.h"
#include "CppTestCompareFunctions.h"
#include "CppTestAssertException.h"
#include "../CPPVariousUtils/Cpp_sstream.h"
#include "../CPPVariousUtils/Cpp_string.h"


namespace CppTestHarness {



	/// @brief	Create a message with file and line and possibly appending user message
	///
	/// @param	buffer	The message buffer to received the results.
	/// @param	file	The file where the method was executing
	/// @param	line	The line being executed
	/// @param	userMsg	The user message.
	TSTHARNESS_API void CreateMsg(CppUtils::Cpp_stringstream& msgBuffer, const char* file, int line, CppUtils::Cpp_stringstream& userMsg);


	/// @brief	Compares two values and asserts if different after a message is written
	///
	/// @tparam	T			The type of the expected and actual value.
	/// @param	file		The file where the method was executing
	/// @param	line		The line being executed
	/// @param	expected	The expected value.
	/// @param	actual		The actual value encountered.
	/// @param	buffer		The message buffer to received the results.
	/// @param	userMsg		The user message.
	template<class T>
	void AreEqual(
		const char* file, int line, const T& expected, const T& actual, CppUtils::Cpp_stringstream& buffer, CppUtils::Cpp_stringstream& userMsg) {

		CppUtils::Cpp_stringstream ss;
		ss << _L_("Expected '") << expected << _L_("' but actual is '") << actual << _L_("'  ");
		CreateMsg(ss, file, line, userMsg);

		if (!CppUtils::CompareEqual(expected, actual, buffer, ss.str())) {
			throw AssertException(file, line, ss.str());
		}
		mr_utils::ResetStringStream(buffer);
		mr_utils::ResetStringStream(userMsg);
	}


	/// @brief	Compares two values and asserts if the same after a message is written
	///
	/// @tparam	T			The type of the non-expected and actual value.
	/// @param	file	The file where the method was executing
	/// @param	line	The line being executed
	/// @param	nonexpected	The value not expected.
	/// @param	actual		The actual value encountered.
	/// @param	buffer		The message buffer to received the results.
	/// @param	userMsg		The user message.
	template<class T>
	void AreNotEqual(
		const char* file, int line, const T& nonexpected, const T& actual, CppUtils::Cpp_stringstream& buffer, CppUtils::Cpp_stringstream& userMsg) {

		mr_utils::mr_stringstream ss;
		ss << _L_("Did not Expected '") << nonexpected << _L_("' but actual is '") << actual << _L_("'  ");
		CreateMsg(ss, file, line, userMsg);

		if (!CppUtils::CompareNotEqual(nonexpected, actual, buffer, ss.str())) {
			throw AssertException(file, line, ss.str());
		}
		mr_utils::ResetStringStream(buffer);
		mr_utils::ResetStringStream(userMsg);
	}


	/// @brief	Test if a condigion is true or otherwise fail and log results
	///
	/// @param	file	The file where the method was executing
	/// @param	line	The line being executed
	/// @param	buffer	The message buffer to received the results.
	/// @param	userMsg	The user message.
	TSTHARNESS_API void IsTrue(
		const char* file, int line, bool condition, CppUtils::Cpp_stringstream& buffer, CppUtils::Cpp_stringstream& userMsg);


	/// @brief	Test if a condigion is false or otherwise fail and log results
	///
	/// @param	file	The file where the method was executing
	/// @param	line	The line being executed
	/// @param	buffer	The message buffer to received the results.
	/// @param	userMsg	The user message.
	TSTHARNESS_API void IsFalse(
		const char* file, int line, bool condition, CppUtils::Cpp_stringstream& buffer, CppUtils::Cpp_stringstream& userMsg);


	TSTHARNESS_API void FailOnNotThrow(
		const char* file, int line, CppUtils::Cpp_stringstream& buffer, CppUtils::Cpp_stringstream& userMsg);


	TSTHARNESS_API void Fail(
		const char* file, int line, CppUtils::Cpp_stringstream& buffer, CppUtils::Cpp_stringstream& userMsg);


	// Class generalization of exeption types
	template<class T>
	class ReportException
	{
	public:
		static void ThrowReport(const char* file, int line, mr_utils::mr_stringstream& buffer, T& exception, mr_utils::mr_stringstream& userMsg) {
			mr_utils::mr_stringstream ss;
			ss << _L_("Did not Expected Unknown Exception ");
			MrTest::CreateMsg(ss, file, line, userMsg);
			buffer << ss.str().c_str();
			throw MrTest::AssertException(file, line, ss.str());
		}
	};


	// Class specific std::exeption type
	template<>
	class ReportException<std::exception>
	{
	public:
		static void ThrowReport(const char* file, int line, CppUtils::Cpp_stringstream& buffer, std::exception& exception, CppUtils::Cpp_stringstream& userMsg) {
			CppUtils::Cpp_stringstream ss;
			ss << L("Did not Expected std::exception ");
			if (exception.what() != 0) {
				ss << exception.what() << _L_(" ");
			}
			CreateMsg(ss, file, line, userMsg);
			buffer << ss.str().c_str();
			throw AssertException(file, line, ss.str());
		}
	};


	// Class specific mr_utils::mr_exception type
	template<>
	class ReportException<CppUtils::Cpp_exception> {
	public:
		static void ThrowReport(const char* file, int line, CppUtils::Cpp_stringstream& buffer, CppUtils::Cpp_exception& exception, CppUtils::Cpp_stringstream& userMsg) {
			CppUtils::Cpp_stringstream ss;
			ss << L("Did not Expected mr_utils::mr_exception ") << exception.longMsg() << _L_(" ");
			CreateMsg(ss, CppUtils::ToCharPtr(exception.fileName()).c_str(), exception.fileLine(), userMsg);
			buffer << ss.str().c_str();
			throw AssertException(CppUtils::ToCharPtr(exception.fileName()).c_str(), exception.fileLine(), ss.str());
		}
	};



	/// @brief	Use the template function to automatically resolve the proper template class handler
	template<class T>
	void FailOnThrow(
		const char* file, int line, CppUtils::Cpp_stringstream& buffer, T& exception, CppUtils::Cpp_stringstream& userMsg) {
		ReportException<T>::ThrowReport(file, line, buffer, exception, userMsg);
	}


	//#define ASSERT_TRUE(_file_, _line_, _condition_, _buffer_, _streamMsg_)		\
	//mr_utils::mr_stringstream ss;												\
	//ss << (_streamMsg_);														\
	//mr_assert::IsTrue(_file_, _line_, _condition_, _buffer_, ss.str().c_str());			\






	//{
	//
	//	mr_utils::mr_stringstream ss;
	//	ss << msg;
	//	CreateMsg(ss, file, line, msg);
	//
	//	if (!mr_test::CompareEqual(true, condition, buffer, ss.str())) {
	//		throw mr_utils::mr_exception(file, line, ss.str());				
	//	}																	
	//}




} // end of namespace

#endif
