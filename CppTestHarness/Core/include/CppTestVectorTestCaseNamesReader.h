#if !defined(CPP_TEST_VECTOR_FIXTURE_TEST_CASE_NAMES_READER_H)
#define CPP_TEST_VECTOR_FIXTURE_TEST_CASE_NAMES_READER_H

#include "CppTestScriptReaderBase.h"
#include "ICppTestFixtureTestCaseNames.h"
#include "..\CPPVariousUtils\CppSharedPtr.h"
#include <vector>

namespace CppTestHarness {

	class IFixutureTestCaseNames;

	/// <summary>Class to abstract the reading of a vector IFixtureTestCaseNames</summary>
	class TSTHARNESS_API VectorFixtureTestCaseNames : public ScriptReaderBase {
	public:

		/// @brief	Constructor.
		/// @param	nameDelimiter	Delimiter character to tokenize the name and 
		///							argument portion of the line.
		/// @param	argDelimiter	Delimiter to tokenize the argument portion of the
		///							line into separate arguments.
		VectorFixtureTestCaseNames(
			const std::vector<CppUtils::CppSharedPtr<IFixutureTestCaseNames>>& fixtureInfos);


		/// @brief	Sets the vector state to the beginning 
		void Open();


		/// @brief	Extracts the test information from the TestFixtureinfoOjbect
		/// @param	fixtureName	Name of the fixture for the test case.
		///	@throw	Throws a scriptException on syntax failure.
		/// @return	The populated testInfoObject for the test.  If the object has no more
		///			lines the testInfoObject.isValid() will return false.
		TestInfoObject GetNextTest(CppUtils::Cpp_string& fixtureName);

	private:
		std::vector<CppUtils::CppSharedPtr<IFixutureTestCaseNames>>	m_infos;

		// TODO - determine why export of iterator failing
		CppUtils::Cpp_string::size_type m_fixtureIndex;
		CppUtils::Cpp_string::size_type	m_testCaseIndex;

	};

} // end namespace

TSTHARNESS_EXPORT template class TSTHARNESS_API 
	std::allocator<CppUtils::CppSharedPtr<CppTestHarness::VectorFixtureTestCaseNames>>;
TSTHARNESS_EXPORT template class TSTHARNESS_API 
	std::vector<CppUtils::CppSharedPtr<CppTestHarness::VectorFixtureTestCaseNames>>;

#endif
