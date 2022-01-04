///--------------------------------------------------------------------------------------
/// @brief	Output Interface to be used with logger objects.
///--------------------------------------------------------------------------------------
#if !defined(ICPP_TEST_ILOG_OUTPUT_H)
#define ICPP_TEST_ILOG_OUTPUT_H

#include "include/CppTestHarnessDefines.h"
#include "../CPPVariousUtils/Cpp_string.h"

namespace CppTestHarness {

	//----------------------------------------------------------------------------------------
	/// @briefs	Pure virtual base class for outputing logging information.
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
	class ILogOutput {
	public:

		/// <summary>Initialise the object</summary>
		/// <returns>true if successful, otherwise false</returns>
		virtual bool InitOutput() = 0;


		/// <summary>Close the object</summary>
		virtual void CloseOutput() = 0;


		/// <summary>Write to the output object</summary>
		/// <param name="str">The string to write out</param>
		/// <exception>CppUtils::Cpp_exception if output is not open</exception>
		/// <returns>true if successful, otherwise false</returns>
		virtual bool Write(const CppUtils::Cpp_string& str) = 0;

	};

} // end namespace

#endif
