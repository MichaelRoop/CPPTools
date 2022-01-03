#include "TestIncludes.h"

using namespace CppUtils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPPRTTestCases {
	TEST_CLASS(CppStringTokenizeTests) {
		static std::vector<CppUtils::Cpp_string> m_tokens;

		// Only run once per file and and can only do statics
		TEST_CLASS_INITIALIZE(ClassInitialize) {
			m_tokens.push_back(_L_("This"));
			m_tokens.push_back(_L_("is"));
			m_tokens.push_back(_L_("a"));
			m_tokens.push_back(_L_("test"));
			m_tokens.push_back(_L_("string"));
			m_tokens.push_back(_L_("with"));
			m_tokens.push_back(_L_("some"));
			m_tokens.push_back(_L_("tokens"));
		}

		TEST_METHOD(T01_01_TokenizerNormal) {
			this->TokenizeString(_L_("This|is|a|test|string|with|some|tokens"));
		}

		TEST_METHOD(T01_02_TokenizerTokensWithEmpty) {
			this->TokenizeString(_L_("This|is|a|test|string|with|some|tokens"));
		}

		TEST_METHOD(T01_03_TokenizerLeadingExtraTokens) {
			this->TokenizeString(_L_("||This|is|a|test|string|with|some|tokens"));
		}

		TEST_METHOD(T01_04_TokenizerTrailingExtraTokens) {
			this->TokenizeString(_L_("This|is|a|test|string|with|some|tokens||"));
		}

protected:
	void CompareToken(std::vector<CppUtils::Cpp_string>::size_type index, const CppUtils::Cpp_string& token) {
		// compare index range.
		if (index >= m_tokens.size()) {
			Assert::IsTrue(index < m_tokens.size(), L(" Exceeds token count"));
		}
		Assert::AreEqual(m_tokens[index], token);
	}


	void TokenizeString(const CppUtils::Cpp_string& str) {
		CppUtils::Cpp_string token;
		CppUtils::Cpp_string::size_type pos = 0;
		std::vector<CppUtils::Cpp_string>::size_type index;

		for (index = 0; CppUtils::MrTokenize(pos, str, token, L('|')); index++) {
			this->CompareToken(index, token);
		}

		// index is same as size since incremented as test to show out of bounds
		Assert::AreEqual(m_tokens.size(), index);
	}


	};

	std::vector<CppUtils::Cpp_string> CppStringTokenizeTests::m_tokens;


}