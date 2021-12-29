#pragma once

namespace CppRTContainers {

	/// <summary>Maintain a circular buffer for fifo queue in real time systems/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class RTFifoQueue {
	public:

		/// <summary>Constructor that allocates memory once</summary>
		/// <param name="capacity">The max capacity of the queue</param>
		RTFifoQueue(int capacity){
			this->Init(capacity);
		}


		~RTFifoQueue() {
			delete this->ptr;
		}


		bool Push(T value) {
			if (this->count < this->capacity) {
				// Set the next out first time
				if (this->count == 0) {
					this->nextOut = 0;
				}
				this->count++;
				this->ptr[this->nextIn] = value;
				this->nextIn++;
				// Handle cirucular buffer roll over
				if (this->nextIn >= this->capacity) {
					// Capacity has already been determined
					this->nextIn = 0;
				}
				return true;
			}
			return false;
		}


		T Pop() {
			// You can only pop if you have one
			if (this->count > 0) {
				int i = this->nextOut;
				this->count--;
				if (this->count > 0) {
					// increment the next out
					this->nextOut++;
					// Handle wrap around
					if (this->nextOut >= this->capacity) {
						this->nextOut = 0;
					}
				}
				return this->ptr[i];
			}
			return 0;
		}


		void Clear() {
			this->nextIn = 0;
			this->nextOut = -1;
			this->count = 0;
		}


		bool IsEmpty() {
			return this->count > 0;
		}


		int Count() {
			return this->count;
		}

	private:
		RTFifoQueue() {
			this->Init(0);
		}

		void Init(int capacity) {
			this->capacity = capacity;
			this->ptr = new T[this->capacity];
			this->Clear();
		}

		T* ptr = 0;
		int capacity = -1;
		int nextIn = 0;
		int nextOut = 0;
		int count = 0;

	};

}

