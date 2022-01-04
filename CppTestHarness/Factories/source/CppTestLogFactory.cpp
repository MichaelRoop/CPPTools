#include "CppTestLogFactory.h"

#include "CppTestLogInitialiserFactory.h"
#include "CppTestLogOutputFactory.h"
#include "CppTestSqlLog.h"
#include "CppTestSimpleLog.h"


namespace CppTestHarness {

    LogSharedPtr LogFactory::Create(
        const Cpp_string& configFileName,
        const Cpp_string& configFileType,
        const Cpp_string& section) {
        LogInitialiserSharedPtr mainInit =
            LogInitialiserFactory::Create(configFileName, configFileType, section);
        mainInit->Load();

        LogInitialiserSharedPtr summaryInit =
            LogInitialiserFactory::Create(configFileName, configFileType, mainInit->GetSummaryLogId());
        summaryInit->Load();

        LogSharedPtr dummyLogSharedPtr;
        LogOutputSharedPtr mainInitOutputSharedPtr = LogOutputFactory::Create(mainInit);
        LogOutputSharedPtr summaryInitSharedPtr = LogOutputFactory::Create(summaryInit);
        LogSharedPtr summaryLogSharedPtr = LogFactory::Create(summaryInitSharedPtr, dummyLogSharedPtr, summaryInit);

        return LogFactory::Create(mainInitOutputSharedPtr, summaryLogSharedPtr, mainInit);
    }


    LogSharedPtr LogFactory::Create(
        CppSharedPtr<ILogOutput>& output,
        CppSharedPtr<ILog>& summaryLog,
        CppSharedPtr<ILogInitialiser>& initialiser) {
        LogSharedPtr log;

        if (initialiser->GetLogType().compare(_L_("SQL")) == 0) {
            log = new SqlLog(output, summaryLog, initialiser);
        }
        else if (initialiser->GetLogType().compare(_L_("CSV")) == 0) {
            log = new SimpleLog(output, summaryLog, initialiser);
        }
        else {
            Cpp_stringstream os;
            os << _L_("Illegal initialiser log type:") << initialiser->GetLogType() << _L_(" Allowed types are 'SQL', 'CSV'");
            Cpp_exception::assertCondition(false, _FL_, os.str());
        }
        return log;
    }


}
