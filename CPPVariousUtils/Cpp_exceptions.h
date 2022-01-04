#pragma once

#include "Cpp_string.h"
#include <exception>

namespace CppUtils {



	/// <summary>
	/// 
	///	Pure virtual base class for exceptions
	///
	/// Provides source code name and line and a user defined message.
	///
	/// Use the FL macro to insert the file name and line from the system.
	/// Use the L() macro to provide cross char width portability.
	/// Use the cross char width streaming so that the message can be displayed on both
	/// both narrow and wide char compilation mode.
	///
	/// Example: throw mr_utils::mr_exception( FL, L("The value is outside range") );
	///
	/// On the catch you can either access the different parts of the message or use the formatted
	/// message.
	///
	///		catch( const mr_utils::mr_exception& e ) {										
	///			mr_cout << e.longMsg() << std::endl;
	///		}										
	/// 
	/// </summary>
	class CPPUTILS_API Cpp_exception : public std::exception {
	public:
		
		Cpp_exception();


		/// <summary>Constructor</summary>
		/// <param name="file">The source code file where problem originates</param>
		/// <param name="line">The source code line where problem originates</param>
		/// <param name="msg">The message explaining the exception</param>
		Cpp_exception(const char* file, int line, const Cpp_string& msg);


		/// @brief	Copy Constructor.
		///
		/// @param	file	The source code file where problem originates.
		/// @param	line	The source code line where problem originates.
		/// @param	msg		The message explaining the exception.
		Cpp_exception(const Cpp_exception& obj);


		/// @brief	Destructor.
		~Cpp_exception();


		/// @brief	Returns the exception message.
		///
		/// @return	User defined exception message.
		const Cpp_string& msg() const;


		/// @brief	Returns the source code file name where the problem originates.
		///
		/// @return	Source file name where problem originates.
		const Cpp_string fileName() const;


		/// @brief	Returns the source code file line where the problem originates.
		///
		/// @return	Source file line where problem originates.
		int fileLine() const;


		/// @brief	Returns a formated verbose exception message.
		///
		/// The format is as following.  \n
		///    	"Exception:SourceFileName:SourceFileLine Exception message"
		///
		/// @return	Verbose exception message.
		virtual const CppUtils::Cpp_string longMsg() const;



		/// @brief	Wrapper to clean up checking for exception throw on condition.
		///
		///	@throw	Throws a mr_exception on failure
		///
		/// @param	condition		The condition to test. If false, the exception is thrown.
		/// @param	file			The source code file where problem originates.
		/// @param	line			The source code line where problem originates.
		/// @param	msg				The message explaining the exception.
		static void assertCondition(
			bool				condition,
			const char* file,
			int					line,
			const Cpp_string& msg);




	protected:

		std::string	m_fileName;	///< Source code file name.
		int			m_line;		///< Source code file line.
		Cpp_string	m_msg;		///< User defined exception message.

	};


}



