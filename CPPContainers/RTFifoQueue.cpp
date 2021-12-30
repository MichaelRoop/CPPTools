#include "RTFifoQueue.h"

namespace CppRTContainers {


	//template <class T>
	//RTFifoQueue<T>::RTFifoQueue() {
	//	this->Init(0);
	//}

	//template <class T>
	//RTFifoQueue<T>::RTFifoQueue(int capacity) {
	//	this->Init(capacity);
	//}

	//template <class T>
	//void RTFifoQueue<T>::Init(int capacity) {
	//	this->capacity = capacity;
	//	this->ptr = new T[this->capacity];
	//	this->clear();
	//}

	//template <class T>
	//RTFifoQueue<T>::~RTFifoQueue() {
	//	delete this->ptr;
	//}



	//template <class T>
	//bool RTFifoQueue<T>::Push(T value) {
	//	if (this->count < this->capacity) {
	//		// Set the next out first time
	//		if (this->count == 0) {
	//			this->nextOut == 0;
	//		}
	//		this->count++;
	//		this->ptr[this->nextIn] = value;
	//		this->nextIn++;
	//		// Handle cirucular buffer roll over
	//		if (this->nextIn >= this->capacity) {
	//			// Capacity has already been determined
	//			this->nextIn = 0;
	//		}
	//		return true;
	//	}
	//	return false;
	//}


	//template <class T>
	//T RTFifoQueue<T>::Pop() {
	//	// You can only pop if you have one
	//	if (this->count > 0) {
	//		int i = this->nextOut;
	//		this->count--;
	//		if (this->count > 0) {
	//			// increment the next out
	//			this->nextOut++;
	//			// Handle wrap around
	//			if (this->nextOut >= this->capacity) {
	//				this->nextOut = 0;
	//			}
	//		}
	//		return this->ptr[i];
	//	}
	//	return 0;

	//	//return NULL;

	//	// Might need to have ** in param and return bool

	//}


	//template<class T>
	//void RTFifoQueue<T>::Clear() {
	//	this->nextIn = 0;
	//	this->nextOut = -1;
	//	this->count = 0;
	//}


	//template<class T>
	//bool RTFifoQueue<T>::IsEmpty() {
	//	return this->count > 0;
	//}


	//template<class T>
	//int RTFifoQueue<T>::Count() {
	//	return 0;
	//}


}