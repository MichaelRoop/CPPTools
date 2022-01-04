#include "CppTestEngine.h"
#include "CppTestEngineImplementation.h"
#include "ICppTestFixtureTestCaseNames.h"

namespace CppTestHarness {

	// Declaration of static instance
	Engine* Engine::m_instance = 0;


	Engine& Engine::Instance() {
		if (m_instance == 0) {
			m_instance = new Engine();
		}
		return *m_instance;
	}


	Engine::Engine() {
		this->m_implementation = new EngineImplementation();
	}


	Engine::~Engine() {
		// singleton so do not bother to clear anything
	}


	void Engine::RegisterCase(IFixture* fixture) {
		this->m_implementation->RegisterCase(fixture);
	}


	void Engine::LoadTests(const CppUtils::Cpp_string& dllName) {
		this->m_implementation->LoadTests(dllName);
	}


	void Engine::UnloadTests() {
		this->m_implementation->UnloadTests();
	}


	void Engine::ProcessTestList(std::vector<CppUtils::CppSharedPtr<ITestFixtureInfoObject> >& list) {
		this->m_implementation->ProcessTestList(list);
	}


	CppUtils::Cpp_string Engine::GetRunId() {
		return this->m_implementation->GetRunId();
	}


	std::vector<CppUtils::CppSharedPtr<IFixutureTestCaseNames> > Engine::GetTestNames() {
		return this->m_implementation->GetTestNames();
	}


	void Engine::RegisterLoggedEvent(DataLoggedEvent loggedCallbackEvent) {
		this->m_implementation->RegisterLoggedEvent(loggedCallbackEvent);
	}


	void Engine::RegisterSummaryEvent(TestRunSummaryData summrayCallbackEvent) {
		this->m_implementation->RegisterSummaryEvent(summrayCallbackEvent);
	}


	void Engine::LoadLoggersByFileDefinition(const CppUtils::Cpp_string& fileName, const CppUtils::Cpp_string& fileType) {
		this->m_implementation->LoadLoggersByFileDefinition(fileName, fileType);
	}

}

