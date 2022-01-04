///--------------------------------------------------------------------------------------
/// @brief	cross platform and char width holder for test information.
///
/// @author		Michael Roop
/// @date		2022
///
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_FIXTURE_INFO_OBJECT_H)
#define ICPP_TEST_FIXTURE_INFO_OBJECT_H

#include "../include/CppTestHarnessDefines.h"
#include "../include/CppTestInfoObject.h"
#include "../CPPVariousUtils/Cpp_string.h"
#include "../CPPVariousUtils/CppSharedPtr.h"
#include <vector>


namespace CppTestHarness {


///--------------------------------------------------------------------------------------
///
/// @brief	Class to abstract the information necessary to retrieve a Fixture of test cases
///
///--------------------------------------------------------------------------------------
class TSTHARNESS_API ITestFixtureInfoObject {

public:

	/// @brief Default constructor
	ITestFixtureInfoObject() {
	}


	/// @brief Retrieve Test fixture name
	virtual const  CppUtils::Cpp_string& GetName() const = 0;


	/// @brief Set the Test fixture name
	/// @brief	name	The test fixture name
	virtual const void SetName(CppUtils::Cpp_string& name) = 0;


	/// @brief	Retrieve the argument set.
	///
	/// @return	The argument set.
	virtual const std::vector<TestInfoObject>& GetTestInfoVector() = 0;


	/// @brief	Add an argument to the argument set.
	///
	/// @param	name	The name of the argument.
	/// @param	value	The value of the argument.
	virtual void AddTestInfo(const TestInfoObject& info) = 0;

private:

	/// @brief	Protected copy constructor to force use of regular constructor.
	/// @param	tc	The testCase used for construction.
	ITestFixtureInfoObject(const ITestFixtureInfoObject& tc) {
	}

};

} // end namespace

// Force export of class with std objects
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppTestHarness::ITestFixtureInfoObject*>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppTestHarness::ITestFixtureInfoObject*>;

#endif
