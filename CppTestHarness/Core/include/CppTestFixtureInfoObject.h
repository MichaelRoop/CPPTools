#if !defined(CPP_TEST_FIXTURE_INFO_OBJECT_H)
#define CPP_TEST_FIXTURE_INFO_OBJECT_H

#include "ICppTestFixtureInfoObject.h"

namespace CppTestHarness {

	/// <summary>
	/// Class to abstract information necessary to retrieve a Fixture of test cases
	/// </summary>
	class TSTHARNESS_API TestFixtureInfoObject : public ITestFixtureInfoObject {

	public:

		/// @brief Constructor
		TestFixtureInfoObject(const CppUtils::Cpp_string& name);


		/// @brief Destructor
		virtual ~TestFixtureInfoObject();


		/// @brief Retrieve Test fixture name
		virtual const CppUtils::Cpp_string& GetName() const;


		/// @brief Set the Test fixture name
		/// @brief	name	The test fixture name
		virtual const void SetName(CppUtils::Cpp_string& name);


		/// @brief	Retrieve the argument set.
		///
		/// @return	The argument set.
		virtual const std::vector<TestInfoObject>& GetTestInfoVector();


		/// @brief	Add an argument to the argument set.
		///
		/// @param	name	The name of the argument.
		/// @param	value	The value of the argument.
		virtual void AddTestInfo(const TestInfoObject& info);

	private:
		CppUtils::Cpp_string		m_name;		///< Fixture name
		std::vector<TestInfoObject>	m_tests;	///< Info objects for tests 	


		/// @brief Default constructor
		TestFixtureInfoObject() {
		}


		/// @brief Copy constructor
		TestFixtureInfoObject(const TestFixtureInfoObject&) {
		}

	};

} // end namespace

// Force export of class with std objects
TSTHARNESS_EXPORT template class TSTHARNESS_API std::allocator<CppTestHarness::TestFixtureInfoObject*>;
TSTHARNESS_EXPORT template class TSTHARNESS_API std::vector<CppTestHarness::TestFixtureInfoObject*>;

#endif
