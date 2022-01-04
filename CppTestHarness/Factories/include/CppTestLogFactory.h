#if !defined(CPP_TEST_LOG_FACTORY_H)
#define CPP_TEST_LOG_FACTORY_H

#include "ICppTestLog.h"
#include "ICppTestLogInitialiser.h"

namespace CppTestHarness {

	typedef CppSharedPtr<ILog> LogSharedPtr;

	//----------------------------------------------------------------------------------------
	/// @brief	Class for creating iLogInitiser objects.
	///
	/// 
	class LogFactory {
	public:

		///	@brief	Creates the appropriate iLogInitialiser.
		///
		/// @param	configFileName	Configuration file name. 
		/// @param	configFileType	Configuration file type. 
		/// @param	section			Configuration file section.
		static LogSharedPtr Create(
			const Cpp_string& configFileName,
			const Cpp_string& configFileType,
			const Cpp_string& section
		);

	private:

		/// @brief	Constructor.
		///
		/// @param	output			A SharedObject logOutput object.
		/// @param	summaryLog		A SharedObject summary logger.
		/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
		static LogSharedPtr Create(
			CppSharedPtr<ILogOutput>& output,
			CppSharedPtr<ILog>& summaryLog,
			CppSharedPtr<ILogInitialiser>& initialiser
		);
	};


}

#endif
