#pragma once

#if defined (_WIN32) || defined (_WIN64)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>

	#if defined(CPPLOGGER_EXPORTS)
		#pragma message("Exporting CppLogger DLL Classes")
		#define CPPLOG_API __declspec(dllexport)
	#else
		#pragma message("Exporting CppLogger DLL Classes")
		#define CPPLOG_API __declspec(dllimport)
	#endif
#elif defined(__linux) || defined(_linux_)
	#if defined(CPPLOGGER_EXPORTS)
		#pragma message("Exporting CppLogger DLL Classes")
		#define CPPLOG_API
	#else
		#pragma message("Exporting CppLogger DLL Classes")
		#define CPPLOG_API
	#endif
#else
	#pragma message("*** Neither WIN or Linux defined ***")
#endif

//#define LOG_TESTS
#define LOG_MSGS

#if defined (LOG_TESTS)
	#if defined (_WIN32) || defined(_WIN64)
		#include "CppUnitTestCommon.h"
		#include "CppUnitTestAssert.h"
		#include "CppUnitTestLogger.h"
		using namespace Microsoft::VisualStudio::CppUnitTestFramework;
		#include <iostream>
		#define LOGMSG(x) { std::stringstream _ss_; _ss_ << x << std::endl; Logger::WriteMessage(_ss_.str().c_str()); }
	#else
		#include <iostream>
		// Just log to console if not windows
		#define LOGMSG(x) { std::cout << x << std::endl; }
	#endif

#elif defined (LOG_MSGS)
	#include <iostream>
	#define LOGMSG(x) { std::cout << x << std::endl; }
#else
	#define LOG_MSG()
#endif



//#define LOG_LEVEL_INFO
//#define LOG_LEVEL_DBG
//#define LOG_LEVEL_WARN
//#define LOG_LEVEL_ERR

#if defined (LOG_LEVEL_INFO)
	#define LOG_INFO(x) LOGMSG(x)
	#define LOG_DBG(x) LOGMSG(x)
	#define LOG_WARN(x) LOGMSG(x)
	#define LOG_ERR(x) LOGMSG(x)
#elif defined (LOG_LEVEL_DBG)
	#define LOG_INFO(x)
	#define LOG_DBG(x) LOGMSG(x)
	#define LOG_WARN(x) LOGMSG(x)
	#define LOG_ERR(x) LOGMSG(x)
#elif defined (LOG_LEVEL_WARN)
	#define LOG_INFO(x)
	#define LOG_DBG(x)
	#define LOG_WARN(x) LOGMSG(x)
	#define LOG_ERR(x) LOGMSG(x)
#elif defined (LOG_LEVEL_ERR)
	#define LOG_INFO(x)
	#define LOG_DBG(x)
	#define LOG_WARN(x)
	#define LOG_ERR(x) LOGMSG(x)
#else
	#define LOG_INFO(x)
	#define LOG_DBG(x)
	#define LOG_WARN(x)
	#define LOG_ERR(x)
#endif

