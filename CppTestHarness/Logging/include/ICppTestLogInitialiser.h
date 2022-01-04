#if !defined(ICPP_TEST_LOG_INITIALISER_H)
#define ICPP_TEST_LOG_INITIALISER_H

#include "CppTestHarnessDefines.h"
#include "CppTestFieldPair.h"
#include <vector>


namespace CppTestHarness {
	
	/// <summary>Interface for retrieving configuration information for the logger</summary>
	class ILogInitialiser {
	public:

		/// @brief	Load the data from source.
		virtual bool Load() = 0;


		/// @brief	Retrieve the SQL table or file etc. name, to contain log data.
		virtual Cpp_string GetLogName() = 0;


		/// @brief	Retrieve list of fields to log.
		virtual FieldVector GetFields() = 0;


		/// @brief	Retrieve the SQL CREATE statement template.
		virtual Cpp_string GetSqlCreateTemplate() = 0;


		/// @brief	Retrieve the SQL DROP statement template.
		virtual Cpp_string GetSqlDropTemplate() = 0;


		/// @brief	Retrieve the SQL INSERT statement template.
		virtual Cpp_string GetSqlInsertTemplate() = 0;


		/// @brief	Retrieve the ODBC DSN name.
		virtual Cpp_string GetOdbcDsnName() = 0;


		/// @brief	Retrieve the ODBC user name.
		virtual Cpp_string GetOdbcUserName() = 0;


		/// @brief	Retrieve the ODBC Authorisation String, usually password.
		virtual Cpp_string GetOdbcAUthorisationStr() = 0;


		/// @brief	Retrieve the ODBC .
		virtual int GetOdbcVersion() = 0;


		/// @brief	Retrieve the ODBC connection timeout.
		virtual int GetOdbcConnectTimeout() = 0;


		/// @brief	Retrieve the string delimiter character.
		///
		///	@param	Is it a fatal error if there is no value.
		virtual Cpp_string GetStringDelimiter(bool emptyErr) = 0;


		/// @brief	Retrieve the field delimiter character.
		virtual Cpp_string GetFieldDelimiter() = 0;


		/// @brief	Retrieve the overwrite file flag.
		virtual bool GetOverwriteLogFlag() = 0;


		/// @brief	Retrieve the auto generate unique table name flag.
		virtual bool GetUseAutoGenUniqueTableName() = 0;


		/// @brief	Retrieve the identifier for the summary log.
		virtual Cpp_string GetSummaryLogId() = 0;


		/// @brief	Get the output type to construct the output object
		virtual Cpp_string GetOutputType() = 0;


		/// @brief	Get the log type to construct the log object
		virtual Cpp_string GetLogType() = 0;


		/// @brief	Get list of logs
		virtual std::vector<Cpp_string> GetLogList() = 0;
	};


}

#endif
