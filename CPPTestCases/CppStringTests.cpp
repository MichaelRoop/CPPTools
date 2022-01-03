#include "TestIncludes.h"

using namespace CppUtils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPPRTTestCases {


	TEST_CLASS(CppStringTests) {

		TEST_METHOD(T01_01_TrimRight_Whitespace) {
			Cpp_string expected = TrimRight(L"This is a string");
			Cpp_string s1 = TrimRight(L("This is a string       "));
			Assert::AreEqual(expected, s1);
		}

		TEST_METHOD(T01_02_TrimRight_HiddenCharacters) {
			Cpp_string expected = TrimRight(L"This is a string");
			Cpp_string s1 = TrimRight(L("This is a string    \t\n\r\0 "));
			Assert::AreEqual(expected, s1);
		}

		TEST_METHOD(T01_01_TrimRight_Empty) {
			Cpp_string expected = TrimRight(L"");
			Cpp_string s1 = TrimRight(L(""));
			Assert::AreEqual(expected, s1);
		}

		TEST_METHOD(T02_01_TrimLeft_Whitespace) {
			Cpp_string expected = TrimLeft(L"This is a string");
			Cpp_string s1 = TrimLeft(L("     This is a string"));
			Assert::AreEqual(expected, s1);
		}

		TEST_METHOD(T02_02_TrimLeft_HiddenCharacters) {
			// Does not handle \0 on left. This is end of line character
			Cpp_string expected = TrimLeft(L"This is a string");
			Cpp_string s1 = TrimLeft(L("    \t\n\r This is a string"));
			Assert::AreEqual(expected, s1);
		}

		TEST_METHOD(T02_03_TrimLeft_Empty) {
			Cpp_string expected = TrimLeft(L"");
			Cpp_string s1 = TrimLeft(L(""));
			Assert::AreEqual(expected, s1);
		}

		//

		TEST_METHOD(T03_01_Trim_Whitespace) {
			Cpp_string expected = Trim(L"This is a string");
			Cpp_string s1 = Trim(L("     This is a string       "));
			Assert::AreEqual(expected, s1);
		}

		TEST_METHOD(T03_02_Trim_HiddenCharacters) {
			// Does not handle \0 on left
			Cpp_string expected = Trim(L"This is a string");
			Cpp_string s1 = Trim(L("    \t\n\r This is a string    \t\n\r "));
			Assert::AreEqual(expected, s1);
		}

		TEST_METHOD(T03_03_Trim_Empty) {
			Cpp_string expected = Trim(L"");
			Cpp_string s1 = Trim(L(""));
			Assert::AreEqual(expected, s1);
		}





		protected:

	};

}
