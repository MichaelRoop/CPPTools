#if !defined(CPP_TEST_LIST_BUILDER_H)
#define CPP_TEST_LIST_BUILDER_H

#include "ICppTestListBuilder.h"

namespace CppTestHarness {
	
	/// <summary>A Singleton class to drive the test case architecture</summary>
	class TSTHARNESS_API ListBuilder : public IListBuilder {
	public:

		/// @brief	Process the test cases using the vector of info objects that were assembled
		/// @param	list	The test fixture info objects and their tests
		virtual std::vector<CppUtils::CppSharedPtr<ITestFixtureInfoObject>>
			Build(IScriptReader& theReader) const;

	};

}

// Force export of class with std objects
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppUtils::CppSharedPtr<CppTestHarness::ListBuilder> >;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppUtils::CppSharedPtr<CppTestHarness::ListBuilder> >;

#endif

