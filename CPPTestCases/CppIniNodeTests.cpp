#include "TestIncludes.h"
#include "../CppIniFile/CppIniNode.h"

using CppUtils::Cpp_string;
using CppIniFileNs::CppIniInputLine;
using CppIniFileNs::CppIniNode;
using CppIniFileNs::INI_DATA_TYPE;
using CppIniFileNs::INI_LINE_TYPE;

namespace CppIniFileTests {

	TEST_CLASS(T01_IniNodeTests) {

		TEST_METHOD(T01_01_Constructor) {
			CppIniInputLine i(_L_("Blip=Blop"));
			CppIniNode n(i);
			TestValidNode(n, Cpp_string(_L_("Blip")), Cpp_string(_L_("Blop")));
		}

		TEST_METHOD(T01_02_CopyConstructor) {
			CppIniInputLine i(_L_("Blip2=Blop2"));
			CppIniNode n(i);
			TestValidNode(CppIniNode(n), Cpp_string(_L_("Blip2")), Cpp_string(_L_("Blop2")));
		}

		TEST_METHOD(T01_03_Assignment) {
			CppIniInputLine i(_L_("Blip3=Blop3"));
			CppIniNode n(i);
			CppIniNode n2 = n;
			TestValidNode(CppIniNode(n), Cpp_string(_L_("Blip3")), Cpp_string(_L_("Blop3")));
		}


		TEST_METHOD(T02_01_NodeInValidNoValue) {
			CppIniNode n(CppIniInputLine(_L_("Blip=")));
			Assert::IsFalse(n.IsDataNode(), L"IsDataNode");
		}

		TEST_METHOD(T02_02_NodeInValidNoName) {
			CppIniNode n(CppIniInputLine(_L_("=Blop")));
			Assert::IsFalse(n.IsDataNode(), L"IsDataNode");
		}

		TEST_METHOD(T02_03_NodeInValidNoEqual) {
			CppIniNode n(CppIniInputLine(_L_("BlipBlop")));
			Assert::IsFalse(n.IsDataNode(), L"IsDataNode");
		}

		TEST_METHOD(T02_04_NodeInValidNoValueOrName) {
			CppIniNode n(CppIniInputLine(_L_("=")));
			Assert::IsFalse(n.IsDataNode(), L"IsDataNode");
		}

		TEST_METHOD(T02_04_NodeInValidEmptyString) {
			CppIniNode n(CppIniInputLine(_L_("")));
			Assert::IsFalse(n.IsDataNode(), L"IsDataNode");
		}

		TEST_METHOD(T02_04_NodeInValidWhiteSpace) {
			CppIniNode n(CppIniInputLine(_L_("		 ")));
			Assert::IsFalse(n.IsDataNode(), L"IsDataNode");
		}


		void TestValidNode(const CppIniNode node, const Cpp_string& name, const Cpp_string& value) {
			Assert::IsTrue(node.IsDataNode(), L"Data valid");
			Assert::AreEqual(name.c_str(), node.Name().c_str());
			Assert::AreEqual(value.c_str(), node.Value().c_str());
			//CppIniFileNs::INI_DATA_TYPE dataType
		}


		void DoTest(const Cpp_string& s, CppIniFileNs::INI_DATA_TYPE dataType) {
			CppIniInputLine i(s);



		//	Assert::AreEqual(ToString(lineType), ToString(i.TypeOf()));
		//	Assert::IsTrue(i.TypeOf() == lineType);
		}

	};

}

