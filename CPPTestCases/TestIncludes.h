#pragma once

#include "CppUnitTest.h"
#include "../CPPVariousUtils/Cpp_exceptions.h"
#include "../CppStateMachine/CppState.h"
#include "../CPPContainers/RTFifoQueue.h"
#include "../CPPVariousUtils/Cpp_string.h"
#include "../CPPVariousUtils/CppSharedPtr.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define LOG_MACROS
#if defined (LOG_MACROS)
#include <iostream>

#define LOGMSG(x) { std::stringstream _ss_; _ss_ << x << std::endl; Logger::WriteMessage(_ss_.str().c_str()); }


#else
#define LOGMSG(x)
#endif
