///--------------------------------------------------------------------------------------
/// @brief	Class that drives the testing architecture.
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_ENGINE_H)
#define CPP_TEST_ENGINE_H

#include "CppTestHarnessDefines.h"
#include "CppTestTypes.h"
#include "../CPPVariousUtils/CppSingleton.h"
#include "../CPPVariousUtils/Cpp_string.h"
#include "../CPPVariousUtils/CppSharedPtr.h"
#include <vector>


namespace CppTestHarness {

	class IFixture;
	class ITestFixtureInfoObject;
	class IFixutureTestCaseNames;
	class IEngineImplementation;

	///--------------------------------------------------------------------------------------
	/// 
	/// @brief	A Singleton class to drive the test case architecture.
	///
	///--------------------------------------------------------------------------------------
	class TSTHARNESS_API Engine : public CppUtils::CppSingleton {
	public:

		/// @brief	Destructor
		virtual ~Engine();


		/// @brief	Static method to retrieve the unique instance of this class.
		///			The engine will be created on first call.
		/// @return	The unique instance of the test engine.
		static Engine& Instance();


		/// @brief	Load a DLL of test cases
		/// @param	dllName	Name of the DLL containing the test cases
		void LoadTests(const CppUtils::Cpp_string& dllName);


		/// @brief 	Unload current DLL of test cases
		void UnloadTests();


		/// @brief	Register a test case to the system for later recall.
		/// It is easier to use the macros to create and register the test case. The engine
		/// takes ownership of the created test case.
		///
		/// @exception	Throws a mr_utils::mr_pointerException if the test case fixture pointer is invalid.
		void RegisterCase(IFixture* fixture);


		/// @brief Method to register a callback handler on the logged event
		void RegisterLoggedEvent(DataLoggedEvent loggedCallbackEvent);


		/// @brief Method to register a callback handler on the summary event
		void RegisterSummaryEvent(TestRunSummaryData summrayCallbackEvent);


		// TODO - unregister functionality on events


		/// TODO - load loggers from text xml passed in
		/// @brief	Load loggers from an init file.
		/// @exception	throws a mr_utils::mr_exception if the load fails.
		/// @param	fileName	Name of the int file.
		/// @param	fileType	Type of file loading.  Presently INI or XML
		void LoadLoggersByFileDefinition(const CppUtils::Cpp_string& fileName, const CppUtils::Cpp_string& fileType);


		/// @brief	Process the test cases using the vector of info objects that were assembled
		/// @param	list	The test fixture info objects and their tests
		void ProcessTestList(std::vector< CppUtils::CppSharedPtr<ITestFixtureInfoObject> >& list);


		/// @brief	Returns the unique id for the test run.
		CppUtils::Cpp_string GetRunId();


		/// @brief Get all the test case names that have been registered
		std::vector<CppUtils::CppSharedPtr<IFixutureTestCaseNames> > GetTestNames();

	protected:
		///@brief	Default constructor
		Engine();

	private:
		IEngineImplementation* m_implementation;	///< The implementation object to hide details
		static Engine* m_instance;			///< The unique instance of the testEngine.
	};

} // end namespace

// Force export so it can be used in of std contained object 
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppTestHarness::Engine*>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppTestHarness::Engine*>;

#endif
