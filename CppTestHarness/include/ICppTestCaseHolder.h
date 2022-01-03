///--------------------------------------------------------------------------------------
/// @brief	Interface object that holds a test function pointer and the test data 
///			accumulator
///
/// @author		Michael Roop
/// @date		2022
/// @version	1.5
///
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_CASE_HOLDER_H)
#define ICPP_TEST_CASE_HOLDER_H

#include "include/CppTestHarnessDefines.h"
#include "ICppTestFixture.h"


namespace CppTestHarness {

	///--------------------------------------------------------------------------------------
	///
	///	@brief	Associates the test pointer with the Case object that stores test results
	///
	///--------------------------------------------------------------------------------------
	class TSTHARNESS_API ITestCaseHolder {

	public:

		/// @brief	Default constructor
		ITestCaseHolder() {
		}


		/// @brief	Return the test method pointer
		virtual IFixture::Ifixture_method_ptr Pointer() const = 0;


		/// @brief	Return the test data capture object
		virtual ICase* Data() const = 0;


		/// @brief	Reset the test case data object to non run state
		virtual void Reset() = 0;

	private:

		/// @brief	Copy constructor
		ITestCaseHolder(const ITestCaseHolder& obj) {
		}

	};

} // end namespace MrTest

// Force export of contained std items
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppTestHarness::ITestCaseHolder*>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppTestHarness::ITestCaseHolder*>;

#endif
