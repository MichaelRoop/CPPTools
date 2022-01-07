#include "TestIncludes.h"
#include "../CppIniFile/CppIniSection.h"

using CppUtils::Cpp_string;
using CppIniFileNs::CppIniInputLine;
using CppIniFileNs::CppIniNode;
using CppIniFileNs::CppIniSection;
using CppIniFileNs::INI_DATA_TYPE;
using CppIniFileNs::INI_LINE_TYPE;

namespace CppIniFileTests {

	TEST_CLASS(T_03_IniSectionTests) {

public:

		//static CppIniSection section(CppIniInputLine(_L_("Blip=Blop")));
		static CppIniSection m_section;

		TEST_CLASS_INITIALIZE(ClassTestIniSectionInitialize) {
			CppIniSection s(CppIniInputLine(_L_("[My Section]")));
			s.AddNode(CppIniInputLine(_L_("Blip1=Blop1")));
			s.AddNode(CppIniInputLine(_L_("Blip2=Blop2")));
			s.AddNode(CppIniInputLine(_L_("Blip3=Blop3")));
			s.AddNode(CppIniInputLine(_L_("Blip4=Blop4")));
			m_section = s;
		}


		TEST_METHOD(T01_01_ConstructorDefault) {
			CppIniSection section;
			Assert::IsFalse(section.IsDataSection(), _L_("IsDataSection"));
			Assert::AreEqual(_L_(""), section.Name().c_str(), _L_("Name"));
			CppIniSection::NodeVector nv = section.Nodes();
			Assert::AreEqual((size_t)0, nv.size(), L"Node size");
		}


		TEST_METHOD(T01_02_ConstructorCopy) {
			CppIniSection section(m_section);
			Assert::IsTrue(section.IsDataSection(), _L_("IsDataSection"));
			Assert::AreEqual(_L_("My Section"), section.Name().c_str(), _L_("Name"));
			Assert::IsTrue(section.NodeExists(_L_("Blip1")), _L_("Node exists Blip1"));
			Assert::IsTrue(section.NodeExists(_L_("Blip2")), _L_("Node exists Blip2"));
			Assert::IsTrue(section.NodeExists(_L_("Blip3")), _L_("Node exists Blip3"));
			Assert::IsTrue(section.NodeExists(_L_("Blip4")), _L_("Node exists Blip4"));
			Assert::IsFalse(section.NodeExists(_L_("Blip5")), _L_("Node exists Blip5"));
		}


		TEST_METHOD(T01_03_ConstructorAssignment) {
			CppIniSection section = m_section;
			Assert::IsTrue(section.IsDataSection(), _L_("IsDataSection"));
			Assert::AreEqual(_L_("My Section"), section.Name().c_str(), _L_("Name"));
			Assert::IsTrue(section.NodeExists(_L_("Blip1")), _L_("Node exists Blip1"));
			Assert::IsTrue(section.NodeExists(_L_("Blip2")), _L_("Node exists Blip2"));
			Assert::IsTrue(section.NodeExists(_L_("Blip3")), _L_("Node exists Blip3"));
			Assert::IsTrue(section.NodeExists(_L_("Blip4")), _L_("Node exists Blip4"));
			Assert::IsFalse(section.NodeExists(_L_("Blip5")), _L_("Node exists Blip5"));
		}


		TEST_METHOD(T01_03_ConstructorInputLine) {
			CppIniSection section(CppIniInputLine(_L_("[My Input line section]")));
			Assert::IsTrue(section.IsDataSection(), _L_("IsDataSection"));
			Assert::AreEqual(_L_("My Input line section"), section.Name().c_str(), _L_("Name"));
			Assert::AreEqual((size_t)0, section.Nodes().size(), L"Node size");
			Assert::IsFalse(section.NodeExists(_L_("Blip1")), _L_("Node exists Blip1"));
			section.AddNode(CppIniInputLine(_L_("Blip1=Blop1")));
			Assert::AreEqual((size_t)1, section.Nodes().size(), L"Node size");
			Assert::IsTrue(section.NodeExists(_L_("Blip1")), _L_("Node exists Blip1"));
		}


		TEST_METHOD(T02_01_IsDataSectionTrue) {
			CppIniSection section(CppIniInputLine(_L_("[My Input line section]")));
			Assert::IsTrue(section.IsDataSection(), _L_("IsDataSection"));
		}


		TEST_METHOD(T02_02_IsDataSectionFalse) {
			CppIniSection section(CppIniInputLine(_L_("My Input bad section name]")));
			Assert::IsFalse(section.IsDataSection(), _L_("IsDataSection"));
		}



		//TEST_METHOD(T05_01_Validate) {
		//	Assert::IsTrue(m_section.IsDataSection(), _L_("IsDataSection"));
		//	Assert::AreEqual(_L_("My Section"), m_section.Name().c_str(), _L_("Name"));
		//	Assert::IsTrue(m_section.NodeExists(_L_("Blip1")), _L_("Node exists Blip1"));
		//	Assert::IsTrue(m_section.NodeExists(_L_("Blip2")), _L_("Node exists Blip2"));
		//	Assert::IsTrue(m_section.NodeExists(_L_("Blip3")), _L_("Node exists Blip3"));
		//	Assert::IsTrue(m_section.NodeExists(_L_("Blip4")), _L_("Node exists Blip4"));
		//	Assert::IsFalse(m_section.NodeExists(_L_("Blip5")), _L_("Node exists Blip5"));
		//}



		//void TestValidNode(const CppIniNode node, const Cpp_string& name, const Cpp_string& value) {
		//	Assert::IsTrue(node.IsDataNode(), L"Data valid");
		//	Assert::AreEqual(name.c_str(), node.Name().c_str());
		//	Assert::AreEqual(value.c_str(), node.Value().c_str());
		//}

	};
	
	CppIniSection T_03_IniSectionTests::m_section;

}



