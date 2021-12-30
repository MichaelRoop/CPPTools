#include "TestIncludes.h"

using namespace CppStateMachine;

namespace CPPRTTestCases {

	class TickObj {
	public:
		int m_id;
		TickObj() {
			this->m_id = 0;
		}
	};


	TEST_CLASS(CppStateTests) {

		TEST_METHOD(T01_01_Scratch) {

			CppState<TickObj> s(1);


		}



	};


}