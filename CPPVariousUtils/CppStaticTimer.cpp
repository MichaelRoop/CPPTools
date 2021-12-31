#include "CppStaticTimer.h"
#include "Cpp_exceptions.h"
#include <sys/timeb.h>


namespace CppUtils {

	CppStaticTimer::CppStaticTimer() {
		this->m_secTime = 0;
		this->m_msTime = 0;
	}


	void CppStaticTimer::Start() {
		// WARNING:  This will wrap after Dec 2038.
		/// @todo	Determine a way around the wrapping.  This will happen in 2038 
		///			if the application is still compiled in 32 bits.
		timeb t;
		ftime(&t);
		this->m_secTime = t.time;
		this->m_msTime = t.millitm;
	}


	void CppStaticTimer::Stop() {
		timeb t;
		ftime(&t);

		long long newSec = t.time;
		long long newMSec = t.millitm;

		this->m_secTime = newSec - m_secTime;

		if (t.millitm < m_msTime) {
			Cpp_exception::assertCondition(
				this->m_secTime > 0, FL, L("logic error with time calculation"));
			--this->m_secTime;
			t.millitm += 1000;
		}
		this->m_msTime = t.millitm - this->m_msTime;
	}


	long long CppStaticTimer::GetMsInterval() const {
		return (this->m_secTime * 1000) + this->m_msTime;
	}

}
