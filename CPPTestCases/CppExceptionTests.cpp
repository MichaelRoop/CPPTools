#include "pch.h"
#include "CppUnitTest.h"
#include "../CPPVariousUtils/Cpp_exceptions.h"
using namespace CppUtils;


namespace CPPRTTestCases {


	TEST_CLASS(CppExceptionTests) {

		TEST_METHOD(T01_01_Scratch) {
			//Cpp_exception e(FL, _L_("My msg"));

			Cpp_exception e();

		}

	};


}
