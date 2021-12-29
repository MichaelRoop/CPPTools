#include "pch.h"
#include "CppUnitTest.h"
#include "../CPPContainers/RTFifoQueue.h"
using namespace CppRTContainers;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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





	};

}