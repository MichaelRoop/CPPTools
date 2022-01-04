#include "CppTestLogEngine.h"
#include "CppTestLogInitialiserFactory.h"
#include "CppTestLogFactory.h"
#include <algorithm>


namespace CppTestHarness {


	//--------------------------------------------------------------------------------------
	/// @brief	Functor to write a log header per iteration on a container of log objects.
	struct WriteLogHeaders {
		/// @brief	Function operator called on each iteration.
		/// @param	theLog	The log object to call.
		void operator () (CppSharedPtr<ILog>& log) {
			Cpp_exception::assertCondition(log.IsValid(), _FL_, _L_("Invalid pointer"));
			log->WriteHeader();
		}
	};


	//--------------------------------------------------------------------------------------
	/// @brief	Functor to write a log footer per iteration on a container of log objects.
	struct WriteLogSummaries {
		/// @brief	Function operator called on each iteration.
		/// @param	theLog	The log object to call.
		void operator () (CppSharedPtr<ILog>& log) {
			Cpp_exception::assertCondition(log.IsValid(), _FL_, _L_("Invalid pointer"));
			log->Summarize();
		}
	};


	//--------------------------------------------------------------------------------------
	/// @brief	Functor to write a log entry per iteration on a container of log objects.
	struct WriteLogEntries {

		/// @brief	Constructor.
		///
		/// @param	ptr	The testCase object that contains the information to log.
		WriteLogEntries(ICase& testCase) : m_case(testCase) {
		}


		/// @brief	Function operator called on each iteration.
		///
		/// @param	theLog	The log object to call.
		void operator () (CppSharedPtr<ILog>& log) {
			Cpp_exception::assertCondition(log.IsValid(), _FL_, _L_("Invalid pointer"));
			log->LogTest(this->m_case);
		}
	private:
		ICase& m_case; ///< The testCase information containing log information.
	};


	//--------------------------------------------------------------------------------------
	/// @brief	Functor to load named test to testLogEngine.
	struct LoadLogsFromVector {
		LoadLogsFromVector(
			LogEngine* logEngine,
			const Cpp_string& fileName,
			const Cpp_string& fileType
		)
			: m_logEngine(logEngine),
			m_fileName(fileName),
			m_fileType(fileType) {
		}

		void operator () (const Cpp_string& str) {
			this->m_logEngine->AddLogger(LogFactory::Create(this->m_fileName, this->m_fileType, str));
		}

		LogEngine* m_logEngine;
		const Cpp_string& m_fileName;
		const Cpp_string& m_fileType;
	};

	//--------------------------------------------------------------------------------------
	// End functors.
	//--------------------------------------------------------------------------------------


	LogEngine::LogEngine() {
	}


	LogEngine::~LogEngine() {
	}


	bool LogEngine::WriteHeaders() {
		std::for_each(this->m_logs.begin(), this->m_logs.end(), WriteLogHeaders());
		return true;
	}


	bool LogEngine::Log(ICase& testCase) {
		std::for_each(this->m_logs.begin(), this->m_logs.end(), WriteLogEntries(testCase));
		return true;
	}


	bool LogEngine::WriteSummaries() {
		std::for_each(this->m_logs.begin(), this->m_logs.end(), WriteLogSummaries());
		return true;
	}


	void LogEngine::AddLogger(const CppSharedPtr<ILog>& log) {
		Cpp_exception::assertCondition(log.IsValid(), _FL_, _L_("Invalid testLog"));
		this->m_logs.push_back(log);
	}


	void LogEngine::LoadLoggers(const Cpp_string& fileName, const Cpp_string& fileType) {
		Cpp_exception::assertCondition(!fileName.empty(), _FL_, _L_("Empty file name"));
		std::vector<Cpp_string> logs =
			LogInitialiserFactory::Create(fileName, fileType)->GetLogList();

		std::for_each(logs.begin(), logs.end(), LoadLogsFromVector(this, fileName, fileType));
	}


}
