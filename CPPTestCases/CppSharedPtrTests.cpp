
#include "CppUnitTest.h"
#include "../CPPVariousUtils/CppSharedPtr.h"
#include <iostream>
//#include "../CPPVariousUtils/Cpp_sstream.h"
using namespace CppUtils;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPPRTTestCases {

	TEST_CLASS(CppSharedPtrTests) {

		class TstClass {
		public:
			TstClass() {}
			TstClass(int val) { value = val; }
			int value = 1;
		};

//public:
		// also redirect of OS stream
		//https://stackoverflow.com/questions/51491235/c-visual-studio-how-to-output-to-test-output-window			
		std::streambuf* backup;
		std::stringstream ss;
		int x;

		// Only run once and can only do statics
		TEST_CLASS_INITIALIZE(ClassInitialize) {
			Logger::WriteMessage("-Fixture Setup");
		}

		TEST_CLASS_CLEANUP(ClassCleanup) {
			Logger::WriteMessage("-Fixture Teardown");
		}

		// A new class is created for each TEST_METHOD so this 
		// is where you initialise class instance variables
		TEST_METHOD_INITIALIZE(TestInit) {
			// REDIRECT STD STREAM
			backup = std::cout.rdbuf();
			std::cout.rdbuf(ss.rdbuf());
			x = 2;
			Logger::WriteMessage("--Test Setup");
		}

		TEST_METHOD_CLEANUP(TestCleanup) {
			Logger::WriteMessage("--Test Teardown");
			// ASSIGN COUT BACK TO STDOUT
			std::cout.rdbuf(backup);
		}


		TEST_METHOD(T01_01_DefaultConstructor) {
			Logger::WriteMessage("******* My message via logger *******");
			int i = 345110011;
			std::cout << "Blippy poo:" << i << std::endl;
			Logger::WriteMessage(ss.str().c_str());

			CppSharedPtr<TstClass> sp1;
			Assert::AreEqual((unsigned)0, sp1.Count(), L"sp1 count default constructor");
		}


		TEST_METHOD(T01_02_ConstructorWithPointer) {
			CppSharedPtr<TstClass> sp1(new TstClass());
			Assert::AreEqual((unsigned)1, sp1.Count(), L"sp1 count");
			CppSharedPtr<TstClass> sp2(sp1);
			Assert::AreEqual((unsigned)2, sp1.Count(), L"sp1 count");
			Assert::AreEqual((unsigned)2, sp2.Count(), L"sp2 count");
			CppSharedPtr<TstClass> sp3 = sp2;
			Assert::AreEqual((unsigned)3, sp1.Count(), L"sp1 count");
			Assert::AreEqual((unsigned)3, sp2.Count(), L"sp2 count");
			Assert::AreEqual((unsigned)3, sp3.Count(), L"sp3 count");
		}


		TEST_METHOD(T02_01_AssignWithPtr) {
			CppSharedPtr<TstClass> sp1;
			Assert::AreEqual((unsigned)0, sp1.Count(), L"sp1 count default constructor");
			sp1 = new TstClass();
			Assert::AreEqual((unsigned)1, sp1.Count(), L"sp1 count");
		}


		TEST_METHOD(T02_02_AssignWithCppSharedPtr) {
			CppSharedPtr<TstClass> sp1(new TstClass());
			Assert::AreEqual((unsigned)1, sp1.Count(), L"sp1 count initial");
			CppSharedPtr<TstClass> sp2 = sp1;
			Assert::AreEqual((unsigned)2, sp1.Count(), L"sp1 after used for init sp1");
			Assert::AreEqual((unsigned)2, sp2.Count(), L"sp2 after assignment");
		}


		TEST_METHOD(T03_01_PointerOperator) {
			CppSharedPtr<TstClass> sp1(new TstClass(333));
			Assert::AreEqual(333, sp1->value);
		}


		TEST_METHOD(T03_02_ReferenceOperator) {
			CppSharedPtr<TstClass> sp1(new TstClass(333));
			Assert::AreEqual(333, (*sp1).value);
		}


		TEST_METHOD(T08_01_DestructorDecrement) {

			CppSharedPtr<TstClass> sp1;
			Assert::AreEqual((unsigned)0, sp1.Count(), L"sp1 count default constructor");
			sp1 = new TstClass;
			Assert::AreEqual((unsigned)1, sp1.Count(), L"sp1 count pointer assigned");
			{
				{
					CppSharedPtr<TstClass> sp2(sp1);
					Assert::AreEqual((unsigned)2, sp1.Count(), L"sp1 count after second");
					Assert::AreEqual((unsigned)2, sp2.Count(), L"sp2 count after second");
				}
				Assert::AreEqual((unsigned)1, sp1.Count(), L"sp1 count after sp2 out of scope");
			}
		}


		TEST_METHOD(T08_02_DestructorDecrementWithPtrCheck) {
			TstClass* ptr = new TstClass();
			ptr->value = 2000;
			Assert::IsNotNull(ptr);

			// Need to keep pointer to object to access it after instance has
			// gone out of scope
			CppSharedPtr<TstClass>* sPtrPtr = NULL;
			{
				CppSharedPtr<TstClass> sp1(ptr);
				sPtrPtr = &sp1;
				Assert::AreEqual((unsigned)1, sp1.Count(), L"sp1 count after ptr assignment");
				Assert::AreEqual(2000, sp1->value, L"Value of contained pointer");
				// the shared ptr will go out of scope and pointer will be deleted

			}
			bool isThrown = false;
			try {
				Assert::IsNotNull(sPtrPtr, L"SO ptr pointer is null");
				Assert::AreEqual((unsigned)0, sPtrPtr->Count(), L"sp1 count after obj scope");
				Assert::IsNull(sPtrPtr->GetPtr(), L"Pointer in SO should be NULL");
				int i = ptr->value;
				isThrown = false;
			}
			catch(...) {
				isThrown = true;
			}
			Assert::IsFalse(isThrown, L"Should not have thrown");

		}

	};




}