#include "TestIncludes.h"

#include "../CppIniFile/CppIniInputLine.h"

using CppUtils::Cpp_string;
using CppIniFileNs::CppIniInputLine;


namespace CppIniFileTests {

	TEST_CLASS(T01_InputLineFirst) {

		TEST_METHOD(T01_01_SectionValid) {

			Cpp_string s(_L_("[Blah section]"));
			CppIniInputLine i(s);
			Assert::AreEqual(
				ToString(CppIniFileNs::INI_LINE_TYPE::SECTION), 
				ToString(i.TypeOf()));
			Assert::IsTrue(i.TypeOf() == CppIniFileNs::INI_LINE_TYPE::SECTION);


		}

	};

}

