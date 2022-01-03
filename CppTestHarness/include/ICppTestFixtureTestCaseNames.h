///--------------------------------------------------------------------------------------
/// @file	IMrTestFixtureTestCaseNames.h
/// @brief	Interface for storage for test fixture name and its test case names
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_FIXTURE_TEST_CASE_NAMES_H)
#define ICPP_TEST_FIXTURE_TEST_CASE_NAMES_H

#include "include/CppTestHarnessDefines.h"
#include "../CPPVariousUtils/Cpp_string.h"
#include "../CPPVariousUtils/CppSharedPtr.h"
#include <vector>

namespace CppTestHarness {

	//----------------------------------------------------------------------------------------
	/// @brief	Interface for storage for storage for test fixture name and its test case names.
	//----------------------------------------------------------------------------------------
	class TSTHARNESS_API IFixutureTestCaseNames {
	public:

		/// @brief The name of the fixture
		virtual const CppUtils::Cpp_string& FixtureName() const = 0;


		/// @brief A vector of the fixture test case names
		virtual const std::vector<CppUtils::Cpp_string>& TestCaseNames() const = 0;


		/// @brief Add a test case name to the list
		virtual void AddTestCaseName(const CppUtils::Cpp_string& name) = 0;

	};

} // end namespace

// Force the export of the std objects in the class
TSTHARNESS_EXPORT template class CppUtils::CppSharedPtr<CppTestHarness::IFixutureTestCaseNames>;
TSTHARNESS_EXPORT template class std::allocator<CppUtils::CppSharedPtr<CppTestHarness::IFixutureTestCaseNames> >;
TSTHARNESS_EXPORT template class std::vector<CppUtils::CppSharedPtr<CppTestHarness::IFixutureTestCaseNames> >;

#endif
