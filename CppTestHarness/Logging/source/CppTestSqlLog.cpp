#include "CppTestSqlLog.h"
#include "CppTestEngine.h"
//#include "MrTestCase.h"
#include "../CPPVariousUtils/Cpp_pointerException.h"

using CppUtils::Cpp_pointerException;

namespace CppTestHarness {

	SqlLog::SqlLog() : Log() {
	}


	SqlLog::SqlLog(
		CppSharedPtr<ILogOutput>& output,
		CppSharedPtr<ILog>& summaryLog,
		CppSharedPtr<ILogInitialiser>& initialiser
	) : Log(output, summaryLog) {
		this->Init(initialiser);
	}

	// for nix
	//CppSharedPtr<MrTest::ILog> __createDummyLogForConstructor() {
	//    return CppSharedPtr<MrTest::ILog>();
	//}

	CppSharedPtr<ILog> __dummyLogForConstructor;


	SqlLog::SqlLog(
		CppSharedPtr<ILogOutput>& output,
		CppSharedPtr<ILogInitialiser>& initialiser)
		: Log(output, __dummyLogForConstructor) {
		this->Init(initialiser);
	}


	SqlLog::~SqlLog() {
	}

	/// @todo	Get the overwrite bool from ini

	bool SqlLog::WriteHeader() {
		Cpp_exception::assertCondition(this->m_output.IsValid(), FL, L("invalid output"));
		Cpp_exception::assertCondition(this->m_output->InitOutput(), FL, L("output failed init"));

		if (this->OverwriteExistingLog()) {
			this->m_output->Write(this->GetDropStmt());
		}
		return this->m_output->Write(this->GetCreateStmt());
	}


	bool SqlLog::WriteEntry(ICase& testCase) {
		Cpp_exception::assertCondition(this->m_output.IsValid(), FL, L("invalid output"));
		return this->m_output->Write(this->GetInsertStmt(testCase));
	}


	bool SqlLog::WriteSummaryEntry(ILog* log) {
		Cpp_pointerException::ptrAssert(log, FL);
		Cpp_exception::assertCondition(this->m_output.IsValid(), FL, L("invalid output"));

		// Do not check return as some loggers fail if table already exists.
		this->WriteHeader();
		bool ret = this->m_output->Write(this->GetInsertStmt(log));
		this->m_output->CloseOutput();
		return ret;
	}


	bool SqlLog::WriteFooter() {
		Cpp_exception::assertCondition(this->m_output.IsValid(), FL, L("invalid output"));

		/// @todo	Figure out how to save run totals info to DB.  Is it even required since they can
		///			get it by querry or dashboard on the table itself?
		return true;
	}


	void SqlLog::Init(CppSharedPtr<ILogInitialiser>& initialiser) {
		Cpp_exception::assertCondition(
			initialiser.IsValid(), _FL_, _L_("Invalid intialiser"));
		Cpp_exception::assertCondition(
			initialiser->Load(), _FL_, _L_("intialiser failed to load file"));

		this->m_sqlData.m_tableName = initialiser->GetLogName();
		if (initialiser->GetUseAutoGenUniqueTableName()) {
			this->m_sqlData.m_tableName = this->m_sqlData.m_tableName + Engine::Instance().GetRunId();
		}

		this->m_sqlData.m_strQuote = initialiser->GetStringDelimiter(true);
		this->m_sqlData.m_fields = initialiser->GetFields();

		SqlBuilder::BuildCreateStmt(this->m_sqlData, initialiser->GetSqlCreateTemplate());
		SqlBuilder::BuildDropStmt(this->m_sqlData, initialiser->GetSqlDropTemplate());
		SqlBuilder::BuildInsertStmt(this->m_sqlData, initialiser->GetSqlInsertTemplate());

		this->m_overwrite = initialiser->GetOverwriteLogFlag();
	}


	const Cpp_string& SqlLog::GetDropStmt() const {
		return this->m_sqlData.m_dropStmt;
	}


	const Cpp_string& SqlLog::GetCreateStmt() const {
		return this->m_sqlData.m_createStmt;
	}


	Cpp_string SqlLog::GetInsertStmt(ICase& testCase) const {
		return SqlBuilder::BuildInsertStmtWithValues(this->m_sqlData, testCase);
	}


	Cpp_string SqlLog::GetInsertStmt(ILog* log) const {
		return SqlBuilder::BuildInsertStmtWithValues(this->m_sqlData, log);
	}

}

