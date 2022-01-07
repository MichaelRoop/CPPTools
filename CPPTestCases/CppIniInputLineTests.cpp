#include "TestIncludes.h"

#include "../CppIniFile/CppIniInputLine.h"

using CppUtils::Cpp_string;
using CppIniFileNs::CppIniInputLine;
using CppIniFileNs::INI_LINE_TYPE;

namespace CppIniFileTests {

	TEST_CLASS(T_01_InputLineTests) {

		TEST_METHOD(T01_01_SectionValid) {
			DoTest(Cpp_string(_L_("[Blah section]")), INI_LINE_TYPE::SECTION);
		}

		TEST_METHOD(T01_02_SectionBlanksAroundAll) {
			DoTest(Cpp_string(_L_(" [ Blah section ] ")), INI_LINE_TYPE::SECTION);
		}

		TEST_METHOD(T02_01_BlankValid) {
			DoTest(Cpp_string(_L_("")), INI_LINE_TYPE::BLANK);
		}

		TEST_METHOD(T03_01_CommentHashValid) {
			DoTest(Cpp_string(_L_("# this is a comment")), INI_LINE_TYPE::COMMENT);
		}

		TEST_METHOD(T03_02_CommentHashLeadingWhiteSpace) {
			DoTest(Cpp_string(_L_("     # this is a comment")), INI_LINE_TYPE::COMMENT);
		}

		TEST_METHOD(T03_03_CommentStarValid) {
			DoTest(Cpp_string(_L_("* this is a comment")), INI_LINE_TYPE::COMMENT);
		}

		TEST_METHOD(T03_04_CommentStarValidLeadingWhiteSpace) {
			DoTest(Cpp_string(_L_("   * this is a comment")), INI_LINE_TYPE::COMMENT);
		}

		TEST_METHOD(T04_01_NodeValid) {
			DoTest(Cpp_string(_L_("Arg1 = 233")), INI_LINE_TYPE::NODE);
		}

		TEST_METHOD(T05_01_Garbage) {
			DoTest(Cpp_string(_L_("sdflkjsd** kd")), INI_LINE_TYPE::GARBAGE);
		}


		void DoTest(const Cpp_string& s, CppIniFileNs::INI_LINE_TYPE lineType) {
			CppIniInputLine i(s);
			Assert::AreEqual(ToString(lineType), ToString(i.TypeOf()));
			Assert::IsTrue(i.TypeOf() == lineType);
		}

	};

}

