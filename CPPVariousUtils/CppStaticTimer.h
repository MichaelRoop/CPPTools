#pragma once
///--------------------------------------------------------------------------------------
/// @file	mr_staticTimer.h
/// @brief	Defines a static timer to track milliseconds between calls.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppUtilsDefines.h"

namespace CppUtils {


	/// <summary>Tracks milliseconds expired between calls</summary>
	class CPPUTILS_API CppStaticTimer {
	public:

		/// @brief	Constructor.
		CppStaticTimer();


		/// @brief	Reset the millisecond count to start from now.
		void Start();


		/// @brief	Take and preserve the time slice since start was called.
		void Stop();


		/// @brief	Returns the time slice between start and stop.
		///
		/// @return The time in milliseconds between calls to start and stop.
		long long GetMsInterval() const;

	protected:

		long long m_secTime;	///< Seconds interval.
		long long m_msTime;		///< Millisecond portion of interval.

	};

}

