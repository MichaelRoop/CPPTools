///--------------------------------------------------------------------------------------
/// @brief	
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_LIST_BUILDER_H)
#define ICPP_TEST_LIST_BUILDER_H

#include "include/CppTestHarnessDefines.h"
#include "../ScriptReader/include/IMrTestScriptReader.h"
#include "include/ICppTestFixtureInfoObject.h"
#include "../CPPVariousUtils/CppSharedPtr.h"
#include "../CPPVariousUtils/Cpp_string.h"
#include <vector>

namespace CppTestHarness {

	///--------------------------------------------------------------------------------------
	/// 
	/// @brief	Build a list of tests grouped by fixture
	///
	///--------------------------------------------------------------------------------------
	class TSTHARNESS_API IListBuilder {
	public:

		/// @brief	Process the test cases using the vector of info objects that were assembled
		/// @param	list	The test fixture info objects and their tests
		virtual std::vector<CppUtils::CppSharedPtr<ITestFixtureInfoObject> >
			Build(IScriptReader& theReader) const = 0;

	};

} // end namesapce

// Force export of class with std objects
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppUtils::CppSharedPtr<CppTestHarness::IListBuilder> >;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppUtils::CppSharedPtr<CppTestHarness::IListBuilder> >;


#endif
