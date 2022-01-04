///--------------------------------------------------------------------------------------
/// @brief	Storage for test fixture name and its test case names
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_FIXTURE_TEST_CASE_NAMES_H)
#define CPP_TEST_FIXTURE_TEST_CASE_NAMES_H

#include "ICppTestFixtureTestCaseNames.h"

namespace CppTestHarness {

	//----------------------------------------------------------------------------------------
	/// @brief	Storage for test fixture name and its test case names.
	//----------------------------------------------------------------------------------------
	class TSTHARNESS_API FixutureTestCaseNames : public IFixutureTestCaseNames {
	public:

		/// @brief The name of the fixture
		FixutureTestCaseNames(const CppUtils::Cpp_string& name);


		/// @brief A vector of the fixture test case names
		FixutureTestCaseNames(const FixutureTestCaseNames& obj);


		/// @brief The name of the fixture
		virtual const CppUtils::Cpp_string& FixtureName() const;


		/// @brief A vector of the fixture test case names
		virtual const std::vector<CppUtils::Cpp_string>& TestCaseNames() const;


		/// @brief Add a test case name to the list
		virtual void AddTestCaseName(const CppUtils::Cpp_string& name);

	private:
		CppUtils::Cpp_string m_name;
		std::vector<CppUtils::Cpp_string> m_testCaseNames;

	private:

		/// @brief Default constructor
		FixutureTestCaseNames() {
		}

	};

} // end namespace

// Force export
TSTHARNESS_EXPORT template class TSTHARNESS_API CppUtils::CppSharedPtr<CppTestHarness::FixutureTestCaseNames>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppUtils::CppSharedPtr<CppTestHarness::FixutureTestCaseNames> >;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppUtils::CppSharedPtr<CppTestHarness::FixutureTestCaseNames> >;

#endif
