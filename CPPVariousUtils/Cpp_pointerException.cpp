
///--------------------------------------------------------------------------------------
/// @file	mr_pointerException.cpp
/// @brief	Functionality to verify and throw exceptions on bad pointers.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------

#include "Cpp_pointerException.h"


namespace CppUtils {

	Cpp_pointerException::Cpp_pointerException(const char* file, int line)
		: Cpp_exception(file, line, Cpp_string(L("Invalid Pointer")))
	{
	}


	/// @brief	Destructor.
	Cpp_pointerException::~Cpp_pointerException() throw() {
	}


	void Cpp_pointerException::ptrAssert(const void* ptr, const char* file, int line) {
		/// @todo Verify the validity of pointer, not only NULL.
		if (ptr == NULL) {
			throw Cpp_pointerException(file, line);
		}
	}

}