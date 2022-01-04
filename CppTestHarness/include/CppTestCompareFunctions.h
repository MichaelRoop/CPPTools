///--------------------------------------------------------------------------------------
/// @brief	Compare functions.
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_COMP_FUNC_H)
#define CPP_TEST_COMP_FUNC_H

#include "include/CppTestHarnessDefines.h"
#include "../CPPVariousUtils/Cpp_string.h"
#include "../CPPVariousUtils/Cpp_sstream.h"
#include "../CPPVariousUtils/CppDoCompare.h"
#include "../CPPVariousUtils/Cpp_toStream.h"
#include <vector>

namespace CppTestHarness {

	class testCase;


	//--------------------------------------------------------------------------------------
	// Write to buffer functions
	//--------------------------------------------------------------------------------------


	/// @brief	Tests if a condition is false and then writes to the testCase message buffer.
	///
	/// @param	theCase	The test case to write to.
	/// @param	msg		The message to write if the condition is false.
	/// @param	success	Then condition to test.
	///
	/// @return	The value of the success argument.
	TSTHARNESS_API bool WriteToMsgBuff(CppUtils::Cpp_stringstream& buffer, const CppUtils::Cpp_string& msg, bool success);


	/// @brief	Writes the first part of the verbose message to the testCase verbose message buffer.
	///
	///	Message creates the template and is ready for 'expected value'
	///
	/// @param	file	The code file where the call originates.
	/// @param	line	The code line where the call originates.
	/// @param	theCase	The test case to write to.
	TSTHARNESS_API void WriteToVerboseBuffHead(const char* file, int line, CppUtils::Cpp_stringstream& buffer);


	/// @brief	Writes the middle part of the verbose message to the testCase verbose message buffer.
	///
	///	Message creates the template and is ready for 'actual value'
	///
	/// @param	theCase	The test case to write to.
	TSTHARNESS_API void WriteToVerboseBuffMid(CppUtils::Cpp_stringstream& buffer);


	/// @brief	Template function to write to the testCase verbose buffer on a false condition.
	///
	/// @tparam	T			The type of the expected and actual value.
	/// @param	file		The code file where the call originates.
	/// @param	line		The code line where the call originates.
	/// @param	expected	The expected value.
	/// @param	actual		The actual value encountered.
	/// @param	theCase		The testCase to received the results.
	/// @param	success		The condition to check.
	///
	/// @return The value of the success argument.
	template<class T>
	bool WriteToVerboseBuff(
		const char* file,
		int							line,
		const T& expected,
		const T& actual,
		CppUtils::Cpp_stringstream& buffer,
		bool						success) {
		if (!success) {
			WriteToVerboseBuffHead(file, line, buffer);
			CppUtils::ToStream(buffer, expected);
			WriteToVerboseBuffMid(buffer);
			CppUtils::ToStream(buffer, actual);
		}
		return success;
	}


	/// @brief	Template function to write vectors of values to the testCase verbose buffer 
	///			on a false condition.
	///
	/// @tparam	T			The type of the expected and actual values in the containers.
	/// @param	file		The code file where the call originates.
	/// @param	line		The code line where the call originates.
	/// @param	expected	The expected value.
	/// @param	actual		The actual value encountered.
	/// @param	theCase		The testCase to received the results.
	/// @param	success		The condition to check.
	///
	/// @return The value of the success argument.
	template<class T>
	bool WriteVecToVerboseBuff(
		const char* file,
		int							line,
		const std::vector<T>& expected,
		const std::vector<T>& actual,
		CppUtils::Cpp_stringstream& buffer,
		bool						success) {
		if (!success) {
			CppUtils::VecStreamLineDelimited<T> lineFormater(buffer);
			WriteToVerboseBuffHead(file, line, buffer);
			CppUtils::ToStream(buffer, expected, lineFormater);
			WriteToVerboseBuffMid(buffer);
			CppUtils::ToStream(buffer, actual, lineFormater);
		}
		return success;
	}


	//--------------------------------------------------------------------------------------
	// Comparison functions
	//--------------------------------------------------------------------------------------



	/// @brief	Compares two values and write a message when values are different.
	///
	/// @tparam	T			The type of the expected and actual value.
	/// @param	expected	The expected value.
	/// @param	actual		The actual value encountered.
	/// @param	theCase		The testCase to received the results.
	/// @param	msg			The user message. Default is 'Value not as expected'.
	///
	/// @return true if the values are the same, otherwise false.
	template<class T, class T2>
	bool CompareEqual(
		const T& expected,
		const T2& actual,
		CppUtils::Cpp_stringstream& buffer,
		const CppUtils::Cpp_string& msg = L("Value not as expected")) {
		return WriteToMsgBuff(buffer, msg, CppUtils::CompareEqual(expected, actual));
	}


	/// @brief	Compares two values and write a message when the values are the same.
	///
	/// @tparam	T			The type of the expected and actual value.
	/// @param	expected	The expected value.
	/// @param	actual		The actual value encountered.
	/// @param	theCase		The testCase to received the results.
	/// @param	msg			The user message. Default is 'Value not as expected'.
	///
	/// @return true if the values are different, otherwise false.
	template<class T, class T2>
	bool CompareNotEqual(
		const T& expected,
		const T2& actual,
		CppUtils::Cpp_stringstream& buffer,
		const CppUtils::Cpp_string& msg = L("Value not as expected")) {
		return WriteToMsgBuff(buffer, msg, CppUtils::CompareNotEqual(expected, actual));
	}


	/// @brief	Compares two values and writes a verbose message when the values are different.
	///
	/// @tparam	T			The type of the expected and actual value.
	/// @param	file		The code file where the call originates.
	/// @param	line		The code line where the call originates.
	/// @param	expected	The expected value.
	/// @param	actual		The actual value encountered.
	/// @param	theCase		The testCase to received the results.
	/// @param	msg			The user message. Default is 'Value not as expected'.
	///
	/// @return true if the values are the same, otherwise false.
	template<class T>
	bool VerbCompareEqual(
		const char* file,
		int							line,
		const T& expected,
		const T& actual,
		CppUtils::Cpp_stringstream& buffer,
		const CppUtils::Cpp_string& msg = L("Value not as expected")) {
		return WriteToVerboseBuff(
			file, line, expected, actual, buffer, CompareEqual(expected, actual, buffer, msg)
		);
	}


	/// @brief	Compares two values and write a verbose message when the values are the same.
	///
	/// @tparam	T			The type of the expected and actual value.
	/// @param	file		The code file where the call originates.
	/// @param	line		The code line where the call originates.
	/// @param	expected	The expected value.
	/// @param	actual		The actual value encountered.
	/// @param	theCase		The testCase to received the results.
	/// @param	msg			The user message. Default is 'Value not as expected'.
	///
	/// @return true if the values are different, otherwise false.
	template<class T>
	bool VerbCompareNotEqual(
		const char* file,
		int							line,
		const T& expected,
		const T& actual,
		CppUtils::Cpp_stringstream& buffer,
		const CppUtils::Cpp_string& msg = L("Value not as expected")) {
		return WriteToVerboseBuff(
			file, line, expected, actual, buffer, CompareNotEqual(expected, actual, buffer, msg)
		);
	}


	/// @brief	Compares two vectors of values and write a message when the values 
	///			do not match.
	///
	/// @tparam	T			The type of the expected and actual value.
	/// @param	file		The code file where the call originates.
	/// @param	line		The code line where the call originates.
	/// @param	expected	The expected value.
	/// @param	actual		The actual value encountered.
	/// @param	theCase		The testCase to received the results.
	/// @param	msg			The user message. Default is 'Value not as expected'.
	///
	/// @return true if the values are different, otherwise false.
	template<class T>
	bool VerbCompareVecEqual(
		const char* file,
		int							line,
		const std::vector<T>& expected,
		const std::vector<T>& actual,
		CppUtils::Cpp_stringstream& buffer,
		const CppUtils::Cpp_string& msg = L("Value not as expected")) {
		return WriteVecToVerboseBuff(
			file, line, expected, actual, buffer, CompareEqual(expected, actual, buffer, msg)
		);
	}

} // end namespace

#endif
