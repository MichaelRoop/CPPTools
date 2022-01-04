#if !defined(CPP_TEST_SIMPLE_LOG_H)
#define CPP_TEST_SIMPLE_LOG_H


#include "CppTestLog.h"
#include "CppTestFieldPair.h"
#include "ICppTestLogInitialiser.h"

namespace CppTestHarness {

	class ICase;

	/// @brief	Structure to hold the loaded field.
	/// @todo	Need to move this.
	struct StreamFormatData {
		Cpp_string m_strQuote;	///< Char that delineates a string.
		Cpp_string m_delimiter;	///< Char that delineates a field.
		FieldVector	m_fields;	///< List of the field names and types.
	};



	//----------------------------------------------------------------------------------------
	/// @brief	Simple logging class.
	/// 
	/// The simpleLogger writes one line per test to its logOutput object.  Each line an entry
	/// for 3 columns, ID, Status, and Description.
	/// 
	/// The footer gives a summary of the total of successful and failed tests as well as a 
	/// breakdown of the total failures per state.
	/// 
	class SimpleLog : public Log {
	public:

		/// @brief	Constructor.
		SimpleLog();


		/// @brief	Constructor.
		/// @param	output			A pointer to a logOutput object. It now assumes its ownership. 
		/// @param	summaryOutput	A SharedObject reference to a log object for summary output.
		/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
		SimpleLog(
			CppSharedPtr<ILogOutput>& output,
			CppSharedPtr<ILog>& summaryLog,
			CppSharedPtr<ILogInitialiser>& initialiser
		);


		/// @brief	Destructor.
		virtual ~SimpleLog();


		/// @brief	Write the header for the log output.
		/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
		/// @return	true if successful, otherwise false.
		bool WriteHeader();


		/// @brief	Write the footer for the log output.
		/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
		/// @return	true if successful, otherwise false.
		bool WriteFooter();


		/// @brief	Write the line entry for the log output.
		/// @exception	throws a mr_utils::mr_pointerException if the testCase object is invalid.
		/// @exception	throws a mr_utils::mr_exception if the output object is invalid.
		/// @param	fixture	Pointer to the test case fixture object that contains information to log.
		/// @return	true if successful, otherwise false.
		bool WriteEntry(ICase& testCase);


		/// @brief	Write the summary of the logging.
		/// @param	log	The log that contains the summary information.
		/// @return	true if successful, otherwise false.
		virtual bool WriteSummaryEntry(ILog* log);

	private:

		StreamFormatData	m_formatData;
	};


}

#endif
