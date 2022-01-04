#include "CppTestLogInitialiserFactory.h"
#include "CppTestIniLogInitialiser.h"


namespace CppTestHarness {

	LogInitialiserSharedPtr LogInitialiserFactory::Create(
		const Cpp_string& configFileName,
		const Cpp_string& configFileType,
		const Cpp_string& section) {
		LogInitialiserSharedPtr	initialiser;

		if (configFileType.compare(_L_("INI")) == 0) {
			initialiser = new IniLogInitialiser(configFileName, section);
		}
		//else if (configFileType.compare( L("XML") ) == 0)
		//{
		//	Cpp_exception::assertCondition( false, FL, L("Not implemented") );
		//}
		else {
			Cpp_stringstream os;
			os << _L_("Illegal initialiser file type:") << configFileType << _L_(" Allowed types are 'INI'");
			Cpp_exception::assertCondition(false, FL, os.str());
		}

		if (!initialiser->Load()) {
			Cpp_stringstream os;
			os << configFileName.c_str() << _L_(" failed to load");
			Cpp_exception::assertCondition(false, FL, os.str());
		}
		return initialiser;
	}


	LogInitialiserSharedPtr LogInitialiserFactory::Create(
		const Cpp_string& configFileName,
		const Cpp_string& configFileType) {
		/// @todo review this - temp to get an init file to only access test list.
		return LogInitialiserFactory::Create(configFileName, configFileType, Cpp_string());
	}

}

