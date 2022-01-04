#if !defined(CPP_TEST_LOG_INITIALISER_FACTORY_H)
#define CPP_TEST_LOG_INITIALISER_FACTORY_H

#include "ICppTestLogInitialiser.h"


namespace CppTestHarness {

	typedef CppSharedPtr<ILogInitialiser> LogInitialiserSharedPtr;

	//----------------------------------------------------------------------------------------
	/// @brief	Class for creating iLogInitiser objects.
	///
	/// 
	class LogInitialiserFactory {
	public:

		///	@brief	Creates the appropriate iLogInitialiser.
		///
		/// @param	configFileName	Configuration file name. 
		/// @param	configFileType	Configuration file type. 
		/// @param	section			Configuration file section.
		static LogInitialiserSharedPtr Create(
			const Cpp_string& configFileName,
			const Cpp_string& configFileType,
			const Cpp_string& section
		);


		/// @todo	Review this - different object versus reuse
		///	@brief	Creates the appropriate iLogInitialiser without a section
		///
		/// @param	configFileName	Configuration file name. 
		/// @param	configFileType	Configuration file type. 
		/// @param	section			Configuration file section.
		static LogInitialiserSharedPtr Create(
			const Cpp_string& configFileName,
			const Cpp_string& configFileType
		);
	};

}

#endif
