///--------------------------------------------------------------------------------------
/// @file	ICppTestCase.h
/// @brief	Interface for Holder for test case execution results data
///
/// @author		Michael Roop
/// @date		2022
/// @version	1.5
///
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_CASE_H)
#define ICPP_TEST_CASE_H

#include "include/CppTestHarnessDefines.h"
#include "../CPPVariousUtils/Cpp_string.h"
#include "../CPPVariousUtils/Cpp_sstream.h"
#include <assert.h>

namespace CppTestHarness {

///--------------------------------------------------------------------------------------
///	@brief	Holder for test case execution results data
///
/// Besides name and description, this class encapsulates data accumulated during the 
// running of the named test. This includes test status, as well as performance counters
/// for setup, test and teardown. It also has optional long and short messages that can
/// be written within the test case or by one of the assert test macros.
///
/// The test case object can be querried by the logger derived objects to assemble the 
/// information required.
///--------------------------------------------------------------------------------------
class TSTHARNESS_API ICase {

public:

	/// <summary>Status indicator for the test case</summary>
	enum class TestCaseStatus {
		ST_NONE,					///< No status. Default
		ST_DISABLED,				///< Test exists but marked disabled in script
		ST_NOT_EXISTS,				///< Test does not exist
		ST_SUCCESS,					///< Successful
		ST_FAIL_SETUP,				///< Failed on test setup
		ST_FAIL_TEST,				///< Failed on test
		ST_FAIL_CLEANUP,			///< Failed on test teardown
		ST_FAIL_FIXTURE_SETUP,		///< Failed on Fixture setup
		ST_FAIL_FIXTURE_TEARDOWN	///< Failed on Fixture teardown
	};


	/// <summary>Static method to convert status enum to string</summary>
	/// <param name="status">The status to convert</param>
	/// <returns>String form of status</returns>
	static CppUtils::Cpp_string ToString(TestCaseStatus status) {
		switch (status) {
			case TestCaseStatus::ST_NONE:			return L( "NONE" );
			case TestCaseStatus::ST_DISABLED:		return L("DISABLED");
			case TestCaseStatus::ST_SUCCESS:		return L( "SUCCESS" );
			case TestCaseStatus::ST_FAIL_SETUP:		return L( "FAIL_SETUP" );
			case TestCaseStatus::ST_FAIL_TEST:		return L( "FAIL_TEST" );
			case TestCaseStatus::ST_FAIL_CLEANUP:	return L( "FAIL_CLEANUP" );
			case TestCaseStatus::ST_NOT_EXISTS:		return L( "NOT_EXISTS" );
			case TestCaseStatus::ST_FAIL_FIXTURE_SETUP: return _L_("FAIL_FIXTURE_SETUP");
			case TestCaseStatus::ST_FAIL_FIXTURE_TEARDOWN: return _L_("FAIL_FIXTURE_TEARDOWN");
		default:				
			assert(false);
			return L( "ERROR-NO-STATUS" );
		}
	}


	/// @brief	Constructor
	///	@param	name	Name of the test case.
	///	@param	description	Description of test case.
	ICase(
		const CppUtils::Cpp_string& fixtureName,
		const CppUtils::Cpp_string& name,
		const CppUtils::Cpp_string& desc) {

		this->FixtureName = fixtureName;
		this->Name = name;
		this->Description = desc;
	}


	/// @brief	Called to reset internal state
	virtual void Reset() = 0;

public:
	TestCaseStatus				Status = TestCaseStatus::ST_NONE;
	CppUtils::Cpp_string		FixtureName;
	CppUtils::Cpp_string		Name;
	CppUtils::Cpp_string		Description;
	//CppTestHarness::TestArguments	m_args;	
	CppUtils::Cpp_stringstream	MsgBuffer;		
	CppUtils::Cpp_stringstream	MsgBufferEmbedded;	// Used internally to create embedded messages
	CppUtils::Cpp_stringstream	MsgBufferVerbose;	
	long long					SetupTimeMs = 0;
	long long					ExecTimeMs = 0;
	long long					CleanupTimeMs = 0;

private:

	/// @brief	Constructor
	ICase() { }


	/// @brief	Copy constructor
	/// @param	testCase	The testCase used for construction.
	ICase(const ICase& testCase) { }

};

} // end namespace MrTest::Case

// TODO - no longer needed?
// Force export of std items
//TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppTestHarness::ICase*>;
//TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppTestHarness::ICase*>;
TSTHARNESS_EXPORT template class std::allocator<CppTestHarness::ICase*>;
TSTHARNESS_EXPORT template class std::vector<CppTestHarness::ICase*>;

#endif
