#if !defined(CPP_TEST_SCRIPT_EXCEPTION_H)
#define CPP_TEST_SCRIPT_EXCEPTION_H

#include "CppTestHarnessDefines.h"
#include "../CPPVariousUtils/Cpp_exceptions.h"


namespace CppTestHarness {

	///--------------------------------------------------------------------------------------
	///
	///	@brief	Class to throw exceptions detected on reading script.
	///
	/// Extendends the mr_utils::mr_exception by storing the script file name and the 
	/// contents of the line being processed.  This information is appended onto the 
	/// formatted long message.
	///
	/// Use the FL macro to insert the file name and line from the system.
	/// Use the L() macro to provide cross char width portability.
	/// Use the cross char width streaming so that the message can be displayed on both
	/// both narrow and wide char compilation mode.
	///
	/// Example: 
	///		throw mr_utils::scriptException( 
	///			FL, L("The value is outside range"), scriptName, scriptLineContent );
	///
	/// On the catch you can either access the different parts of the message or use the formatted
	/// message.
	///
	///		catch( const mr_utils::mr_exception& e ) {
	///			mr_cout << e.longMsg() << std::endl;
	///		}
	///
	///--------------------------------------------------------------------------------------
	class TSTHARNESS_API ScriptException : public CppUtils::Cpp_exception {
	public:

		/// @brief	Constructor.
		///
		/// @param	file			The source code file where problem originates.
		/// @param	line			The source code line where problem originates.
		/// @param	msg				The message explaining the exception.
		/// @param	scriptFileName	The name of the script file being processed.
		/// @param	scriptLine		The content of the script line being processed.
		ScriptException(
			const char* file,
			int							line,
			const CppUtils::Cpp_string& msg,
			const CppUtils::Cpp_string& scriptFileName,
			const CppUtils::Cpp_string& scriptLine = L("")
		);


		/// @brief	Destructor.
		virtual ~ScriptException() throw();


		/// @brief	Returns a formated verbose exception message.
		///
		/// The format is as following.
		///    	"Exception:SourceFile:SourceLine message : ScriptFile.txt : line contents"
		///
		/// @return	Verbose exception message.
		virtual const CppUtils::Cpp_string LongMsg() const;

	protected:

		CppUtils::Cpp_string m_scriptFileName;	///< Script file being processed.
		CppUtils::Cpp_string m_scriptLine;		///< Contents of the line in question.

	};

}

#endif
