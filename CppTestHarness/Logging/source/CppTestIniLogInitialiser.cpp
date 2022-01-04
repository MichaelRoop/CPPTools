#include "CppTestIniLogInitialiser.h"
#include <algorithm>

using CppIniFileNs::CppIniNode;
using CppIniFileNs::CppIniFile;

namespace CppTestHarness {

	/// @brief	Functor to populate field vector from ini.
	struct PopulateFieldListFromIni {
		PopulateFieldListFromIni(FieldVector& fields) : m_fields(fields) {
		}

		void operator () (const CppIniNode& theNode) {
			if (theNode.IsDataNode()) {
				this->m_fields.push_back(FieldPair(theNode.Name(), theNode.Value()));
			}
		}
	private:
		FieldVector& m_fields;	///< receiving vector of fields.
	};


	/// @brief	Functor to populate field vector from ini.
	struct PopulateLogList {
		PopulateLogList(std::vector<Cpp_string>& logs) : m_logs(logs) {
		}

		void operator () (const CppIniNode& theNode) {
			if (theNode.IsDataNode()) {
				this->m_logs.push_back(theNode.Value());
			}
		}
	private:
		std::vector<Cpp_string>& m_logs;	///< receiving vector of log names.

	};
	//----------------- End Functors -----------------------------------


	IniLogInitialiser::IniLogInitialiser(
		const Cpp_string& fileName,
		const Cpp_string& sectionName
	) : m_fileName(fileName),
		m_sectionName(sectionName),
		m_loaded(false) {
	}


	bool IniLogInitialiser::Load() {
		if (!this->m_loaded) {
			this->m_loaded = m_iniFile.Load(this->m_fileName);
		}
		return this->m_loaded;
	}


	Cpp_string IniLogInitialiser::GetLogName() {
		return this->GetNodeValue(this->m_sectionName, _L_("OutputName"));
	}


	Cpp_string IniLogInitialiser::GetSqlCreateTemplate() {
		return this->GetSyntaxEntry(_L_("CreateTableStmtTemplate"));
	}


	Cpp_string IniLogInitialiser::GetSqlDropTemplate() {
		return this->GetSyntaxEntry(_L_("DropTableStmtTemplate"));
	}


	Cpp_string IniLogInitialiser::GetSqlInsertTemplate() {
		return this->GetSyntaxEntry(_L_("InsertStmtTemplate"));
	}


	Cpp_string IniLogInitialiser::GetOdbcDsnName() {
		return this->GetSyntaxEntry(_L_("DsnName"));
	}


	Cpp_string IniLogInitialiser::GetOdbcUserName() {
		return this->GetSyntaxEntry(_L_("User"), false);
	}


	Cpp_string IniLogInitialiser::GetOdbcAUthorisationStr() {
		return this->GetSyntaxEntry(_L_("AuthorisationString"), false);
	}


	int IniLogInitialiser::GetOdbcVersion() {
		/// @todo Create robust conversion routine
		Cpp_string s = this->GetSyntaxEntry(_L_("ODBCVersion"));
		Cpp_stringstream os;
		os << s;
		int i;
		os >> i;
		return i;

	}


	int IniLogInitialiser::GetOdbcConnectTimeout() {
		/// @todo Create robust conversion routine
		Cpp_string s = this->GetSyntaxEntry(_L_("ConnectTimeoutSeconds"));
		Cpp_stringstream os;
		os << s;
		int i;
		os >> i;
		return i;
	}


	Cpp_string IniLogInitialiser::GetStringDelimiter(bool emptyErr) {
		return this->GetSyntaxEntry(_L_("StringDelimiter"), emptyErr);
	}


	Cpp_string IniLogInitialiser::GetFieldDelimiter() {
		return this->GetSyntaxEntry(_L_("FieldDelimiter"));
	}


	bool IniLogInitialiser::GetOverwriteLogFlag() {
		Cpp_string flag = this->GetNodeValue(this->m_sectionName, _L_("Overwrite"));

		/// @todo	Need to make this more robust.
		return flag.compare(_L_("true")) == 0;
	}


	bool IniLogInitialiser::GetUseAutoGenUniqueTableName() {
		Cpp_string flag = this->GetNodeValue(this->m_sectionName, _L_("AutoGenUniqueFileName"));

		/// @todo	Need to make this more robust.
		return flag.compare(_L_("true")) == 0;
	}


	Cpp_string IniLogInitialiser::GetSummaryLogId() {
		return this->GetNodeValue(this->m_sectionName, _L_("SummaryOutputName"), false);
	}


	Cpp_string IniLogInitialiser::GetOutputType() {
		return this->GetNodeValue(this->m_sectionName, _L_("OutputType"));
	}


	Cpp_string IniLogInitialiser::GetLogType() {
		return this->GetNodeValue(this->m_sectionName, _L_("LogType"));
	}


	std::vector<Cpp_string> IniLogInitialiser::GetLogList() {
		// Find the section.
		CppIniFile::SectionIterator it = this->GetSection(_L_("LogList"));

		std::vector<Cpp_string> logs;
		std::for_each(it->Nodes().begin(), it->Nodes().end(), PopulateLogList(logs));

		if (logs.empty()) {
			this->ThrowError(
				this->GetNodeValue(this->m_sectionName, _L_("LogList")),
				L(""),
				L("There are no valid entries for loggers to log the tests"));
		}
		return logs;
	}


	Cpp_string IniLogInitialiser::GetSyntaxEntry(
		const Cpp_string& nodeName,
		bool						fatalErr
	) {
		return this->GetNodeValue(
			this->GetNodeValue(this->m_sectionName, _L_("OutputSyntax"), fatalErr),
			nodeName,
			fatalErr
		);
	}


	Cpp_string IniLogInitialiser::GetNodeValue(
		const Cpp_string& sectionName,
		const Cpp_string& nodeName,
		bool						emptyErr,
		bool						foundErr
	) {
		if (!this->GetSection(sectionName)->NodeExists(nodeName) && foundErr) {
			this->ThrowError(sectionName, nodeName, _L_("not found"));
		}

		Cpp_string str = this->m_iniFile.GetValue(sectionName, nodeName);
		if (str.empty() && emptyErr) {
			this->ThrowError(sectionName, nodeName, _L_("has no value after '='"));
		}
		return str;
	}


	CppIniFile::SectionIterator IniLogInitialiser::GetSection(
		const Cpp_string& sectionName) {
		CppIniFile::SectionIterator it = this->m_iniFile.GetSection(sectionName);
		if (it == this->m_iniFile.Sections().end() || (!it->IsDataSection())) {
			this->ThrowError(sectionName, L(""), _L_("section not found"));
		}
		return it;
	}


	FieldVector IniLogInitialiser::GetFields() {
		CppIniFile::SectionIterator it =
			this->GetSection(this->GetNodeValue(this->m_sectionName, _L_("FieldList")));

		FieldVector fields;
		std::for_each(
			it->Nodes().begin(), it->Nodes().end(), PopulateFieldListFromIni(fields)
		);

		if (fields.empty()) {
			this->ThrowError(
				this->GetNodeValue(this->m_sectionName, _L_("FieldList")),
				_L_(""),
				_L_("There are no valid entries for fields that require logging"));
		}
		return fields;
	}


	void IniLogInitialiser::ThrowError(
		const Cpp_string& sectionName,
		const Cpp_string& nodeName,
		const Cpp_string& msg
	)
	{
		Cpp_stringstream os;
		os << _L_("[") << sectionName << _L_("] ") << nodeName << _L_(" ") << msg;
		Cpp_exception::assertCondition(false, _FL_, os.str());
	}



}

