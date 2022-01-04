#if !defined(CPP_TEST_CONSOLE_OUTPUT_H)
#define CPP_TEST_CONSOLE_OUTPUT_H


#include "ICppTestLogOutput.h"


namespace CppTestHarness {

	//----------------------------------------------------------------------------------------
	/// @brief	Class for outputing logging information to the console.
	///
	/// Always use the cross character width objects and macros to make the data portable
	/// for wide and narrow char compilation.
	///
	/// When feeding chars to the output stream use the L() macro
	///	 example: fileOutput->getOsStream() << L("This is a message");
	/// 
	/// When feeding string objects to the output stream use the mr_string or mr_stringstream.
	///	 example: 
	///		mr_string s( L("This is a message") );
	///		fileOutput->getOsStream() << s;
	///
	///
	/// This class is used by derived logger classes to output the log data after formating.
	///
	//----------------------------------------------------------------------------------------
	class ConsoleOutput : public ILogOutput {
	public:

		/// @brief	Initialise the object.
		/// @return	true if successful, otherwise false.
		bool InitOutput();


		/// @brief	Close the object.
		/// @return	true if successful, otherwise false.
		void CloseOutput();


		/// @brief	Write to the output object.
		/// @return	true if successful, otherwise false.
		bool Write(const Cpp_string& str);

	};

}

#endif
