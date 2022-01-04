///--------------------------------------------------------------------------------------
/// @file	MrTestAssertException.h
/// @brief	Exception exclusively for use in test assert methods
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_ASSERT_EXCEPTION_H)
#define CPP_TEST_ASSERT_EXCEPTION_H

#include "include/CppTestHarnessDefines.h"
#include "../CPPVariousUtils/Cpp_exceptions.h"

namespace CppTestHarness {

	///--------------------------------------------------------------------------------------
	///
	///	@brief	Class to throw exceptions on test assert failures
	///
	/// Use the FL macro to insert the file name and line from the system.
	/// Use the L() macro to provide cross char width portability.
	/// Use the cross char width streaming so that the message can be displayed on both
	/// both narrow and wide char compilation mode.
	///
	///--------------------------------------------------------------------------------------
	class TSTHARNESS_API AssertException : public CppUtils::Cpp_exception {
	public:

		/// @brief	Constructor.
		///
		/// @param	file			The source code file where problem originates.
		/// @param	line			The source code line where problem originates.
		/// @param	msg				The message explaining the exception.
		AssertException(const char* file, int line, const Cpp_string& msg);


		/// @brief	Copy Constructor.
		///
		/// @param	msg				The message explaining the exception.
		AssertException(const AssertException& obj);


		/// @brief	Destructor.
		virtual ~AssertException() throw();


	};

} // end of namespace

#endif
