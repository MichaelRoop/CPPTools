///--------------------------------------------------------------------------------------
/// @brief	Abstracts the retrieval of the intialisation data for the log object from ini
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_INI_LOG_INITIALISER_H)
#define CPP_TEST_INI_LOG_INITIALISER_H


#include "ICppTestLogInitialiser.h"
#include "../CppIniFile/CppIniFile.h"


namespace CppTestHarness {

	//----------------------------------------------------------------------------------------
	/// @brief	Interface for retrieving configuration information for the logger from ini file.
	///
	//----------------------------------------------------------------------------------------
	class IniLogInitialiser : public ILogInitialiser {
	public:


		/// @brief	Constructor.
		///
		/// @param	fileName	Name of the ini file.
		/// @param	sectionName	The section that has the specific information for the output.
		IniLogInitialiser(const Cpp_string& fileName, const Cpp_string& sectionName);


		/// @brief	Load the data from source.
		virtual bool Load();


		/// @brief	Retrieve the SQL table or file etc. name, to contain log data.
		virtual Cpp_string GetLogName();


		/// @brief	Retrieve list of fields to log.
		virtual FieldVector GetFields();


		/// @brief	Retrieve the SQL CREATE statement template.
		virtual Cpp_string GetSqlCreateTemplate();


		/// @brief	Retrieve the SQL DROP statement template.
		virtual Cpp_string GetSqlDropTemplate();


		/// @brief	Retrieve the SQL INSERT statement template.
		virtual Cpp_string GetSqlInsertTemplate();


		/// @brief	Retrieve the string delimiter character.
		///
		/// @param	emptyErr	Is it a fatal error if node empty.
		virtual Cpp_string GetStringDelimiter(bool emptyErr);


		/// @brief	Retrieve the ODBC DSN name.
		virtual Cpp_string GetOdbcDsnName();


		/// @brief	Retrieve the ODBC user name.
		virtual Cpp_string GetOdbcUserName();


		/// @brief	Retrieve the ODBC Authorisation String, usually password.
		virtual Cpp_string GetOdbcAUthorisationStr();


		/// @brief	Retrieve the ODBC version number.
		virtual int GetOdbcVersion();


		/// @brief	Retrieve the ODBC connection timeout.
		virtual int GetOdbcConnectTimeout();


		/// @brief	Retrieve the field delimiter character.
		virtual Cpp_string GetFieldDelimiter();


		/// @brief	Retrieve the overwrite file flag.
		virtual bool GetOverwriteLogFlag();


		/// @brief	Retrieve the auto generate unique table name flag.
		virtual bool GetUseAutoGenUniqueTableName();


		/// @brief	Retrieve the identifier for the summary log.
		virtual Cpp_string GetSummaryLogId();


		/// @brief	Get the output type to construct the output object
		virtual Cpp_string GetOutputType();


		/// @brief	Get the log type to construct the log object
		virtual Cpp_string GetLogType();

		/// @brief	Get list of logs
		virtual std::vector<Cpp_string> GetLogList();

	private:
		Cpp_string m_fileName;
		Cpp_string m_sectionName;
		CppIniFileNs::CppIniFile m_iniFile;
		bool m_loaded;


		/// @brief	Helper method to parse out syntax definitions and report errors.
		///
		/// @param	nodeName	The name of the node in the section defined by the 
		///						OutputSyntax ini entry for the output.
		/// @param	fatalErr	Is it fatal if node is not found or empty.
		///
		/// @return	The node value.
		Cpp_string GetSyntaxEntry(const Cpp_string& nodeName, bool fatalErr = true);


		/// @brief	Helper method to retrieve a value from the section according to node name.
		///
		/// @param	sectionName	The name of the ini section.
		/// @param	nodeName	The name of the node within the section.
		/// @param	emptyErr	Is it a fatal error if node empty. Default is true.
		/// @param	foundErr	Is it a fatal error if node is not found. Default is true.
		///
		/// @return	The node value if successful or an empty string if no value or not found.
		Cpp_string GetNodeValue(
			const Cpp_string& sectionName,
			const Cpp_string& nodeName,
			bool						emptyErr = true,
			bool						foundErr = true
		);


		/// @brief	Helper method to retrieve section by name.
		///
		/// @param	sectionName	The name of the ini section.
		///
		/// @return	A section Iterator.
		CppIniFileNs::CppIniFile::SectionIterator GetSection(const Cpp_string& sectionName);


		/// @brief	Helper method to format msg for exception and do throw.
		///
		/// @param	sectionName	The name of the ini section requested.
		/// @param	nodeName	The name of the node requested.
		/// @param	msg			Error message.
		void ThrowError(
			const Cpp_string& sectionName,
			const Cpp_string& nodeName,
			const Cpp_string& msg
		);
	};

}

#endif
