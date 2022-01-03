///--------------------------------------------------------------------------------------
/// @brief	Encapsulates loading and unloading of test case DLLs
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_DLL_MANAGER_H)
#define ICPP_TEST_DLL_MANAGER_H

#include "include/CppTestHarnessDefines.h"
#include "../CPPVariousUtils/Cpp_string.h"
#include "../CPPVariousUtils/CppSharedPtr.h"

namespace CppTestHarness {

///--------------------------------------------------------------------------------------
///	@brief	Manages the loading and unloading of test case DLLs
///--------------------------------------------------------------------------------------
class TSTHARNESS_API IDllManager {

public:

	/// @brief	Load a named DLL
	virtual void Load(const CppUtils::Cpp_string& name) = 0;


	/// @brief	Unload a named DLL
	virtual void Unload() = 0;

};

} // end namespace MrTest::Case

// Force export of std items
TSTHARNESS_EXPORT template class TSTHARNESS_API CppUtils::CppSharedPtr<CppTestHarness::IDllManager>;

#endif
