#if !defined(CPP_TEST_LOG_ENGINE_H)
#define CPP_TEST_LOG_ENGINE_H

#include "CppTestHarnessDefines.h"
#include "ICppTestCase.h"
#include "ICppTestLog.h"
#include "../CPPVariousUtils/CppSharedPtr.h"
#include "../CPPVariousUtils/Cpp_string.h"
#include <vector>


namespace CppTestHarness {

	/// <summary>Drives test case info logging across a variable number of derived Logs</summary>
	class TSTHARNESS_API LogEngine {
	public:

		/// @brief	Constructor.
		LogEngine();


		/// @brief	Destructor.
		virtual ~LogEngine();


		/// @brief	Write the header information across all loggers.
		/// @exception	throws a mr_utils::mr_pointerException on invalid loggers.
		/// @return	true if successful, otherwise false.
		bool WriteHeaders();


		/// @brief	Write the summary information across all loggers.
		/// @exception	throws a mr_utils::mr_pointerException on invalid loggers.
		/// @return	true if successful, otherwise false.
		bool WriteSummaries();


		/// @brief	Log the test case information across all loggers.
		///
		/// @exception	throws a mr_utils::mr_pointerException on invalid testCase.
		/// @exception	throws a mr_utils::mr_pointerException on invalid loggers.
		///
		/// @return	true if successful, otherwise false.
		bool Log(ICase& testCase);


		/// <summary>Add a logger object to the logger group</summary>
		/// <param name="theLogger">Pointer to the logger to add</param>
		/// <exception>CppUtils::Cpp_exception if test case object is invalid</exception>
		void AddLogger(const CppUtils::CppSharedPtr<ILog>& theLogger);


		/// <summary>Load loggers from init file</summary>
		/// <param name="filename">File name</param>
		/// <exception>CppUtils::Cpp_exception on load failure</exception>
		/// <param name="fileType">Type of file loading.  Presently INI or XML</param>
		void LoadLoggers(const CppUtils::Cpp_string& filename, const CppUtils::Cpp_string& fileType);

	protected:

		///< Vector of derived logger objects.
		std::vector<CppUtils::CppSharedPtr<ILog>>	m_logs; 
	};

} // end namespace

// Force export
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppUtils::CppSharedPtr<CppTestHarness::LogEngine>>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppUtils::CppSharedPtr<CppTestHarness::LogEngine>>;

#endif
