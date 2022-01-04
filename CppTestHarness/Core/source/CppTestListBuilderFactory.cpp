///--------------------------------------------------------------------------------------
/// @file	MrTestListBuilderFactory.h
/// @brief	
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------

#include "CppTestListBuilderFactory.h"
#include "CppTestFileScriptReader.h"


#include "ICppTestScriptReader.h"
#include "CppTestCommandLineReader.h"
#include "CppTestVectorLineReader.h"
#include "CppTestVectorTestCaseNamesReader.h"
#include "CppTestListBuilder.h"
#include "ICppTestFixtureTestCaseNames.h"

using CppUtils::Cpp_string;
using CppUtils::Cpp_char;
using CppUtils::CppSharedPtr;


namespace CppTestHarness {

	std::vector<CppSharedPtr<ITestFixtureInfoObject> >
		ListBuilderFactory::FromFile(
			const Cpp_string& filename,
			Cpp_char nameDelimiter,
			Cpp_char argDelimiter) {

		FileScriptReader reader(filename, nameDelimiter, argDelimiter);
		reader.Open();
		return ListBuilder().Build(reader);
	}


	std::vector<CppSharedPtr<ITestFixtureInfoObject> >
		ListBuilderFactory::FromLine(const Cpp_string& line) {

		CommandLineReader reader(line);
		reader.Open();
		return ListBuilder().Build(reader);
	}


	std::vector<CppSharedPtr<ITestFixtureInfoObject> >
		ListBuilderFactory::FromLines(
			const std::vector<Cpp_string>& lines,
			Cpp_char nameDelimiter,
			Cpp_char argDelimiter) {

		VectorLineReader reader(lines, nameDelimiter, argDelimiter);
		reader.Open();
		return ListBuilder().Build(reader);
	}


	std::vector<CppSharedPtr<ITestFixtureInfoObject> >
		ListBuilderFactory::FromTestCaseNames(
			const std::vector<CppSharedPtr<IFixutureTestCaseNames> >& testCaseNames) {
		VectorFixtureTestCaseNames reader(testCaseNames);
		return ListBuilder().Build(reader);
	}

}

