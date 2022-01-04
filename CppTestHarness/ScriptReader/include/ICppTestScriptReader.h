///--------------------------------------------------------------------------------------
/// @brief	cross platform and char width script exception for dev test platform.
///--------------------------------------------------------------------------------------

#if !defined(ICPP_TEST_SCRIPT_READER_H)
#define ICPP_TEST_SCRIPT_READER_H

#include "include/CppTestHarnessDefines.h"
#include "include/CppTestInfoObject.h"
#include "../CPPVariousUtils/Cpp_exceptions.h"


namespace CppTestHarness {

	///--------------------------------------------------------------------------------------
	///
	/// @brief	Pure virtual class to abstract the reading of a test script.
	///
	/// The derived classes can read a script file of any format from any source as long
	/// as they satisfy the interface.  In this case you could have a custom format of script
	/// file or one that used known formats such as ini or XML.
	///--------------------------------------------------------------------------------------
	class TSTHARNESS_API IScriptReader {
	public:

		/// @brief	Opens the script.
		virtual void Open() = 0;


		/// @brief	Extracts the test information from the current test script line.
		/// @param	fixtureName	Name of the fixture for the test case.
		/// @return	The populated testInfoObject for the test.  If the object has no more
		///			script lines the testInfoObject.isValid() will return false.
		virtual TestInfoObject GetNextTest(Cpp_string& fixtureName) = 0;

	};

} // end namespace

TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppTestHarness::IScriptReader*>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppTestHarness::IScriptReader*>;

#endif
