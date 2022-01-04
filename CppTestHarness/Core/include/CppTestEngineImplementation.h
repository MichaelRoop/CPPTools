#if !defined(CPP_TEST_ENGINE_IMPLEMENTATION_H)
#define CPP_TEST_ENGINE_IMPLEMENTATION_H


#include "ICppTestEngineImplementation.h"
#include "CppTestLogEngine.h"
#include "CppTestCaseCounter.h"
#include "ICppTestDllManager.h"
#include "../CPPVariousUtils/CppSharedPtr.h"

namespace CppTestHarness {
			
class IFixture;					///< Forward declaration of fixture interface pointer
class IFixutureTestCaseNames;	///< Forward declaration of test case name object
class ITestFixtureInfoObject;	///< Forward declaration of Info objects to launch tests
class TestInfoObject;			///< Forward declaration of Info objects to launch a test

/// <summary>Class that hides the implementation of the test engine</summary>
class EngineImplementation : public IEngineImplementation {
public:

	/// @brief	Default constructor
	EngineImplementation();


	/// @brief	Load a DLL of test cases
	/// @param	dllName	Name of the DLL containing the test cases
	virtual void LoadTests(const CppUtils::Cpp_string& dllName);


	/// @brief 	Unload current DLL of test cases
	virtual void UnloadTests();


	/// @brief	Register a test case to the system for later recall.
	/// It is easier to use the macros to create and register the test case. The engine
	/// takes ownership of the created test case.
	///
	/// @exception	Throws a mr_utils::mr_pointerException if the test case fixture pointer is invalid.
	virtual void RegisterCase(IFixture* fixture);


	/// @brief Method to register a callback handler on the logged event
	virtual void RegisterLoggedEvent(DataLoggedEvent loggedCallbackEvent);


	/// @brief Method to register a callback handler on the summary event
	virtual void RegisterSummaryEvent(TestRunSummaryData summrayCallbackEvent);


	// TODO - unregister functionality on events


	/// TODO - load loggers from text xml passed in
	/// @brief	Load loggers from an init file.
	/// @exception	throws a mr_utils::mr_exception if the load fails.
	/// @param	fileName	Name of the int file.
	/// @param	fileType	Type of file loading.  Presently INI or XML
	virtual void LoadLoggersByFileDefinition(
		const CppUtils::Cpp_string& fileName, const CppUtils::Cpp_string& fileType);


	/// @brief	Process the test cases using the vector of info objects that were assembled
	/// @param	list	The test fixture info objects and their tests
	virtual void ProcessTestList(std::vector<CppUtils::CppSharedPtr<ITestFixtureInfoObject> >& list);


	/// @brief	Returns the unique id for the test run.
	virtual CppUtils::Cpp_string GetRunId();

	/// @brief Get all the test case names that have been registered
	virtual std::vector<CppUtils::CppSharedPtr<IFixutureTestCaseNames> > GetTestNames();

private:
	std::vector<IFixture*>			m_fixtures;		///< The vector of registered test case fixtures.
	CppUtils::Cpp_string			m_runId;		///< Unique ID for the run used in log files.
	LogEngine						m_logEngine;	///< The logging engine.
	std::vector<DataLoggedEvent>	m_logEvents;	///< Vector of registered log events
	std::vector<TestRunSummaryData> m_summaryEvents;///< Vector of registered log events
	CaseCounter						m_caseCounter;	///< track test case summary data
	CppUtils::CppSharedPtr<IDllManager>m_testDllManger;///< Manages the test case DLLs


	/// @brief	Process one test case fixture based on information contained in the testInfoObject.
	///			The testInfoObject has the test name for lookup as well as the arguments needed to 
	///			feed to the test case.
	/// @param	testInfo	The data necessary to look up and run the test case.
	void ProcessCase(const TestInfoObject& testInfo);


	/// @brief	Log the results of one test case across log outputs.
	/// @exception	Throws a mr_utils::mr_pointerException if the testCase pointer is invalid.
	/// @param	fixture	The test case fixture whose results are to be logged.
	void LogResults(ICase& caseData);


	/// @brief	Run every test case in the fixture
	/// @param	fixtureName	The name of the fixture with the test cases
	void RunAllFixtureTests(const CppUtils::Cpp_string& fixtureName);


	/// @brief	Run every test case in the fixture
	/// @param	fixtureName	The name of the fixture with the test cases
	void RunSelectFixtureTests(
		const CppUtils::Cpp_string& fixtureName, const std::vector<TestInfoObject>& testInfos);


	/// @brief	Get the fixture from the registered list
	/// @param	fixtureName	The name of the fixture to retrieve
	std::vector<IFixture*>::iterator GetFixtureIterator(const CppUtils::Cpp_string& fixtureName);


	/// @brief	Log the summary results of all test cases for a run
	void LogSummaries();

};

} // end namespace

#endif
