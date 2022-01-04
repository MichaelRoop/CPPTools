#if !defined(CPP_TEST_SCRIPT_READER_BASE_H)
#define CPP_TEST_SCRIPT_READER_BASE_H

#include "ICppTestScriptReader.h"


namespace CppTestHarness {

	/// <summary>
	/// Pure virtual class to abstract the reading of a test script.
	///
	/// The derived classes can read a script file of any format from any source as long
	/// as they satisfy the interface.  In this case you could have a custom format of script
	/// file or one that used known formats such as ini or XML.
	/// </summary>
	class TSTHARNESS_API ScriptReaderBase : public IScriptReader {
	protected:

		/// @brief	Constructor.
		/// @param	origine			The origine of the script
		/// @param	nameDelimiter	Delimiter character to tokenize the name and 
		///							argument portion of the line.
		/// @param	argDelimiter	Delimiter to tokenize the argument portion of the
		///							line into separate arguments.
		ScriptReaderBase(
			const Cpp_string& origine, 
			Cpp_char nameDelimiter = _L_('$'), 
			Cpp_char argDelimiter = _L_('|'));


		/// @brief	Helper method to process one line of the script file.
		/// @param	fixtureName	Name of the fixture for the test case.
		///	@throw	Throws a scriptException on failure
		/// @param	testInfo	The testInfoObject to populate from the script file.
		/// @param	str			The line as read from the file.
		void ProcessLine(
			Cpp_string& fixtureName, 
			TestInfoObject& testInfo, 
			Cpp_string str);


		/// @brief	Helper method to process the arguments portion of the script line.
		///	@throw	Throws a scriptException on failure
		/// @param	testInfo	The testInfoObject to populate from the script file.
		/// @param	args		The args portion of the script line.
		void ProcessArgs(TestInfoObject& testInfo, const Cpp_string& args);


		/// @brief	Helper method to process one argument string token.
		/// Each argument should be in the format name=value.
		///	@throw	Throws a scriptException on failure
		/// @param	testInfo	The testInfoObject to populate from the script file.
		/// @param	args		The arg token from the script line.
		void ProcessArg(TestInfoObject& testInfo, const Cpp_string& arg);


		/// @brief	Extracts name on first call and value on second.
		///	@throw	Throws a scriptException on failure
		/// @param	pos		The current position in the argument string.
		/// @param	str		The argument string.
		/// @param	token	The string token to be extracted from the argument string.
		void GetArgComponent(
			Cpp_string::size_type& pos, const Cpp_string& str, Cpp_string& token) const;


		/// @brief	Wrapper to clean up checking for exception throw.
		///	@throw	Throws a scriptException on failure
		/// @param	origine			Where is this sript line originating from
		/// @param	condition		The condition to test. If false an exception is thrown.
		/// @param	file			The source code file where problem originates.
		/// @param	line			The source code line where problem originates.
		/// @param	msg				The message explaining the exception.
		/// @param	scriptFileLine	The content of the script line being processed.
		void ScriptAssert(
			bool condition,
			const char* file,
			int line,
			const Cpp_string& msg,
			const Cpp_string& scriptLine = _L_("")) const;


		/// @brief	Wrapper to clean up checking for exception throw.
		///	@throw	Throws a fileException on failure
		/// @param	origine			Where is this sript line originating from
		/// @param	condition		The condition to test. If false an exception is thrown.
		/// @param	file			The source code file where problem originates.
		/// @param	line			The source code line where problem originates.
		/// @param	msg				The message explaining the exception.
		void FileAssert(
			bool condition,
			const char* file,
			int line,
			const Cpp_string& msg) const;

	private:
		Cpp_char m_nameDelimiter;
		Cpp_char m_argDelimiter;
		Cpp_string m_origine;

		/// @brief	Default constructor
		ScriptReaderBase();

	};

} // end namespace

TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppTestHarness::ScriptReaderBase*>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppTestHarness::ScriptReaderBase*>;

#endif
