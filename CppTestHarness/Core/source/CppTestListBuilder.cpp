#include "CppTestListBuilder.h"
#include "CppTestFixtureInfoObject.h"

namespace CppTestHarness {


	std::vector< CppUtils::CppSharedPtr<ITestFixtureInfoObject> >
		ListBuilder::Build(IScriptReader& theReader) const {

		std::vector<CppUtils::CppSharedPtr<ITestFixtureInfoObject> > list;

		CppUtils::Cpp_string currentFixtureName = _L_("");
		CppUtils::Cpp_string newFixtureName = _L_("");
		TestInfoObject info = theReader.GetNextTest(newFixtureName);

		CppUtils::CppSharedPtr<ITestFixtureInfoObject> fixtureInfo;

		// Create the initial fixture info object if there is any date to accumulate
		if (!info.IsNull()) {
			currentFixtureName = newFixtureName;
			fixtureInfo = new TestFixtureInfoObject(currentFixtureName);
		}

		// Evaluate the last test which was read in from the script reader 
		while (!info.IsNull()) {
			if (currentFixtureName != newFixtureName) {
				// The fixture name has changed. Push current Fixture info to vector and start another
				list.push_back(fixtureInfo);
				currentFixtureName = newFixtureName;
				fixtureInfo = new TestFixtureInfoObject(currentFixtureName);
			}

			// Add the test info read to the current Fixture info
			fixtureInfo->AddTestInfo(info);

			// get the next test info. If null push existing fixtureInfo so it is not lost
			info = theReader.GetNextTest(newFixtureName);
			if (info.IsNull() && fixtureInfo.IsValid()) {
				list.push_back(fixtureInfo);
			}
		}

		return list;
	}

}

