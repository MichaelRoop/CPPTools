#if !defined(CPP_TEST_PARAM_PARSER_H)
#define CPP_TEST_PARAM_PARSER_H

#include "CppTestHarnessDefines.h"
#include "../CPPVariousUtils/Cpp_string.h"

namespace CppTestHarness {

	class ParamParserImplementation;

	/// <summary>Read in and parse the arguments</summary>
	class TSTHARNESS_API ParamParser {

	public:
		/// @brief	Status indicator for the test case.
		enum class ArgType {
			PROGRAM_NAME,	///< Supplied by system. Executable name
			CONFIG_FILE,	///< Configuration file name
			TEST_CASE_LINE,	///< Test fixture or fixture.testCase to execute
			TEST_CASE_LIST,	///< File name for list of test cases
			TEST_CASE_DLL,	///< The DLL containing the test cases to load
			UNKNOWN
		};


		/// @brief	Constructor
		ParamParser();


		/// @brief	Destructor
		virtual ~ParamParser();


		/// @brief	Parse out the narrow character command line arguments
		void Parse(int number, char* args[]);


		/// @brief	Parse out the wide character command line arguments
		void Parse(int number, wchar_t* args[]);


		/// @brief	Report if the parser found an argument of a certain type
		bool HasArg(ParamParser::ArgType) const;


		/// @brief	Retrieve an argument of a certain type
		const CppUtils::Cpp_string& GetArg(ParamParser::ArgType) const;


	private:
		///< Implementation object to hide internals
		ParamParserImplementation* m_implementation; 

	};

} 

#endif
