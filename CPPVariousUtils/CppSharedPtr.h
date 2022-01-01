#pragma once


namespace CppUtils {

	/// <summary>Reference counted pointer holder</summary>
	/// <typeparam name="T">The type of pointer to hold</typeparam>
	template<class T> class CppSharedPtr {
	public:

		CppSharedPtr() : m_ptr(NULL), m_count(NULL) {
		}


		CppSharedPtr(T* ptr) : m_ptr(NULL), m_count(NULL) {
			this->InitFromPointer(ptr);
		}


		CppSharedPtr(const CppSharedPtr& sp) : m_ptr(NULL), m_count(NULL) {
			this->InitFromSharedPtrObject(sp);
		}


		~CppSharedPtr() {
			this->Decrement();
		}


		CppSharedPtr& operator = (const CppSharedPtr& sp) {
			if (&sp != this) {
				this->InitFromSharedPtrObject(sp);
			}
			return *this;
		}


		CppSharedPtr& operator = (T* ptr) {
			this->InitFromPointer(ptr);
			return *this;
		}


		T* operator -> () {
			return this->GetPtr();
		}


		T& operator *() {
			return this->GetRef();
		}


		T* GetPtr() {
			//assert(m_ptr);
			return m_ptr;
		}


		T& GetRef() {
			return *(this->GetPtr());
		}


		unsigned Count() const {
			if (m_count != NULL) {
				return *m_count;
			}
			return 0;
		}


		bool IsValid() const {
			return m_ptr != NULL;
		}


		void Reset() {
			this->InitFromPointer(NULL);
		}


	private:
		T* m_ptr;
		unsigned* m_count;


		void InitFromPointer(T* ptr) {
			this->Decrement();
			if (ptr != NULL) {
				m_count = new unsigned();
				*m_count = 1;
			}
			m_ptr = ptr;
		}


		/// <summary>
		/// Used when SharedPtr constructed with copy constructor or
		/// assignment operator from another CppSharedPtr. TAKES OVER THE ONE PASSED IN
		/// </summary>
		/// <param name="sp"></param>
		void InitFromSharedPtrObject(const CppSharedPtr& sp) {
			// TODO - look at this. Supposed to decrement the one passed in and increment our count?
			// Why are we decrementing our count first?
			this->Decrement();
			// Increment the counter of the sending so it does not delete early?
			if (sp.m_count != NULL) {
				++(*sp.m_count);
			}
			m_count = sp.m_count;
			m_ptr = sp.m_ptr;
		}


		/// <summary>
		/// Decrement SharedPtr count sharing pointer. Delete pointer if last
		/// /// </summary>
		void Decrement() {
			if (m_count != NULL) {
				--(*m_count);
				if (*m_count == 0) {
					delete m_ptr;
					m_ptr = NULL;
					delete m_count;
					m_count = NULL;
				}
			}
		}


	};



}

