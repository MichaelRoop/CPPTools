#include "CppTestLogOutputFactory.h"
//#include "MrTestIniLogInitialiser.h"
#include "CppTestOdbcOutput.h"
#include "CppTestFileOutput.h"
#include "CppTestConsoleOutput.h"
//#include "mr_exception.h"
//#include "mr_sstream.h"
//#include "mr_defines.h"


namespace CppTestHarness {

	LogOutputSharedPtr LogOutputFactory::Create(CppSharedPtr<ILogInitialiser>& initialiser) {
		LogOutputSharedPtr output;

		if (initialiser->GetOutputType().compare(_L_("ODBC")) == 0) {
			output = new OdbcOutput(initialiser);
		}
		else if (initialiser->GetOutputType().compare(_L_("FILE")) == 0) {
			Cpp_exception::assertCondition(false, _FL_, _L_("FILE output not ready"));
			output = new FileOutput("Simple log file.txt");
		}
		else if (initialiser->GetOutputType().compare(_L_("CONSOLE")) == 0) {
			output = new ConsoleOutput();
		}
		else {
			Cpp_stringstream os;
			os << _L_("Illegal output type:") << initialiser->GetOutputType() << _L_(" Allowed types are 'ODBC', 'FILE', 'CONSOLE'");
			Cpp_exception::assertCondition(false, FL, os.str());
		}

		return output;
	}

}

