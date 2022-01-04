#include "CppTestVectorTestCaseNamesReader.h"
#include "ICppTestFixtureTestCaseNames.h"
#include "../CPPVariousUtils/Cpp_macroDefines.h"
#include "../CPPVariousUtils/Cpp_iostream.h"
#include <algorithm>


namespace CppTestHarness {

	VectorFixtureTestCaseNames::VectorFixtureTestCaseNames(
		const std::vector<CppSharedPtr<IFixutureTestCaseNames> >& infos) :
		ScriptReaderBase(L("VectorOfFixtureTestCaseNames"), _L_('$'), _L_('I')),
		m_infos(infos),
		m_fixtureIndex(0),
		m_testCaseIndex(0) {

		this->Open();
	}


	void VectorFixtureTestCaseNames::Open() {
		this->m_fixtureIndex = 0;
		this->m_testCaseIndex = 0;
	}


	TestInfoObject VectorFixtureTestCaseNames::GetNextTest(Cpp_string& fixtureName) {

		Cpp_cout << L("GetNextTest") << std::endl;

		TestInfoObject		testInfo;
		if (this->m_fixtureIndex < this->m_infos.size()) {
			Cpp_cout << L("Got fixture:") << this->m_infos[this->m_fixtureIndex]->FixtureName() << std::endl;

			if (this->m_infos[this->m_fixtureIndex]->TestCaseNames().size() == 0) {
				Cpp_cout << L("No test cases") << std::endl;

				// one iteration only for this info - fixture name only means execute all
				testInfo.SetNull(false);
				this->ProcessLine(fixtureName, testInfo, this->m_infos[this->m_fixtureIndex]->FixtureName());
				this->m_fixtureIndex++;
			}
			else {
				if (this->m_testCaseIndex < this->m_infos[this->m_fixtureIndex]->TestCaseNames().size()) {
					Cpp_cout << L("Test cases:") << this->m_infos[this->m_fixtureIndex]->TestCaseNames().size() << std::endl;

					// Use current case of current fixture - Test case name has fixture.testCase already complete
					testInfo.SetNull(false);
					this->ProcessLine(fixtureName, testInfo, this->m_infos[this->m_fixtureIndex]->TestCaseNames()[this->m_testCaseIndex]);
					this->m_testCaseIndex++;
				}
				else {
					this->m_testCaseIndex = 0;
					this->m_fixtureIndex++;
					// re-entrant
					testInfo = this->GetNextTest(fixtureName);
				}
			}

		}
		return testInfo;
	}



}
