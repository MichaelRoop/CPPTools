#include "pch.h"
#include "CppUnitTest.h"
#include "../CPPContainers/RTFifoQueue.h"
using namespace CppRTContainers;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


class TstClass {
public:
	int A = 0;
	TstClass() {}
	TstClass(int a) {
		this->A = a;
	}
};

class TstClass2 {
public:
	TstClass2() {}
	TstClass2(int value) {
		this->a = value;
	}
	TstClass2(const TstClass2& obj) {
		this->a = obj.a;
	}
	int GetA() { return this->a; }
private:
	int a = 0;

};



namespace CPPRTTestCases {

	TEST_CLASS(RTFifoQueueTestCases) {
public:

	TEST_METHOD(T01_01_Push) {
		RTFifoQueue<int> q(5);
		Assert::IsTrue(q.Push(1));
		Assert::IsTrue(q.Push(2));
		Assert::IsTrue(q.Push(3));
		Assert::IsTrue(q.Push(4));
		Assert::IsTrue(q.Push(5));
		Assert::IsFalse(q.Push(6));
		Assert::AreEqual(5, q.Count());
	}


	TEST_METHOD(T02_01_Pop) {
		RTFifoQueue<int> q(5);
		for (int i = 1; i < 6; i++) {
			q.Push(i);
		}
		Assert::AreEqual(5, q.Count());

		int val = q.Pop();
		Assert::AreEqual(1, val);
		val = q.Pop();
		Assert::AreEqual(2, val);
		val = q.Pop();
		Assert::AreEqual(3, val);
		val = q.Pop();
		Assert::AreEqual(4, val);
		val = q.Pop();
		Assert::AreEqual(5, val);
		Assert::AreEqual(0, q.Count());

		val = q.Pop();
		Assert::AreEqual(0, val);
	}


	TEST_METHOD(T02_02_PopPushPop) {
		RTFifoQueue<int> q(5);
		for (int i = 1; i < 6; i++) {
			q.Push(i);
		}
		Assert::AreEqual(5, q.Count());

		// Remove 1,2
		int val = q.Pop();
		val = q.Pop();

		// Push 2 more
		q.Push(3222);
		q.Push(1010);

		val = q.Pop();
		Assert::AreEqual(3, val);
		val = q.Pop();
		Assert::AreEqual(4, val);
		val = q.Pop();
		Assert::AreEqual(5, val);
		Assert::AreEqual(2, q.Count());

		// Pop the ones pushed after pops
		val = q.Pop();
		Assert::AreEqual(3222, val);
		val = q.Pop();
		Assert::AreEqual(1010, val);

		Assert::AreEqual(0, q.Count());
	}


	TEST_METHOD(T03_01_PushPopClassPtr) {
		RTFifoQueue<TstClass*> q(3);
		for (int i = 1; i < 4; i++) {
			q.Push(new TstClass(i));
		}
		Assert::AreEqual(3, q.Count());

		TstClass* ptr = q.Pop();
		Assert::IsNotNull(ptr);
		Assert::AreEqual(1, ptr->A);
		Assert::AreEqual(2, q.Count());
		delete ptr;

		ptr = q.Pop();
		Assert::IsNotNull(ptr);
		Assert::AreEqual(2, ptr->A);
		Assert::AreEqual(1, q.Count());
		delete ptr;

		ptr = q.Pop();
		Assert::IsNotNull(ptr);
		Assert::AreEqual(3, ptr->A);
		Assert::AreEqual(0, q.Count());
		delete ptr;

		ptr = q.Pop();
		Assert::IsNull(ptr);
	}


	TEST_METHOD(T04_01_PushPopClassInstance) {
		RTFifoQueue<TstClass2> q(3);
		for (int i = 1; i < 4; i++) {
			q.Push(TstClass2(i));
		}
		Assert::AreEqual(3, q.Count());

		Assert::IsFalse(q.IsEmpty(), L"Should not indicate empty");
		TstClass2 inst = q.Pop();
		Assert::AreEqual(1, inst.GetA());
		Assert::AreEqual(2, q.Count());

		Assert::IsFalse(q.IsEmpty());
		inst = q.Pop();
		Assert::AreEqual(2, inst.GetA());
		Assert::AreEqual(1, q.Count());

		Assert::IsFalse(q.IsEmpty());
		inst = q.Pop();
		Assert::AreEqual(3, inst.GetA());
		Assert::AreEqual(0, q.Count());

		// The returning instance on empty is 0 (null)
		// which default constructs an object
		Assert::IsTrue(q.IsEmpty());
		inst = q.Pop();
		Assert::AreEqual(0, q.Count());

		//Assert::IsNull(inst);
	}




	TEST_METHOD(T05_01_PopIfPresentInstance) {
		RTFifoQueue<TstClass2> q(3);
		for (int i = 1; i < 4; i++) {
			q.Push(TstClass2(i));
		}
		Assert::AreEqual(3, q.Count());

		TstClass2 cpy;
		Assert::IsTrue(q.PopIfPresent(cpy), L"Should be present");
		Assert::AreEqual(1, cpy.GetA());
		Assert::AreEqual(2, q.Count());

		Assert::IsTrue(q.PopIfPresent(cpy), L"Should be present");
		Assert::AreEqual(2, cpy.GetA());
		Assert::AreEqual(1, q.Count());

		Assert::IsTrue(q.PopIfPresent(cpy), L"Should be present");
		Assert::AreEqual(3, cpy.GetA());
		Assert::AreEqual(0, q.Count());

		Assert::IsFalse(q.PopIfPresent(cpy), L"Should NOT be present");
	}


	TEST_METHOD(T05_02_PopIfPresentPtr) {
		RTFifoQueue<TstClass2*> q(3);
		for (int i = 1; i < 4; i++) {
			q.Push(new TstClass2(i));
		}
		Assert::AreEqual(3, q.Count());

		TstClass2* ptr;
		Assert::IsTrue(q.PopIfPresent(ptr), L"Should be present");
		Assert::IsNotNull(ptr);
		Assert::AreEqual(1, ptr->GetA());
		Assert::AreEqual(2, q.Count());
		delete ptr;
		ptr = 0;

		Assert::IsTrue(q.PopIfPresent(ptr), L"Should be present");
		Assert::IsNotNull(ptr);
		Assert::AreEqual(2, ptr->GetA());
		Assert::AreEqual(1, q.Count());
		delete ptr;
		ptr = 0;

		Assert::IsTrue(q.PopIfPresent(ptr), L"Should be present");
		Assert::IsNotNull(ptr);
		Assert::AreEqual(3, ptr->GetA());
		Assert::AreEqual(0, q.Count());
		delete ptr;
		ptr = 0;

		Assert::IsFalse(q.PopIfPresent(ptr), L"Should NOT be present");
	}


	TEST_METHOD(T06_01_PeekInstance) {
		RTFifoQueue<TstClass2> q(2);
		for (int i = 1; i < 3; i++) {
			q.Push(TstClass2(i));
		}
		Assert::AreEqual(2, q.Count());

		TstClass2 cpy = q.Peek();
		Assert::AreEqual(1, cpy.GetA());
		Assert::AreEqual(2, q.Count());
		cpy = q.Pop();
		Assert::AreEqual(1, cpy.GetA());
		Assert::AreEqual(1, q.Count());

		cpy = q.Peek();
		Assert::AreEqual(2, cpy.GetA());
		Assert::AreEqual(1, q.Count());
		cpy = q.Pop();
		Assert::AreEqual(2, cpy.GetA());
		Assert::AreEqual(0, q.Count());

		// empty one should return default constructed object
		cpy = q.Peek();
		Assert::AreEqual(0, cpy.GetA());
	}


	TEST_METHOD(T07_01_PeekIfPresentInstance) {
		RTFifoQueue<TstClass2> q(2);
		for (int i = 1; i < 3; i++) {
			q.Push(TstClass2(i));
		}
		Assert::AreEqual(2, q.Count());

		TstClass2 cpy;
		Assert::IsTrue(q.PeekIfPresent(cpy), L"Should be present");
		Assert::AreEqual(1, cpy.GetA());
		Assert::AreEqual(2, q.Count());
		Assert::IsTrue(q.PopIfPresent(cpy), L"Should be present");
		Assert::AreEqual(1, cpy.GetA());
		Assert::AreEqual(1, q.Count());

		Assert::IsTrue(q.PeekIfPresent(cpy), L"Should be present");
		Assert::AreEqual(2, cpy.GetA());
		Assert::AreEqual(1, q.Count());
		Assert::IsTrue(q.PopIfPresent(cpy), L"Should be present");
		Assert::AreEqual(2, cpy.GetA());
		Assert::AreEqual(0, q.Count());

		Assert::IsFalse(q.PeekIfPresent(cpy), L"Should NOT be present");

	}



	};

}