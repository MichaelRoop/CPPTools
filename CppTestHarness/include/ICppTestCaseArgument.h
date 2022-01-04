///--------------------------------------------------------------------------------------
/// @file	ICppTestCaseArgument.h
/// @brief	One argument for a test case
///
/// @author		Michael Roop
/// @date		2022
/// @version	1.0
///
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_CASE_ARGUMENT_H)
#define ICPP_TEST_CASE_ARGUMENT_H

#include "../include/CppTestHarnessDefines.h"
#include "../CPPVariousUtils/Cpp_macroDefines.h"
#include "../CPPVariousUtils/Cpp_string.h"


namespace CppTestHarness {

	// Follow up. Exporting each thing because of public std variable give warning
	// and do not want to turn them into pointers

	class TSTHARNESS_API ICaseArgument {
	public:

		/// <summary>Constructor</summary>
		/// <param name="name">Argument name</param>
		/// <param name="value">Argument value</param>
		ICaseArgument(const CppUtils::Cpp_string& name, const CppUtils::Cpp_string& value) {
			Name = name;
			this->Value = value;
		}


		/// <summary>Default constructor to satisfy vector requirements</summary>
		ICaseArgument() {
			Name = _L_("");
			this->Value = _L_("");

		}


		/// <summary>Copy constructor to satisfy vector requirements</summary>
		/// <param name="obj">The object to copy</param>
		ICaseArgument(const ICaseArgument& obj) {
			this->Name = obj.Name;
			this->Value = obj.Value;
		}

		// TODO - make them pointers and have function. Avoid 
		// warnings about dll-interface
		CppUtils::Cpp_string Name;
		CppUtils::Cpp_string Value;

	};


	/// <summary>Typedef for a vector of argument pairs</summary>
	/*TSTHARNESS_EXPORT*/  typedef std::vector<ICaseArgument> TestCaseArguments;

}

TSTHARNESS_EXPORT template class std::allocator<CppTestHarness::ICaseArgument>;
TSTHARNESS_EXPORT template class std::vector<CppTestHarness::ICaseArgument>;

#endif
