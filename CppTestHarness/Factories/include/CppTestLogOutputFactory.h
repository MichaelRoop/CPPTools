#if !defined(CPP_TEST_LOG_OUTPUT_FACTORY_H)
#define CPP_TEST_LOG_OUTPUT_FACTORY_H


#include "ICppTestLogOutput.h"
#include "ICppTestLogInitialiser.h"


namespace CppTestHarness {

	typedef CppSharedPtr<ILogOutput> LogOutputSharedPtr;

	//----------------------------------------------------------------------------------------
	/// @brief	Class for creating iLogInitiser objects.
	///
	/// 
	class LogOutputFactory {
	public:

		///	@brief	Creates the appropriate iLogInitialiser.
		///
		/// @param	initialiser	Initialiser object. 
		static LogOutputSharedPtr Create(CppSharedPtr<ILogInitialiser>& initialiser);
	};


}

#endif
