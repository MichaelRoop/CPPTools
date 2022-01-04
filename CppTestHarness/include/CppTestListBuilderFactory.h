#if !defined(CPP_TEST_LIST_BUILDER_FACTORY_H)
#define CPP_TEST_LIST_BUILDER_FACTORY_H

#include "CppTestHarnessDefines.h"
#include "ICppTestFixtureInfoObject.h"
#include "../CPPVariousUtils/CppSharedPtr.h"
#include <vector>

namespace CppTestHarness {

	class IFixutureTestCaseNames;
	
	/// <summary>Builds a list of tests grouped by fixture
	/// 
	/// </summary>
	class TSTHARNESS_API ListBuilderFactory {
	public:

		/// @brief	Build a test list from file
		/// @param	filename	The name of the file with the list
		static std::vector<CppUtils::CppSharedPtr<ITestFixtureInfoObject>>
			FromFile(
				const CppUtils::Cpp_string& filename,
				CppUtils::Cpp_char nameDelimiter = _L_('$'),
				CppUtils::Cpp_char argDelimiter = _L_('|'));

		/// @brief	Build a test list from a single line
		/// @param	line	The line with test information to process
		static std::vector<CppUtils::CppSharedPtr<ITestFixtureInfoObject>>
			FromLine(const CppUtils::Cpp_string& line);


		/// @brief	Build a test list from a vector of lines, one test per line
		/// @param	lines	The vector with the test lines 
		static std::vector<CppUtils::CppSharedPtr<ITestFixtureInfoObject>>
			FromLines(
				const std::vector<CppUtils::Cpp_string>& lines,
				CppUtils::Cpp_char nameDelimiter = _L_('$'),
				CppUtils::Cpp_char argDelimiter = _L_('|'));


		/// @brief	Build a test list from a vector Fixture Test Case Names
		/// @param	lines	The vector with the test case names objects 
		static std::vector<CppUtils::CppSharedPtr<ITestFixtureInfoObject>>
			FromTestCaseNames(const std::vector<CppUtils::CppSharedPtr<IFixutureTestCaseNames> >& testCaseNames);

	};

}

// Force export of class with std objects
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppUtils::CppSharedPtr<CppTestHarness::ListBuilderFactory*>>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppUtils::CppSharedPtr<CppTestHarness::ListBuilderFactory*>>;


#endif
