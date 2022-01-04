
#include "CppTestSimpleLog.h"
#include "CppTestColumnBuilder.h"
#include "../CPPVariousUtils/Cpp_pointerException.h"

using CppUtils::Cpp_pointerException;

namespace CppTestHarness {

	SimpleLog::SimpleLog() : Log() {
	}


	SimpleLog::SimpleLog(
		CppSharedPtr<ILogOutput>& output,
		CppSharedPtr<ILog>& summaryLog,
		CppSharedPtr<ILogInitialiser>& initialiser) 
		: Log(output, summaryLog) {
		Cpp_exception::assertCondition(
			initialiser.IsValid(), _FL_, _L_("Invalid intialiser"));
		Cpp_exception::assertCondition(
			initialiser->Load(), _FL_, _L_("intialiser failed to load file"));

		this->m_formatData.m_strQuote = initialiser->GetStringDelimiter(false);
		this->m_formatData.m_delimiter = initialiser->GetFieldDelimiter();
		this->m_formatData.m_fields = initialiser->GetFields();
		this->m_overwrite = initialiser->GetOverwriteLogFlag();
	}


	SimpleLog::~SimpleLog() {
	}


	bool SimpleLog::WriteHeader() {
		Cpp_exception::assertCondition(this->m_output.IsValid(), _FL_, _L_("invalid output"));
		Cpp_exception::assertCondition(this->m_output->InitOutput(), _FL_, _L_("output failed init"));

		Cpp_stringstream os;
		os << ColumnBuilder::CreateColumnHeaders(this->m_formatData.m_fields, this->m_formatData.m_delimiter);
		os << std::endl;
		return this->m_output->Write(os.str());
	}


	bool SimpleLog::WriteEntry(ICase& testCase) {
		Cpp_exception::assertCondition(this->m_output.IsValid(), _FL_, _L_("invalid output"));

		Cpp_stringstream os;
		os << ColumnBuilder::CreateColumnData(
			this->m_formatData.m_fields,
			this->m_formatData.m_delimiter,
			this->m_formatData.m_strQuote,
			testCase);
		os << std::endl;
		return m_output->Write(os.str());
	}


	bool SimpleLog::WriteSummaryEntry(ILog* log) {
		

		Cpp_pointerException::ptrAssert(log, _FL_);
		Cpp_exception::assertCondition(this->m_output.IsValid(), _FL_, _L_("invalid output"));

		this->WriteHeader();

		Cpp_stringstream os;
		os << ColumnBuilder::CreateColumnData(
			this->m_formatData.m_fields,
			this->m_formatData.m_delimiter,
			this->m_formatData.m_strQuote,
			log
		);
		os << std::endl;

		bool ret = this->m_output->Write(os.str());
		this->m_output->CloseOutput();
		return ret;
	}


	bool SimpleLog::WriteFooter() {
		/// @todo	Remove writeFooter methods entirely ? and use the summary call.

		Cpp_exception::assertCondition(this->m_output.IsValid(), _FL_, _L_("invalid output"));

		Cpp_stringstream os;
		os << L("----------- End of Tests -------------") << std::endl
			<< L("\tSummary of test states:") << std::endl
			<< L("\t------------") << std::endl
			<< L("\t     Success:") << this->m_stSuccessCount << std::endl
			<< L("\t   Fail Init:") << this->m_stFailInitCount << std::endl
			<< L("\t  Fail Setup:") << this->m_stFailSetupCount << std::endl
			<< L("\t   Fail Test:") << this->m_stFailTestCount << std::endl
			<< L("\tFail Cleanup:") << this->m_stFailCleanupCount << std::endl
			<< L("\t   Not Found:") << this->m_stNotExistCount << std::endl
			<< L("\t--------------------") << std::endl
			<< L("\t       Total:") << +this->m_stSuccessCount + this->m_stFailInitCount + this->m_stFailSetupCount +
			this->m_stFailTestCount + this->m_stFailCleanupCount + this->m_stNotExistCount
			<< std::endl;
		return this->m_output->Write(os.str());
	}


}

