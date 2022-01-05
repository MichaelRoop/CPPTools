#include "CppTestScriptReaderBase.h"
#include "CppTestScriptException.h"
#include "../CPPVariousUtils/Cpp_macroDefines.h"
#include "../CPPVariousUtils/CppFileException.h"


namespace CppTestHarness {


	ScriptReaderBase::ScriptReaderBase(
		const Cpp_string& origine,
		Cpp_char nameDelimiter,
		Cpp_char argDelimiter) :
		m_origine(origine),
		m_nameDelimiter(nameDelimiter),
		m_argDelimiter(argDelimiter) {
	}


	void ScriptReaderBase::ProcessLine(Cpp_string& fixtureName, TestInfoObject& testInfo, Cpp_string line) {

		// Check for Disabled indicator
		testInfo.SetActive(line[0] != _L_('@'));
		// TODO - make more robust
		if (!testInfo.IsActive()) {
			line = CppUtils::SubString(line, 1);
		}

		Cpp_string name;
		Cpp_string args;
		Cpp_string::size_type pos = 0;

		// If no '.' then assume it is the fixture name only. This means execute all tests on that fixture
		if (line.find(_L_('.')) == CppUtils::StrNPos()) {
			if (CppUtils::StrTokenize(pos, line, fixtureName, m_nameDelimiter)) {
				return;
			}
			this->ScriptAssert(false, _FL_, L("Invalid script line format"), line);
		}
		else {
			CppUtils::StrTokenize(pos, line, fixtureName, _L_('.'));

			if (CppUtils::StrTokenize(pos, line, name, m_nameDelimiter)) {
				testInfo.SetName(name);

				// It is possible for the test to have only a name and no arguments.
				if (CppUtils::StrTokenize(pos, line, args, m_nameDelimiter)) {
					this->ProcessArgs(testInfo, args);
				}
			}
		}
	}


	void ScriptReaderBase::ProcessArgs(TestInfoObject& testInfo, const Cpp_string& args) {
		Cpp_string oneArg;
		Cpp_string::size_type pos = 0;

		while (CppUtils::StrTokenize(pos, args, oneArg, m_argDelimiter)) {
			this->ProcessArg(testInfo, oneArg);
		}
	}


	void ScriptReaderBase::ProcessArg(TestInfoObject& testInfo, const Cpp_string& arg) {
		Cpp_string name;
		Cpp_string value;
		Cpp_string::size_type pos = 0;

		this->GetArgComponent(pos, arg, name);
		this->GetArgComponent(pos, arg, value);
		testInfo.AddArgument(name, value);
	}


	void ScriptReaderBase::GetArgComponent(
		Cpp_string::size_type& pos, const Cpp_string& str, Cpp_string& token) const {

		this->ScriptAssert(
			CppUtils::StrTokenize(pos, str, token, _L_('=')), _FL_, L("Invalid Argument Format"), str
		);
	}


	void ScriptReaderBase::ScriptAssert(
		bool condition,
		const char* file,
		int	line,
		const Cpp_string& msg,
		const Cpp_string& scriptLine) const {

		if (!condition) {
			throw ScriptException(file, line, msg, this->m_origine, scriptLine);
		}
	}


	void ScriptReaderBase::FileAssert(
		bool condition, const char* file, int line, const Cpp_string& msg) const {
		if (!condition) {
			throw CppUtils::CppFileException(file, line, msg, this->m_origine);
		}
	}

}
