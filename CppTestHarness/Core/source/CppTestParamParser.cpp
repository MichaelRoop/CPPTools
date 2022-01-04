#include "CppTestParamParser.h"
#include "../CPPVariousUtils/Cpp_macroDefines.h"
#include "CppFileException.h"
#include "../CPPVariousUtils/Cpp_pointerException.h"
#include <algorithm>

namespace CppTestHarness {

	/// @brief	Internal class to group command option value with enum type identifier
	class ParamParserArg {
	public:
		ParamParserArg(ParamParser::ArgType	arg, Cpp_string value) :
			Arg(arg),
			Value(value) {
		}

		ParamParser::ArgType	Arg;
		Cpp_string				Value;
	};


	/// @brief	Functor to find if the vector has a command option type
	class HasArgFunctor {
	public:
		HasArgFunctor(const ParamParser::ArgType& arg) : m_arg(arg) {
		}
		bool operator () (const ParamParserArg& arg) {
			return arg.Arg == this->m_arg;
		}
		ParamParser::ArgType m_arg;
	};


	///--------------------------------------------------------------------------------------
	///	@brief	Read in and parse the arguments
	///--------------------------------------------------------------------------------------
	class ParamParserImplementation {

	public:

		void Parse(int number, char* args[]) {
			CppUtils::Cpp_pointerException::ptrAssert(args, _FL_);
			std::vector<Cpp_string> argList;
			for (int i = 0; i < number; i++) {
				CppUtils::Cpp_pointerException::ptrAssert(args[i], _FL_);
				argList.push_back(CppUtils::ToMrString(args[i]));
			}
			this->ParseArgs(argList);
		}


		void Parse(int number, wchar_t* args[]) {
			CppUtils::Cpp_pointerException::ptrAssert(args, _FL_);
			std::vector<Cpp_string> argList;
			for (int i = 0; i < number; i++) {
				CppUtils::Cpp_pointerException::ptrAssert(args[i], _FL_);
				argList.push_back(CppUtils::ToMrString(args[i]));
			}
			this->ParseArgs(argList);
		}


		bool HasArg(ParamParser::ArgType arg) const {
			return std::find_if(
				this->m_args.begin(),
				this->m_args.end(),
				HasArgFunctor(arg)) != this->m_args.end();
		}


		const Cpp_string& GetArg(ParamParser::ArgType arg) const {
			std::vector<ParamParserArg>::const_iterator it =
				std::find_if(
					this->m_args.begin(),
					this->m_args.end(),
					HasArgFunctor(arg));

			// Should always validate existence first to avoid secondary validation
			CppUtils::CppFileException::assertCondition(it != this->m_args.end(), _FL_, L("Arg not found"));
			return it->Value;
		}

	private:
		std::vector<ParamParserArg> m_args;

		void ParseArgs(const std::vector<Cpp_string>& argList) {
			if (argList.size() == 1 && (argList[0] == L("-h") || argList[0] == L("--help"))) {
				this->ThrowMsg(_FL_, L(""));
			}
			if (argList.size() < 3) {
				this->ThrowMsg(_FL_, L("There must be at least one valid arg"));
			}
			if (argList.size() % 2 != 1) {
				this->ThrowMsg(_FL_, L("Args must be in indicator / value pairs"));
			}

			//this->m_args.push_back(MrTest::ParamParserArg(MrTest::ParamParser::PROGRAM_NAME, argList[0]));
			for (unsigned int i = 1; i < argList.size(); i += 2) {
				this->AddArg(argList[i], argList[i + 1]);
			}
			this->ValidateArgs();
		}


		void AddArg(const Cpp_string& arg, const Cpp_string& value) {
			ParamParser::ArgType argType = ParamParser::ArgType::PROGRAM_NAME;
			if (arg == L("-d") || arg == L("--dll")) {
				argType = ParamParser::ArgType::TEST_CASE_DLL;
			}
			else if (arg == L("-c") || arg == L("--cfg")) {
				argType = ParamParser::ArgType::CONFIG_FILE;
			}
			else if (arg == L("-t") || arg == L("--test")) {
				argType = ParamParser::ArgType::TEST_CASE_LINE;
			}
			else if (arg == L("-l") || arg == L("--list")) {
				argType = ParamParser::ArgType::TEST_CASE_LIST;
			}
			else {
				Cpp_stringstream ss;
				ss << L("command option ") << arg << L(" is invalid");
				this->ThrowMsg(_FL_, ss.str());
			}
			this->m_args.push_back(ParamParserArg(argType, value));
		}


		/// @brief	Validate combinations, missing options, and duplicates
		void ValidateArgs() {
			if (!this->HasArg(ParamParser::ArgType::TEST_CASE_DLL)) {
				this->ThrowMsg(_FL_, L("No -d|-dll option to open test case DLL"));
			}

			if (this->HasArg(ParamParser::ArgType::TEST_CASE_LINE) &&
				this->HasArg(ParamParser::ArgType::TEST_CASE_LIST)) {
				this->ThrowMsg(_FL_, L("-t|-test and -l|-list options are mutually exclusive"));
			}
		}


		Cpp_string ThrowMsg(const char* file, int line, const Cpp_string& msg) {
			throw CppUtils::Cpp_exception(file, line, this->GetMsg(msg));
		}


		Cpp_string GetMsg(const Cpp_string& msg) {
			Cpp_stringstream ss;
			ss << std::endl;
			if (!msg.empty()) {
				ss << msg << std::endl;
			}
			ss << L("-------------------") << std::endl
				<< L("programName [-d|-dll] testsuite.dll [[-c|--cfg] configFileName.ini]  [[-t|--test] fixtureName[.testCaseName]]  [[-l|--list] TestCaseListFile.txt]") << std::endl
				<< L("-------------------") << std::endl
				<< L("-d|--dll The dll containing the test case code to be executed") << std::endl
				<< L("-c|--cfg configFileName.ini  - Optional - configuration file for extra log outputs") << std::endl
				<< L("-t|--test fixtureName[.testCaseName] - Optional - Execute a fixture of tests or optionaly one test case in the fixture") << std::endl
				<< L("-l|--list TestCaseListFile.txt - - Optional - File of test case identifiers to execute") << std::endl
				<< L("-h|--help This help message") << std::endl
				<< L("Note: -l|--list and t|-test are mutually exclusive") << std::endl
				<< std::endl;

			return ss.str();
		}

	};



	// Exposed ParamParser class wrapper

	ParamParser::ParamParser() : m_implementation(0) {
		this->m_implementation = new ParamParserImplementation();
	}


	ParamParser::~ParamParser() {
		if (this->m_implementation != 0) {
			delete this->m_implementation;
			this->m_implementation = 0;
		}
	}


	void ParamParser::Parse(int number, char* args[]) {
		this->m_implementation->Parse(number, args);
	}


	void ParamParser::Parse(int number, wchar_t* args[]) {
		this->m_implementation->Parse(number, args);
	}


	bool ParamParser::HasArg(ParamParser::ArgType arg) const {
		return this->m_implementation->HasArg(arg);
	}


	const Cpp_string& ParamParser::GetArg(ParamParser::ArgType arg) const {
		return this->m_implementation->GetArg(arg);
	}

}

