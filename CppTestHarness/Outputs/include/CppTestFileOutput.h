#if !defined(CPP_TEST_FILE_OUTPUT_H)
#define CPP_TEST_FILE_OUTPUT_H


#include "ICppTestLogOutput.h"
#include "../CPPVariousUtils/Cpp_fstream.h"

using CppUtils::Cpp_ofstream;

namespace CppTestHarness {

	//----------------------------------------------------------------------------------------
	/// @brief	Class for outputing logging information to a file.
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
	/// This class is used by derived logger classes to output the log data after formating.
	///
	//----------------------------------------------------------------------------------------
	class FileOutput : public ILogOutput {
	public:

		/// @brief	Constructor.
		/// @param	filename	Name of the output log file.
		FileOutput(const std::string& filename);


		/// @brief	Initialise the object.
		/// @exception	mr_exception if the file name is empty or the file cannot be opened.
		/// @return	true if successful, otherwise false.
		bool InitOutput();


		/// @brief	Close the object.
		/// @return	true if successful, otherwise false.
		void CloseOutput();


		/// @brief	Write to the output object.
		/// @exception mr_utils::mr_exception if file is not open.
		/// @return	true if successful, otherwise false.
		bool Write(const Cpp_string& str);

	private:
		std::string m_filename;
		Cpp_ofstream m_file;


		/// @brief	Default constructor hidden to protect against default construction.
		FileOutput();
	};

}

#endif
