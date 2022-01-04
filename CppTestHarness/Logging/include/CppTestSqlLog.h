#if !defined(CPP_TEST_SQL_LOG_H)
#define CPP_TEST_SQL_LOG_H


#include "CppTestLog.h"
#include "CppTestSqlBuilder.h"
#include "ICppTestLogInitialiser.h"

namespace CppTestHarness {

	class ICase;


	//----------------------------------------------------------------------------------------
	/// @brief	Log class for formatting SQL statements from data.
	/// 
	/// Header will create the file with table name, column names and types
	/// 
	/// 
	/// The footer gives a summary of the total of successful and failed tests as well as a 
	/// breakdown of the total failures per state.
	/// 
	class SqlLog : public Log {
	public:

		/// @brief	Constructor.
		SqlLog();


		/// @brief	Constructor.
		/// @param	output			A pointer to a logOutput object. It now assumes its ownership. 
		/// @param	summaryOutput	A SharedObject reference to a log object for summary output.
		/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
		SqlLog(
			CppSharedPtr<ILogOutput>& output,
			CppSharedPtr<ILog>& summaryLog,
			CppSharedPtr<ILogInitialiser>& initialiser);


		/// @brief	Constructor.
		/// @param	output			A pointer to a logOutput object. It now assumes its ownership. 
		/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
		SqlLog(
			CppSharedPtr<ILogOutput>& output,
			CppSharedPtr<ILogInitialiser>& initialiser);


		/// @brief	Destructor.
		virtual ~SqlLog();


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

		SQLData	m_sqlData;		///< SQL data loaded from config.


		/// @brief	Initialisation method.
		/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
		void Init(CppSharedPtr<ILogInitialiser>& initialiser);


		/// @brief	Returns the SQL DROP TABLE statement.
		/// @return	The drop statement.
		const Cpp_string& GetDropStmt() const;


		/// @brief	Returns the SQL CREATE TABLE statement.
		/// @return	The create statement.
		const Cpp_string& GetCreateStmt() const;


		/// @brief	Returns the SQL INSERT statement.
		/// @return	The insert statement.
		Cpp_string GetInsertStmt(ICase& testCase) const;


		/// @brief	Returns the SQL INSERT statement.
		/// @return	The insert statement.
		Cpp_string GetInsertStmt(ILog* log) const;

	};

}

#endif