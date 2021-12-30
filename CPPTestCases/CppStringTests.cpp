#include "TestIncludes.h"

using namespace CppUtils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPPRTTestCases {


	TEST_CLASS(CppStringTests) {

		TEST_METHOD(T01_01_Scratch) {

			// OK
			Cpp_string s1 = TrimRight(L("This is a string       "));
			Cpp_string s2 = TrimRight(L"This is a string");
			Assert::AreEqual(L"This is a string", s1.c_str());
			Assert::AreEqual(s1, s2);


		}

	};


}
