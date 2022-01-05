#include "Cpp_string.h"
#include "CppUtilsDefines.h"
#include "Cpp_exceptions.h"
#include "Cpp_sstream.h"
#include "Cpp_toStream.h"
#include "Cpp_functors.h"

#include <algorithm>

///--------------------------------------------------------------------------------------
/// @file	Cpp_string.cpp
/// @brief	Cross char witdh defines for string class.
///
/// @author		Michael Roop
/// @date		2021
/// @version	1.0
///
/// Copyright 2021 Michael Roop
///--------------------------------------------------------------------------------------


namespace CppUtils {

	Cpp_string TrimRight(const Cpp_string& str) {
		if (str.empty()) {
			return str;
		}

		Cpp_string::size_type end = str.find_last_not_of(L(" \n\t\r"));

		// TODO - follow up. Seems we can use the npos within the DLL
		//if (end == CppUtils::StrNPos()) {
		if (end == CppUtils::Cpp_string::npos) {
			// only blanks in string.
			return str;
		}
		return str.substr(0, end + 1);
	}


	Cpp_string TrimLeft(const Cpp_string& str) {
		if (str.empty()) {
			return str;
		}

		Cpp_string::size_type start = str.find_first_not_of(L(" \n\t\r"));
		if (start == CppUtils::StrNPos()) {
			// only blanks in string.
			return str;
		}
		return str.substr(start);
	}



	Cpp_string Trim(const Cpp_string& str) {
		return TrimLeft(TrimRight(str));
	}


	std::string ExtractFileName(const std::string& pathAndFile) {
		if (pathAndFile.empty()) {
			return pathAndFile;
		}

		std::string::size_type pos = pathAndFile.find_last_of("\\/");
		if (pos == CppUtils::StrNPos()) {
			return pathAndFile;
		}

		// If found, check that it is not the only character.
		Cpp_exception::assertCondition(pathAndFile.length() > 1, FL, L("Path and file only contains slashes"));
		return pathAndFile.substr(pos + 1);
	}


	std::wstring ExtractFileName(const std::wstring& pathAndFile) {
		if (pathAndFile.empty()) {
			return pathAndFile;
		}

		std::string::size_type pos = pathAndFile.find_last_of(L"\\/");
		if (pos == CppUtils::StrNPos()) {
			return pathAndFile;
		}

		// If found, check that it is not the only character.
		Cpp_exception::assertCondition(pathAndFile.length() > 1, FL, L("Path and file only contains slashes"));
		return pathAndFile.substr(pos + 1);
	}




	// But simple wide to narrow conversion.  No Unicode considered.  Will only 
	// work with normal range of ANSII characters in wide format.
	std::string WideToNarrowString(const std::wstring& str) {
		// Create matching buffers and add null terminator char to end.
		std::vector<wchar_t> wideChars(str.length() + 1, L'\0');
		std::vector<char> narrowChars(str.length() + 1, '\0');
		memcpy(&wideChars[0], str.c_str(), str.length() * sizeof(wchar_t));

		std::for_each(wideChars.begin(), wideChars.end(), AnsiiWideCharToNarrow(narrowChars));
		return std::string(&narrowChars[0]);
	}


	std::string WideToNarrowString(const std::string& str) {
		return str;
	}


	// But simple narrow to wide conversion.  No Unicode considered.  Will only 
	// work with normal range of ANSII characters in wide format.
	std::wstring NarrowToWideString(const std::string& str) {
		// Create matching buffers and add null terminator char to end.
		std::vector<wchar_t> wideChars(str.length() + 1, L'\0');
		std::vector<char>	 narrowChars(str.length() + 1, '\0');
		memcpy(&narrowChars[0], str.c_str(), str.length());

		std::for_each(narrowChars.begin(), narrowChars.end(), NarrowCharToWide(wideChars));
		return std::wstring(&wideChars[0]);
	}


	std::wstring NarrowToWideString(const std::wstring& str) {
		return str;
	}


	bool StrTokenize(Cpp_string::size_type& currentPos, const Cpp_string& str, Cpp_string& token, Cpp_char delimiter) {
		if (currentPos == CppUtils::StrNPos() || currentPos > str.length() - 1) {
			return false;
		}

		// End case Skip leading delimiters
		Cpp_exception::assertCondition(currentPos < str.length(), FL, L("Exceeded receptor limits"));

		if (str[currentPos] == delimiter) {
			currentPos = str.find_first_not_of(delimiter, currentPos);
			if (currentPos == CppUtils::StrNPos()) {
				// End case - string only has delimiters.
				return false;
			}
		}

		token.clear();

		Cpp_string::size_type delimiterPos = str.find_first_of(&delimiter, currentPos);
		if (delimiterPos == CppUtils::StrNPos()) {
			// If the delimiter is not found then the entire remaining string is the token.
			Cpp_string::size_type tmp = currentPos;

			// Move current position passed length of string to fail on next iteration
			currentPos = str.length();
			token = str.substr(tmp);
		}
		else {
			// Get token and skip to next non delimiter position.
			token = str.substr(currentPos, delimiterPos - currentPos);
			currentPos = str.find_first_not_of(delimiter, delimiterPos);
		}
		return true;
	}


	Cpp_string SubString(
		const Cpp_string& s,
		Cpp_string::size_type pos,
		Cpp_string::size_type length) {

		return s.substr(pos, length); // Now it is working. Go figure

		//if(pos >= s.length()) {
		//	throw CppUtils::Cpp_exception(_FL_, _L_("The position is passed the end of line"));
		//}

		//if (length == CppUtils::StrNPos()) {
		//	length = s.length() - pos;
		//}

		//if((pos + length) > s.length()) {
		//	throw CppUtils::Cpp_exception(_FL_, _L_("The start position plus length requested is passed the end of line"));
		//}

		//// bit of pointer arithmetic since we cannot use the substring
		//CppUtils::Cpp_string copy;
		//copy.append((s.c_str() + pos), length);
		//return copy;
	}


	Cpp_string SubString(const CppUtils::Cpp_string& s, CppUtils::Cpp_string::size_type pos) {
		//return CppUtils::SubString(s, pos, CppUtils::StrNPos());
		return s.substr(pos);
	}


	// TODO - validate this.  Seems to be enough to access the npos within the DLL and send back the value 
	// via an exported function
	Cpp_string::size_type StrNPos() {
		return CppUtils::Cpp_string::npos;
	}


	std::string::size_type Find(const std::string& s, const std::string pattern, std::string::size_type pos) {
		return s.find(pattern, pos);
	}


	bool Contains(const std::string& s, const std::string pattern) {
		return s.find(pattern) != std::string::npos;
	}


	bool Contains(const std::wstring& s, const std::wstring pattern) {
		return s.find(pattern) != std::wstring::npos;
	}


	Cpp_string ToMrString(const char* value) {
		// Convert to wide or narrow Cpp_string
		Cpp_stringstream ss;
		ToStream(ss, (value == 0 ? "" : value));
		return ss.str().c_str();
	}


	Cpp_string ToMrString(const wchar_t* value) {
		// Convert to wide or narrow Cpp_string
		Cpp_stringstream ss;
		ToStream(ss, (value == 0 ? L"" : value));
		return ss.str().c_str();
	}


	Cpp_string ToMrString(const std::string& value) {
		return CppUtils::ToMrString(value.c_str());
	}


	Cpp_string ToMrString(const std::wstring& value) {
		return CppUtils::ToMrString(value.c_str());
	}


	std::string ToCharPtr(const std::string& value) {
		return value;
	}


	std::string ToCharPtr(const std::wstring value) {
		return CppUtils::WideToNarrowString(value);
	}


}