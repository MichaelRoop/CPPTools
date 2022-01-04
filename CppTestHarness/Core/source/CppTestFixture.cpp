#include "CppTestFixture.h"
#include "CppTestCaseHolder.h"
#include "CppTestFixtureTestCaseNames.h"
#include "CppTestSegfaultHandler.h"
#include "CppTestAssertException.h"
#include "../CPPVariousUtils/CppStaticTimer.h"
#include "../CPPVariousUtils/Cpp_iostream.h"
#include "../CPPVariousUtils/Cpp_functors.h"

#include <algorithm>


namespace CppTestHarness {


	//---------------------------------------------------------------------------------------
	/// @brief Functor to determine if the name is a match for the test case name.
	struct HasNamedTestFunctor {
	public:
		HasNamedTestFunctor(const CppUtils::Cpp_string& name) : m_name(name) {
		}

		bool operator () (const ITestCaseHolder* testHolder) {
			return testHolder->Data()->Name == this->m_name;
		}
	private:
		const CppUtils::Cpp_string& m_name;
	};


	Fixture::Fixture(const CppUtils::Cpp_string& name)
		: m_name(name),
		m_currentTestCase(0),
		m_fixtureSetup(0),
		m_fixtureTeardown(0),
		m_testSetup(0),
		m_testTeardown(0),
		m_isFixtureCalled(false),
		m_testCaseNames(new FixutureTestCaseNames(name)) {
	}


	Fixture::~Fixture() {
		CppUtils::DeletePtr<ITestCaseHolder> deleter;
		std::for_each(this->m_tests.begin(), this->m_tests.end(), deleter);
	}


	const TestCaseArguments& Fixture::CurrentArgs() const {
		return this->m_args;
	}


	void Fixture::RegisterFixtureSetup(IFixture::Ifixture_method_ptr setup) {
		assert(setup);
		this->m_fixtureSetup = setup;
	}


	void Fixture::RegisterFixtureTeardown(IFixture::Ifixture_method_ptr teardown) {
		assert(teardown);
		this->m_fixtureTeardown = teardown;
	}


	void Fixture::RegisterTestSetup(IFixture::Ifixture_method_ptr setup) {
		assert(setup);
		this->m_testSetup = setup;
	}


	void Fixture::RegisterTestTeardown(IFixture::Ifixture_method_ptr teardown) {
		assert(teardown);
		this->m_testTeardown = teardown;
	}


	void Fixture::RegisterTest(
		IFixture::Ifixture_method_ptr test,
		const CppUtils::Cpp_string& name,
		const CppUtils::Cpp_string& description) {

		assert(test);
		// TODO - test if already there?
		// TODO - look at a scheme where you would have TestFixtureName.TestCaseName

		// When using the macro it uses the # and will insert the full &ClassName::MethodName
		CppUtils::Cpp_string scratch(name);
		size_t pos = scratch.find(_L_("::"));

		// TODO - fix when linker problem solved in VS2010
		// Need to use exported method to access string global npos within the DLL
		if (pos != CppUtils::StrNPos()) {
			scratch = CppUtils::SubString(name, pos + 2);
		}

		this->m_tests.push_back(new TestCaseHolder(test, this->Name(), scratch, description));
		this->m_testCaseNames->AddTestCaseName(scratch);
	}


	bool Fixture::HasTest(const CppUtils::Cpp_string& name) const {
		// TODO - look at a scheme where you would have TestFixtureName.TestCaseName
		return std::find_if(
			this->m_tests.begin(),
			this->m_tests.end(),
			HasNamedTestFunctor(name)) != this->m_tests.end();
	}


	CppUtils::CppSharedPtr<IFixutureTestCaseNames> Fixture::GetTestNames() const {
		return this->m_testCaseNames;
	}


	ICase& Fixture::CurrentTestCase() const {
		assert(this->m_currentTestCase);
		return *(this->m_currentTestCase->Data());
	}


	const CppUtils::Cpp_string& Fixture::Name() const {
		return this->m_name;
	}


	void Fixture::SetCurrentTest(const CppUtils::Cpp_string& name) {
		// cannot use iterator because of __try and objects with destructors 
		// cannot be created there.
		unsigned size = this->m_tests.size();
		bool found = false;
		for (unsigned i = 0; i < size; i++) {
			if (this->m_tests[i]->Data()->Name == name) {
				this->m_currentTestCase = this->m_tests[i];
				found = true;
				break;
			}
		}
		assert(found);
	}


	void Fixture::RunTest(const CppUtils::Cpp_string& name, const TestCaseArguments& args) {
		// Clear out any information from a previous test case
		this->ResetTest();

		// Get a copy of the optional arguments for the current named test case
		this->m_args = args;

		START_SEGFAULT_CATCH_BLOCK
			this->SetCurrentTest(name);
		this->ExecTestFixtureSetup();
		this->ExecStep(this->m_currentTestCase->Data()->SetupTimeMs, this->m_testSetup, ICase::TestCaseStatus::ST_FAIL_SETUP);
		this->ExecStep(this->m_currentTestCase->Data()->ExecTimeMs, this->m_currentTestCase->Pointer(), ICase::TestCaseStatus::ST_FAIL_TEST);
		this->ExecStep(this->m_currentTestCase->Data()->CleanupTimeMs, this->m_testTeardown, ICase::TestCaseStatus::ST_FAIL_CLEANUP);
		// Test fixture teardown is called on fixture from outside when no more tests to execute in fixture
		END_SEGFAULT_CATCH_BLOCK
	}


	void Fixture::ExecStep(long long& timeVal, IFixture::Ifixture_method_ptr funcPtr, ICase::TestCaseStatus failStatus) {

		try {
			// In this case there may not even be a step registered
			timeVal = 0;
			if (funcPtr != 0) {
				CppUtils::CppStaticTimer timer;
				timer.Start();
				// set to failed in case it throws
				this->m_currentTestCase->Data()->Status = failStatus;
				(this->*funcPtr)();
				this->m_currentTestCase->Data()->Status = ICase::TestCaseStatus::ST_SUCCESS;

				timer.Stop();
				timeVal = timer.GetMsInterval();
			}
		}
		catch (const AssertException&) {
			// This has been generated by one of the assert methods. Message already registered
			throw;
		}
		catch (const CppUtils::Cpp_exception& e) {
			// Exception available in the Utils dll of the Mr Test Harness. This has been used in
			// application or test by user. It contains all the information we need.
			if (this->m_currentTestCase != 0) {
				CppUtils::ResetStringStream(this->m_currentTestCase->Data()->MsgBuffer);
				this->m_currentTestCase->Data()->MsgBuffer << L("Application Exception Caught:") << e.longMsg();
			}
			throw;
		}
		catch (const std::exception& e) {
			// Register the message from application exception
			if (this->m_currentTestCase != 0) {
				CppUtils::ResetStringStream(this->m_currentTestCase->Data()->MsgBuffer);

				// TODO - cross platform stack trace walker - this is a big deal on Win. Seems
				// relatively straight forward on gcc
				// http://stackoverflow.com/questions/590160/how-to-log-stack-frames-with-windows-x64
				//http://www.codeproject.com/Articles/11132/Walking-the-callstack

				// For now we will at least preserver the exception message
				this->m_currentTestCase->Data()->MsgBuffer << L("Application Exception Caught:");
				if (e.what() != 0) {
					this->m_currentTestCase->Data()->MsgBuffer << e.what();
				}
			}
			throw;
		}
		catch (...) {
			mr_cout << L("Caught ...") << std::endl;
			//throw;
		}
	}


	void Fixture::ExecTestFixtureSetup() {
		// Fire the fixture setup if not previously fired by another test
		if (!this->m_isFixtureCalled) {
			// The fixture setup is not presently timed
			long long bogusTimeVal = 0;
			this->ExecStep(bogusTimeVal, this->m_fixtureSetup, ICase::TestCaseStatus::ST_FAIL_FIXTURE_SETUP);
			this->m_isFixtureCalled = true;
		}
	}


	void Fixture::ResetTest() {
		if (this->m_currentTestCase != 0) {
			this->m_currentTestCase->Reset();
		}
	}


	void Fixture::ResetFixture() {
		this->ResetTest();
		if (this->m_isFixtureCalled) {

			// Do not report errors on test fixture teardown
			START_SEGFAULT_CATCH_BLOCK
				this->m_isFixtureCalled = false;
			if (this->m_fixtureTeardown != 0) {
				(this->*m_fixtureTeardown)();
			}
			END_SEGFAULT_CATCH_BLOCK
		}
	}


} 
